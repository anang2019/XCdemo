#include "stdafx.h"
#include <fstream>
#include "base.h"
#include "YY.h"
#include "RegDM.h"
#include "Common.h"

#include "time.h"

#include "dmexport.h"  //打码插件头文件

#include <algorithm>

#include<cmath>
#pragma comment(lib,"dc.lib")
#include "tab3.h"

#include "cy.h"

using   namespace   std;
bool oldCJed = false;

WNDPROC OldProc;


Dm::Idmsoft *dm = GetDmbject();


//检测慢窗口
void TestSwin(){
	for (int j = 1; j <= XMgs; j += 5){
		int min = 5000;
		int max = 200;
		int minhs = 0;
		int maxhs=0;
		int ls[5] = { 0 };
		for (int i = 0; i < 5; i++){
			if (j + i>XMgs) break;
			ls[i] = _ttoi(getlisttext(j + i, lbk.runnum));
			if (getlisttext(j + i, lbk.xjs) == "慢"){
				setlisttext(j + i, lbk.xjs, "0", true);
			}
		}
		for (int i = 0; i < 5; i++){
			if (j + i>XMgs) break;
			if (ls[i] > 200 && ls[i] < min){
				min = ls[i];
				minhs = i;
			}
			if (ls[i] > max){
				max = ls[i];
				maxhs = i;
			}
		}
		if (maxhs != minhs&&maxhs - minhs > 80){
			Output("oo,管理:1111    %d  %d\n", maxhs, minhs);
			setlisttext(minhs, lbk.xjs, "慢", true);
		}
	}
}

//检测窗口
void TestWin(){
	if (XMgs > 0){
		string a = dm->EnumWindow(0, "崩溃", "#32770", 1 + 2);
		vector<string> array;
		split(a, ",", array);
		if (array.size() > 0){
			JingBaoYin = 5;
			return;
		}
	}
	for (int j = 0; j < XMgs; j++){
		if (winls[j].h>0){
			if (!IsWindow(winls[j].h)){
				setlisttext(j, lbk.text, "★  窗口关闭", true);
				if (getlistbool(j, lbk.run)){
					JingBaoYin = 5;
					winls[j].h = 0;
				}
			}
		}
		else if (IsHungAppWindow(winls[j].h)){//窗口未响应
			setlisttext(j, lbk.text, "★  窗口未响应", true);
			if (getlistbool(j, lbk.run)){
				winls[j].wxy++;
			}
		}
		else if (getlisttext(j, lbk.name )!= "未登录" ){
			string bt = dm->GetWindowTitle((int)winls[j].h);
			if (bt.find("线") < 0){
				CString text = getlisttext(j,lbk.text);
				if (text != "进鼠洞"&&text != "完成"){
					setlisttext(j, lbk.text, "★  掉线", true);
					if (getlistbool(j, lbk.run))JingBaoYin = 5;
				}
			}
		}
	}
}

//取行脚文件名
void getXJname(){
	string ls = textLS + "img";
	CString ls1 = ls.c_str();
	CreateDirectory(ls1, NULL);

	//Output("oo,管理:1111  %d  \n", CreateDirectory(ls1, NULL));

	ls = textLS + "行脚";
	ls1 = ls.c_str();

	CreateDirectory(ls1, NULL);
	
	
	time_t rawtime;
	struct tm *info;
	char buffer[80];

	time(&rawtime);

	info = localtime(&rawtime);

	strftime(buffer, 80, "\\%Y-%m-%d.ini", info);

	PeiZhiXingJiao = ls + buffer;
	//Output("oo,管理:1111    %s", PeiZhiXingJiao.c_str());

}

//识别验证码
string toYZM(string user ,string pass){
	string ls = textLS + "img\\c.jpg";

	string strRe = RecYZM_A((LPSTR)ls.c_str(), (LPSTR)user.c_str(), (LPSTR)pass.c_str(), "60594");

	int pos = strRe.find("|!|");
	if (pos>-1)
	{
		vector<string> array;
		split(strRe, "|!|", array);
		softId = array[1];
		return array[0];
	}
	Output("oo,管理:打码错误    %s", strRe.c_str());
	return "";
}

//转换验证码
int YZMtoINT(string text){
	transform(text.begin(), text.end(), text.begin(), ::toupper);
	char p[4];
	text.copy(p, 4, 0);
	int code = (int)p[0] * 1000000;
	 code += (int)p[1] * 10000;
	 code += (int)p[2] * 100;
	 code += (int)p[3] ;

	Output("oo,管理:    %d", code);
	return code;
}

//大漠截图
bool DMgetTP(int hwend, int zb){

	bool isZXH = false;
	while (IsIconic((HWND)hwend)){
		isZXH = true;
		ShowWindow((HWND)hwend, 1);
		Sleep(1000);
	}
	//CoInitialize(0);
	int dm_ret = dm->BindWindow(hwend, "dx", "normal", "normal", 0);
	Sleep(100);
	Output("oo,管理:dm初始化    %d", dm_ret);
	int x = zb % 800 + 32;
	int y = (zb - zb % 800) / 800 + 41;
	string ls = textLS + "img\\c.jpg";

	dm_ret = dm->CaptureJpg(x, y, x + 130, y + 50, (_bstr_t)ls.c_str(), 50);
	dm->UnBindWindow();
	//CoUninitialize();

	if (isZXH) PostMessage((HWND)hwend, 52228, 8, 6);
	if (dm_ret == 1)return true;
	else return false;
}



//开窗口线程
DWORD WINAPI ThreadProcKck(LPVOID lpParam)  {


	string a=dm->EnumWindow(0, WindowsYXbt.c_str(), "QQSGWinClass", 1+2 + 4 + 8 + 16);

	vector<string> array;
	split(a, ",", array);
	Output("oo,管理:窗口数    %d", array.size());
	
	wchar_t   cknum[256];
	memset(cknum, 0, 256);

	XRichEdit_GetText(m_KckEdit, cknum, 256);

	int num = (int)_wtoi(cknum) - array.size();
	if (num > 0){
		STARTUPINFO stStartUpInfo = { sizeof(stStartUpInfo) };
		PROCESS_INFORMATION pProcessInfo;
		ZeroMemory(&stStartUpInfo, sizeof(STARTUPINFO));
		stStartUpInfo.cb = sizeof(STARTUPINFO);
		stStartUpInfo.dwFlags = STARTF_USESHOWWINDOW;
		stStartUpInfo.wShowWindow = 1;//窗口显示为0不显示 

		for (int i = 0; i < num; i++){
			CreateProcess(L"D:\\新QQ三国\\QQSG.exe", L" -.	", NULL, NULL, false, NULL, NULL, NULL, &stStartUpInfo, &pProcessInfo);
			Sleep(10000);
		}
		
	}

	//MessageBox(NULL, (LPCSTR)cknum, "222", MB_OK);
	Sleep(10000);

	return 0;
}

//报警
void myBeep(DWORD h){
	Beep(h, 800);
	Sleep(200);
	for (int i = 0; i < JiQi; i++){
		Beep(h - 20, 200);
		Sleep(100);
		if (i % 3 == 0)Sleep(200);
	}
}


//在回调函数中操作UI   设置打码个数
int CALLBACK ThreadsetYZMbtn(int data)
{
	int doed = _ttoi(getini("窗口", "打码", (CString)PeiZhiXingJiao.c_str(), "0")) + 1;
	XBtn_SetText(m_hButtonDMCX, "查询点" + intToCstr(doed));
	setini("窗口", "打码", PeiZhiXingJiao, to_string(doed));
	return 0;
}

//超时检测
int CALLBACK CStime(int data){
	int bz = 0;
	for (int j = 0; j < XMgs; j++){
		if (winls[j].cstime>0){
			winls[j].cstime += 2;
			CString text = intToCstr(winls[j].cstime - 1);
			if (winls[j].hskg == 1){
				text = "*" + text;
				if (winls[j].cstime > 120 && winls[j].notbj == 0){
					CString tt = getlisttext(j, lbk.text);
					if (tt.Find(L"★") < 0){
						setlisttext(j, lbk.text, "★ " + tt, true);
					}
					bz = 1;
				}
			}
			setlisttext(j, lbk.csime, text, true);

		}
	}
	return bz;
}



//警报线程
DWORD WINAPI BaoJingThread(LPVOID lpParam){

	while (JingBao>-100){
		if (JingBao == 1){
			
			//LARGE_INTEGER t1;
			//QueryPerformanceCounter(&t1);
			time_t result = time(nullptr);
			//xtrace("%d\n", t1.QuadPart);
			if (result - JingBaoTime  > 60){
				JingBaoTime = result;
				myBeep(220);
			}
			JingBao = 0;

		}
		else if (JingBaoYin > 0){
			switch (JingBaoYin)
			{
			case 1://死亡
				Beep(150, 300);
				JingBaoYin = 0;
				break;
			case 2://屏蔽
				myBeep(880);
				Sleep(4000);
				JingBaoYin = 0;
				break;
			case 3://线路满了
				myBeep(180);
				Sleep(2000);
				JingBaoYin = 0;
				break;
			case 4://无法登录
				myBeep(180);
				Sleep(4000);
				JingBaoYin = 0;
				break;
			case 5://掉窗口
				myBeep(180);
				Sleep(6000);
				break;
			case 6://掉线
				Beep(730 - JiQi * 38, 200);
				Beep(730 - JiQi * 38, 800);
				JingBaoYin = 0;
				break;
			}
		}
		Sleep(1000);
	}
	return 0;
}

//打码线程
DWORD WINAPI DaMaThread(LPVOID lpParam){

	int yzmJL = 0;
	while (DaMaHwend>-100){
		if (DaMaHwend > 0 && DaMaPos>0){
			if (getini("窗口", "自动打码", PeiZhiText, "") != ""){
				vector<string> array;
				split(getini("窗口", "自动打码账号", PeiZhiText, ""), "-", array);
				if (array.size() > 1 && DMgetTP((int)winls[DaMaHwend-1].h,DaMaPos)){
					if (DaMaHwend > 0){
						Output("oo,管理:打码中    %d\n", DaMaHwend);
						yzmJL = DaMaHwend;
						string jg=toYZM(array[0], array[1]);
						if (yzmJL == DaMaHwend){
							if (jg != ""){
								
								Output("oo,管理:打码成功,返回结果%d   %s\n", DaMaHwend, jg.c_str());

								if (jg.length() > 3){
									int code = YZMtoINT(jg);
									PostMessageA(winls[DaMaHwend-1].h, 52228, 7, code);
								}
								else{
									PostMessageA(winls[DaMaHwend-1].h, 52228, 7, 180000);
								}

								int ret = XC_CallUiThread(ThreadsetYZMbtn, 0);

								Sleep(5000);
							}
							else{
								Output("oo,管理:打码错误 %s\n", jg.c_str());
							}
							DaMaPos = 0;
						}
						else{
							Output("oo,管理:验证窗口记录不同  记录%d  当下%d\n", yzmJL, DaMaHwend);
						}
					}
				}
				else{
					Output("oo,管理:没找到图片 ");
					DaMaPos = 0;
				}
			}
			else{//手动打码
				if (IsIconic(winls[DaMaHwend-1].h)){
					Beep(150, 300);
					ShowWindow(winls[DaMaHwend-1].h, 1);
					Sleep(1000);
					BringWindowToTop(winls[DaMaHwend-1].h);//置顶
				}
				Sleep(1000);
			}
		}
		Sleep(1000);
		//Output("oo,管理:打码   %d\n", 1);
	}
	return 0;
}


//上号线程
DWORD WINAPI  toRoot(LPVOID lpParam){
	int j = (int)lpParam;
	xtrace("上号线程 %d   %d\n", j, winls[j].rootnum);
	string name, pw;
	getZhangHao(winls[j].rootnum, name, pw);
	xtrace("上号线程 %d   %d  %s  %s\n", j, winls[j].rootnum, name.c_str(), pw.c_str());
	PostMessageA(winls[j].h, 52228, 11, winls[j].rootnum);
	LiftClock(winls[j].h, 216, 466, 100);
	KeyPress(winls[j].h, 9, 50);
	for (int i = 0; i < 20; i++){
		KeyPress(winls[j].h, 8, 10);
	}
	toWindowsText(winls[j].h, name);
	Sleep(100);
	KeyPress(winls[j].h, 9, 50);
	Sleep(100);
	toWindowsText(winls[j].h, pw);
	Sleep(100);
	KeyPress(winls[j].h, 13, 1000);
	return 0;
}

//-----------------------------处理--------------------

//脚本行数
int CALLBACK OnSetText27(WPARAM wParam, LPARAM lParam, BOOL *pbHandled)
{
	if (winls[wParam - 1].hskg != 1 && winls[wParam - 1].cstime>0){
		winls[wParam - 1].cstime = 1;
	}
	if (lParam >= 10002 && lParam <= 10005){
		winls[wParam - 1].rootnum = 0;
		if (DaMaHwend == wParam)DaMaHwend = 0;

	}
	winls[wParam - 1].hs = (int)lParam;

	//XEle_SendEvent(g_hEle, g_hEle, XE_USER_SETTEXT, wParam, lParam);
	return 0;
}

//三国币&等级
int CALLBACK OnSetText26(WPARAM wParam, LPARAM lParam, BOOL *pbHandled)
{
	
	if (lParam < 150){
		setlisttext(wParam - 1, lbk.nl, intToCstr(lParam));
	}
	else{
		if (lParam >150)
			setlisttext(wParam - 1, lbk.money, FloatToCstr(ceil((lParam - 150) / 100) / 100));
		else
			setlisttext(wParam - 1, lbk.money, "0");
	}

	return 0;
}

//运行
int CALLBACK OnSetText25(WPARAM wParam, LPARAM lParam, BOOL *pbHandled)
{
	
	switch (lParam){
	case 0:
		setlistbool(wParam - 1, lbk.run, false, true);
		winls[wParam - 1].cstime = 0;
		winls[wParam - 1].hsjl = 0;
		winls[wParam - 1].rootnum = 0;
		break;
	case 1:
		setlistbool(wParam - 1, lbk.run, true, true);
		winls[wParam - 1].cstime = 1;
		break;
	case 2:
		setlisttext(wParam - 1, lbk.name, L"未登录");
		winls[wParam - 1].cstime++;
		int n1;
		n1 = XComboBox_GetSelItem(hComboBoxFS);
		if (n1 >= 3){//设置换IP换号

		}
		else{
			int xh = getHuanHaoNum(wParam - 1);
			if (xh > 0){
				winls[wParam - 1].rootnum = xh;
				//设置行数
				PostMessageA(winls[wParam - 1].h, 52228, 1, 4);
				//设置登录线程
				if (isRootT == 0){
					isRootT = 1;
					::CreateThread(0, 0, rootThread, 0, 0, 0);
				}
			}
			else{
				PostMessageA(winls[wParam - 1].h, 52228, 3, 0);
				PostMessageA(winls[wParam - 1].h, 52228, 1, 0);
			}
		}
		break;
	case 3://完成验证
		if (DaMaHwend == wParam)DaMaHwend = 0;
		winls[wParam - 1].rootnum = 0;
		break;
	case 5://进副本,清除行数记录
		winls[wParam - 1].hskg = 0;
		winls[wParam - 1].hsjl = 0;
		break;
	case 6://掉线
		winls[wParam - 1].rootnum = 10000;
		setlisttext(wParam - 1, lbk.name, "未登录");
		setlisttext(wParam - 1, lbk.text, "掉线");
		JingBaoYin = 6;
		//设置登录线程
		if (isRootT == 0){
			isRootT = 1;
			::CreateThread(0, 0, rootThread, 0, 0, 0);
		}
		break;
	}
	return 0;
}

int CALLBACK OnSetText23(WPARAM wParam, LPARAM lParam, BOOL *pbHandled)
{
	if (lParam == 0){//组队
		CString name = "";
		for (int i = wParam; i < wParam + 4; i++){
			if (winls[i].h > 0){
				CString name1 = getlisttext(i, lbk.name);
				if (name1 != ""&&name1 != "未登录"){
					name += name1 + "|";
				}
			}
		}
		if (name != ""){
			setini("组队", intToCstr(wParam), PeiZhiText, name);
		}

	}
	else if (lParam == 1){//输入角色名
		liftDclock(winls[wParam - 1].h, 376, 545, 200);
		toWindowsText(winls[wParam - 1].h, getNameSJ());

	}
	return 0;
}

//验证码
int CALLBACK OnSetText22(WPARAM wParam, LPARAM lParam, BOOL *pbHandled)
{
	//验证窗口句柄 ＝ 0 或 验证窗口句柄 ＝ wp 且 验证窗口坐标 ＝ 0
	if (getlistbool(wParam - 1, lbk.run) && (DaMaHwend == 0 || (DaMaHwend == wParam&&DaMaPos == 0))){
		DaMaHwend = wParam;
		DaMaPos = lParam;
		Output("oo,管理:打码中  %d  序号%d\n", DaMaPos, DaMaHwend);
	}
	return 0;
}

//登录账号序号
int CALLBACK OnSetText21(WPARAM wParam, LPARAM lParam, BOOL *pbHandled)
{
	
	if (lParam > 0){
		setlisttext(wParam - 1, lbk.rootnum, intToCstr((int)lParam));
		CString name = getlisttext(wParam - 1, lbk.name);
		if (name != ""&&name != "未登录"){//行脚文件
			setlisttext(wParam - 1, lbk.xjs, getini(intToCstr((int)lParam), name, (CString)PeiZhiXingJiao.c_str(), "0"));
		}
	}
	return 0;
}

int CALLBACK OnSetText20(WPARAM wParam, LPARAM lParam, BOOL *pbHandled)
{

	return 0;
}

//交易号标志
int CALLBACK OnSetText19(WPARAM wParam, LPARAM lParam, BOOL *pbHandled)
{

	buying = 1;
	setlisttext(wParam - 1, lbk.text, "上交 交易中");
	return 0;
}

//登录第几角色
int CALLBACK OnSetText18(WPARAM wParam, LPARAM lParam, BOOL *pbHandled)
{
	setlisttext(wParam - 1, lbk.rootp, intToCstr((int)lParam));
	return 0;
}

int CALLBACK OnSetText5000(WPARAM wParam, LPARAM lParam, BOOL *pbHandled)
{
	toQipao1(Qipao);
	return 0;
}

//-----------------------------处理--------------------

LRESULT CALLBACK NewProc1(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	//if (hWnd == myHwnd)return CallWindowProc(OldProc, hWnd, message, wParam, lParam);
	//Output("oo,管理:消息  记录%d  当下%d\n", message);
	if (!hWnd)return CallWindowProc(OldProc, hWnd, message, wParam, lParam);
	//Output("oo,管理:  %d   %d   %d   %d\n", hWnd, message, wParam, lParam);
	switch (message)
	{
	case 12:
		if (wParam<52327 && wParam>52227){
			CString name((char*)lParam);
			int xh = wParam - 52227 - 1;

			CString str = getlisttext(xh, lbk.rootnum);
			if (str != "" || str != "未登录"){
				setlisttext(xh, lbk.xjs, getini(str, name, (CString)PeiZhiXingJiao.c_str(), "0"), true);
			}
			if (name.GetLength() > 4)
				setlisttext(xh, lbk.name, name);
			winls[xh].rootnum = 0;
			winls[xh].hskg = 0;
			winls[xh].hsjl = 0;
			if (DaMaHwend == wParam)DaMaHwend = 0;
		}
		return 0;
	}
	return CallWindowProc(OldProc, hWnd, message, wParam, lParam);
}

//处理
LRESULT CALLBACK NewProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	//if (hWnd == myHwnd)return CallWindowProc(OldProc, hWnd, message, wParam, lParam);
	//Output("oo,管理:消息  记录%d  当下%d\n", message);
	if (!hWnd)return 0;
	//Output("oo,管理:  %d   %d   %d   %d\n", hWnd, message, wParam, lParam);
	switch (message)
	{
	case 12:
		if (wParam<52327 && wParam>52227){
			CString name((char*)lParam);
			int xh=wParam - 52227-1;
			//wstring str1(name.GetBuffer(MAX_PATH));
			//string aa = wstring2string(str1);
			CString str = getlisttext(xh, lbk.rootnum);
			if (str != "" || str != "未登录"){
				setlisttext(xh, lbk.xjs, getini(str, name, (CString)PeiZhiXingJiao.c_str(), "0"),true);
			}
			if (name.GetLength()>2)
			setlisttext(xh, lbk.name, name);
			winls[xh].rootnum = 0;
			winls[xh].hskg = 0;
			winls[xh].hsjl = 0;
			if (DaMaHwend == wParam)DaMaHwend = 0;
		}
		return 0;
	case 52227://脚本行数
		if (winls[wParam - 1].hskg != 1 && winls[wParam - 1].cstime>0){
			winls[wParam - 1].cstime = 1;
		}
		if (lParam >= 10002 && lParam <= 10005){
			winls[wParam - 1].rootnum = 0;
			if (DaMaHwend == wParam)DaMaHwend = 0;

		}
		winls[wParam - 1].hs = (int)lParam;
		return 0;
	case 52226://三国币&等级
		if (lParam < 150){
			setlisttext(wParam - 1, lbk.nl, intToCstr(lParam));
		}
		else{
			if (lParam >150)
				setlisttext(wParam - 1, lbk.money, FloatToCstr(ceil((lParam - 150) / 100)/100));
			else
				setlisttext(wParam - 1, lbk.money, "0");
		}
		return 0;
	case 52225://运行
		switch (lParam){
		case 0:
			setlistbool(wParam - 1, lbk.run, false, true);
			winls[wParam - 1].cstime = 0;
			winls[wParam - 1].hsjl = 0;
			winls[wParam - 1].rootnum = 0;
			break;
		case 1:
			setlistbool(wParam - 1, lbk.run, true, true);
			winls[wParam - 1].cstime = 1;
			break;
		case 2:
			setlisttext(wParam - 1, lbk.name, L"未登录");
			winls[wParam - 1].cstime++;
			int n1;
			n1=XComboBox_GetSelItem(hComboBoxFS);
			if (n1 >= 3){//设置换IP换号
				
			}
			else{
				int xh = getHuanHaoNum(wParam - 1);
				if (xh > 0){
					winls[wParam - 1].rootnum = xh;
					//设置行数
					PostMessageA(winls[wParam - 1].h, 52228, 1, 4);
					//设置登录线程
					if (isRootT == 0){
						isRootT = 1;
						::CreateThread(0, 0, rootThread, 0, 0, 0);
					}
				}
				else{
					PostMessageA(winls[wParam - 1].h, 52228, 3, 0);
					PostMessageA(winls[wParam - 1].h, 52228, 1, 0);
				}
			}
			break;
		case 3://完成验证
			if (DaMaHwend == wParam)DaMaHwend = 0;
			winls[wParam - 1].rootnum = 0;
			break;
		case 5://进副本,清除行数记录
			winls[wParam - 1].hskg = 0;
			winls[wParam - 1].hsjl = 0;
			break;
		case 6://掉线
			winls[wParam - 1].rootnum = 10000;
			setlisttext(wParam - 1, lbk.name, "未登录");
			setlisttext(wParam - 1, lbk.text, "掉线");
			JingBaoYin = 6;
			//设置登录线程
			if (isRootT == 0){
				isRootT = 1;
				::CreateThread(0, 0, rootThread, 0, 0, 0);
			}
			break;
		}
		return 0;
	case 52223:
		if (lParam==0){//组队
			CString name="";
			for (int i = wParam; i < wParam + 4; i++){
				if (winls[i].h > 0){
					CString name1 =getlisttext(i,lbk.name);
					if (name1 != ""&&name1 != "未登录"){
						name += name1 + "|";
					}
				}
			}
			if (name != ""){
				setini("组队", intToCstr(wParam), PeiZhiText, name);
			}

		}
		else if (lParam == 1){//输入角色名
			liftDclock(winls[wParam - 1].h, 376, 545, 200);
			toWindowsText(winls[wParam - 1].h, getNameSJ());

		}
		return 0;
	case 52222://验证码
		
		//验证窗口句柄 ＝ 0 或 验证窗口句柄 ＝ wp 且 验证窗口坐标 ＝ 0
		if (getlistbool(wParam - 1, lbk.run) && (DaMaHwend == 0 || (DaMaHwend == wParam&&DaMaPos == 0))){
			DaMaHwend = wParam;
			DaMaPos = lParam;
			Output("oo,管理:打码中  %d  序号%d\n", DaMaPos, DaMaHwend);
		}
		return 0;
	case 52221://登录账号序号
		if (lParam > 0){
			setlisttext(wParam - 1, lbk.rootnum, intToCstr((int)lParam));
			CString name = getlisttext(wParam - 1, lbk.name);
			if (name != ""&&name != "未登录"){//行脚文件
				setlisttext(wParam - 1, lbk.xjs, getini(intToCstr((int)lParam), name, (CString)PeiZhiXingJiao.c_str(), "0"));
			}
		}
		return 0;
	case 52220: //摆摊编辑框EX1
		//wParam = (wParam - (wParam % 2000)) / 2000;


		return 0;
	case 52219://交易号标志
		buying = 1;
		setlisttext(wParam - 1, lbk.text, "上交 交易中");
		return 0;
	case 52218:
		setlisttext(wParam - 1, lbk.rootp, intToCstr((int)lParam));
		return 0;
	case 50000:
		toQipao1(Qipao);
		return 0;

	}
	return CallWindowProc(OldProc, hWnd, message, wParam, lParam);
}

//初始化------------------------------------------------------
void init(){
	//xtrace("%d\n", getHuanHaoNum(0));
	
}



//增加一行
void addLSfun(int i){
	

	XAdTable_AddItemText(hAdapter, intToCstr(i+1));
	for (int j = 1; j < 12; j++){
		XAdTable_SetItemText(hAdapter, i, j, L"");
	}
	XAdTable_SetItemText(hAdapter, i, 3, L"未登录");
	XList_RefreshItem(m_hList, i);
	//XAdTable_SetItemText(hAdapter, i, 8, L"查");
	
}


//设置表格
void setLSfun(){
	XList_SetItemTemplateXML(m_hList, L"List_Item.xml");
	int wlist[] = { 20, 25, 25, 80, 30, 45, 30, 30, 30, 55, 35, 115 };
	CString btlist[] = { "序", "号", "", "名字", "等级", "金币", "行脚", "运行", "查看", "执行行数", "超时", "脚本内容" };
	XList_SetItemHeightDefault(m_hList,22,22);
	XList_SetHeaderHeight(m_hList, 22);


	HXCGUI hAdapterHeader = XAdMap_Create();
	XList_BindAdapterHeader(m_hList, hAdapterHeader);

	hAdapter = XAdTable_Create();
	XList_BindAdapter(m_hList, hAdapter);

	for (int i = 0; i < sizeof(wlist) / sizeof(wlist[0]); i++){
		XList_AddColumn(m_hList, wlist[i]);
		
		CString tt = "name";
		tt.Format(_T("%d"), i + 1);
		tt = "name"+tt;

		
		XAdMap_AddItemText(hAdapterHeader, tt, btlist[i]);
		XAdTable_AddColumn(hAdapter, tt);
		XList_SetColumnWidth(m_hList, i, wlist[i]);
	}

	//wchar_t tmp[MAX_PATH] = { 0 };
	for (int i = 0; i<20; i++)
	{
		//wsprintf(tmp, L"item-%d", i);
		//addLSfun(i);
		
	}



	//XList_RefreshItem(m_hList, 1);
	//XEle_RedrawEle(m_hList, true);

}

//取句柄记录
void getHwndJl(){
	XMgs = XAdTable_GetCount(hAdapter);
	for (int i = 1; i <= MAXWIN; i++){
		HWND hwnd = (HWND)stoi(getini("hwnd", to_string(i), PeiZhiText, "0"));
		string bn = dm->GetWindowTitle((int)hwnd);
		//xtrace("%s   %d\n", bn.c_str(), bn.find(WindowsYXbt));
		if (hwnd > 0 && IsWindow(hwnd) && bn.find(WindowsYXbt)==0){
			winls[i - 1].h = hwnd;
			PostMessageA(winls[i - 1].h, 52228, 5, (int)myHwnd);
			//xtrace("%d   %d   %d\n", XMgs, i, hwnd);
			for (int j = XMgs; j < i; j++){
				addLSfun(j);
			}
			XMgs = i;
			PostMessageA(winls[i - 1].h, 52228, 6, i);
			PostMessageA(winls[i - 1].h, 52228, 8, 1);
			if (IsIconic(winls[i - 1].h)){
				setlisttext(i, 8, L"查", true);
			}
			else{
				setlisttext(i, 8, L"立", true);
			}
		}
		
	}
}
//-----------------事件----------------------

//刷新窗口
int OnBtnClickSX1()
{
	
	JingBaoYin = 0;
	//清理关掉的窗口
	for (int i = 0; i < MAXWIN; i++){
		if (winls[i].h>0 && !IsWindow(winls[i].h)){
			winls[i].h = 0;
			setlisttext(i, lbk.name, "", true);
			setlisttext(i, lbk.nl, "", true);
			setlistbool(1, 7, false, true);
			setlisttext(i, lbk.money, "", true);
			winls[i].cstime = 0;
			winls[i].hskg = 0;
			winls[i].hsjl = 0;

		}
	}

	string jbsz = dm->EnumWindow(0, WindowsYXbt.c_str(), "QQSGWinClass", 1 + 2 + 4 + 8 + 16);

	vector<string> array;
	split(jbsz, ",", array);
	for (int i = 0; i < array.size(); i++){
		bool bn = false;
		HWND hwnd = (HWND)atoi(array[i].c_str());
		//找下有没有
		for (int j = 0; j < MAXWIN; j++){
			if (hwnd == winls[j].h){
				bn = true;
				if (IsIconic(hwnd)){
					setlisttext( j, 8, L"查",true);
				}
				else{
					setlisttext(j, 8, L"立", true);
				}
				break;
			}
		}
		//如果没有
		if (!bn){
			PostMessageA(hwnd, 52228, 5, (int)myHwnd);
			for (int j = 0; j < MAXWIN; j++){
				if (winls[j].h == 0){
					winls[j].h = hwnd;
					setini("hwnd", to_string(j+1), PeiZhiText, to_string((int)hwnd));
					if (XAdTable_GetCount(hAdapter) < j + 1){
						addLSfun(j);
					}
					if (IsIconic(hwnd)){
						setlisttext(j, 8, L"查", true);
					}
					else{
						setlisttext(j, 8, L"立", true);
					}
					PostMessageA(hwnd, 52228, 6, j + 1);
					PostMessageA(hwnd, 52228, 8, 1);
					break;
				}
			}
		}
	}
	
	//XEle_RedrawEle(m_hList, true);

	DaMaHwend = 0;
	DaMaPos = 0;
	XMgs = XAdTable_GetCount(hAdapter);
	
	return 0;
}




//-----------------事件----------------------

class CWindow_Demo
{
public:
	HWINDOW m_hWindow;
	//HELE    m_KckEdit;

	CWindow_Demo()
	{
		Init();
	}

	//分页切换
	void XTabBar_Adjust(HELE hTabBar, int cx, int cy)
	{
		int nCount = XTabBar_GetLabelCount(hTabBar);
		if (nCount < 1)
		{
			return;
		}

		HELE hLable = XTabBar_GetLabel(hTabBar, 0);
		RECT rt;
		RECT Clientrt;
		XEle_GetRect(hTabBar, &rt);
		XEle_GetClientRect(hTabBar, &Clientrt);


		rt.top += Clientrt.bottom;
		rt.right = rt.left + cx;
		rt.bottom = rt.top + cy;

		HELE hPage = NULL;
		for (int i = 0; i < nCount; i++)
		{
			hLable = XTabBar_GetLabel(hTabBar, i);
			hPage = XBtn_GetBindEle(hLable);
			XEle_SetRect(hPage, &rt);
		}

	}

	//加分页
	HELE XTabBar_AddPage(HELE hTabBar, wchar_t* lpText, BOOL bShow = FALSE)
	{
		int nIndex = XTabBar_AddLabel(hTabBar, lpText);
		HELE hLable = XTabBar_GetLabel(hTabBar, nIndex);
		XTabBar_SetLabelWidth(hTabBar,nIndex, 50);
		HELE hParent = XEle_GetParentEle(hTabBar);
		HXCGUI hp = NULL;
		if (hParent == NULL)
		{
			hp = (HWINDOW)XEle_GetHWINDOW(hTabBar);
		}
		else
		{
			hp = hParent;
		}

		

		HELE hPage1 = XEle_Create(0, 0, 100, 100, hp);
		XBtn_SetBindEle(hLable, hPage1);

		XEle_ShowEle(hPage1, bShow);

		return hPage1;
	}

	void Init()
	{
		int x = atoi(getini("pos", "x1", PeiZhiText, "0").c_str());
		int y = atoi(getini("pos", "y1", PeiZhiText, "0").c_str());
		int h = atoi(getini("pos", "h1", PeiZhiText, "800").c_str());

		//Output("oo,管理: 开窗11口数  %s\n", getini("pos", "h1", PeiZhiText, "800").c_str());

		//Output("oo,管理:打码成功,返回结果   %d  %d   %d", x,y,h);
		m_hWindow = XWnd_Create(x, y, 550, h, L"YY", NULL, xc_window_style_nothing | xc_window_style_drag_window);

		XWnd_SetMinimumSize(m_hWindow, 550, 550);
		XBtn_SetType(XBtn_Create(510, 5, 30, 20, L"x", m_hWindow), button_type_close);
		XBtn_SetType(XBtn_Create(475, 5, 30, 20, L"-", m_hWindow), button_type_min);

		myHwnd = XWnd_GetHWND(m_hWindow);
		//setini("窗口", "C管理", PeiZhiText, to_string((int)myHwnd));

		//分页栏
		HELE hTabBar = XTabBar_Create(7, 30, 292, 20, m_hWindow);
		HELE hPage = NULL;
		hPage = XTabBar_AddPage(hTabBar, L"设置", TRUE);
		//HELE m_hButton = XBtn_Create(0, 50, 60, 25, L"Button", hPage);

		table1 table1(hPage);

		HELE m_hButton = XBtn_Create(237, 6, 48, 22, L"上号", hPage);
		XEle_RegEventCPP(m_hButton, XE_BNCLICK, &CWindow_Demo::OnEventBtnClickSH);
		XEle_SetTextColor(m_hButton, RGB(128, 0, 64), 255);

		hPage = XTabBar_AddPage(hTabBar, L"高级");
		XTabBar_Adjust(hTabBar, 292, 188);

		//分页栏1
		hTabBar = XTabBar_Create(307, 30, 236, 20, m_hWindow);
		hPage = XTabBar_AddPage(hTabBar, L"设置", TRUE);
		
		//HELE m_hButton = XBtn_Create(0, 50, 60, 25, L"Button", hPage);
		XTabBar_Adjust(hTabBar, 236, 188);
		table3 table3(hPage);

		m_KckEdit = XRichEdit_Create(56, 58, 30, 22, hPage);

		XRichEdit_EnableEvent_XE_RICHEDIT_CHANGE(m_KckEdit, true);
		XEle_RegEventCPP(m_KckEdit, XE_RICHEDIT_CHANGE, &CWindow_Demo::OnRichEditChangeXH);
		//Output("oo,管理: 开窗口数  %s\n", getini("窗口", "开窗口数", (CString)PeiZhiText.c_str(), "1"));

		XRichEdit_SetText(m_KckEdit, getini("窗口", "开窗口数", (CString)PeiZhiText.c_str(), "1"));

		

		XWnd_RegEventCPP(m_hWindow, XWM_PAINT_DISPLAY, &CWindow_Demo::Oninit);
		

		m_hButton = XBtn_Create(88, 58, 52, 22, L"开窗口", hPage);
		XEle_RegEventCPP(m_hButton, XE_BNCLICK, &CWindow_Demo::OnEventBtnClickKck);
		m_hButton = XBtn_Create(145, 2, 82, 26, L"刷新窗口", hPage);
		XEle_RegEventCPP(m_hButton, XE_BNCLICK, &CWindow_Demo::OnBtnClickSX);

		

		//边框大小
		XWnd_SetLayoutSize(m_hWindow, 1, 28, 1, 20);
		XWnd_RegEventCPP1(m_hWindow, WM_DESTROY, &CWindow_Demo::OnDestroy);
		XWnd_RegEventCPP1(m_hWindow, WM_SIZE, &CWindow_Demo::OnDestroySIZE);
		


		m_hList = XList_Create(7, 243, 536, h - 20 - 243, m_hWindow);
		

		//QiPao = XShapeText_Create(363, h-18, 180, 20, L"", m_hWindow);
		//XShapeText_SetTextAlign(QiPao, textAlignFlag_center | textAlignFlag_right);
		//XShapeText_SetTextColor(QiPao, RGB(255, 255, 255), 255);

		setLSfun();
		//XWnd_AdjustLayout(m_hWindow);

		//按键1
		m_hButtonAJ1 = XBtn_Create(372, 233, 40, 22, L"设置", m_hList);
		XEle_ShowEle(m_hButtonAJ1,false);

		XEle_RegEventCPP(m_hButtonAJ1, XE_BNCLICK, &CWindow_Demo::OnEventBtnClickAJ1);

		
		XWnd_ShowWindow(m_hWindow, SW_SHOW);
		


		//-----------------------------------------------------------
		OldProc = (WNDPROC)SetWindowLongA(myHwnd, GWL_WNDPROC, (LONG)NewProc);

		//int dm_ret = dm->BindWindow((int)myHwnd, "dx", "normal", "normal", 0);
		
		//Sleep(1000);
		//dm->UnBindWindow();
		//Output("oo,管理:dm初始化1111    %d", dm_ret);
		
		//---------------------------------------------------------------
	}

	//刷新按钮
	int OnBtnClickSX(BOOL *pbHandled)
	{
		OnBtnClickSX1();

		//事件响应
		return 0;
	}

	int Oninit(BOOL *pbHandled){
		

		if (isGoWin)return 0;
		isGoWin = true;
		xtrace("1111111\n");

		getXJname();
		//取句柄记录
		getHwndJl();
		OnBtnClickSX1();
		//lua取脚本
		takeluatext();
		init();
		
		XWnd_RegEventCPP(m_hWindow, XWM_MENU_SELECT, &CWindow_Demo::OnWndMenuSelect1);
		XEle_RegEventCPP(m_hList, XE_LIST_TEMP_CREATE_END, &CWindow_Demo::OnListTemplateCreateEnd);
		XEle_RegEventCPP(m_hList, XE_LBUTTONDBCLICK, &CWindow_Demo::OnRButtonUp);//右键菜单
		XEle_RegEventCPP(m_hList, XE_LIST_SELECT, &CWindow_Demo::OnRButtonUpSELECT);

		XList_EnableDragChangeColumnWidth(m_hList, false);
		/*
		XWnd_RegEventC(m_hWindow, XE_USER_SET, OnSetText27);
		XWnd_RegEventC(m_hWindow, XE_USER_SET - 1, OnSetText26);
		XWnd_RegEventC(m_hWindow, XE_USER_SET - 2, OnSetText25);
		XWnd_RegEventC(m_hWindow, XE_USER_SET - 4, OnSetText23);
		XWnd_RegEventC(m_hWindow, XE_USER_SET - 5, OnSetText22);
		XWnd_RegEventC(m_hWindow, XE_USER_SET - 6, OnSetText21);
		XWnd_RegEventC(m_hWindow, XE_USER_SET - 7, OnSetText20);
		XWnd_RegEventC(m_hWindow, XE_USER_SET - 8, OnSetText19);
		XWnd_RegEventC(m_hWindow, XE_USER_SET - 9, OnSetText18);
		XWnd_RegEventC(m_hWindow, 50000, OnSetText5000);
	*/
		//启动打码线程
		::CreateThread(0, 0, DaMaThread, 0, 0, 0);
		::CreateThread(0, 0, BaoJingThread, 0, 0, 0);
		//::CreateThread(0, 0, SetTimerThread, 0, 0, 0);



		XWnd_RegEventCPP(m_hWindow, WM_TIMER, &CWindow_Demo::OnWndXCTimer);
		XWnd_SetTimer(m_hWindow, 100, 2000);
		
		//XWnd_RemoveEventCPP(m_hWindow, XWM_PAINT_DISPLAY, &CWindow_Demo::Oninit);

		return 0;
	}

	//时钟线程
	//DWORD WINAPI SetTimerThread(LPVOID lpParam){
	int OnWndXCTimer(UINT nTimerID, BOOL *pbHandled){
		//Sleep(3000);
		//xtrace("111  %d\n", nTimerID);
		if (nTimerID != 100)return 0;
		isDateList = true;

		//while (true){
		int jb_jb = 0;//警报标志_局
		for (int j = 0; j < MAXWIN; j++){
			if (winls[j].hs>0 && winls[j].h > 0){
				switch (winls[j].hs){
				case 10001:
					if (getlisttext(j, lbk.text) != "死亡"){
						JingBaoYin = 1;
						setlisttext(j, lbk.text, "死亡", true);
					}
					break;
				case 10002:
					JingBaoYin = 4;
					setlisttext(j, lbk.text, "★  无法登录", true);
					break;
				case 10003:
					setlisttext(j, lbk.text, "★  验证码不对", true);
					if (softId != "" && getini("窗口", "自动打码", (CString)PeiZhiText.c_str(), "") == "1"){
						Output("oo,管理: 上报打码错误  %d\n", DaMaHwend);
						vector<string> array;
						split(getini("窗口", "自动打码账号", PeiZhiText, ""), "-", array);
						//Output("oo,管理:  softId   %d  当下%d      \n",  DaMaHwend);
						ReportError((LPSTR)array[0].c_str(), (LPSTR)softId.c_str());
						softId = "";
					}
					break;
				case 10004:
					JingBaoYin = 2;
					setlisttext(j, lbk.text, "★  屏蔽", true);
					break;
				case 10005:
					JingBaoYin = 3;
					setlisttext(j, lbk.text, "★  线路满了", true);
					break;
				case 20000:
					winls[j].hsjl = 0;
					setlisttext(j, lbk.name, "未登录", true);
					break;
				case 10000:
				{
							  CString tt;
							  tt = getlisttext(j, lbk.text);
							  if (tt.Find(L"★")<0){
								  setlisttext(j, lbk.text, "★ " + tt, true);
							  }
							  jb_jb = 1;

				}

					break;
				default:
					setlisttext(j, lbk.runnum, intToCstr(winls[j].hs), true);
					if (rumtext.size() > winls[j].hs){
						setlisttext(j, lbk.text, rumtext[winls[j].hs], true);
						if (winls[j].hsjl >= winls[j].hs){
							if (rumtext[winls[j].hs].Find(L"kill") >= 0){
								winls[j].notbj = 1;
							}
							if (winls[j].hsjl > winls[j].hs){
								winls[j].hskg = 1;
							}
						}
						else{
							if (winls[j].hskg > 0){
								winls[j].hskg = 0;
							}
							winls[j].notbj = 0;
							winls[j].hsjl = winls[j].hs;
						}
					}
					//如果真 (窗口数据数组 [j].行数记录开关 ＝ 1 且 比对脚本 (脚本数组 [窗口数据数组 [j].行数]))
					if (winls[j].hskg == 1 && NOT_BJ_TEXT.Find(L"|" + rumtext[winls[j].hs] + "|") > 0){
						winls[j].hskg = 0;
						winls[j].hsjl = winls[j].hs - 3;
					}
					if (rumtext[winls[j].hs] == "行脚"){
						CString num = getlisttext(j, lbk.rootnum);
						CString name = getlisttext(j, lbk.name);
						CString tt = getini(num, name, (CString)PeiZhiXingJiao.c_str(), "0");
						tt = intToCstr(_ttoi(tt) + 1);
						setlisttext(j, lbk.xjs, tt, true);
					}
					else if (rumtext[winls[j].hs] == "等待队友" || rumtext[winls[j].hs] == "等待队友,2"){
						waitteam = 1;
					}
					else if (rumtext[winls[j].hs] == "等待队友,1"){
						waitteamall = 1;
					}

				}
				winls[j].hs = 0;
			}
			if (winls[j].wxy > 0){
				if (IsHungAppWindow(winls[j].h)){
					winls[j].wxy++;
					if (winls[j].wxy > 10) {
						bool bn = myKillProcess(winls[j].h);
						Output("oo,管理:窗口%d  关闭未响应的窗口  %d\n", j, bn);
						winls[j].wxy = 0;
					}

				}
				else{
					winls[j].wxy = 0;
				}
			}
		}
		if (TimerNum > 20){//检测慢窗口
			TimerNum = 0;
			TestSwin();
			TestWin();
		}
		if (XC_CallUiThread(CStime ,0)== 1 || jb_jb == 1)JingBao = 1;

		if (waitteam == 1){//等待队友中
			waitteamFun();
		}
		if (buying == 1){//检测交易号标志
			tastBuyFun();
		}
		if (waitteamall == 1){//等待全部队友
			waitteamAllFun();
		}
		TimerNum++;
		//Sleep(2000);

		XEle_RedrawEle(m_hList, true);
		//}

		return 0;
	}


	//开窗口个数
	int OnRichEditChangeXH(BOOL *pbHandled){
		wchar_t   cknum[256];
		memset(cknum, 0, 256);
		XRichEdit_GetText(m_KckEdit, cknum, 256);

		setini("窗口", "开窗口数", PeiZhiText, cknum);
		return 0;
	}

	//开窗口
	int OnEventBtnClickKck(BOOL *pbHandled)
	{
		JingBaoYin = 0;
		::CreateThread(0, 0, ThreadProcKck, 0, 0, 0);
		//::CreateThread(0, 0, DllThread, 0, 0, 0);
		return 0;
	}

	//绑定列表完成的事件
	int OnListTemplateCreateEnd(list_item_i* pItem, BOOL *pbHandled)
	{
		
		if (pItem->iSubItem == 0) //按钮在第0列
		{

			//运行
			HXCGUI hBtn = XList_GetTemplateObject(m_hList, pItem->index, lbk.run, lbk.run);
			if (XC_GetObjectType(hBtn) == XC_BUTTON){
				XEle_RegEventCPP1((HELE)hBtn, XE_BUTTON_CHECK, &CWindow_Demo::OnButtonCheckRun);
				BOOL isCheck = XList_GetItemData(m_hList, pItem->index, lbk.run);
				XBtn_SetCheck((HELE)hBtn, isCheck);
			}


			//查看
			hBtn = XList_GetTemplateObject(m_hList, pItem->index, lbk.look, lbk.look);
			
			if (XC_GetObjectType(hBtn) == XC_BUTTON){
				XEle_RegEventCPP1((HELE)hBtn, XE_BNCLICK, &CWindow_Demo::OnEventBtnClickLook);
			}

			//脚本行数
			hBtn = XList_GetTemplateObject(m_hList, pItem->index, lbk.runnum, lbk.runnum);
			//xtrace("hBtn  %d   %d     %d\n", hBtn, XC_GetObjectType(hBtn), pItem->index);
			if (XC_GetObjectType(hBtn) == XC_RICHEDIT){
				XRichEdit_EnableEvent_XE_RICHEDIT_CHANGE((HELE)hBtn, TRUE);
				XEle_RegEventCPP1(hBtn, XE_RICHEDIT_CHANGE, &CWindow_Demo::OnRichEditChangeHS);
				XEle_RegEventCPP1(hBtn, XE_SETFOCUS, &CWindow_Demo::OnEventBtnClickRunNum);
				XEle_RegEventCPP(hBtn, XE_KILLFOCUS, &CWindow_Demo::OnEventBtnClickRunNum1);
			}
			//行脚数
			hBtn = XList_GetTemplateObject(m_hList, pItem->index, lbk.xjs, lbk.xjs);
			if (XC_GetObjectType(hBtn) == XC_RICHEDIT){
				XEle_RegEventCPP1((HELE)hBtn, XE_KILLFOCUS, &CWindow_Demo::OnEventBtnClickXJS);
				XRichEdit_EnableEvent_XE_RICHEDIT_CHANGE((HELE)hBtn, TRUE);
				XEle_RegEventCPP1(hBtn, XE_RICHEDIT_CHANGE, &CWindow_Demo::OnRichEditChangeXJS);
			}
			
			//XEle_RemoveEventCPP(m_hList, XE_LIST_TEMP_CREATE_END, &CWindow_Demo::OnListTemplateCreateEnd);
		}

		//		*pbHandled = TRUE;
		return 0;
	}
	//运行按钮
	int OnButtonCheckRun(HELE hEventEle, BOOL bCheck, BOOL *pbHandled)
	{
		//项目数
		int item = XList_GetItemIndexFromHXCGUI(m_hList, hEventEle);
		//setlistbool(item, lbk.run, !bCheck);
		if (bCheck){
			setRoot(item);
		}
		else{
			PostMessageA(winls[item].h, 52228, 3, 0);
		}
		//setlistbool(item, lbk.run, bCheck);
		XEle_RedrawEle(m_hList, true);
		
		//XEle_ShowEle(m_hButtonAJ1, false);
		//XEle_RedrawEle(m_hButtonAJ1, true);
		//setlistbool(item, lbk.run, true);
		xtrace("%d   %d\n", bCheck,getlistbool(item, lbk.run));
		XEle_RedrawEle(m_hList, true);
		return 0;
	}
	//查看
	int OnEventBtnClickLook(HELE hEventEle, BOOL *pbHandled)
	{
		//项目数
		int item = XList_GetItemIndexFromHXCGUI(m_hList, hEventEle);
		xtrace("%d   \n", item);
		if (winls[item].h > 0){
			if (IsIconic(winls[item].h)){
				PostMessageA(winls[item].h, 52228, 8, 7);
				setlisttext(item, lbk.look, "立");
				BringWindowToTop(winls[item].h);//置顶
			}
			else{
				PostMessageA(winls[item].h, 52228, 8, 6);
				setlisttext(item, lbk.look, "查");
			}
		}
		XEle_RedrawEle(m_hList, true);
		return 0;
	}
	//行数编辑框
	int OnEventBtnClickRunNum(HELE hEventEle, BOOL *pbHandled)
	{
		//项目数
		int item = XList_GetItemIndexFromHXCGUI(m_hList, hEventEle);
		RECT zb;

		XEle_GetRectLogic(hEventEle, &zb);
		XEle_RectClientToWndClient(hEventEle, &zb);

		//xtrace("%d   %d    %d   %d\n", zb.left, zb.right, zb.top, zb.bottom);
		zb.left = zb.right - 7;
		zb.right = zb.left + 40;
		zb.top -= 243;
		zb.bottom = zb.top+22;
		int t=XEle_SetRect(m_hButtonAJ1, &zb, true);

		//XEle_SetRectLogic(m_hButtonAJ1, &zb);
		//xtrace("%d   %d    %d   %d\n", zb.left, zb.right, zb.top, zb.bottom);

		//XEle_Move(m_hButtonAJ1, zb.left, zb.top, true, xc_adjustLayout_all);
		XEle_ShowEle(m_hButtonAJ1, true);
		XEle_RedrawEle(m_hButtonAJ1, true);
		//XEle_AdjustLayout(m_hList);
		onNum = item;
		isUpDate = item;
		return 0;
	}

	int OnEventBtnClickRunNum1(BOOL *pbHandled)
	{
		isUpDate = -1;
		return 0;
	}

	//行数编辑框--改变
	int OnRichEditChangeHS(HELE hele, BOOL *pbHandled)
	{
		wchar_t data[MAX_PATH] = { 0 };
		//本来应该用 下面这个函数获取文本长度，
		//然后new分配，这里为了减少代码，直接用固定的
		//XRichEdit_GetTextLength(hele);
		XRichEdit_GetText(hele, data, MAX_PATH*sizeof(wchar_t));

		int nIndex = XList_GetItemIndexFromHXCGUI(m_hList, hele);
		XAdTable_SetItemText(hAdapter, nIndex, lbk.runnum, data);

		return 0;
	}
	
	
	//按钮1
	int OnEventBtnClickAJ1(BOOL *pbHandled)
	{
		if (winls[onNum].h > 0 && onNum>=0){
			int num = _ttoi(getlisttext(onNum, lbk.runnum));
			if (num > 0)PostMessageA(winls[onNum].h, 52228, 1, num);
			else PostMessageA(winls[onNum].h, 52228, 1, 10000);
		}
		xtrace("%d    %d  %s\n", onNum, _ttoi(getlisttext(onNum, lbk.runnum)));
		if (XEle_IsShow(m_hButtonAJ1)){
			XEle_ShowEle(m_hButtonAJ1, false);
			XEle_RedrawEle(m_hButtonAJ1, true);
		}
		return 0;
	}
	
	int OnRButtonUp(UINT nFlags, POINT *pPt, BOOL *pbHandled)
	{
		int i = XList_GetSelectItem(m_hList);
		if (i >= 0){
			POINT pt = *pPt;
			//创建弹出菜单
			HMENUX hMenu = XMenu_Create();
			XMenu_AddItem(hMenu, 201, L"查看脚本");
			XMenu_AddItem(hMenu, 202, L"组队");
			XMenu_AddItem(hMenu, 203, L"清理背包");
			XMenu_AddItem(hMenu, 204, L"脚本加1");
			XMenu_AddItem(hMenu, 205, L"脚本减1");
			XMenu_AddItem(hMenu, 206, L"退出静修");


			::ClientToScreen(myHwnd, &pt);
			RECT pt1;
			XEle_GetRect(m_hList, &pt1);
			XMenu_Popup(hMenu, myHwnd, pt1.left + pt.x, pt1.top + pt.y);
		}
		return 0;
	}
	//弹出菜单
	int  OnWndMenuSelect1(int nID, BOOL *pBool)
	{
		int i = XList_GetSelectItem(m_hList);
		int runn = _ttoi(getlisttext(i, lbk.runnum));
		switch (nID){
		case 201://查看脚本
		{
					 CWindow_Demo1 CWindow_Demo1(runn, i);
		}
			break;
		case 202://组队
			::CreateThread(0, 0, toTeamThread, 0, 0, 0);
			break;
		case 203://清理背包
			if (winls[i].h > 0 && runn>0){
				PostMessageA(winls[i].h, 52228, 8, 5);
			}
			break;
		case 204://+1
			if (winls[i].h > 0 && runn>0){
				PostMessageA(winls[i].h, 52228, 1, runn+1);
			}
			break;
		case 205://-1
			if (winls[i].h > 0 && runn>0){
				PostMessageA(winls[i].h, 52228, 1, runn-1);
			}
			break;
		case 206://退出静修
			for (int j = 150; j < 400; j++){
				if (rumtext[j] == "Tag,退出静修"){
					PostMessageA(winls[i].h, 52228, 1, j + 1);
					return 0;
				}
			}
		}

		return 0;
	}

	//上号
	int OnEventBtnClickSH(BOOL *pbHandled)
	{
		string a = dm->EnumWindow(0, WindowsYXbt.c_str(), "QQSGWinClass", 1 + 2 + 4 + 8 + 16);
		vector<string> array;
		split(a, ",", array);

		int xh = 0;
		if (array.size() > 0){
			for (int i = 0; i < MAXWIN; i++){
				if (winls[i].h == (HWND)stoi (array[0])){
					xh = i;
					break;
				}
			}
			if (xh == 0){
				return 0;
			}
			CString n;
			int i = IntPut("输入登录", "输入要登录的序号", intToCstr(xh + getEditInt(m_EditXH)), n);
			//xtrace("%d   %d  %d\n", i, _ttoi(n), xh);
			if (i == 1){
				winls[xh].rootnum = _ttoi(n);
				setlisttext(xh, lbk.rootnum, n);
				
				::CreateThread(0, 0, toRoot, (LPVOID)xh, 0, 0);
			}
		}
		

		return 0;

	}

	//行脚数编辑列
	int OnEventBtnClickXJS(HELE hEventEle, BOOL *pbHandled){
		//项目数
		int item = XList_GetItemIndexFromHXCGUI(m_hList, hEventEle);
		CString name = getlisttext(item, lbk.name);
		//xtrace("%d    %d  %s\n", item, _ttoi(getlisttext(item, lbk.xjs)), name);
		if (name != ""&&name != "未登录"){
			setini(getlisttext(item, lbk.rootnum), name, PeiZhiXingJiao, getlisttext(item, lbk.xjs));
		}
		return 0;
	}
	//行脚数编辑列-  改变
	int OnRichEditChangeXJS(HELE hEventEle, BOOL *pbHandled){
		wchar_t data[MAX_PATH] = { 0 };
		XRichEdit_GetText(hEventEle, data, MAX_PATH*sizeof(wchar_t));
		int item = XList_GetItemIndexFromHXCGUI(m_hList, hEventEle);
		XAdTable_SetItemText(hAdapter, item, lbk.xjs, data);
		return 0;
	}


	//列表框被选择关按钮1
	int OnRButtonUpSELECT(int iItem, BOOL *pbHandled){
		if (XEle_IsShow(m_hButtonAJ1)){
			XEle_ShowEle(m_hButtonAJ1, false);
			XEle_RedrawEle(m_hButtonAJ1, true);
		}
		
		return 0;
	}
	//窗口大小改变
	int OnDestroySIZE(HWINDOW m_hWind, UINT nFlags, SIZE *pSize, BOOL *pbHandled){
		SIZE pt = *pSize;
		//xtrace("%d   %d  %d \n", nFlags,pt.cx, pt.cy);
		int h = (int)pt.cy - 20 ;
		RECT zb;
		zb.top = 243;
		zb.left = 7;
		zb.right = 536;
		zb.bottom = h;
		XEle_SetRect(m_hList, &zb, TRUE);
		//XEle_SetLayoutHeight(m_hList, layout_size_type_fixed, h);
		//XEle_SendEvent(m_hList, m_hButtonAJ1, WM_SIZE, 0, h);

		return 0;
	}
	
	int OnDestroy(HWINDOW m_hWind,BOOL* pbHandled)
	{

		RECT t;
		XWnd_GetClientRect(m_hWind, &t);
		variant_t x1, y1, x2, y2;
		dm->GetClientRect((int)myHwnd, &x1, &y1, &x2, &y2);
		RECT ab;
		GetWindowRect(myHwnd, &ab);
		if (ab.left > 0 && ab.top > 0){
			Output("oo,管理  窗口位置 %d   %d  %d", ab.left, ab.top, t.bottom);
			setini("pos", "x1", PeiZhiText, to_string(ab.left));
			setini("pos", "y1", PeiZhiText, to_string(ab.top));
			setini("pos", "h1", PeiZhiText, to_string(t.bottom));
		}
		
		//xtrace("%d   %s  %d   %d   \n", t.bottom, to_string((int)y1).c_str(), ((int)y1));
		return 0;
	}
};

int WINAPI _tWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPTSTR lpCmdLine, int nCmdShow)
{

	XInitXCGUI();

	CWindow_Demo  MyWindow;
	
	XRunXCGUI();

	XExitXCGUI();
	return TRUE;
}

