#ifndef Common_h__
#define Common_h__
/********************************************************************
created:	2015/07/15
created:	15:7:2015   17:37
filename: 	Common.h
file path:	WinMain
file base:	Common
file ext:	h
author:		 ��ɫ����

purpose:	�Ųʼ���ͷ�ļ�(����vc6 vs2008 2010 2013 2015 ��)
*********************************************************************/


#ifndef _UNICODE
#define _UNICODE
#define UNICODE
#endif

#define _CRT_SECURE_NO_WARNINGS

#include <windows.h>
#ifndef strcpy_s
#define strcpy_s strcpy
#endif

//�����Ųʽ�����ļ�
#pragma comment(lib, "XCGUI.lib")
#include "xcgui.h"

#ifndef _tWinMain
#ifdef _UNICODE
#define _tWinMain   wWinMain
#else
#define _tWinMain   WinMain
#endif
#endif

#ifndef _T
#define _T(x) L ## x
#endif

#ifndef wstring

#include <string>
using namespace std;
#endif

#endif // Common_h__