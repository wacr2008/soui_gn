#pragma once

#include <control/SCmnCtrl.h>

namespace SOUI
{
    class SRadioBox2 : public SRadioBox
    {
    SOUI_CLASS_NAME_DECL(SRadioBox2,L"radio2")
    public:
        SRadioBox2(void);
        ~SRadioBox2(void);
        
    protected:
        virtual CSize GetDesiredSize(LPCRECT pRcContainer)
        {
            if(m_pSkin) return m_pSkin->GetSkinSize();
            else return SWindow::GetDesiredSize(pRcContainer);
        }
        virtual void GetTextRect(LPRECT pRect)
        {
            SWindow::GetTextRect(pRect);
            pRect->left+=m_nTextOffset;
        }
        virtual void DrawFocus(IRenderTarget *pRT)
        {
        }

    protected:       
        void OnPaint(IRenderTarget *pRT);

        SOUI_MSG_MAP_DECL()

		SOUI_ATTRS_DECL()

        ISkinObj *  m_pIcon;
        CPoint      m_ptIcon;
        int         m_nTextOffset;

    };

}
