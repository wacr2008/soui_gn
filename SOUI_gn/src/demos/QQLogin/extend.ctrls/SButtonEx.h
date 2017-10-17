#pragma once
#include "control\SCmnCtrl.h"

namespace SOUI
{

    class SButtonEx : public SButton
    {
        SOUI_CLASS_NAME_DECL(SButtonEx, L"buttonex")
    public:
        SButtonEx(void);
        ~SButtonEx(void);

    protected:
        void OnPaint(IRenderTarget *pRT);
        void DrawSkin(ISkinObj * pSkin, IRenderTarget *pRT);
        virtual void DrawText(IRenderTarget *pRT, LPCTSTR pszBuf, int cchText, LPRECT pRect, UINT uFormat);

        SOUI_MSG_MAP_DECL()
		SOUI_ATTRS_DECL()

        HRESULT OnAttrImage(const SStringW & strValue, BOOL bLoading);


        SIZE       m_sizeTextShift;
        ISkinObj * m_pbkgndSkin;
    };
};