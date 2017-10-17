// dui-demo.cpp : main source file
//

#include "Stabctrl2.h"
#include "SAnimImg.h"
#include "MainDlg.h"
#include "com-cfg.h"

#include "core/SSkin.h"
#include "control/souictrls.h"
#include "layout/SouiLayout.h"
#include "SDateTimeEdit.h"
#define RES_TYPE 0
//#define RES_TYPE 0   //从文件中加载资源
//#define RES_TYPE 1   //从PE资源中加载UI资源

 
#define SYS_NAMED_RESOURCE _T("soui-sys-resource.dll")

using namespace SOUI;
class CSystemObjectRegister : public TObjRefImpl<ISystemObjectRegister>
{
public:
	void RegisterWindows(SObjectFactoryMgr *objFactory) override
	{
		objFactory->TplRegisterFactory<SWindow>();
		objFactory->TplRegisterFactory<SPanel>();
		objFactory->TplRegisterFactory<SStatic>();
		objFactory->TplRegisterFactory<SButton>();
		objFactory->TplRegisterFactory<SImageWnd>();
		objFactory->TplRegisterFactory<SProgress>();
		objFactory->TplRegisterFactory<SImageButton>();
		objFactory->TplRegisterFactory<SCheckBox>();
		objFactory->TplRegisterFactory<SIconWnd>();
		objFactory->TplRegisterFactory<SRadioBox>();
		objFactory->TplRegisterFactory<SLink>();
		objFactory->TplRegisterFactory<SGroup>();
		objFactory->TplRegisterFactory<SAnimateImgWnd>();
		objFactory->TplRegisterFactory<SScrollView>();
		objFactory->TplRegisterFactory<SToggle>();
		objFactory->TplRegisterFactory<SCaption>();
		objFactory->TplRegisterFactory<STabCtrl>();
		objFactory->TplRegisterFactory<STabPage>();
		objFactory->TplRegisterFactory<SHeaderCtrl>();
		objFactory->TplRegisterFactory<SListCtrl>();
	}

	void RegisterSkins(SObjectFactoryMgr *objFactory) override
	{
		objFactory->TplRegisterFactory<SSkinImgList>();
		objFactory->TplRegisterFactory<SSkinImgFrame>();
		objFactory->TplRegisterFactory<SSkinButton>();
		objFactory->TplRegisterFactory<SSkinScrollbar>();
	}

	void RegisterLayouts(SObjectFactoryMgr *objFactory) override
	{
		objFactory->TplRegisterFactory<SouiLayout>();
	}

	void RegisterInterpolator(SObjectFactoryMgr *objFactory) override
	{

	}
};

int WINAPI _tWinMain(HINSTANCE hInstance, HINSTANCE /*hPrevInstance*/, LPTSTR /*lpstrCmdLine*/, int /*nCmdShow*/)
{
    HRESULT hRes = OleInitialize(NULL);
    SASSERT(SUCCEEDED(hRes));
	(void)hRes;
    
    int nRet = 0; 
    
    SComMgr * pComMgr = new SComMgr;
    //将程序的运行路径修改到项目所在目录所在的目录
    TCHAR szCurrentDir[MAX_PATH]={0};
    GetModuleFileName( NULL, szCurrentDir, sizeof(szCurrentDir) );
    LPTSTR lpInsertPos = _tcsrchr( szCurrentDir, _T('\\') );
    _tcscpy(lpInsertPos+1,_T("\\..\\..\\src\\demos\\360"));
    SetCurrentDirectory(szCurrentDir);
        
    {

        CAutoRefPtr<SOUI::IImgDecoderFactory> pImgDecoderFactory;
        CAutoRefPtr<SOUI::IRenderFactory> pRenderFactory;
        pComMgr->CreateRender_GDI((IObjRef**)&pRenderFactory);
        pComMgr->CreateImgDecoder((IObjRef**)&pImgDecoderFactory);

        pRenderFactory->SetImgDecoderFactory(pImgDecoderFactory);

        SApplication *theApp=new SApplication(pRenderFactory,hInstance,L"360demo",new CSystemObjectRegister());
        
        theApp->RegisterWindowClass<STabPage2>();//注册STabPage2
        theApp->RegisterWindowClass<STabCtrl2>();//注册STabCtrl2
        theApp->RegisterWindowClass<SAnimImg>();//注册SAnimImg

		theApp->RegisterWindowClass<CDateTimeUI>();

        CAutoRefPtr<ITranslatorMgr> trans;
        pComMgr->CreateTranslator((IObjRef**)&trans);
        if(trans)
        {
            theApp->SetTranslator(trans);
            pugi::xml_document xmlLang;
            if(xmlLang.load_file(L"Translator/lang_cn.xml"))
            {
                CAutoRefPtr<ITranslator> langCN;
                trans->CreateTranslator(&langCN);
				pugi::xml_node node =xmlLang.child(L"language");
				langCN->Load(&node, 1);//1=LD_XML
                trans->InstallTranslator(langCN);
            }
        }
        	
        CAutoRefPtr<IResProvider>   pResProvider;
#if (RES_TYPE == 0)
        CreateResProvider(RES_FILE,(IObjRef**)&pResProvider);
        if(!pResProvider->Init((LPARAM)_T("uires"),0))
        {
            SASSERT(0);
            return 1;
        }
#else 
        CreateResProvider(RES_PE,(IObjRef**)&pResProvider);
        pResProvider->Init((WPARAM)hInstance,0);
#endif

        theApp->AddResProvider(pResProvider);
        
        //加载系统资源
        HMODULE hSysResource=LoadLibrary(SYS_NAMED_RESOURCE);
        if(hSysResource)
        {
            CAutoRefPtr<IResProvider> sysSesProvider;
            CreateResProvider(RES_PE,(IObjRef**)&sysSesProvider);
            sysSesProvider->Init((WPARAM)hSysResource,0);
            theApp->LoadSystemNamedResource(sysSesProvider);
        }
        // BLOCK: Run application
        {
            CMainDlg dlgMain;  
            dlgMain.Create(GetActiveWindow(),0,0,0,0);
            dlgMain.SendMessage(WM_INITDIALOG);
            dlgMain.CenterWindow(dlgMain.m_hWnd);
            dlgMain.ShowWindow(SW_SHOWNORMAL);
            nRet=theApp->Run(dlgMain.m_hWnd);
        }

        delete theApp;
    }


    delete pComMgr;
    OleUninitialize();
    return nRet;
}
