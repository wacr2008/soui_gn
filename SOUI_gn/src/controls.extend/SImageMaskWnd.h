#pragma once

namespace SOUI
{
    class SImageMaskWnd : public SImageWnd
    {
    SOUI_CLASS_NAME_DECL(SImageMaskWnd,L"imageMask")
    public:
        SImageMaskWnd(void);
        ~SImageMaskWnd(void);

    protected:
        void OnPaint(IRenderTarget *pRT);
        
        SOUI_MSG_MAP_DECL()

		SOUI_ATTRS_DECL()
        

        
        HRESULT OnAttrMask(const SStringW & strValue,BOOL bLoading);
        HRESULT OnAttrImage(const SStringW & strValue,BOOL bLoading);
        
        void MakeCacheApha(ISkinObj *pSkin);
        
    
        SStringW                m_strSkin;
        CAutoRefPtr<IBitmap>    m_bmpCache;
        CAutoRefPtr<IBitmap>    m_bmpMask;
        int                     m_iMaskChannel;
    };
}
