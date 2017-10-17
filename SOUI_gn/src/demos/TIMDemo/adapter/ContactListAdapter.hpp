#pragma once 
#include <helper/SAdapterBase.h>
#include <helper/STime.h>
#include <list>
#include "Typedef.h"



class ContactListAdapter : public SMcAdapterBase
{
protected:
	enum EnItemType
	{
		eFIT_Group = 0,
		eFIT_Data = 1,
	};

	struct ContactListItemInfo
	{
		EnItemType			eType;
		bool						bExpend;
		UINT						uId;
		SStringT					sName;
		SStringT					sContent;		
	};
	
public:
	ContactListAdapter(std::function<void(UINT)> fun)
		: m_funItemClick(&ContactListAdapter::OnItemClick, this)
		, m_funItemDbClick(&ContactListAdapter::OnItemDbClick, this)
		, m_funDbClick(fun)
	{
#if 0
		int iItem = 0;
		ContactListItemInfo* pInfo =  new ContactListItemInfo;
		pInfo->eType = eFIT_Group;
		pInfo->bExpend = false;
		pInfo->uId = 23;
		pInfo->sName = _T("测试部门");
		iItem = m_ItemInfoArr.Add(pInfo);
		m_cache_layer.Add(iItem);

		SStringT sTitle;
		for (int i=0; i<5; ++i)
		{
			pInfo =  new ContactListItemInfo;
			pInfo->eType = eFIT_Data;
			pInfo->uId = 110 + i;
			pInfo->sName.Format(_T("测试_%02d"), i);
			pInfo->sContent.Format(_T("今天状态___%d"), i * i + i);

			iItem = m_ItemInfoArr.Add(pInfo);
			//m_cache_layer.Add(iItem);
		}

		pInfo =  new ContactListItemInfo;
		pInfo->bExpend = false;
		pInfo->eType = eFIT_Group;
		pInfo->uId = 23;
		pInfo->sName = _T("开发部门");
		
		iItem = m_ItemInfoArr.Add(pInfo);
		m_cache_layer.Add(iItem);

		for (int i=0; i<5; ++i)
		{
			pInfo =  new ContactListItemInfo;
			pInfo->eType = eFIT_Data;
			pInfo->uId = 160 + i;
			pInfo->sName.Format(_T("开发_%02d"), i);
			pInfo->sContent.Format(_T("今天 心情___%d"), i * i + i);

			iItem = m_ItemInfoArr.Add(pInfo);
			//m_cache_layer.Add(iItem);
		}
#endif
	}
    ~ContactListAdapter()
	{
		for (size_t i=0; i<m_ItemInfoArr.size(); ++i)
		{
			delete m_ItemInfoArr[i];
		}
		m_ItemInfoArr.clear();
	}
public:
	int AddUnit(UINT uId, LPCTSTR lpName)
	{
		ContactListItemInfo* pInfo =  new ContactListItemInfo;
		pInfo->eType = eFIT_Group;
		pInfo->bExpend = false;
		pInfo->uId = uId;
		pInfo->sName = lpName;

		m_ItemInfoArr.push_back(pInfo);
		size_t iItem = m_ItemInfoArr.size() - 1;
		m_cache_layer.push_back(iItem);

		notifyDataSetChanged();

		return iItem;
	}
	int AddUser(UINT uId, LPCTSTR lpName, LPCTSTR lpContent, int nUnitId)
	{
		ContactListItemInfo* pInfo =  new ContactListItemInfo;
		pInfo->eType = eFIT_Data;
		pInfo->uId = uId;
		pInfo->sName = lpName;
		pInfo->sContent = lpContent;

		//m_ItemInfoArr.InsertAt(nUnitId+1, pInfo);
		m_ItemInfoArr.push_back(pInfo);
		
		notifyDataSetChanged();
		return m_ItemInfoArr.size() - 1;
	}
	bool Get(UINT uIndex)
	{
		
		return true;
	}
	bool GetById(UINT uId, SStringT& sName, SStringT& sContent)
	{
		size_t nCount = m_ItemInfoArr.size();
		for (size_t i=0; i<nCount; ++i)
		{
			auto& info = m_ItemInfoArr[i];
			if(uId == info->uId)
			{
				sName = info->sName;
				sContent = info->sContent;
				return true;
			}
		}

		return false;
	}
private:
	ContactListItemInfo* GetVisibleNode(int nPosition)
	{
		size_t sPos = static_cast<size_t>(nPosition);

		if(sPos < 0 || sPos > m_cache_layer.size())
			return NULL;

		
		size_t iItem = m_cache_layer[sPos];
		if(iItem < 0 || iItem > m_ItemInfoArr.size())
			return NULL;

		return m_ItemInfoArr[iItem];
	}
	void Expend(int nPosition)
	{
		size_t sPos = static_cast<size_t>(nPosition);
		if(sPos < 0 || sPos > m_cache_layer.size())
			return ;

		int iItem = m_cache_layer[sPos];

		auto pInfo = m_ItemInfoArr[iItem];
		if(eFIT_Group != pInfo->eType)		// 如果 该item  不是组  就返回
			return ;

		pInfo->bExpend = !pInfo->bExpend;

		// 从 该组 项 的下一个 开始 枚举
		for (size_t i=iItem+1,j=0; i<m_ItemInfoArr.size(); ++i,++j)
		{
			auto& pTemp = m_ItemInfoArr[i];
			if(eFIT_Group == pTemp->eType)				// 如果是 组 就退出
				break;

			/*if(pInfo->bExpend)
			m_cache_layer.InsertAt(nPosition+1+j, i);
			else
			m_cache_layer.RemoveAt(nPosition+1);*/
			if(pInfo->bExpend)
				m_cache_layer.insert(m_cache_layer.begin()+sPos+1+j, i);
			else
				m_cache_layer.erase(m_cache_layer.begin()+sPos+1);
		}

		
	}
protected:    
	virtual void InitByTemplate(pugi::xml_node xmlTemplate)
	{
		m_nGroupItemHeight = xmlTemplate.attribute(L"defHeight").as_int(30);
		m_nFriendItemHeight = xmlTemplate.attribute(L"friendItemHeight").as_int(58); 
	}
    virtual int getCount()
	{
		return static_cast<int>(m_cache_layer.size());
	}

	int getViewTypeCount()			// 有两种 布局 
	{
		return 2;
	}
	virtual SIZE getViewDesiredSize(int nPosition, SOUI::SWindow *pItem, LPCRECT prcContainer)
	{
		auto pInfo = GetVisibleNode(nPosition);
		
		SIZE size = {0, 0};
		if(NULL != pInfo)
		{
			if(eFIT_Group == pInfo->eType)
				size.cy = m_nGroupItemHeight;
			else
				size.cy = m_nFriendItemHeight;
		}
		
		return size;
	}
	virtual int getItemViewType(int nPosition)
	{
		auto pInfo = GetVisibleNode(nPosition);
		if(NULL == pInfo)
			return 0;

		return (int)pInfo->eType;
	}

	virtual SStringT GetColumnName(int iCol) const
	{
		return L"col_nick";
	}
	virtual void getView(int nPosition, SWindow* pItem, pugi::xml_node xmlTemplate)
	{
		auto pInfo = GetVisibleNode(nPosition);
		if(NULL == pInfo)
			return ;

		if(0 == pItem->GetChildrenCount())
		{
			pugi::xml_node xmlItem;
			if(eFIT_Group == pInfo->eType)
				xmlItem = xmlTemplate.child(L"item_group");
			else if(eFIT_Data == pInfo->eType)
				xmlItem = xmlTemplate.child(L"item_data");
			
			pItem->InitFromXml(xmlItem);
		
		}

		if(eFIT_Group == pInfo->eType)
		{
			SToggle* pToggle = pItem->FindChildByName2<SToggle>(L"ml_toggle");
			if(NULL != pToggle)
			{
				pToggle->SetToggle(pInfo->bExpend);
			}
			
			SStatic* pText = pItem->FindChildByName2<SStatic>(L"ml_text_group");
			if (NULL != pText)
			{
				pText->SetWindowText(pInfo->sName);
			}
			//pItem->GetEventSet()->unsubscribeEvent(EVT_ITEMPANEL_CLICK, m_funItemClick);
			pItem->GetEventSet()->subscribeEvent(EVT_ITEMPANEL_CLICK, m_funItemClick);
		}
		else if(eFIT_Data == pInfo->eType)
		{
			/*SMaskImage* pImg = pItem->FindChildByName2<SMaskImage>(L"ml_img_user");
			if(NULL != pImg && NULL == pImg->GetSkin())
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

			pItem->GetEventSet()->subscribeEvent(EVT_ITEMPANEL_DBCLICK, m_funItemDbClick);
		}

		
		

		//SImageWnd* pImg = pItem->FindChildByName2<SImageWnd>(L"ml_img_user");
		//if(NULL != pImg && NULL == pImg->GetSkin())
		//{
		//	pImg->SetAttribute(L"skin", L"ico_user");
		//}

		

		////pItem->GetEventSet()->unsubscribeEvent(EVT_ITEMPANEL_CLICK, Subscriber(&CFriendListAdapter::OnGroupClick, this));
		//
		//pItem->GetEventSet()->subscribeEvent(EVT_ITEMPANEL_LEAVE, Subscriber(&CTalkListAdapter::OnMouseLeave, this));

	}
	bool OnItemClick(EventArgs* e)
	{
		EventItemPanelClick* pEvt = sobj_cast<EventItemPanelClick>(e);
		if(NULL == pEvt)
			return true;
		
		SItemPanel* pItem = sobj_cast<SItemPanel>(e->sender); 

		int nIndex = (int)pItem->GetItemIndex(); 
				
		auto pInfo = GetVisibleNode(nIndex);
		if(NULL == pInfo) return true;

		if(eFIT_Group == pInfo->eType)
		{			
			Expend(nIndex);
		}
		else if(eFIT_Data == pInfo->eType)
		{

		}
		notifyDataSetChanged();
		return true;
	}
	bool OnItemDbClick(EventArgs* e)
	{
		EventItemPanelDbclick* pEvt = sobj_cast<EventItemPanelDbclick>(e);
		if(NULL == pEvt)
			return true;

		SItemPanel* pItem = sobj_cast<SItemPanel>(e->sender); 

		int nIndex = (int)pItem->GetItemIndex(); 

		auto pInfo = GetVisibleNode(nIndex);
		if(NULL == pInfo) return true;

		if(eFIT_Data != pInfo->eType)
		{			
			return true;
		}
	
		m_funDbClick(pInfo->uId);


		//notifyDataSetChanged();
		return true;
	}
private:
	
	int			m_nGroupItemHeight;
	int			m_nFriendItemHeight;
	std::vector<ContactListItemInfo*>			m_ItemInfoArr;
	std::vector<size_t>									m_cache_layer;			//加一个缓存层，简单处理隐藏显示

	MemberFunctionSlot<ContactListAdapter, EventArgs>			m_funItemClick;
	MemberFunctionSlot<ContactListAdapter, EventArgs>			m_funItemDbClick;

	// 主窗口 回调 函数
	std::function<void(UINT)>		m_funDbClick;
};
