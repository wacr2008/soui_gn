/*
SListView 的数据适配器
扩展了 SAdapterBase  
自己处理 ItemClick 等 5个 事件 且 设置了 bubbleup 不让 其他调用
这样就可以 点击 item里的按钮 而不会导致整个item 选中 
*/

#pragma once 
#include <helper/SAdapterBase.h>


// SListView 数据适配器 封装
class LvAdapterHandle : public SAdapterBase
{
public:
	LvAdapterHandle(SListView*	pOwner)
		: m_pOwner(pOwner)
		, m_evtSlot_ItemClick(&LvAdapterHandle::OnEventItemClick, this)
		, m_evtSlot_ItemDbClick(&LvAdapterHandle::OnEventItemDbClick, this)
		, m_evtSlot_ItemRClick(&LvAdapterHandle::OnEventItemRClick, this)
		, m_evtSlot_ItemHover(&LvAdapterHandle::OnEventItemHover, this)
		, m_evtSlot_ItemLeave(&LvAdapterHandle::OnEventItemLeave, this)
	{
		//assert(m_pOwner);
		if(NULL != m_pOwner)
		{
			m_pOwner->GetEventSet()->subscribeEvent(&LvAdapterHandle::OnEventLvSelChangeing, this);
		}
	}

    virtual ~LvAdapterHandle()
	{
	
	}
	
	void SelectItem(int nItem, bool bNotify=false)
	{
		m_pOwner->SetSel(nItem, bNotify ? TRUE : FALSE);
	}
	int GetSelectItem()
	{
		return m_pOwner->GetSel();
	}
protected:
	// 这个用来 显示 数据  在 getView 里 调用 这里去掉了  模版加载  
	virtual void ShowView(int nItem, SWindow* pItem)
	{

	}
	// item click 回调 可以
	virtual void ItemClick(int nItem, SItemPanel* pItem, const CPoint& pt)
	{

	}
	// 
	virtual void ItemDbClick(int nItem, SItemPanel* pItem, const CPoint& pt)
	{

	}
	virtual void ItemRClick(int nItem, SItemPanel* pItem, const CPoint& pt)
	{

	}
	virtual void ItemHover(int nItem, SItemPanel* pItem, const CPoint& pt)
	{

	}
	virtual void ItemLeave(int nItem, SItemPanel* pItem)
	{

	}
	// 判断 是否 点击item 用来 item 里 有按钮等  控件 判断
	virtual bool IsItemClick(int nItem, const SStringT& szSndName)
	{
		return true;
	}
protected:    
	virtual void InitByTemplate(pugi::xml_node xmlTemplate)
	{
		//auto ite = xmlTemplate.attribute(L"colorSelected");
		//m_szSelectColor = ite.as_string();
		//ite = L"#FFFFFF00";			// 设置成 透明 的  
	}
	      
	//virtual SIZE getViewDesiredSize(int position, SOUI::SWindow *pItem, LPCRECT prcContainer)
	//{

	//}
	/*virtual int getItemViewType(int position)
	{

	}*/
	//virtual SStringT GetColumnName(int iCol) const
	//{
	//	return L"col_nick";
	//}
	virtual void getView(int nPosition, SWindow* pItem, pugi::xml_node xmlTemplate)
	{		
		if(0 == pItem->GetChildrenCount())
		{
			pItem->InitFromXml(xmlTemplate);

			auto eventItem = pItem->GetEventSet();
			eventItem->subscribeEvent(EventItemPanelClick::EventID, m_evtSlot_ItemClick);
			eventItem->subscribeEvent(EventItemPanelDbclick::EventID, m_evtSlot_ItemDbClick);
			eventItem->subscribeEvent(EventItemPanelRclick::EventID, m_evtSlot_ItemRClick);
			eventItem->subscribeEvent(EventItemPanelHover::EventID, m_evtSlot_ItemHover);
			eventItem->subscribeEvent(EventItemPanelLeave::EventID, m_evtSlot_ItemLeave);
		}

		
		
		

		ShowView(nPosition, pItem);
	}
	bool OnEventLvSelChangeing(EventLVSelChanging* pEvt)
	{
		if(NULL == pEvt)
			return true;
		
		pEvt->bubbleUp = false;

		if(-1 == pEvt->iNewSel)				// 不能设置 -1 
			pEvt->bCancel = TRUE;

		return true;
	}
	bool OnEventItemClick(EventArgs* e)
	{
		EventItemPanelClick* pEvt = sobj_cast<EventItemPanelClick>(e);
		if(NULL == pEvt) return true;

		SItemPanel* pItem = sobj_cast<SItemPanel>(pEvt->sender);
		if(NULL == pItem) return true;
			
		int nItem = static_cast<int>(pItem->GetItemIndex());

		CPoint pt;
		pt.x = GET_X_LPARAM(pEvt->lParam);
		pt.y = GET_Y_LPARAM(pEvt->lParam);
		
		// 判断 点击 的 是否是  删除按钮
		SWND hHover = pItem->SwndFromPoint(pt, FALSE);
		SWindow* pChild = SWindowMgr::GetWindow(hHover);
	
		if(NULL != pChild)			// 如果 有 消息 就 不选中
		{
			if(!IsItemClick(nItem, pChild->GetName())	)
			{
				e->bubbleUp = false; // 设置了   点击事件 只在 这里处理 SListView 不处理 
				return true;
			}
		}
		
		ItemClick(nItem, pItem, pt);
				
		return true;

	}
	
	bool OnEventItemDbClick(EventArgs* e)
	{
		EventItemPanelDbclick* pEvt = sobj_cast<EventItemPanelDbclick>(e);
		if(NULL == pEvt) return true;

		SItemPanel* pItem = sobj_cast<SItemPanel>(pEvt->sender);
		if(NULL == pItem) return true;

		int nItem = static_cast<int>(pItem->GetItemIndex());

		CPoint pt;
		pt.x = GET_X_LPARAM(pEvt->lParam);
		pt.y = GET_Y_LPARAM(pEvt->lParam);

		ItemDbClick(nItem, pItem, pt);

		return true;
	}
	bool OnEventItemRClick(EventArgs* e)
	{
		EventItemPanelRclick* pEvt = sobj_cast<EventItemPanelRclick>(e);
		if(NULL == pEvt) return true;

		SItemPanel* pItem = sobj_cast<SItemPanel>(pEvt->sender);
		if(NULL == pItem) return true;

		int nItem = static_cast<int>(pItem->GetItemIndex());
		
		CPoint pt;
		pt.x = GET_X_LPARAM(pEvt->lParam);
		pt.y = GET_Y_LPARAM(pEvt->lParam);

		ItemRClick(nItem, pItem, pt);

		return true;
	}

	bool OnEventItemHover(EventArgs* e)
	{
		EventItemPanelHover* pEvt = sobj_cast<EventItemPanelHover>(e);
		if(NULL == pEvt)
			return true;
		
		SItemPanel* pItem = sobj_cast<SItemPanel>(pEvt->sender);
		if(NULL == pItem) return true;

		int nItem = static_cast<int>(pItem->GetItemIndex());

		CPoint pt;
		pt.x = GET_X_LPARAM(pEvt->lParam);
		pt.y = GET_Y_LPARAM(pEvt->lParam);

		ItemHover(nItem, pItem, pt);

		return true;
	}

	bool OnEventItemLeave(EventArgs* e)
	{
		EventItemPanelLeave* pEvt = sobj_cast<EventItemPanelLeave>(e);
		if(NULL == pEvt)
			return true;
		
		SItemPanel* pItem = sobj_cast<SItemPanel>(pEvt->sender);
		if(NULL == pItem) return true;

		int nItem = static_cast<int>(pItem->GetItemIndex());
		
		ItemLeave(nItem, pItem);

		return true;
	}

protected:
	SListView*						m_pOwner;
private:	
	MemberFunctionSlot<LvAdapterHandle, EventArgs>			m_evtSlot_ItemClick;
	MemberFunctionSlot<LvAdapterHandle, EventArgs>			m_evtSlot_ItemDbClick;
	MemberFunctionSlot<LvAdapterHandle, EventArgs>			m_evtSlot_ItemRClick;
	MemberFunctionSlot<LvAdapterHandle, EventArgs>			m_evtSlot_ItemHover;
	MemberFunctionSlot<LvAdapterHandle, EventArgs>			m_evtSlot_ItemLeave;
};
