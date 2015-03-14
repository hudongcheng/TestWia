// TestWIA.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <Windows.h>
#include <WIA.h>
//#include <Objbase.h>
#include <comdef.h>

#pragma comment(lib, "wiaguid.lib")

HRESULT CreateWiaDeviceManager(IWiaDevMgr2** ppWiaDevMgr)
{
	// Validate arguments
	if (NULL == ppWiaDevMgr)
	{
		return E_INVALIDARG;
	}

	// Initialize out variables
	*ppWiaDevMgr = NULL;

	// Create an instance of the device manager
	HRESULT hr = CoCreateInstance(CLSID_WiaDevMgr2, NULL, CLSCTX_LOCAL_SERVER, IID_IWiaDevMgr2, (void**)ppWiaDevMgr);

	// Return the result of creating the device manager
	return hr;
}


HRESULT CreateWiaDevice( IWiaDevMgr2 *pWiaDevMgr, BSTR bstrDeviceID, IWiaItem2 **ppWiaDevice ) 
{
	// Validate arguments
	if (NULL == pWiaDevMgr || NULL == bstrDeviceID || NULL == ppWiaDevice)
	{
		return E_INVALIDARG;
	}

	// Initialize out variables
	*ppWiaDevice = NULL;

	// Create the WIA Device
	HRESULT hr = pWiaDevMgr->CreateDevice(0, bstrDeviceID, ppWiaDevice );

	// Return the result of creating the device
	return hr;
}


HRESULT ScanFromDeviceDlg(IWiaDevMgr2 *pWiaDevMgr)
{
	if (NULL == pWiaDevMgr)
	{
		return E_INVALIDARG;
	}

	HRESULT hr;
	BSTR *bstrDeviceID = new BSTR[0];
	IWiaItem2 *pItemRoot = NULL;
	hr = pWiaDevMgr->SelectDeviceDlg(NULL, 0, 0, bstrDeviceID, &pItemRoot);
	
	if (S_OK == hr)
	{
		_bstr_t FolderName("f:\\temp\\");
		_bstr_t FileName("img");
		LONG x = 0L;
		BSTR *files = new BSTR[0];
		pItemRoot->DeviceDlg(0, NULL, FolderName, FileName, &x, &files, &pItemRoot);
		for(int i=0; i<x; i++)
		{
			wprintf(L"file name: %s\n", files[i]);
		}
		CoTaskMemFree(files);
	}
	//delete bstrDeviceID;
	return hr;
}

int _tmain(int argc, _TCHAR* argv[])
{
	CoInitialize(NULL);
	IWiaDevMgr2 *pWiaDevMgr = NULL;
	CreateWiaDeviceManager(&pWiaDevMgr);
	ScanFromDeviceDlg(pWiaDevMgr);
	return 0;
}

