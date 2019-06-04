#include "stdafx.h"
#include<vector> //向量
#include<iostream>




using   namespace   std;

//左键双击---------------------------------------------------------------
void liftDclock(HWND h, int x, int y, int t=20){
	int zb = x + y * 65536;
	PostMessageA(h, 515, 32769, zb);
	PostMessageA(h, 514, 32769, zb);
	Sleep(t);
}

void LiftClock(HWND h, int x, int y, int t = 20){
	int zb = x + y * 65536;
	PostMessageA(h, 513, 32769, zb);
	PostMessageA(h, 514, 32769, zb);
	Sleep(t);
}

void KeyPress(HWND h,int k, int time = 20){
	PostMessageA(h, 256, k, 0);
	Sleep(rand() % 16 + 8);
	PostMessageA(h, 257, k, 0);
	Sleep(time);
}

//按键消息-----------------------------------------------------------------

//分割文本
void split(string str1, string fg, vector<string> &array)
{
	int a = 0;
	int b = str1.find(fg, a);
	while (b >= 0)
	{
		array.push_back(str1.substr(a, b - a));
		a = b + fg.length();
		//Output("%d %d %s\n", b,i,list[i]);
		b = str1.find(fg, a);
	}
	string en = str1.substr(a, str1.length() - a);
	if (en != "")
	array.push_back(en);
}

void Output(const char * strOutputString, ...)
{
	char strBuffer[4096] = { 0 };
	va_list vlArgs;
	va_start(vlArgs, strOutputString);

	//_vsnprintf(strBuffer, sizeof(strBuffer)-1, strOutputString, vlArgs);

	vsprintf(strBuffer,strOutputString,vlArgs);
	va_end(vlArgs);

	CString bb = strBuffer;

	OutputDebugString(bb);
}

//读配置
string getini(string a, string b, string ls, string nothing){

	CString  szPassBuff;
	GetPrivateProfileString((CString)a.c_str(), (CString)b.c_str(), (CString)nothing.c_str(), szPassBuff.GetBuffer(MAX_PATH), MAX_PATH, (CString)ls.c_str());
	szPassBuff.ReleaseBuffer();
	return (string)CW2A(szPassBuff);
}

CString getini1(string a, string b, string ls, string nothing){

	CString  szPassBuff;


	GetPrivateProfileString((CString)a.c_str(), (CString)b.c_str(), (CString)nothing.c_str(), szPassBuff.GetBuffer(MAX_PATH), MAX_PATH, (CString)ls.c_str());
	szPassBuff.ReleaseBuffer();
	return szPassBuff;
}

CString getini(CString a, CString b, CString ls, CString nothing){

	CString  szPassBuff;
	GetPrivateProfileString(a, b, nothing, szPassBuff.GetBuffer(MAX_PATH), MAX_PATH, ls);
	szPassBuff.ReleaseBuffer();
	return szPassBuff;
}

int setini(string a, string b, string ls, string text){
	//CString a="";

	WritePrivateProfileString((CString)a.c_str(), (CString)b.c_str(), (CString)text.c_str(), (CString)ls.c_str());
	return 0;
}

int setini(CString a, CString b, string ls, CString text){
	//CString a="";

	WritePrivateProfileString(a, b, text, (CString)ls.c_str());
	return 0;
}

//int To CString
CString intToCstr(int n){
	CString str = "";
	str.Format(_T("%d"), n);
	return str;
}

CString FloatToCstr(float n){
	CString str = "";
	str.Format(_T("%.1f"), n);
	return str;
}

//结束进程
bool myKillProcess(HWND h){
	DWORD pid=0;
	GetWindowThreadProcessId(h, &pid);
	if (pid == 0)return true;

	return TerminateProcess(OpenProcess(1, 0, (DWORD)pid), 0);
}

DWORD string_to_hex(const string str1)

{
	char str[20];

	for (unsigned i = 0; i < str1.size() + 1; i++)
	{
		str[i] = str1[i];
	}

	unsigned    i = 0;
	char  *index = "0123456789abcdef";				//记录查找索引
	char  *temp = strdup(str);						//copy str
	char  *lower = strlwr(temp);
	char  *find = NULL;
	DWORD dword = 0;

	if (strstr(lower, "0x")) {						//检测"ox"标记
		strcpy(lower, lower + 2);
	}


	while (i < strlen(lower)) {

		find = strchr(index, lower[i]);

		dword = dword ^ (((DWORD)(find - index)) << ((strlen(lower) - 1 - i) * 4));

		i++;
	}

	return dword;

}

//16转10
unsigned long HextoDec(const unsigned char *hex, int length)
{
	int i;
	unsigned long rslt = 0;
	for (i = 0; i < length; i++)
	{
		rslt += (unsigned long)(hex[i]) << (8 * (length - 1 - i));

	}
	return rslt;
}

//汉字转asc
int HZtoAsc(int t){
	char hex[10];
	//转换成16进制并强制显示8个字符长度

	sprintf_s(hex, 10, "%.2x", t);
	string b = hex;
	b = b.substr(b.size() - 2, 2);
	unsigned char Hex[1] = { string_to_hex(b) };
	return  HextoDec(Hex, 1);

}
//向窗口写文本
void toWindowsText(HWND h,string t){
	int len = t.length();
	const char *p = t.c_str();

	for (int i = 0; i < len; i++){
		short aa = *(p + i);
		if (aa < 0){
			aa = HZtoAsc(aa);
			//cout << i << "1111: " << HZtoAsc((short)*(p + i)) << endl;
		}
		SendMessageA(h, 258, aa, 1);
		//Output("oo,%d窗口 字符  %d", winII, aa);
		Sleep(10);
	}
}

// 判断文件是否存在
BOOL IsFileExist(string csFile)
{
	DWORD dwAttrib = GetFileAttributes((LPCWSTR)csFile.c_str());
	return INVALID_FILE_ATTRIBUTES != dwAttrib && 0 == (dwAttrib & FILE_ATTRIBUTE_DIRECTORY);
}

//提升进程权限
BOOL EnablePriv()
{
	HANDLE hToken;
	OpenProcessToken(GetCurrentProcess(), TOKEN_ADJUST_PRIVILEGES, &hToken);

		TOKEN_PRIVILEGES tkp;

		LookupPrivilegeValueA(NULL, "SeShutdownPrivilege", &tkp.Privileges[0].Luid);//修改进程权限
		tkp.PrivilegeCount = 1;
		tkp.Privileges[0].Attributes = SE_PRIVILEGE_ENABLED;
		AdjustTokenPrivileges(hToken, FALSE, &tkp, sizeof tkp, NULL, NULL);//通知系统修改进程权限

		return((GetLastError() == ERROR_SUCCESS));

	//return TRUE;
}

//打开程序
void openProgram(CString name,CString cmd="",bool show=true)
{
	STARTUPINFO stStartUpInfo = { sizeof(stStartUpInfo) };
	PROCESS_INFORMATION pProcessInfo;
	ZeroMemory(&stStartUpInfo, sizeof(STARTUPINFO));
	stStartUpInfo.cb = sizeof(STARTUPINFO);
	stStartUpInfo.dwFlags = STARTF_USESHOWWINDOW;
	if (show)
		stStartUpInfo.wShowWindow = 1;//窗口显示为0不显示 
	else
		stStartUpInfo.wShowWindow = 0;
	CreateProcess(name, (LPWSTR)(LPCTSTR)cmd, NULL, NULL, false, NULL, NULL, NULL, &stStartUpInfo, &pProcessInfo);

}

//复制文件
bool copyFile(char* src, char* dst)
{
	ifstream in(src, ios::binary);
	ofstream out(dst, ios::binary);
	if (!in.is_open()) {
		return false;
	}
	if (!out.is_open()) {
		return false;
	}
	if (src == dst) {
		return false;
	}
	char buf[2048];
	long long totalBytes = 0;
	while (in)
	{
		//read从in流中读取2048字节，放入buf数组中，同时文件指针向后移动2048字节
		//若不足2048字节遇到文件结尾，则以实际提取字节读取。
		in.read(buf, 2048);
		//gcount()用来提取读取的字节数，write将buf中的内容写入out流。
		out.write(buf, in.gcount());
		totalBytes += in.gcount();
	}
	in.close();
	out.close();
	return true;
}

//替换
string replace(string t, string a, string b){
	int a1 = t.find(a);
	return t.replace(a1, a.length(), b);
}


//将wstring转换成string  
string wstring2string(wstring wstr)
{
	string result;
	//获取缓冲区大小，并申请空间，缓冲区大小事按字节计算的  
	int len = WideCharToMultiByte(CP_ACP, 0, wstr.c_str(), wstr.size(), NULL, 0, NULL, NULL);
	char* buffer = new char[len + 1];
	//宽字节编码转换成多字节编码  
	WideCharToMultiByte(CP_ACP, 0, wstr.c_str(), wstr.size(), buffer, len, NULL, NULL);
	buffer[len] = '\0';
	//删除缓冲区并返回值  
	result.append(buffer);
	delete[] buffer;
	return result;
}
