#include "souistd.h"
#include <event/EventSet.h>
#include <event/Events.h>

namespace SOUI
{
    //////////////////////////////////////////////////////////////////////////
    // SEvent

    SEvent::SEvent(DWORD dwEventID,LPCWSTR pszEventName) :m_dwEventID(dwEventID),m_strEventName(pszEventName)
    {

    }

    SEvent::~SEvent()
    {
        for(UINT i=0;i<m_evtSlots.GetCount();i++)
        {
            delete m_evtSlots[i];
        }
        m_evtSlots.RemoveAll();
    }


    bool SEvent::subscribe( const ISlotFunctor& slot )
    {
        if(findSlotFunctor(slot) != -1) return false;
        m_evtSlots.Add(slot.Clone());
        return true;
    }

    bool SEvent::unsubscribe( const ISlotFunctor& slot )
    {
        int idx=findSlotFunctor(slot);
        if(idx==-1) return false;

        delete m_evtSlots[idx];
        m_evtSlots.RemoveAt(idx);
        return true;
    }

    int SEvent::findSlotFunctor( const ISlotFunctor& slot )
    {
        for(UINT i=0;i<m_evtSlots.GetCount();i++)
        {
            if(m_evtSlots[i]->Equal(slot))
            {
                return i;
            }
        }
        return -1;
    }


    void SEvent::operator()(EventArgs& args)
    {
        // execute all subscribers, updating the 'handled' state as we go
        for (int i=(int)m_evtSlots.GetCount()-1;i>=0; i--)
        {//the latest event handler handles the event first.
            BOOL bHandled = (*m_evtSlots[i])(&args);
            if(bHandled)
            {
                ++args.handled;
                if(!args.bubbleUp) break;
            }
        }
    }

    void SEvent::SetScriptHandler(const SStringA & strScriptHandler)
    {
        m_strScriptHandler = strScriptHandler;
    }

    SOUI::SStringA SEvent::GetScriptHandler() const
    {
        return m_strScriptHandler;
    }

    SOUI::SStringW SEvent::GetName() const
    {
        return m_strEventName;
    }

    DWORD SEvent::GetID()
    {
        return m_dwEventID;
    }

    //////////////////////////////////////////////////////////////////////////
    // SEventSet
    SEventSet::SEventSet(void):m_bMuted(FALSE)
    {
    }

    SEventSet::~SEventSet(void)
    {
        removeAllEvents();
    }

    SEvent * SEventSet::GetEventObject(const DWORD dwEventID )
    {
        for(UINT i=0;i<m_evtArr.GetCount();i++)
        {
            if(m_evtArr[i]->GetID()==dwEventID) return m_evtArr[i];
        }
        return NULL;
    }

    void SEventSet::FireEvent(EventArgs& args )
    {
        // find event object
        SEvent* ev = GetEventObject(args.GetID());

        // fire the event if present and set is not muted
        if ((ev != 0) && !m_bMuted)
        {
            (*ev)(args);
        }
    }

    void SEventSet::addEvent( const DWORD dwEventID ,LPCWSTR pszEventHandlerName)
    {
        if(!isEventPresent(dwEventID))
        {
            m_evtArr.Add(new SEvent(dwEventID,pszEventHandlerName));
        }
    }

    void SEventSet::removeEvent( const DWORD dwEventID )
    {
        for(UINT i=0;i<m_evtArr.GetCount();i++)
        {
            if(m_evtArr[i]->GetID()==dwEventID)
            {
                delete m_evtArr[i];
                m_evtArr.RemoveAt(i);
                return;
            }
        }
    }

    bool SEventSet::isEventPresent( const DWORD dwEventID )
    {
        return GetEventObject(dwEventID)!=NULL;
    }

    void SEventSet::removeAllEvents( void )
    {
        for(UINT i=0;i<m_evtArr.GetCount();i++)
        {
            delete m_evtArr[i];
        }
        m_evtArr.RemoveAll();
    }

    bool SEventSet::subscribeEvent( const DWORD dwEventID, const ISlotFunctor & subscriber )
    {
        if(!isEventPresent(dwEventID)) return false;
        return GetEventObject(dwEventID)->subscribe(subscriber);
    }

    bool SEventSet::unsubscribeEvent( const DWORD dwEventID, const ISlotFunctor & subscriber )
    {
        if(!isEventPresent(dwEventID)) return false;
        return GetEventObject(dwEventID)->unsubscribe(subscriber);
    }

    bool SEventSet::setEventScriptHandler( const SStringW & strEventName,const SStringA strScriptHandler )
    {
        for(UINT i=0;i<m_evtArr.GetCount();i++)
        {
            if(m_evtArr[i]->GetName() == strEventName)
            {
                m_evtArr[i]->SetScriptHandler(strScriptHandler);
                return true;
            }
        }
        return false;
    }

    SStringA SEventSet::getEventScriptHandler( const SStringW & strEventName ) const
    {
        for(UINT i=0;i<m_evtArr.GetCount();i++)
        {
            if(m_evtArr[i]->GetName() == strEventName)
            {
                return m_evtArr[i]->GetScriptHandler();
            }
        }
        return "";
    }

	SOUI_CLASS_NAME(EventArgs, L"eventargs")

	EventArgs::EventArgs(SObject *pSender)
		: bubbleUp(true)
		, handled(0)
		, sender(pSender)
	{
		idFrom = pSender->GetID();
		nameFrom = pSender->GetName();
	}

	EventArgs::~EventArgs()
	{

	}

	int EventCmnArgs:: GetID() const 
	{ 
		return nID; 
	}

	SOUI_CLASS_NAME(EventInit, L"on_init")

	SOUI_CLASS_NAME(EventExit, L"on_exit")

	SOUI_CLASS_NAME(EventTimer, L"on_timer")

	SOUI_CLASS_NAME(EventSwndCreate, L"on_create")

	SOUI_CLASS_NAME(EventSwndDestroy, L"on_destroy")

	SOUI_CLASS_NAME(EventSwndSize, L"on_size")

	SOUI_CLASS_NAME(EventSwndStateChanged, L"on_state_changed")

	SOUI_CLASS_NAME(EventSwndVisibleChanged, L"on_visible_changed")

	SOUI_CLASS_NAME(EventSwndMouseLeave, L"on_mouse_leave")

	SOUI_CLASS_NAME(EventSwndMouseHover, L"on_mouse_hover")

	SOUI_CLASS_NAME(EventItemPanelRclick, L"on_itemparem_rclick")

	SOUI_CLASS_NAME(EventItemPanelDbclick, L"on_itempanel_dbclick")

	SOUI_CLASS_NAME(EventItemPanelClick, L"on_itempanel_click")

	SOUI_CLASS_NAME(EventItemPanelHover, L"on_itempanel_hover")

	SOUI_CLASS_NAME(EventItemPanelLeave, L"on_itempanel_leave")

	SOUI_CLASS_NAME(EventLButtonDown, L"on_mouse_lbutton_down")

	SOUI_CLASS_NAME(EventLButtonUp, L"on_mouse_lbutton_up")

	SOUI_CLASS_NAME(EventCmd, L"on_command")

	SOUI_CLASS_NAME(EventCtxMenu, L"on_conext_menu")

	SOUI_CLASS_NAME(EventSetFocus, L"on_set_focus")

	SOUI_CLASS_NAME(EventKillFocus, L"on_kill_focus")

	SOUI_CLASS_NAME(EventScrollViewOriginChanged, L"on_scrollview_origin_changed")

	SOUI_CLASS_NAME(EventScrollViewSizeChanged, L"on_scrollview_size_changed")

	SOUI_CLASS_NAME(EventScroll, L"on_scroll")

	SOUI_CLASS_NAME(EventOfEvent, L"on_event_of_event")

	SOUI_CLASS_NAME(EventOfPanel, L"on_event_of_panel")

	SOUI_CLASS_NAME(EventTabSelChanging, L"on_tab_sel_changing")

	SOUI_CLASS_NAME(EventTabSelChanged, L"on_tab_sel_changed")

	SOUI_CLASS_NAME(EventTabItemHover, L"on_tab_item_hover")

	SOUI_CLASS_NAME(EventTabItemLeave, L"on_tab_item_leave")

	SOUI_CLASS_NAME(EventLBSelChanging, L"on_listbox_sel_changing")

	SOUI_CLASS_NAME(EventLBSelChanged, L"on_listbox_sel_changed")

	SOUI_CLASS_NAME(EventLBDbClick, L"on_listbox_item_dbclick")

	SOUI_CLASS_NAME(EventLVSelChanged, L"on_listview_select_changed")

	SOUI_CLASS_NAME(EventLVSelChanging, L"on_listview_select_changing")

	SOUI_CLASS_NAME(EventTVSelChanged, L"on_treeview_select_changed")

	SOUI_CLASS_NAME(EventTVSelChanging, L"on_treeview_select_changing")

	SOUI_CLASS_NAME(EventRENotify, L"on_richedit_notify")

	SOUI_CLASS_NAME(EventREMenu, L"on_richedit_menu")

	SOUI_CLASS_NAME(EventSliderPos, L"on_slider_pos")

	SOUI_CLASS_NAME(EventHeaderClick, L"on_header_click")

	SOUI_CLASS_NAME(EventHeaderItemChanging, L"on_header_item_changing")

	SOUI_CLASS_NAME(EventHeaderItemChanged, L"on_header_item_changed")

	SOUI_CLASS_NAME(EventHeaderItemSwap, L"on_header_item_swap")

	SOUI_CLASS_NAME(EventCBSelChange, L"on_combobox_sel_change")

	SOUI_CLASS_NAME(EventCBDropdown, L"on_combobox_dropdown")

	SOUI_CLASS_NAME(EventLCSelChanging, L"on_listctrl_sel_changing")

	SOUI_CLASS_NAME(EventLCSelChanged, L"on_listctrl_sel_changed")

	SOUI_CLASS_NAME(EventLCDbClick, L"on_listctrl_item_dbclick")

	SOUI_CLASS_NAME(EventLCItemDeleted, L"on_listctrl_del_item")

	SOUI_CLASS_NAME(EventCalendarSelDay, L"on_calendar_sel_day")

	SOUI_CLASS_NAME(EventCalendarSetDate, L"on_calendar_set_date")

	SOUI_CLASS_NAME(EventCalendarExChanged, L"on_calendarex_changed")

	SOUI_CLASS_NAME(EventDateTimeChanged, L"on_datetime_changed")

	SOUI_CLASS_NAME(EventTCSelChanging, L"on_treectrl_sel_changing")

    SOUI_CLASS_NAME(EventTCSelChanged, L"on_treectrl_sel_changed")

    SOUI_CLASS_NAME(EventTCCheckState, L"on_treectrl_item_check")

    SOUI_CLASS_NAME(EventTCExpand, L"on_treectrl_item_expand")

    SOUI_CLASS_NAME(EventTCDbClick, L"on_treectrl_item_dbclick")

    SOUI_CLASS_NAME(EventSpinValue2String, L"on_spin_value2string")

    SOUI_CLASS_NAME(EventSplitPaneMoved, L"on_split_pane_moved")

    SOUI_CLASS_NAME(EventAnimateStart, L"on_animate_start")

    SOUI_CLASS_NAME(EventAnimateStop, L"on_animate_stop")

    SOUI_CLASS_NAME(EventSelectMenu, L"on_select_menu")

    SOUI_CLASS_NAME(EventSetHotKey, L"on_hot_key_set_event")


	EventTimer::EventTimer(SObject *pSender, UINT _uID) :TplEventArgs<EventTimer>(pSender), uID(_uID) 
	{
	}

	EventSwndSize::EventSwndSize(SObject *pSender, CSize _szWnd) :TplEventArgs<EventSwndSize>(pSender), szWnd(_szWnd)
	{
	}

	EventSwndStateChanged::EventSwndStateChanged(SObject *pSender) :TplEventArgs<EventSwndStateChanged>(pSender)
	{
	}

	EventItemPanelRclick::EventItemPanelRclick(SObject *pSender, WPARAM wp, LPARAM lp) :TplEventArgs<EventItemPanelRclick>(pSender), wParam(wp), lParam(lp)
	{
	}

	EventItemPanelDbclick::EventItemPanelDbclick(SObject *pSender, WPARAM wp, LPARAM lp) :TplEventArgs<EventItemPanelDbclick>(pSender), wParam(wp), lParam(lp) 
	{
	}
	
	EventItemPanelClick::EventItemPanelClick(SObject *pSender, WPARAM wp, LPARAM lp) :TplEventArgs<EventItemPanelClick>(pSender), wParam(wp), lParam(lp) 
	{
	}

	EventItemPanelHover::EventItemPanelHover(SObject *pSender, WPARAM wp, LPARAM lp) :TplEventArgs<EventItemPanelHover>(pSender), wParam(wp), lParam(lp) 
	{
	}

	EventItemPanelLeave::EventItemPanelLeave(SObject *pSender) :TplEventArgs<EventItemPanelLeave>(pSender) 
	{
	}

	EventLButtonDown::EventLButtonDown(SObject *pSender) :TplEventArgs<EventLButtonDown>(pSender) 
	{
	}

	EventLButtonUp::EventLButtonUp(SObject *pSender) :TplEventArgs<EventLButtonUp>(pSender) 
	{
	}

	EventCmd::EventCmd(SObject *pSender) :TplEventArgs<EventCmd>(pSender) 
	{
	}

	EventCtxMenu::EventCtxMenu(SObject *pSender) :TplEventArgs<EventCtxMenu>(pSender), bCancel(FALSE) 
	{
	}

	EventSetFocus::EventSetFocus(SObject *pSender) :TplEventArgs<EventSetFocus>(pSender) 
	{
	}

	EventKillFocus::EventKillFocus(SObject *pSender) :TplEventArgs<EventKillFocus>(pSender) 
	{
	}

	EventScrollViewOriginChanged::EventScrollViewOriginChanged(SObject *pSender) :TplEventArgs<EventScrollViewOriginChanged>(pSender) 
	{
	}
	
	EventScrollViewSizeChanged::EventScrollViewSizeChanged(SObject *pSender) :TplEventArgs<EventScrollViewSizeChanged>(pSender) 
	{
	}

	EventScroll::EventScroll(SObject *pSender) :TplEventArgs<EventScroll>(pSender) 
	{
	}

	EventOfEvent::EventOfEvent(SObject *pSender, EventArgs *_pOrgEvt)
		:TplEventArgs<EventOfEvent>(pSender)
		, pOrgEvt(_pOrgEvt)
	{
	}

	EventOfPanel::EventOfPanel(SObject * pSender, SItemPanel *_pPanel, EventArgs *_pOrgEvt)
		: TplEventArgs<EventOfPanel>(pSender)
		, pPanel(_pPanel)
		, pOrgEvt(_pOrgEvt)
	{

	}

	EventTabSelChanging::EventTabSelChanging(SObject *pSender) :TplEventArgs<EventTabSelChanging>(pSender), bCancel(FALSE) 
	{
	}

	EventTabSelChanged::EventTabSelChanged(SObject *pSender) :TplEventArgs<EventTabSelChanged>(pSender) 
	{
	}

	EventTabItemHover::EventTabItemHover(SObject *pSender) :TplEventArgs<EventTabItemHover>(pSender) 
	{
	}

	EventTabItemLeave::EventTabItemLeave(SObject *pSender) :TplEventArgs<EventTabItemLeave>(pSender) 
	{
	}
	
	EventLBSelChanging::EventLBSelChanging(SObject *pSender) :TplEventArgs<EventLBSelChanging>(pSender), bCancel(FALSE) 
	{

	}
	
	EventLBSelChanged::EventLBSelChanged(SObject *pSender) :TplEventArgs<EventLBSelChanged>(pSender) 
	{
	}

	EventLBDbClick::EventLBDbClick(SObject *pSender) :TplEventArgs<EventLBDbClick>(pSender) 
	{
	}

	EventLVSelChanged::EventLVSelChanged(SObject *pSender)
		:TplEventArgs<EventLVSelChanged>(pSender)
	{
	}

	EventLVSelChanging::EventLVSelChanging(SObject *pSender)
		:TplEventArgs<EventLVSelChanging>(pSender), bCancel(FALSE)
	{

	}

	EventTVSelChanged::EventTVSelChanged(SObject *pSender)
		:TplEventArgs<EventTVSelChanged>(pSender) 
	{
	}

	EventTVSelChanging::EventTVSelChanging(SObject *pSender)
		:TplEventArgs<EventTVSelChanging>(pSender), bCancel(FALSE) 
	{
	}

	EventRENotify::EventRENotify(SObject *pSender) :TplEventArgs<EventRENotify>(pSender) 
	{
	}

	EventREMenu::EventREMenu(SObject *pSender) :TplEventArgs<EventREMenu>(pSender) 
	{
	}

	EventSliderPos::EventSliderPos(SObject *pSender) :TplEventArgs<EventSliderPos>(pSender) 
	{
	}

	EventHeaderClick::EventHeaderClick(SObject *pSender) :TplEventArgs<EventHeaderClick>(pSender) 
	{
	}

	EventHeaderItemChanging::EventHeaderItemChanging(SObject *pSender) :TplEventArgs<EventHeaderItemChanging>(pSender) 
	{
	}

	EventHeaderItemChanged::EventHeaderItemChanged(SObject *pSender) :TplEventArgs<EventHeaderItemChanged>(pSender) 
	{
	}

	EventHeaderItemSwap::EventHeaderItemSwap(SObject *pSender) :TplEventArgs<EventHeaderItemSwap>(pSender) 
	{
	}

	EventCBSelChange::EventCBSelChange(SObject *pSender, int _nCurSel) :TplEventArgs<EventCBSelChange>(pSender), nCurSel(_nCurSel) 
	{
	}

	EventCBDropdown::EventCBDropdown(SObject *pSender) :TplEventArgs<EventCBDropdown>(pSender) 
	{

	}

	EventLCSelChanging::EventLCSelChanging(SObject *pSender) :TplEventArgs<EventLCSelChanging>(pSender), bCancel(FALSE) 
	{
	}

	EventLCSelChanged::EventLCSelChanged(SObject *pSender) :TplEventArgs<EventLCSelChanged>(pSender) 
	{
	}

	EventLCDbClick::EventLCDbClick(SObject *pSender) :TplEventArgs<EventLCDbClick>(pSender)
	{
	}

	EventLCItemDeleted::EventLCItemDeleted(SObject *pSender) :TplEventArgs<EventLCItemDeleted>(pSender) 
	{
	}

	EventCalendarSelDay::EventCalendarSelDay(SObject *pSender) :TplEventArgs<EventCalendarSelDay>(pSender) 
	{
	}
	
	EventCalendarSetDate::EventCalendarSetDate(SObject *pSender) :TplEventArgs<EventCalendarSetDate>(pSender) 
	{
	}

	EventCalendarExChanged::EventCalendarExChanged(SObject *pSender) :TplEventArgs<EventCalendarExChanged>(pSender) 
	{
	}

	EventDateTimeChanged::EventDateTimeChanged(SObject *pSender) :TplEventArgs<EventDateTimeChanged>(pSender) 
	{
	}

	EventTCSelChanging::EventTCSelChanging(SObject *pSender) :TplEventArgs<EventTCSelChanging>(pSender), bCancel(FALSE) 
	{
	}

	EventTCSelChanged::EventTCSelChanged(SObject *pSender) :TplEventArgs<EventTCSelChanged>(pSender) 
	{
	}

	EventTCCheckState::EventTCCheckState(SObject *pSender) :TplEventArgs<EventTCCheckState>(pSender) 
	{
	}

	EventTCExpand::EventTCExpand(SObject *pSender) :TplEventArgs<EventTCExpand>(pSender) 
	{
	}

	EventTCDbClick::EventTCDbClick(SObject *pSender)
		:TplEventArgs<EventTCDbClick>(pSender)
		, bCancel(FALSE)
	{
	}

	EventSpinValue2String::EventSpinValue2String(SObject *pSender)
		:TplEventArgs<EventSpinValue2String>(pSender)
	{
	}

	EventSpinValue2String::~EventSpinValue2String()
	{

	}

	EventSplitPaneMoved::EventSplitPaneMoved(SObject *pSender)
		:TplEventArgs<EventSplitPaneMoved>(pSender)
	{
	}

	EventAnimateStart::EventAnimateStart(SObject *pSender)
		:TplEventArgs<EventAnimateStart>(pSender)
	{
	}

	EventAnimateStop::EventAnimateStop(SObject *pSender)
		:TplEventArgs<EventAnimateStop>(pSender)
	{
	}
	
	EventSelectMenu::EventSelectMenu(SObject *pSender) :TplEventArgs<EventSelectMenu>(pSender)
	{
	}

    EventSetHotKey::EventSetHotKey(SObject *pSender) :TplEventArgs<EventSetHotKey>(pSender) 
    {

    } 
}//end of namespace