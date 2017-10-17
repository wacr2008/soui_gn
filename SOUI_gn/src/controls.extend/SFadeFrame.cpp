
#include "SFadeFrame.h"

#define TIMER_SHOW  1
#define TIMER_HIDE  2

namespace SOUI{
	SOUI_CLASS_NAME(SFadeFrame, L"fadeframe")

	SOUI_ATTRS_BEGIN(SFadeFrame)
		ATTR_UINT(L"AniTime", m_nAniTime, FALSE)
		ATTR_UINT(L"DelayTime", m_nDelayTime, FALSE)
		ATTR_STRINGW(L"targetName", m_strTargetName, FALSE)
		ATTR_UINT(L"showAlpha", m_byAlphaShow, FALSE)
		ATTR_INT(L"initShow", m_bInitShow, FALSE)
	SOUI_ATTRS_END()
		
	SOUI_MSG_MAP_BEGIN(SFadeFrame)
		MSG_WM_MOUSEHOVER(OnMouseHover)
		MSG_WM_MOUSELEAVE(OnMouseLeave)
		MSG_WM_TIMER_EX(OnTimer)
		MSG_WM_CREATE(OnCreate)
	SOUI_MSG_MAP_END()

    SFadeFrame::SFadeFrame(void):m_nAniTime(200),m_nDelayTime(200),m_byAlphaShow(0xFF),m_byAlphaCurrent(0xFF),m_bInitShow(TRUE)
    {
        m_style.m_bTrackMouseEvent = true;
    }

    SFadeFrame::~SFadeFrame(void)
    {
    }

    void SFadeFrame::OnMouseLeave()
    {
        SWindow::OnMouseLeave();
        KillTimer(TIMER_SHOW);
        SetTimer(TIMER_HIDE,m_nDelayTime);
    }

    void SFadeFrame::OnMouseHover(WPARAM wParam, CPoint ptPos)
    {
        SWindow::OnMouseHover(wParam,ptPos);
        KillTimer(TIMER_HIDE);
        SetTimer(TIMER_SHOW,m_nDelayTime);
    }

    void SFadeFrame::OnTimer(char cTimerID)
    {
        KillTimer(cTimerID);
        if(cTimerID == TIMER_SHOW)
        {
            if(m_byAlphaCurrent == m_byAlphaShow) return;
            m_nAlphaBegin = m_byAlphaCurrent;
            m_nAlphaEnd = m_byAlphaShow;
        }else if(cTimerID == TIMER_HIDE)
        {
            if(m_byAlphaCurrent == 0) return;
            m_nAlphaBegin = m_byAlphaCurrent;
            m_nAlphaEnd = 0;
        }
        SAnimator::Start(m_nAniTime);
        GetContainer()->RegisterTimelineHandler(this);
    }

    void SFadeFrame::OnAnimatorState(int percent)
    {
        if(percent == SAnimator::PER_END)
        {
            SetChildrenAlpha((BYTE)m_nAlphaEnd);
            GetContainer()->UnregisterTimelineHandler(this);
        }else
        {
            BYTE byAlpha = (BYTE)(m_nAlphaBegin + (m_nAlphaEnd - m_nAlphaBegin)* percent/100);
            SetChildrenAlpha(byAlpha);
        }
    }

    void SFadeFrame::OnNextFrame()
    {
        SAnimator::Update();
    }

    void SFadeFrame::SetChildrenAlpha(BYTE byAlpha)
    {
        SWindow *pTarget = GetRoot()->FindChildByName(m_strTargetName);
        if(pTarget)
        {
            if(pTarget->IsVisible(FALSE) ^ (byAlpha>0))
                pTarget->SetVisible(byAlpha>0,TRUE);
            pTarget->SetAttribute(L"alpha",SStringW().Format(L"%d",byAlpha));
        }
        m_byAlphaCurrent = byAlpha;
    }

    int SFadeFrame::OnCreate(LPVOID)
    {
        SWindow::OnCreate(NULL);
        if(!m_bInitShow) OnTimer(TIMER_HIDE);
        return 0;
    }

}