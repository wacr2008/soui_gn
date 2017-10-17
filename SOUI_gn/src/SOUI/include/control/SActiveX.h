#pragma once
#include "core/SWnd.h"
#include "activex/flash10t.tlh"
#include <mshtmhst.h>

namespace SOUI
{

    class SOUI_EXP SActiveX : public SWindow
    {
        friend class SAxContainerImpl;
    public:
        SOUI_CLASS_NAME_DECL(SActiveX, L"activex")
        explicit SActiveX();
        ~SActiveX() override;

        IUnknown * GetIUnknown();
    protected:
        virtual void OnAxActivate(IUnknown *pUnknwn){}

        int OnCreate(LPVOID);
        void OnSize(UINT nType, CSize size);
        void OnPaint(IRenderTarget *pRT);
        LRESULT OnMouseEvent(UINT uMsg,WPARAM wp,LPARAM lp);
        LRESULT OnKeyEvent(UINT uMsg,WPARAM wp,LPARAM lp);
        void OnShowWindow(BOOL bShow, UINT nStatus);

		UINT OnGetDlgCode() override;

		BOOL IsFocusable() override;

        HRESULT OnAttrClsid(const SStringW & strValue,BOOL bLoading);

        SOUI_MSG_MAP_DECL() 

        SOUI_ATTRS_DECL() 

        virtual void OnInitActiveXFinished(){}

        BOOL InitActiveX();
        void SetActiveXVisible(BOOL bVisible);
        void SetExternalUIHandler(IDocHostUIHandler *pUiHandler);
    protected:
        SAxContainerImpl * m_axContainer;
        CLSID    m_clsid;
        DWORD    m_clsCtx;
        BOOL        m_bDelayInit;
    };

    class SOUI_EXP SFlashCtrl : public SActiveX
    {
    public:
        SOUI_CLASS_NAME_DECL(SFlashCtrl, L"flash")
        SFlashCtrl();
		~SFlashCtrl() override;

        ShockwaveFlashObjects::IShockwaveFlash* GetFlashInterface()  const
        {
            return flash_;
        }

        BOOL Play(LPCWSTR pszUrl);
    protected:
        void OnAxActivate(IUnknown *pUnknwn) override;

        HRESULT OnAttrUrl(const SStringW & strValue,BOOL bLoading);
        
        SOUI_ATTRS_DECL() 

        SStringW m_strUrl;

        SComQIPtr<ShockwaveFlashObjects::IShockwaveFlash> flash_;
    };


    
}

