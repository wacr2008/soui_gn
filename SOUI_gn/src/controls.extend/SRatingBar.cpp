
#include "SRatingBar.h"

namespace SOUI
{
	SOUI_CLASS_NAME(SRatingBar, L"ratingbar")

	SOUI_MSG_MAP_BEGIN(SRatingBar)
		MSG_WM_PAINT_EX(OnPaint)
	SOUI_MSG_MAP_END()

	SOUI_ATTRS_BEGIN(SRatingBar)
		ATTR_SKIN(L"starSkin", m_pStar, TRUE)
		ATTR_INT(L"starNum", m_nStars, TRUE)
		ATTR_FLOAT(L"value", m_fValue, TRUE)
	SOUI_ATTRS_END()

    SRatingBar::SRatingBar(void):m_pStar(NULL),m_nStars(5),m_fValue(0.0f)
    {
    }

    SRatingBar::~SRatingBar(void)
    {
    }

    void SRatingBar::OnPaint(IRenderTarget *pRT)
    {
        CRect rcClient = GetClientRect();
        int nWid = (int)(rcClient.Width()*m_fValue/m_nStars);
        CRect rcFore = rcClient;
        rcFore.right = rcFore.left + nWid;
        pRT->PushClipRect(rcFore);
        DrawStars(pRT,rcClient,TRUE);
        pRT->PopClip();
        CRect rcBack = rcClient;
        rcBack.left = rcFore.right;
        pRT->PushClipRect(rcBack);
        DrawStars(pRT,rcClient,FALSE);
        pRT->PopClip();
    }

    CSize SRatingBar::GetDesiredSize(LPCRECT pRcContainer)
    {
        SASSERT(m_pStar);
        CSize szStar = m_pStar->GetSkinSize();
        szStar.cx *= m_nStars;
        return szStar;
    }

    void SRatingBar::DrawStars(IRenderTarget *pRT,CRect rc,BOOL bForeground)
    {
        CSize szStar = rc.Size();
        szStar.cx/=m_nStars;
        CRect rcStar(rc.TopLeft(),szStar);
        
        for(int i=0;i<m_nStars;i++)
        {
            m_pStar->Draw(pRT,rcStar,bForeground?0:1);
            rcStar.OffsetRect(szStar.cx,0);
        }
    }

    void SRatingBar::SetValue(float fValue)
    {
        m_fValue = fValue;
        if(m_fValue>(float)m_nStars) m_fValue = (float)m_nStars;
        Invalidate();
    }

}
