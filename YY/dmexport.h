#pragma once

/*
#ifdef DM_EXPORT
#define DM_API  extern "C" __declspec(dllexport)
#else
#define DM_API  extern "C" __declspec(dllimport)
#endif
*/
#define DM_API  extern "C"

#define  STRINGTYPE char*
/*
#if _MSC_VER==1200
#define  STRINGTYPE CString
#else
#define  STRINGTYPE char*
#endif
*/


//��ͨ����֤�뱾��·��һ����ȡ�����

DM_API STRINGTYPE    WINAPI RecYZM(STRINGTYPE  strYZMPath,STRINGTYPE strVcodeUser,STRINGTYPE  strVcodePass);


//��������֤�����

DM_API void       WINAPI ReportError(STRINGTYPE strVcodeUser,STRINGTYPE strDaMaWorker);
DM_API int       WINAPI  ReportError_A(STRINGTYPE strVcodeUser,STRINGTYPE strDaMaWorker);

//��ͨ�������ֽڻ�ȡ��֤������

DM_API STRINGTYPE    WINAPI RecByte(BYTE* byte,int  len,STRINGTYPE strVcodeUser,STRINGTYPE  strVcodePass);


//����ȡʣ�������

DM_API STRINGTYPE    WINAPI GetUserInfo(STRINGTYPE strUser,STRINGTYPE strPass);
DM_API STRINGTYPE    WINAPI GetUserInfo_A(STRINGTYPE strUser,STRINGTYPE strPass,STRINGTYPE strSoftkey);


//�����߷ֳɺ���,ͨ�������ֽڻ�ȡ��֤������

DM_API STRINGTYPE    WINAPI RecByte_A(BYTE* byte,int  len,STRINGTYPE strVcodeUser,STRINGTYPE  strVcodePass,STRINGTYPE strSoftkey);


//�����߷ֳɺ�����

DM_API STRINGTYPE   WINAPI RecYZM_A(STRINGTYPE  strYZMPath,STRINGTYPE strVcodeUser,STRINGTYPE  strVcodePass,STRINGTYPE strSoftkey);
