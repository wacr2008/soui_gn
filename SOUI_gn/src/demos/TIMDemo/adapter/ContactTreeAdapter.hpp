#pragma once 
#include <helper/SAdapterBase.h>
#include <map>
#include <list>


struct ContactTreeInfo
{
	int					nType;				// 用来区分  两种 布局
	UINT				uId;
	SStringT			sName;
	SStringT			sContent;
};

class ContactTreeAdapter : public STreeAdapterBase<ContactTreeInfo*>
{
public:
	ContactTreeAdapter(STreeView* pOwner)
		: m_pOwner(pOwner)
		, m_nGroupItemHeight(30)
		, m_nDataItemHeight(54)
		, m_evtSlot_ToggleClick(&ContactTreeAdapter::OnEventItemToggleClick, this)
		, m_evtSlot_ItemClick(&ContactTreeAdapter::OnEventItemClick, this)
		, m_evtSlot_ItemDbClick(&ContactTreeAdapter::OnEventItemDbClick, this)
		, m_callBackItemClick(nullptr)
		, m_callBackItemDbClick(nullptr)
	{
#if 0
		for (int u=0; u<10; ++u)
		{
			ContactTreeInfo* pUnitData = new ContactTreeInfo;

			pUnitData->nType = 0;
			pUnitData->sName.Format(L"测试部门_%d", u);
			pUnitData->sContent = L"非密";
			
			HSTREEITEM hRoot = InsertItem(pUnitData);
			SetItemExpanded(hRoot,FALSE);

			
			for(int i=0;i<10;i++)
			{
				ContactTreeInfo* pUserData = new ContactTreeInfo;
				pUserData->nType = 1;
				pUserData->sName.Format(L"branch_%d",i);
				InsertItem(pUserData, hRoot);
			}
		}
#endif

//		ASSERT(m_pOwner);
		//m_pOwner->ShowScrollBar(1, FALSE);

		//auto eventTree = m_pOwner->GetEventSet();
		//eventTree->subscribeEvent(&ContactTreeAdapter::OnEventHoverTree, this);
		//eventTree->subscribeEvent(&ContactTreeAdapter::OnEventLeaveTree, this);

		//m_nItemWidth = ;
	}
    ~ContactTreeAdapter()
	{
		for each(auto var in m_mapContact)
			delete var.second;

		for each(auto var in m_listUnit)
			delete var;
	}

	void SetItemClickCallBack(std::function<void(UINT)> fun)
	{
		m_callBackItemClick = fun;
	}
	void SetItemDbClickCallBack(std::function<void(UINT)> fun)
	{
		m_callBackItemDbClick = fun;
	}
public:
	HSTREEITEM AddUnit(UINT uId, LPCTSTR lpName)
	{
		ContactTreeInfo* pUnitData = new ContactTreeInfo;

		pUnitData->nType = 0;
		pUnitData->uId = uId;
		pUnitData->sName = lpName;
		
		m_listUnit.push_back(pUnitData);

		auto hItem = InsertItem(pUnitData);
		SetItemExpanded(hItem, FALSE);
	
		notifyBranchChanged(ITvAdapter::ITEM_ROOT);
		return hItem;
	}

	void AddUser(UINT uId, LPCTSTR lpName, LPCTSTR lpContent, HSTREEITEM hParent = STVI_ROOT)
	{
		ContactTreeInfo* pUserData = new ContactTreeInfo;

		pUserData->nType = 1;
		pUserData->uId = uId;
		pUserData->sName = lpName;
		pUserData->sContent = lpContent;

		m_mapContact[uId] = pUserData;

		auto hItem = InsertItem(pUserData, hParent);
		(void)hItem;
	
		notifyBranchChanged(ITvAdapter::ITEM_ROOT);
	}

	bool GetUserById(UINT uId, SStringT& sName, SStringT& sContent)
	{
		auto ite = m_mapContact.find(uId);
		if(ite == m_mapContact.end())
			return false;

		sName = ite->second->sName;
		sContent = ite->second->sContent;

		return true;
	}

protected:
	virtual void InitByTemplate(pugi::xml_node xmlTemplate)
	{
		m_nGroupItemHeight = xmlTemplate.attribute(L"Height1").as_int(30);
		m_nDataItemHeight = xmlTemplate.attribute(L"Height2").as_int(54); 
	}

	virtual int getViewType(SOUI::HTREEITEM hItem) const
	{
		ItemInfo& ii = m_tree.GetItemRef((HSTREEITEM)hItem);
		return ii.data->nType;
	}

	virtual int getViewTypeCount() const
	{
		return 2;
	}

	virtual SIZE getViewDesiredSize(SOUI::HTREEITEM hItem,SWindow * pItem, LPCRECT prcContainer)
	{
		//return pItem->GetDesiredSize(prcContainer);
		SIZE size = {prcContainer->right, 0};
		ItemInfo& ii = m_tree.GetItemRef((HSTREEITEM)hItem);
		if(0 == ii.data->nType)
		{
			size.cy = m_nGroupItemHeight;
		}
		else if(1 == ii.data->nType)
		{
			size.cy = m_nDataItemHeight;
		}
		return size;
	}
	virtual void getView(SOUI::HTREEITEM loc, SWindow * pItem, pugi::xml_node xmlTemplate) 
	{
		ItemInfo& ii = m_tree.GetItemRef((HSTREEITEM)loc);

		if(0 == pItem->GetChildrenCount())
		{
			pugi::xml_node xmlItem;
			if(0 == ii.data->nType)
				xmlItem = xmlTemplate.child(L"item_group");
			else if(1 == ii.data->nType)
				xmlItem = xmlTemplate.child(L"item_data");

			pItem->InitFromXml(xmlItem);

			auto eventItem = pItem->GetEventSet();
			eventItem->subscribeEvent(EventItemPanelClick::EventID, m_evtSlot_ItemClick);
			eventItem->subscribeEvent(EventItemPanelDbclick::EventID, m_evtSlot_ItemDbClick);
		}
		pItem->SetUserData(loc);
		SWindow* pTextUser = pItem->FindChildByName(L"tv_text_user");
		if(NULL != pTextUser)
		{
			pTextUser->SetWindowText(S_CW2T(ii.data->sName));
		}

		if(0 == ii.data->nType)
		{
			SToggle* pSwitch = pItem->FindChildByName2<SToggle>(L"tv_switch");
			if(NULL != pSwitch)
			{
				//pSwitch->SetVisible(HasChildren(loc));
				pSwitch->SetToggle(IsItemExpanded(loc));
				pSwitch->GetEventSet()->subscribeEvent(EVT_CMD, m_evtSlot_ToggleClick);
			}			
		}
		else if(1 == ii.data->nType)
		{
			SWindow* pTextContent = pItem->FindChildByName(L"tv_text_content");
			if(NULL != pTextContent)
			{
				pTextContent->SetWindowText(ii.data->sContent);
			}
		}	
	}

protected:
	bool OnEventItemToggleClick(EventArgs* e)
	{
		EventCmd* pEvt = sobj_cast<EventCmd>(e);
		if(NULL == pEvt) return true;

		SToggle* pToggle = sobj_cast<SToggle>(pEvt->sender);
		if(NULL == pToggle) return true;
		
		SItemPanel* pItem = sobj_cast<SItemPanel>(pToggle->GetRoot());
		if(NULL == pItem) return true;

		auto hItem = static_cast<SOUI::HTREEITEM>(pItem->GetItemIndex());
		ExpandItem(hItem, ITvAdapter::TVC_TOGGLE);

		return true;
	}
	bool OnEventItemClick(EventArgs* e)
	{
		EventItemPanelClick* pEvt = sobj_cast<EventItemPanelClick>(e);
		if(NULL == pEvt) return true;

		SItemPanel* pItem = sobj_cast<SItemPanel>(pEvt->sender);
		if(NULL == pItem) return true;

		auto hItem = static_cast<SOUI::HTREEITEM>(pItem->GetItemIndex());

		ItemInfo& ii = m_tree.GetItemRef((HSTREEITEM)hItem);
		if(0 == ii.data->nType)			// 点击 group 
		{
			pEvt->bubbleUp = false;

			CPoint pt;
			pt.x = GET_X_LPARAM(pEvt->lParam);
			pt.y = GET_Y_LPARAM(pEvt->lParam);

			// 判断 点击 的 是否是  删除按钮
			SWND hHover = pItem->SwndFromPoint(pt, FALSE);
			SWindow* pChild = SWindowMgr::GetWindow(hHover);
			if(NULL != pChild)			// 如果 有 消息 就 不选中
			{
				if(0 == _tcscmp(pChild->GetName(), L"tv_switch")	)			// 点击 group 里的 toggle 控件 
				{
					return true;
				}
			}

			ExpandItem(hItem, ITvAdapter::TVC_TOGGLE);
		}
		else if(1 == ii.data->nType)			// 点击 用户 
		{
			if(nullptr != m_callBackItemClick)
				m_callBackItemClick(ii.data->uId);
		}
		
		return true;
	}
	bool OnEventItemDbClick(EventArgs* e)
	{
		EventItemPanelDbclick* pEvt = sobj_cast<EventItemPanelDbclick>(e);
		if(NULL == pEvt) return true;

		SItemPanel* pItem = sobj_cast<SItemPanel>(pEvt->sender);
		if(NULL == pItem) return true;

		auto hItem = static_cast<SOUI::HTREEITEM>(pItem->GetItemIndex());
		ItemInfo& ii = m_tree.GetItemRef((HSTREEITEM)hItem);
		if(1 == ii.data->nType)			// 用户
		{
			if(nullptr != m_callBackItemDbClick)
				m_callBackItemDbClick(ii.data->uId);
		}

		return true;
	}
	/*bool OnEventHoverTree(EventSwndMouseHover* pEvt)
	{
	m_pOwner->SetAttribute(L"sbWid", L"8");
	return true;
	}
	bool OnEventLeaveTree(EventSwndMouseLeave* pEvt)
	{
	m_pOwner->SetAttribute(L"sbWid", L"0");

	return true;
	}*/

protected:
	STreeView*			m_pOwner;
	std::map<UINT, ContactTreeInfo*>			m_mapContact;
	std::list<ContactTreeInfo*>						m_listUnit;

	std::function<void(UINT)>							m_callBackItemClick;				// item 单机 回调
	std::function<void(UINT)>							m_callBackItemDbClick;			//  item 双击 回调
private:
	int						m_nGroupItemHeight;
	int						m_nDataItemHeight;

	MemberFunctionSlot<ContactTreeAdapter, EventArgs>			m_evtSlot_ToggleClick;
	MemberFunctionSlot<ContactTreeAdapter, EventArgs>			m_evtSlot_ItemClick;
	MemberFunctionSlot<ContactTreeAdapter, EventArgs>			m_evtSlot_ItemDbClick;
};
