/*
扩展了 SMcAdapterBase  
自己处理 ItemClick 等 5个 事件 且 设置了 bubbleup 不让 其他调用
这样就可以 点击 item里的按钮 而不会导致整个item 选中 
*/

#pragma once 
#include <helper/SAdapterBase.h>


// SMcListView 数据适配器 封装
class McListAdapterHandle : public SMcAdapterBase
{
public:
	McListAdapterHandle()
		: m_funItemClick(&McListAdapterHandle::OnItemClick, this)
		, m_funItemDbClick(&McListAdapterHandle::OnItemDbClick, this)
		, m_funItemRClick(&McListAdapterHandle::OnItemRClick, this)
		, m_funMouseHover(&McListAdapterHandle::OnMouseHover, this)
		, m_funMouseLeave(&McListAdapterHandle::OnMouseLeave, this)
		, m_pSelectItem(NULL)
	{
		
	}

    virtual ~McListAdapterHandle()
	{
	
	}
	// 设置 选中常驻  就是点击 空白处  不会 取消select
	void SetAlwaysSelect(SMCListView* pMcView)
	{
		
		if(NULL != pMcView)
		{
			pMcView->GetEventSet()->subscribeEvent(&McListAdapterHandle::OnMcViewEventChangeing, this);
		}
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
	//	auto ite = xmlTemplate.attribute(L"colorSelected");
	//	m_szSelectColor = ite.as_string();
	//	ite = L"#FFFFFF00";			// 设置成 透明 的  
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
		}

		auto eventItem = pItem->GetEventSet();
		
		eventItem->subscribeEvent(EventItemPanelClick::EventID, m_funItemClick);
		eventItem->subscribeEvent(EventItemPanelDbclick::EventID, m_funItemDbClick);
		eventItem->subscribeEvent(EventItemPanelRclick::EventID, m_funItemRClick);
		eventItem->subscribeEvent(EventItemPanelHover::EventID, m_funMouseHover);
		eventItem->subscribeEvent(EventItemPanelLeave::EventID, m_funMouseLeave);

		ShowView(nPosition, pItem);
	}
	bool OnMcViewEventChangeing(EventLVSelChanging* pEvt)
	{
		if(NULL == pEvt)
			return true;
		
		pEvt->bubbleUp = false;

		if(-1 == pEvt->iNewSel)				// 不能设置 -1 
			pEvt->bCancel = TRUE;

		return true;
	}
	bool OnItemClick(EventArgs* e)
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
				e->bubbleUp = false; // 只 处理 我这个就可以了 
				return true;
			}
		}

		m_nSelItem = nItem;

		ItemClick(m_nSelItem, pItem, pt);
		return true;

		//// 取消之前选中项 
		//if(NULL != m_pSelectItem)
		//	m_pSelectItem->SetAttribute(L"colorBkgnd", L"#FFFFFF00");
		//		
		//// 自己 设置 选中 背景色
		//pWindow->SetAttribute(L"colorBkgnd", m_szSelectColor);
		//
		//m_pSelectItem = pWindow;
		
	}
	
	bool OnItemDbClick(EventArgs* e)
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
	bool OnItemRClick(EventArgs* e)
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

	bool OnMouseHover(EventArgs* e)
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

	bool OnMouseLeave(EventArgs* e)
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
private:
	
	int														m_nSelItem;
	SWindow*											m_pSelectItem;
	SStringT												m_szSelectColor;


	MemberFunctionSlot<McListAdapterHandle, EventArgs>			m_funItemClick;
	MemberFunctionSlot<McListAdapterHandle, EventArgs>			m_funItemDbClick;
	MemberFunctionSlot<McListAdapterHandle, EventArgs>			m_funItemRClick;
	MemberFunctionSlot<McListAdapterHandle, EventArgs>			m_funMouseHover;
	MemberFunctionSlot<McListAdapterHandle, EventArgs>			m_funMouseLeave;
};
