#include "SEdit2.h"

namespace SOUI
{
	SOUI_CLASS_NAME(EventKeyEnter, L"on_key_enter")

	SOUI_CLASS_NAME(SEdit2, L"edit2")

	SOUI_MSG_MAP_BEGIN(SEdit2)
		MSG_WM_KEYDOWN(OnKeyDown)
	SOUI_MSG_MAP_END()

    SEdit2::SEdit2(void)
    {
        m_evtSet.addEvent(EVENTID(EventKeyEnter));
    }

    SEdit2::~SEdit2(void)
    {
    }

    void SEdit2::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
    {
        if(nChar == VK_RETURN)
        {
            EventKeyEnter evt(this);
            FireEvent(evt);
        }else
        {
            SEdit::OnKeyDown(nChar,nRepCnt,nFlags);
        }
        
    }

}
