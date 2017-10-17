#pragma once 
#include "LvAdapterHandle.hpp"
#include <vector>
#include <functional>



// 最近 聊天好友列表 数据 适配器
class RecentListAdapter : public LvAdapterHandle
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
	RecentListAdapter(SListView* pOwner)
		: LvAdapterHandle(pOwner)
		, m_funBtnDel(&RecentListAdapter::OnEventDelBtn, this)
		//, m_pSelectItem(NULL)
		, m_callBackItemClick(nullptr)
		, m_callBackBtnClick(nullptr)
	{
		//std::function<void(int)> funItemClick, std::function<void(int)> funBtnClick)
	}

    ~RecentListAdapter()
	{
		for (size_t i=0; i<m_ItemInfoArr.size(); ++i)
		{
			delete m_ItemInfoArr[i];
		}
		m_ItemInfoArr.clear();
	}

	void SetItemClickCallBack(std::function<void(int)> fun)
	{
		m_callBackItemClick = fun;
	}
	void SetBtnClickCallBack(std::function<void(int)> fun)
	{
		m_callBackBtnClick = fun;
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
	bool Get(int nIndex, UINT& uId, SStringT* sName=NULL, UINT* uCount=NULL)
	{
		if(nIndex < 0 || nIndex >= static_cast<int>(m_ItemInfoArr.size()))
			return false;

		auto& pInfo = m_ItemInfoArr[nIndex];

		uId = pInfo->uId;
		if(NULL != sName)
			*sName = pInfo->sName;
		if(NULL != uCount)
			*uCount = pInfo->uCount;
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
	UINT GetTotalUnreadCount()
	{
		UINT uCount = 0;
		for each(auto var in m_ItemInfoArr)
		{
			uCount += var->uCount;
		}

		return uCount;
	}
protected:    
	virtual int getCount()
	{
		return static_cast<int>(m_ItemInfoArr.size());
	}
	
	virtual SStringT GetColumnName(int iCol) const
	{
		return L"col_nick";
	}
	void ShowView(int nItem, SWindow* pItem)
	{
		size_t sPos = static_cast<size_t>(nItem);

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
	}
		
	void ItemHover(int nItem, SItemPanel* pItem, const CPoint& pt)
	{
		SWindow* pBtn = pItem->FindChildByName(L"ml_btn_del");
		if(NULL != pBtn)
			pBtn->SetVisible(TRUE, TRUE);

		SWindow* pCount = pItem->FindChildByName(L"ml_count");
		if(NULL != pCount)
			pCount->SetVisible(FALSE, TRUE);
	}
	void ItemLeave(int nItem, SItemPanel* pItem)
	{
		SWindow* pBtn = pItem->FindChildByName(L"ml_btn_del");
		if(NULL != pBtn)
			pBtn->SetVisible(FALSE, TRUE);

		SWindow* pCount = pItem->FindChildByName(L"ml_count");
		if(NULL != pCount && !pCount->GetWindowText().IsEmpty())
		{
			pCount->SetVisible(TRUE, TRUE);
		}
	}
	void ItemClick(int nItem, SItemPanel* pItem, const CPoint& pt)
	{
		if(nullptr != m_callBackItemClick)
			m_callBackItemClick(nItem);
	}
	bool IsItemClick(int nItem, const SStringT& szSndName)
	{
		if(0 == szSndName.CompareNoCase(L"ml_btn_del"))
			return false;

		return true;
	}
	bool OnEventDelBtn(EventArgs* e)
	{
		e->bubbleUp = false;
		EventCmd* pEvt = sobj_cast<EventCmd>(e);
		if(NULL == pEvt) return true;

		SImageButton* pBtn = sobj_cast<SImageButton>(pEvt->sender);
		if(NULL == pBtn) return true;

		SItemPanel* pItem = sobj_cast<SItemPanel>(pBtn->GetParent());
		if(NULL == pItem) return true;

		if(nullptr != m_callBackBtnClick)
			m_callBackBtnClick(static_cast<int>(pItem->GetItemIndex()));

		return true;
	}
private:
	std::vector<RecentListItem*>				m_ItemInfoArr;				// 数据 
	
	std::function<void(int)>						m_callBackItemClick;		// item 单机 回调
	std::function<void(int)>						m_callBackBtnClick;			//  item  btn 回调

	MemberFunctionSlot<RecentListAdapter, EventArgs>			m_funBtnDel;
};
