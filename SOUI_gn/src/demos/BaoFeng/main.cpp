#include "MainWnd.h"
#include "resource.h"
#include <com-loader.hpp>


#ifdef _DEBUG
#define COM_IMGDECODER  _T("imgdecoder-wicd.dll")
#define COM_RENDER_GDI  _T("render-gdid.dll")
#define SYS_NAMED_RESOURCE _T("soui-sys-resourced.dll")
#else
#define COM_IMGDECODER  _T("imgdecoder-wic.dll")
#define COM_RENDER_GDI  _T("render-gdi.dll")
#define SYS_NAMED_RESOURCE _T("soui-sys-resource.dll")
#endif

using namespace SOUI;


int WINAPI _tWinMain(HINSTANCE hInstance, HINSTANCE /*hPrevInstance*/, LPTSTR /*lpstrCmdLine*/, int /*nCmdShow*/)
{
	HRESULT hRes = OleInitialize(NULL);
	(void)hRes;
	SASSERT(SUCCEEDED(hRes));

	int nRet = 0; 

	SComLoader imgDecLoader;
	SComLoader renderLoader;
	SComLoader transLoader;

	CAutoRefPtr<SOUI::IImgDecoderFactory> pImgDecoderFactory;
	CAutoRefPtr<SOUI::IRenderFactory> pRenderFactory;
	imgDecLoader.CreateInstance(COM_IMGDECODER, (IObjRef**)&pImgDecoderFactory);
	renderLoader.CreateInstance(COM_RENDER_GDI, (IObjRef**)&pRenderFactory);

	pRenderFactory->SetImgDecoderFactory(pImgDecoderFactory);

	SApplication *theApp = new SApplication(pRenderFactory, hInstance);

	//将程序的运行路径修改到项目所在目录所在的目录 
	SStringT strResDir = theApp->GetAppDir();
	strResDir += _T("\\..\\..\\src\\demos\\BaoFeng");
	SetCurrentDirectory(strResDir);
	//SOUI系统总是从appdir去查找资源
	theApp->SetAppDir(strResDir);

	{
		 
		HMODULE hSysResource=LoadLibrary(SYS_NAMED_RESOURCE);
		if(hSysResource)
		{
			CAutoRefPtr<IResProvider> sysSesProvider;
			CreateResProvider(RES_PE,(IObjRef**)&sysSesProvider);
			sysSesProvider->Init((WPARAM)hSysResource,0);
			theApp->LoadSystemNamedResource(sysSesProvider);
		}


		CAutoRefPtr<IResProvider>   pResProvider;
		CreateResProvider(RES_FILE,(IObjRef**)&pResProvider);
		if(!pResProvider->Init((LPARAM)_T("uires"),0))
		{
			SASSERT(0);
			return 1;
		}
		theApp->AddResProvider(pResProvider); 

		{//在这里加入主窗口运行代码
			CMainWnd wndMain;  
			wndMain.Create(GetActiveWindow(),0,0,0,0);
			wndMain.SendMessage(WM_INITDIALOG);
			wndMain.CenterWindow(wndMain.m_hWnd);
			wndMain.ShowWindow(SW_SHOWNORMAL);
			nRet=theApp->Run(wndMain.m_hWnd);
			//程序结束

		}

		delete theApp;
	}

	OleUninitialize();
	return nRet;
}