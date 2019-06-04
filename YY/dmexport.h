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


//【通过验证码本地路径一键获取结果】

DM_API STRINGTYPE    WINAPI RecYZM(STRINGTYPE  strYZMPath,STRINGTYPE strVcodeUser,STRINGTYPE  strVcodePass);


//【报告验证码错误】

DM_API void       WINAPI ReportError(STRINGTYPE strVcodeUser,STRINGTYPE strDaMaWorker);
DM_API int       WINAPI  ReportError_A(STRINGTYPE strVcodeUser,STRINGTYPE strDaMaWorker);

//【通过传送字节获取验证码结果】

DM_API STRINGTYPE    WINAPI RecByte(BYTE* byte,int  len,STRINGTYPE strVcodeUser,STRINGTYPE  strVcodePass);


//【获取剩余点数】

DM_API STRINGTYPE    WINAPI GetUserInfo(STRINGTYPE strUser,STRINGTYPE strPass);
DM_API STRINGTYPE    WINAPI GetUserInfo_A(STRINGTYPE strUser,STRINGTYPE strPass,STRINGTYPE strSoftkey);


//【作者分成函数,通过传送字节获取验证码结果】

DM_API STRINGTYPE    WINAPI RecByte_A(BYTE* byte,int  len,STRINGTYPE strVcodeUser,STRINGTYPE  strVcodePass,STRINGTYPE strSoftkey);


//【作者分成函数】

DM_API STRINGTYPE   WINAPI RecYZM_A(STRINGTYPE  strYZMPath,STRINGTYPE strVcodeUser,STRINGTYPE  strVcodePass,STRINGTYPE strSoftkey);
