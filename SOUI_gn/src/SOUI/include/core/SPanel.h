/**
* Copyright (C) 2014-2050 
* All rights reserved.
* 
* @file       SPanel.h
* @brief      
* @version    v1.0      
* @author     SOUI group   
* @date       2014/08/02
* 
* Describe    SOUI的窗口面板，实现在非客户区的滚动条支持
*/

#pragma once

#include "SWnd.h"

namespace SOUI
{

#define SSB_NULL    0
#define SSB_HORZ    1
#define SSB_VERT    2
#define SSB_BOTH    (SSB_HORZ|SSB_VERT)
#define TIMER_SBWAIT    1        //启动连续滚动的定时器
#define TIMER_SBGO    2        //连续滚动的定时器


    typedef struct tagSBHITINFO
    {
        DWORD uSbCode:16;   //HIT位置
        DWORD bVertical:16; //是否为vertical
    } SBHITINFO,*PSBHITINFO;

    inline bool operator !=(const SBHITINFO &a, const SBHITINFO &b)
    {
        return memcmp(&a,&b,sizeof(SBHITINFO))!=0;
    }

    class SOUI_EXP SPanel: public SWindow
    {
        SOUI_CLASS_NAME_DECL(SPanel, L"div")

    public:
        SPanel();
		~SPanel() override;

        BOOL ShowScrollBar(int wBar, BOOL bShow);

        BOOL EnableScrollBar(int wBar,BOOL bEnable);

        BOOL IsScrollBarEnable(BOOL bVertical);

        void SetScrollInfo(SCROLLINFO si,BOOL bVertical);

        BOOL SetScrollPos(BOOL bVertical, int nNewPos,BOOL bRedraw);

        int GetScrollPos(BOOL bVertical);

        BOOL SetScrollRange(BOOL bVertical,int nMinPos,int nMaxPos,BOOL bRedraw);

        BOOL GetScrollRange(BOOL bVertical,    LPINT lpMinPos,    LPINT lpMaxPos);

        BOOL HasScrollBar(BOOL bVertical);


        SBHITINFO HitTest(CPoint pt);

        void GetClientRect(LPRECT pRect) const override;
        CRect GetClientRect() const override;
    protected:
        CRect GetSbPartRect(BOOL bVertical,UINT uSBCode);
        CRect GetSbRailwayRect(BOOL bVertical);
        CRect GetScrollBarRect(BOOL bVertical);

        int OnCreate(LPVOID);

        void OnNcPaint(IRenderTarget *pRT);

        BOOL OnNcHitTest(CPoint pt) override;

        void OnNcLButtonDown(UINT nFlags, CPoint point);

        void OnNcLButtonUp(UINT nFlags,CPoint pt);

        void OnNcMouseMove(UINT nFlags, CPoint point) ;


        void OnNcMouseLeave();

        //滚动条显示或者隐藏时发送该消息
        LRESULT OnNcCalcSize(BOOL bCalcValidRects, LPARAM lParam);

        BOOL OnMouseWheel(UINT nFlags, short zDelta, CPoint pt);

        void OnTimer(char cTimerID);

        void OnShowWindow(BOOL bShow, UINT nStatus);
        
        void OnVScroll(UINT nSBCode, UINT nPos, HWND);
        void OnHScroll(UINT nSBCode, UINT nPos, HWND);
    protected:
        virtual int  GetScrollLineSize(BOOL bVertical);
        virtual BOOL OnScroll(BOOL bVertical,UINT uCode,int nPos);
        void OnColorize(COLORREF cr) override;
        void OnScaleChanged(int nScale) override;

		int GetSbArrowSize();
		int GetSbWidth();

        int GetSbSlideLength(BOOL bVertical);

        CRect GetSbSlideRectByPos(BOOL bVertical,int nPos);

        void ScrollUpdate();

        HRESULT OnAttrScrollbarSkin(SStringW strValue,BOOL bLoading);

        SCROLLINFO m_siVer,m_siHoz;
        SSkinScrollbar *m_pSkinSb;

	private:	//修改为私有，派生类只能使用GetSbArrowSize(),GetSbWidth()获取
        SLayoutSize    m_nSbArrowSize;
		SLayoutSize    m_nSbWid;

	protected:
		SLayoutSize	   m_nSbLeft;   //滚动条距离左边距离
		SLayoutSize    m_nSbRight;  //滚动条距离边边距离
		SLayoutSize	   m_nSbTop;    //滚动条距离上边距离
		SLayoutSize    m_nSbBottom; //滚动条距离下边距离
        CPoint         m_ptDragSb;
        
        enum {
        DSB_NULL=0,
        DSB_VERT,
        DSB_HORZ,
        }           m_dragSb;
        SBHITINFO        m_HitInfo;
        int            m_nDragPos;

        CRect        m_rcClient;
        int            m_wBarVisible;    //滚动条显示信息
        int            m_wBarEnable;    //滚动条可操作信息

        DWORD        m_dwUpdateTime;    //记录调用UpdateSWindow的时间
        DWORD        m_dwUpdateInterval;
        
		short		 m_zDelta;
        int          m_nScrollSpeed;
        SOUI_ATTRS_DECL() 

        SOUI_MSG_MAP_DECL() 
    };

    class SOUI_EXP SScrollView : public SPanel
    {
        SOUI_CLASS_NAME_DECL(SScrollView, L"scrollview")
    public:
        SScrollView();
		~SScrollView() override;

        CSize GetViewSize();

        void SetViewSize(CSize szView);

        CPoint GetViewOrigin();

        void SetViewOrigin(CPoint pt);

    protected:
        void OnSize(UINT nType,CSize size);
    protected:
        virtual void OnViewSizeChanged(CSize szOld,CSize szNew);
        virtual void OnViewOriginChanged(CPoint ptOld,CPoint ptNew);
		virtual void UpdateChildrenPosition();
    protected:
        CRect GetChildrenLayoutRect() override;

        BOOL OnScroll(BOOL bVertical,UINT uCode,int nPos) override;

        virtual void UpdateScrollBar();

		
    protected:
    
        HRESULT OnAttrViewSize(const SStringW & strValue,BOOL bLoading);
        
        SOUI_ATTRS_DECL() 

        SOUI_MSG_MAP_DECL() 
    protected:
        BOOL  m_bAutoViewSize;
        CSize m_szView;
        CPoint m_ptOrigin;
    };

}//namespace SOUI