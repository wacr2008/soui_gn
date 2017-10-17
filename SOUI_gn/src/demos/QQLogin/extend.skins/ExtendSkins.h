#pragma once

#include "core/SSkinObjBase.h"

namespace SOUI
{

    class SColorMask : public SSkinObjBase
    {
#define STATE_COUNT 4
        SOUI_CLASS_NAME_DECL(SColorMask, L"colormask")

            enum {
            ST_NORMAL = 0,
            ST_HOVER,
            ST_PUSHDOWN,
            ST_DISABLE,
        };

    public:
        SColorMask();
        virtual BOOL IgnoreState() { return FALSE; }
        virtual int  GetStates() { return STATE_COUNT; }
        virtual SIZE GetSkinSize() { return m_size; }

        void SetColors(COLORREF cr[4]);

    protected:
        virtual void _Draw(IRenderTarget *pRT, LPCRECT rcDraw, DWORD dwState, BYTE byAlpha);
        HRESULT      OnAttrMask(const SStringW & strValue, BOOL bLoading);
        void         MakeCacheApha();

        COLORREF    m_crStates[STATE_COUNT];
        SIZE        m_size;

        SOUI_ATTRS_DECL()

        //CAutoRefPtr<IBitmap> *  m_pBmpCaches;

        SStringW                m_strSkin;
        CAutoRefPtr<IBitmap>    m_bmpSkin;
        CAutoRefPtr<IBitmap>    m_bmpMask;
        CRect                   m_rcMargin;
        int                     m_iMaskChannel;
    };

};