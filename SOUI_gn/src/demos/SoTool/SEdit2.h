#pragma once
#include <control/SRichEdit.h>
namespace SOUI
{
    class EventKeyEnter : public TplEventArgs<EventKeyEnter>
    {
    SOUI_CLASS_NAME_DECL(EventKeyEnter,L"on_key_enter")
    public:
        enum {EventID = EVT_EXTERNAL_BEGIN+500};
        EventKeyEnter(SObject *pSender):TplEventArgs<EventKeyEnter>(pSender){}
    };
    
    class SEdit2 : public SEdit
    {
    SOUI_CLASS_NAME_DECL(SEdit2,L"edit2")
    public:
        SEdit2(void);
        ~SEdit2(void);
        
    protected:
        void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
        SOUI_MSG_MAP_DECL()
        
    };
}
