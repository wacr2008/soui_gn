#pragma once 
#include "McListAdapterHandle.hpp"
#include <vector>
#include <functional>



// 最近 聊天好友列表 数据 适配器
class RecentListAdapter : public SMcAdapterBase
{
protected:
	struct RecentListItem
	{
		UINT				uId;							// id
		UINT				uCount;			//
		SStringT			sName;						// 名称
		SStringT			sContent;
	};
public:
	RecentListAdapter(std::function<void(int)> funItemClick, std::function<void(int)> funBtnClick)
		: m_funItemClick(&RecentListAdapter::OnItemClick, this)
		, m_funMouseHover(&RecentListAdapter::OnMouseHover, this)
		, m_funMouseLeave(&RecentListAdapter::OnMouseLeave, this)
		, m_funBtnDel(&RecentListAdapter::OnEventDelBtn, this)
		, m_pSelectItem(NULL)
		, m_callBackItemClick(funItemClick)
		, m_callBackBtnClick(funBtnClick)
	{
	
	}

    ~RecentListAdapter()
	{
		for (size_t i=0; i<m_ItemInfoArr.size(); ++i)
		{
			delete m_ItemInfoArr[i];
		}
		m_ItemInfoArr.clear();
	}


public:
	int Insert0(UINT dwUserId, LPCTSTR lpTitle, LPCTSTR lpContent, UINT uCount=0)
	{
		RecentListItem* pInfo =  new RecentListItem;
		pInfo->uId = dwUserId;
		pInfo->sName = lpTitle;
		pInfo->sContent = lpContent;
		pInfo->uCount = uCount;
				
		m_ItemInfoArr.insert(m_ItemInfoArr.begin(), pInfo);

		notifyDataSetChanged();

		return 0;
	}
	int Add(UINT dwUserId, LPCTSTR lpTitle, LPCTSTR lpContent, UINT uCount=0)
	{
		RecentListItem* pInfo =  new RecentListItem;
		pInfo->uId = dwUserId;
		pInfo->sName = lpTitle;
		pInfo->sContent = lpContent;
		pInfo->uCount = uCount;

		m_ItemInfoArr.push_back(pInfo);

		notifyDataSetChanged();

		return m_ItemInfoArr.size() - 1;
	}
	bool Get(int nIndex, UINT& uId, SStringT& sName, UINT& uCount)
	{
		if(nIndex < 0 || nIndex >= static_cast<int>(m_ItemInfoArr.size()))
			return false;

		auto& pInfo = m_ItemInfoArr[nIndex];

		uId = pInfo->uId;
		sName = pInfo->sName;
		uCount = pInfo->uCount;
		return true;
	}
	int Find(UINT uId, SStringT* sName=NULL, UINT* uCount=NULL)
	{
		size_t nCount = m_ItemInfoArr.size();
		for (size_t i=0; i<nCount; ++i)
		{
			auto& info = m_ItemInfoArr[i];
			if(uId == info->uId)
			{
				if(NULL != sName)
					*sName = info->sName;

				if(NULL != uCount)
					*uCount = info->uCount;

				return i;
			}
		}

		return -1;
	}
	
	void Update(int nIndex, UINT uCount, LPCTSTR lpContent, LPCTSTR lpName=NULL)
	{
		size_t sIndex = static_cast<size_t>(nIndex);

		if(sIndex < 0 || sIndex >= m_ItemInfoArr.size())
			return ;

		auto& pInfo = m_ItemInfoArr[sIndex];
		pInfo->uCount = uCount;
		if(NULL != lpName)
			pInfo->sName = lpName;
		if(NULL != lpContent)
			pInfo->sContent = lpContent;

		notifyDataSetChanged();
	}
	void MoveToBegin(int nIndex)
	{
		size_t sIndex = static_cast<size_t>(nIndex);

		if(sIndex <= 0 || sIndex >= m_ItemInfoArr.size())
			return ;

		auto pInfo = m_ItemInfoArr[sIndex];
		auto ite = m_ItemInfoArr.begin();
		m_ItemInfoArr.erase(ite + sIndex);
		m_ItemInfoArr.insert(ite, pInfo);

		notifyDataSetChanged();
	}
	bool IsEmpty()
	{
		return m_ItemInfoArr.size() <= 0;
	}
	void DeleteItem(int nIndex)
	{
		size_t sIndex = static_cast<size_t>(nIndex);

		if(sIndex < 0 || sIndex >= m_ItemInfoArr.size())
			return ;

		m_ItemInfoArr.erase(m_ItemInfoArr.begin() + nIndex);

		notifyDataSetChanged();
	}
	void SelectItem(int nIndex)
	{

	}
protected:    
	virtual void InitByTemplate(pugi::xml_node xmlTemplate)
	{
		auto ite = xmlTemplate.attribute(L"colorSelected");
		m_szSelectColor = ite.as_string();
		ite = L"#FFFFFF00";
	}
    virtual int getCount()
	{
		return static_cast<int>(m_ItemInfoArr.size());
	}
	  
	//virtual SIZE getViewDesiredSize(int position, SOUI::SWindow *pItem, LPCRECT prcContainer)
	//{

	//}
	/*virtual int getItemViewType(int position)
	{

	}*/
	virtual SStringT GetColumnName(int iCol) const
	{
		return L"col_nick";
	}
	virtual void getView(int nPosition, SWindow* pItem, pugi::xml_node xmlTemplate)
	{		
		if(0 == pItem->GetChildrenCount())
		{
			//auto s = xmlTemplate.text().as_string();
			pItem->InitFromXml(xmlTemplate);
		}

		size_t sPos = static_cast<size_t>(nPosition);

		if(sPos >= m_ItemInfoArr.size())
			return ;

		auto pInfo = m_ItemInfoArr[sPos];
		if(NULL == pInfo)
			return ;

		/*SMaskImage* pImg = pItem->FindChildByName2<SMaskImage>(L"ml_img_user");
		if(NULL != pImg )
		{
			pImg->SetAttribute(L"skin", L"default");
		}*/

		SStatic* pTextUser = pItem->FindChildByName2<SStatic>(L"ml_text_user");
		if (NULL != pTextUser)
		{
			pTextUser->SetWindowText(pInfo->sName);
		}

		SStatic* pTextMsg = pItem->FindChildByName2<SStatic>(L"ml_text_msg");
		if (NULL != pTextMsg)
		{
			pTextMsg->SetWindowText(pInfo->sContent);
		}

		SWindow* pCount = pItem->FindChildByName(L"ml_count");
		if(NULL != pCount)
		{
			if(0 == pInfo->uCount)
			{
				pCount->SetVisible(FALSE, TRUE);
				pCount->SetWindowText(_T(""));
			}
			else
			{
				SStringT sCount;
				if(pInfo->uCount > 99)
					sCount.Format(_T("%d+"), 99);
				else
					sCount.Format(_T("%d"), pInfo->uCount);
				pCount->SetVisible(TRUE, TRUE);
				pCount->SetWindowText(sCount);
			}
		}

		SImageButton* pBtn = pItem->FindChildByName2<SImageButton>(L"ml_btn_del");
		if(NULL != pBtn)
			pBtn->GetEventSet()->subscribeEvent(EventCmd::EventID, m_funBtnDel);
		//pItem->GetEventSet()->unsubscribeEvent(EVT_ITEMPANEL_CLICK, Subscriber(&CFriendListAdapter::OnGroupClick, this));
		
		pItem->GetEventSet()->subscribeEvent(EVT_ITEMPANEL_CLICK, m_funItemClick);
		pItem->GetEventSet()->subscribeEvent(EVT_ITEMPANEL_HOVER, m_funMouseHover);
		pItem->GetEventSet()->subscribeEvent(EVT_ITEMPANEL_LEAVE, m_funMouseLeave);

	}
	bool OnMouseHover(EventArgs* e)
	{
		e->bubbleUp = false;
		EventItemPanelHover* pEvt = sobj_cast<EventItemPanelHover>(e);
		if(NULL == pEvt)
			return true;
		SWindow* pItem = sobj_cast<SWindow>(pEvt->sender);

		SWindow* pBtn = pItem->FindChildByName(L"ml_btn_del");
		if(NULL != pBtn)
			pBtn->SetVisible(TRUE, TRUE);

		SWindow* pCount = pItem->FindChildByName(L"ml_count");
		if(NULL != pCount)
			pCount->SetVisible(FALSE, TRUE);

		return true;
	}
	bool OnMouseLeave(EventArgs* e)
	{
		e->bubbleUp = false;
		EventItemPanelLeave* pEvt = sobj_cast<EventItemPanelLeave>(e);
		if(NULL == pEvt)
			return true;
		SWindow* pItem = sobj_cast<SWindow>(pEvt->sender);

		SWindow* pBtn = pItem->FindChildByName(L"ml_btn_del");
		if(NULL != pBtn)
			pBtn->SetVisible(FALSE, TRUE);

		SWindow* pCount = pItem->FindChildByName(L"ml_count");
		if(NULL != pCount && !pCount->GetWindowText().IsEmpty())
		{
			pCount->SetVisible(TRUE, TRUE);
		}

		return true;
	}

	bool OnItemClick(EventArgs* e)
	{
		e->bubbleUp = false;

		EventItemPanelClick* pEvt = sobj_cast<EventItemPanelClick>(e);
		if(NULL == pEvt) return true;

		SItemPanel* pItem = sobj_cast<SItemPanel>(pEvt->sender);
		if(NULL == pItem) return true;

		SWindow* pWindow = pItem->FindChildByName(L"col_nick");
		if(NULL == pWindow) return true;

		CPoint pt;
		pt.x = GET_X_LPARAM(pEvt->lParam);
		pt.y = GET_Y_LPARAM(pEvt->lParam);
		
		// 判断 点击 的 是否是  删除按钮
		SWND hHover = pWindow->SwndFromPoint(pt, FALSE);

		SImageButton* pBtn = pWindow->FindChildByName2<SImageButton>(L"ml_btn_del");
		if(NULL != pBtn && hHover == pBtn->GetSwnd())
		{
			return true;
		}

		// 取消之前选中项 
		if(NULL != m_pSelectItem)
			m_pSelectItem->SetAttribute(L"colorBkgnd", L"#FFFFFF00");
				
		// 自己 设置 选中 背景色
		pWindow->SetAttribute(L"colorBkgnd", m_szSelectColor);
		
		m_pSelectItem = pWindow;
		
		m_callBackItemClick(static_cast<int>(pItem->GetItemIndex()));

		return true;
	}
	bool OnEventDelBtn(EventArgs* e)
	{
		e->bubbleUp = false;
		EventCmd* pEvt = sobj_cast<EventCmd>(e);
		if(NULL == pEvt) return true;

		SImageButton* pBtn = sobj_cast<SImageButton>(pEvt->sender);
		if(NULL == pBtn) return true;

		SItemPanel* pItem = sobj_cast<SItemPanel>(pBtn->GetParent()->GetParent());
		if(NULL == pItem) return true;

		m_callBackBtnClick(static_cast<int>(pItem->GetItemIndex()));

		return true;
	}
private:
	std::vector<RecentListItem*>				m_ItemInfoArr;				// 数据 
	
	SWindow*											m_pSelectItem;				// 自己 模拟 的 选中 项
	SStringT												m_szSelectColor;			// 选中 的背景色 字符串

	std::function<void(int)>						m_callBackItemClick;		// item 单机 回调
	std::function<void(int)>						m_callBackBtnClick;			//  item  btn 回调

	MemberFunctionSlot<RecentListAdapter, EventArgs>			m_funItemClick;
	MemberFunctionSlot<RecentListAdapter, EventArgs>			m_funMouseHover;
	MemberFunctionSlot<RecentListAdapter, EventArgs>			m_funMouseLeave;
	MemberFunctionSlot<RecentListAdapter, EventArgs>			m_funBtnDel;
};
