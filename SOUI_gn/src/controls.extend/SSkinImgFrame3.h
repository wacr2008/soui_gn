#pragma once
#include <core/sskin.h>

namespace SOUI
{
    /*usage
    <imgframe2 src="imgx:png_test{0,0,100,100}" xxx/>
    */
    class SSkinImgFrame3 : public SSkinImgFrame
    {
    SOUI_CLASS_NAME_DECL(SSkinImgFrame3,L"imgframe3")
    public:
        SSkinImgFrame3(void);
        ~SSkinImgFrame3(void);
        
        virtual SIZE GetSkinSize();
        
        virtual bool SetImage(IBitmap *pImg){return false;}
        
        SOUI_ATTRS_DECL()
        
    protected:
        LRESULT OnAttrSrc(const SStringW & strValue,BOOL bLoading);

        virtual void _Draw(IRenderTarget *pRT, LPCRECT rcDraw, DWORD dwState,BYTE byAlpha);

        CRect m_rcImg;
        CRect m_offset;
        SStringW m_strImgKey;
    };

}
