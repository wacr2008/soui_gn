// dui-demo.cpp : main source file
//

#include "stdafx.h"
#include "MainDlg.h"
#include "..\controls.extend\SRadioBox2.h"
#include "..\controls.extend\SVscrollbar.h"
#include "SouiRealWndHandler.h"
//从PE文件加载，注意从文件加载路径位置
#define RES_TYPE 1
// #define RES_TYPE 1  //从PE资源中加载UI资源

#ifdef _DEBUG
#define SYS_NAMED_RESOURCE _T("soui-sys-resourced.dll")
#else
#define SYS_NAMED_RESOURCE _T("soui-sys-resource.dll")
#endif


//定义唯一的一个R,UIRES对象,ROBJ_IN_CPP是resource.h中定义的宏。
ROBJ_IN_CPP
	
/*
    提示：如果运行提示找不到libvlc.dll，注意把SOUI目录下的third-part/vlc/bin目录下的文件复制到程序运行目录。
*/
int WINAPI _tWinMain(HINSTANCE hInstance, HINSTANCE /*hPrevInstance*/, LPTSTR lpstrCmdLine, int /*nCmdShow*/)
{
    HRESULT hRes = OleInitialize(NULL);
    SASSERT(SUCCEEDED(hRes));

    int nRet = 0;
    

    //将程序的运行路径修改到项目所在目录所在的目录
    TCHAR szCurrentDir[MAX_PATH] = { 0 };
    GetModuleFileName(NULL, szCurrentDir, sizeof(szCurrentDir));
    LPTSTR lpInsertPos = _tcsrchr(szCurrentDir, _T('\\'));
	*lpInsertPos=0;

	SStringT strExePath = szCurrentDir;
	SStringT strResPath = strExePath + _T("\\..\\demos\\FrogPlay");
    SetCurrentDirectory(strResPath);
	
	SComMgr *pComMgr = new SComMgr;
	{
        BOOL bLoaded=FALSE;
        CAutoRefPtr<SOUI::IImgDecoderFactory> pImgDecoderFactory;
        CAutoRefPtr<SOUI::IRenderFactory> pRenderFactory;
        bLoaded = pComMgr->CreateRender_Skia((IObjRef**)&pRenderFactory);
        SASSERT_FMT(bLoaded,_T("load interface [render] failed!"));
        bLoaded=pComMgr->CreateImgDecoder((IObjRef**)&pImgDecoderFactory);
        SASSERT_FMT(bLoaded,_T("load interface [%s] failed!"),_T("imgdecoder"));

        pRenderFactory->SetImgDecoderFactory(pImgDecoderFactory);
        SApplication *theApp = new SApplication(pRenderFactory, hInstance);

		//加载系统资源
		HMODULE hSysResource=LoadLibrary(SYS_NAMED_RESOURCE);
		if(hSysResource)
		{
			CAutoRefPtr<IResProvider> sysSesProvider;
			CreateResProvider(RES_PE,(IObjRef**)&sysSesProvider);
			sysSesProvider->Init((WPARAM)hSysResource,0);
			theApp->LoadSystemNamedResource(sysSesProvider);
		}

        CAutoRefPtr<IResProvider>   pResProvider;
		theApp->RegisterWindowClass<SRadioBox2>();//注册RadioBox2
		theApp->RegisterSkinClass<SSkinVScrollbar>();//注册纵向滚动条皮肤
#if (RES_TYPE == 0)
        CreateResProvider(RES_FILE, (IObjRef**)&pResProvider);
        if (!pResProvider->Init((LPARAM)_T("uires"), 0))
        {
            SASSERT(0);
            return 1;
        }
#else 
        CreateResProvider(RES_PE, (IObjRef**)&pResProvider);
        pResProvider->Init((WPARAM)hInstance, 0);
#endif

		theApp->InitXmlNamedID(namedXmlID,ARRAYSIZE(namedXmlID),TRUE);
        theApp->AddResProvider(pResProvider);

		//设置真窗口处理接口
		CSouiRealWndHandler * pRealWndHandler = new CSouiRealWndHandler();
		theApp->SetRealWndHandler(pRealWndHandler);
		pRealWndHandler->Release();
		//设置提示窗口布局
		CTipWnd::SetLayout(L"layout:dlg_tip");
        // BLOCK: Run application
        {
            CMainDlg dlgMain;
            dlgMain.Create(GetActiveWindow());
            dlgMain.SendMessage(WM_INITDIALOG);
            dlgMain.CenterWindow(dlgMain.m_hWnd);
            dlgMain.ShowWindow(SW_SHOWNORMAL);
            nRet = theApp->Run(dlgMain.m_hWnd);
        }

        delete theApp;
    }
    
    delete pComMgr;
    
    OleUninitialize();
    return nRet;
}
