#pragma once 
#include <helper/SAdapterBase.h>
#include "skin\SAntialiasSkin.h"



class EmotionTileAdapter : public SAdapterBase
{
public:
	EmotionTileAdapter(std::function<void(UINT)> fun, LPCTSTR lpPath)
		: m_funItemClick(&EmotionTileAdapter::OnItemClick, this)
		, m_funDbClick(fun)
		, m_szGifImagePath(lpPath)
	{

	}
    ~EmotionTileAdapter()
	{
	
	}

protected:    
	virtual int getCount()
	{
		return 134;
	}
		
	virtual void getView(int nPosition, SWindow* pItem, pugi::xml_node xmlTemplate)
	{
		if(0 == pItem->GetChildrenCount())
		{
			pItem->InitFromXml(xmlTemplate);
		}

		SImageView* pGifImg = pItem->FindChildByName2<SImageView>(L"img_emoticons");
		if(NULL != pGifImg)
		{
			auto ite = m_mapSkin.find(nPosition);
			if(ite == m_mapSkin.end())
			{
				SStringT szPath;
				szPath.Format(_T("%s%d.gif"), m_szGifImagePath, nPosition);

				SAntialiasSkin* pAntSkin = new SAntialiasSkin();
				if (!pAntSkin->LoadFromFile(szPath))
				{
					delete pAntSkin;
					return ;
				}

				m_mapSkin[nPosition] = pAntSkin;
				pGifImg->SetSkin(pAntSkin);
			}
			else
				pGifImg->SetSkin(ite->second);
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
		(void)nIndex;
		
		return true;
	}
	
private:
	std::map<int, ISkinObj*>	m_mapSkin;
	SStringT				m_szGifImagePath;
	MemberFunctionSlot<EmotionTileAdapter, EventArgs>			m_funItemClick;

	// 主窗口 回调 函数
	std::function<void(UINT)>		m_funDbClick;
};
