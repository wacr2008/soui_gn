/**
* Copyright (C) 2014-2050 SOUI团队
* All rights reserved.
* 
* @file       STabCtrl2.h
* @brief      
* @version    v1.0      
* @author     水木之      
* @date       2014-07-06
* 
* Describe    另一个tabctrl
*/
#pragma once
#include <control/SCmnCtrl.h>

namespace SOUI
{
	enum ANI_STATUS{
		STATUS_NOR=0,
		STATUS_IN,
		STATUS_OUT,
	} ;
    
    class SPageAniObj
    {
    public:
        SPageAniObj();
        void AnimateIn(int nInterval);

        void AnimateOut(int nInterval);

        BOOL Draw(IRenderTarget *pRT,const CRect &rc);
        BOOL OnNextFrame(int nIntervel);

        ANI_STATUS m_aniStatus;
        int          m_iFrame;//当前帧
        int          m_tmWaitFor;
        ISkinObj    *m_pAniIn;//移入动画
        ISkinObj    *m_pAniOut;//移出动画
    };

	class STabPage2 : public STabPage
	{
		SOUI_CLASS_NAME_DECL(STabPage2, L"page2")
        friend class STabCtrl2;
	public:
		STabPage2(void);
		~STabPage2(void);

		protected:
		SOUI_ATTRS_DECL() 

        SPageAniObj m_aniObj;
	 };

    class STabCtrl2 : public STabCtrl,protected ITimelineHandler
    {
		SOUI_CLASS_NAME_DECL(STabCtrl2, L"tabctrl2")
	public:
		STabCtrl2(void);
		~STabCtrl2(void);
    protected:
		virtual void OnNextFrame();
        STabPage * CreatePageFromXml(pugi::xml_node xmlPage);

        void OnDestroy();
		int  OnCreate(void*);
		void OnPaint(IRenderTarget *pRT);
		void DrawItem(IRenderTarget *pRT,const CRect &rcItem,int iItem,DWORD dwState );

	   virtual void OnStateChanged(DWORD dwOldState,DWORD dwNewState);
	   bool OnItemHover(EventArgs *pEvt);
	   bool OnItemLeave(EventArgs *pEvt);
 
        SOUI_MSG_MAP_DECL() 
		
		ISkinObj *m_pSkinHeadBg;//tab头背景
        int m_iInterval;//动画间隔 单位毫秒

        SOUI_ATTRS_DECL()
    };

}//namespace SOUI