
#include "SRadioBox2.h"

namespace SOUI
{
	SOUI_CLASS_NAME(SRadioBox2, L"radio2")

	SOUI_MSG_MAP_BEGIN(SRadioBox2)
		MSG_WM_PAINT_EX(OnPaint)
	SOUI_MSG_MAP_END()

	SOUI_ATTRS_BEGIN(SRadioBox2)
		ATTR_SKIN(L"iconSkin", m_pIcon, TRUE)
		ATTR_POINT(L"iconPos", m_ptIcon, TRUE)
		ATTR_INT(L"textOffset", m_nTextOffset, TRUE)
	SOUI_ATTRS_END()

    SRadioBox2::SRadioBox2(void):m_pIcon(NULL),m_nTextOffset(0)
    {
    }

    SRadioBox2::~SRadioBox2(void)
    {
    }

    void SRadioBox2::OnPaint(IRenderTarget *pRT)
    {
        if(m_pSkin)
        {
            CRect rc;
            GetClientRect(&rc);
            int nState = 0;
            if(GetState() & WndState_Check) nState = 2;
            else if(GetState() & WndState_PushDown) nState = 2;
            else if(GetState() & WndState_Hover) nState = 1;
            
            m_pSkin->Draw(pRT,rc,nState);
        }
        if(m_pIcon)
        {
            CRect rcIcon=GetClientRect();
            rcIcon.OffsetRect(m_ptIcon);
            rcIcon=CRect(rcIcon.TopLeft(),m_pIcon->GetSkinSize());
            m_pIcon->Draw(pRT,rcIcon,IIF_STATE3(GetState(),0,1,2));
        }
        SWindow::OnPaint(pRT);
    }

}
