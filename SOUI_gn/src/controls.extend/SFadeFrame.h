#pragma once

#include "SAnimator.h"

namespace SOUI
{
    class SFadeFrame : public SWindow, public SAnimator, public ITimelineHandler
    {
        SOUI_CLASS_NAME_DECL(SFadeFrame,L"fadeframe")
    public:
        SFadeFrame(void);
        ~SFadeFrame(void);

    protected:        
        void SetChildrenAlpha(BYTE byAlpha);
        
        virtual void OnAnimatorState(int percent);
        virtual void OnNextFrame();

        SOUI_ATTRS_DECL()
		SOUI_MSG_MAP_DECL()

        void OnMouseHover(WPARAM wParam, CPoint ptPos);
        void OnMouseLeave();
        void OnTimer(char cTimerID);
        int OnCreate(LPVOID);

    protected:
        DWORD  m_nAniTime;
        DWORD  m_nDelayTime;
        
        SStringW m_strTargetName;
        int     m_nAlphaBegin,m_nAlphaEnd;
        BYTE    m_byAlphaCurrent;
        BYTE    m_byAlphaShow;
        BOOL    m_bInitShow;
    };

}

