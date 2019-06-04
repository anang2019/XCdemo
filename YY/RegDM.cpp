#include "stdafx.h"
#include "RegDM.h"

Dm::Idmsoft* GetDmbject()
{
	typedef  HRESULT(__stdcall * PDllGetClassObject)(REFCLSID, REFIID, LPVOID*);
	PDllGetClassObject  pDllGetClassObject = NULL;
	HMODULE  h = ::LoadLibrary(L"dm.dll");
	if (h == 0)
	{
		return  NULL;
	}
	pDllGetClassObject = (PDllGetClassObject)GetProcAddress(h, "DllGetClassObject");
	if (pDllGetClassObject == NULL)
	{
		return  NULL;
	}
	IClassFactory* pcf = NULL;
	HRESULT hr = pDllGetClassObject(__uuidof(Dm::dmsoft), IID_IClassFactory, (void**)&pcf);
	if (SUCCEEDED(hr) && pcf != NULL)
	{
		DWORD* PGetRes = NULL;
		hr = pcf->CreateInstance(NULL, IID_IUnknown, (void**)&PGetRes);
		if (SUCCEEDED(hr) && PGetRes != NULL)
		{
			pcf->Release();
			return (Dm::Idmsoft*)PGetRes;
		}
		if (pcf != NULL)
		{
			pcf->Release();
		}
	}
	if (pcf != NULL)
	{
		pcf->Release();
	}
	return  NULL;
}
