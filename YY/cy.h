
//取账号
bool getZhangHao(int num,CString &name,CString &pass){
	
	vector<string> array;
	split(getini("1", to_string(num), textLS + "base.ini", ""), "----", array);
	if (array.size() > 1){
		name = array[0].c_str();
		pass = array[1].c_str();
		return true;
	}
	return false;
}
bool getZhangHao(int num, string &name, string &pass){

	vector<string> array;
	split(getini("1", to_string(num), textLS + "base.ini", ""), "----", array);
	xtrace("%d\n", array.size());
	if (array.size() > 1){
		name = array[0];
		pass = array[1];
		return true;
	}
	return false;
}

//取换号序号
int getHuanHaoNum(int num){
	int xh = _ttoi(getlisttext(num, lbk.rootnum));

	if (xh > 0){
		xh = xh + getEditInt(m_KckEdit);
		int max = getEditInt(m_EditZDHH);
		if (getini("1", to_string(xh), textLS + "base.ini", "") != "" && (max == 0 || max >= xh)){
			return xh;
		}
	}
	return 0;
}
//取角色名
string getNameSJ(){
	vector<string> array, array1, array2;
	split(SJ_NAME_Q, ",", array);
	split(SJ_NAME_H, ",", array1);
	split(SJ_NAME_Z, ",", array2);
	LARGE_INTEGER t1;
	QueryPerformanceCounter(&t1);

	srand((int)t1.QuadPart);
	string a = array[rand() % (array.size() + 1)] + array1[rand() % (array1.size() + 1)];
	string b = array2[rand() % (array2.size() + 1)];
	if (a.length() > 12){
		a.substr(0, 12);
	}
	
	int zj = (rand() % ((int)floor(a.length() / 2) - 1) + 1) * 2;

	//Output("%s   %s   %d\n", a.c_str(), b.c_str(), zj);
	a = a.substr(0, zj) + b + a.substr(zj, a.length() - zj);
	return a;
}

//等待队友中
void waitteamFun(){
	int numall = 0;
	for (int j = 0; j < XMgs; j+=5){
		int shm5 = 0;
		int num = 0;
		for (int i = 0; i < 5; i++){
			if (j + i>=XMgs){
				shm5 = XMgs % 5;
				break;
			}
			CString text = getlisttext(j + i, lbk.text);
			if (text == "" || text == "1" || text.Find(L"等待队友") >= 0 || text.Find(L"死亡") >= 0){
				num++;
			}
		}
		if ((num >= 5 || shm5 > 0) && num >= shm5){
			for (int i = 0; i < 5; i++){
				if (j + i>=XMgs)break;
				CString text = getlisttext(j + i, lbk.text);
				if (text == "等待队友" || text == "等待队友,2"){
					PostMessageA(winls[j + i].h, 52228, 8, 2);
				}
			}
			num = 0;
		}
		numall += num;
	}
	if (numall == 0)waitteam = 0;

}

//检测交易号标志
void tastBuyFun(){
	int num = atoi(getini("msger", "buyer", PeiZhiText, "0").c_str());
	if (num == 0)buying = 0;
	else if (getlisttext(num, lbk.text).Find(L"上交") < 0 || !getlistbool(num, lbk.run)){
		buying = 0;
		setini((string)"msger", "buyer", PeiZhiText, "0");
	}

}
//等待全部队友
void waitteamAllFun(){
	int numall = 0;
	for (int j = 0; j < XMgs; j += 5){
		int shm5 = 0;
		int num = 0;
		int runnum = 0;
		for (int i = 0; i < 5; i++){
			if (j + i>=XMgs){
				shm5 = XMgs % 5;
				break;
			}
			CString text = getlisttext(j + i, lbk.text);
			xtrace("%d  %d\n", j, i);
			if (text == "等待队友,1"){
				if (runnum == 0){
					runnum = _ttoi(getlisttext(j + i, lbk.runnum));
				}
				else if (runnum != _ttoi(getlisttext(j + i, lbk.runnum))){
					JingBaoYin = 3;
					setlisttext(j+i, lbk.xjs, "★", true);
					break;
				}
				num++;
			}
			else if (text == "1"){
				num++;
			}
		}
		if ((num >= 5 || shm5 > 0) && num >= shm5){
			for (int i = 0; i < 5; i++){
				if (j + i>=XMgs){
					break;
				}
				PostMessageA(winls[j + i].h, 52228, 8, 2);
				if (getlisttext(j+i, lbk.xjs) == "★")setlisttext(j+i , lbk.xjs, "0", true);
			}
			num = 0;
		}
		numall += num;
	}
	if (numall == 0)waitteamall = 0;
}

//组队线程
DWORD WINAPI toTeamThread(LPVOID lpParam){
	int i = XList_GetSelectItem(m_hList);
	HWND h = winls[i].h;
	KeyPress(h, 115, 500);
	LiftClock(h, 245, 138, 500);
	for (int j = 1; j < 5; j++){
		if (XMgs>i){
			CString name = getlisttext(i + j, lbk.name);
			xtrace("%d   %d\n", i, j);
			if (name != "未登录"&&name != ""){
				LiftClock(h, 237, 441, 500);
				toWindowsText(h, (string)CW2A(name));
				LiftClock(h, 337, 358, 500);
			}
		}
	}
	LiftClock(h, 215, 138, 500);
	KeyPress(h, 27, 1500);
	for (int j = 1; j < 5; j++){
		if (i + j<=XMgs  &&winls[i + j].h>0){
			PostMessageA(winls[i + j].h, 52228, 8, 3);
			Sleep(200);
		}
	}

	return 0;
}


void setReg(string n){

	LPCTSTR data_Set = _T("SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Run");
	HKEY hKey;
	REGSAM flag = KEY_WOW64_64KEY;
	DWORD dwDisposition = REG_OPENED_EXISTING_KEY;
	LONG lRet = RegOpenKeyEx(HKEY_LOCAL_MACHINE, data_Set, 0, KEY_ALL_ACCESS | flag, &hKey);

	if (ERROR_SUCCESS == lRet)

	{

		// 使用hKey来操作data_Set这个KEY里面的值。
		//string n = textLS + "演义.exe";
		//TCHAR *pchrName = (TCHAR*)n.c_str();

		char pchrName[] = "D:\\YY\\YY.exe";
		xtrace("3333   %s   %d\n", pchrName, strlen((char*)pchrName));
		if (ERROR_SUCCESS != ::RegSetValueEx(hKey, TEXT("我的启动项"), NULL, REG_MULTI_SZ, (LPBYTE)pchrName, strlen(pchrName)*sizeof(char)+1))

		{
			::RegCloseKey(hKey);
			xtrace("11111");
			return;



		}
		::RegCloseKey(hKey);
	}
	xtrace("2222  %d   %d   %d\n", GetLastError(), lRet, ERROR_SUCCESS);
}