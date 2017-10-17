#pragma once

#include "core/Swnd.h"
#include "core/SItemPanel.h"
#include "interface/Adapter-i.h"
#include "interface/TvItemLocator-i.h"

namespace SOUI
{
    //////////////////////////////////////////////////////////////////////////
    class SOUI_EXP STreeViewItemLocator : public TObjRefImpl<ITreeViewItemLocator>
    {
    public:
        STreeViewItemLocator(int nIndent=10);

        ~STreeViewItemLocator() override;

        void SetAdapter(ITvAdapter *pAdapter) override;

        void OnBranchChanged(HTREEITEM hItem) override;

        void OnBranchExpandedChanged(HTREEITEM hItem,BOOL bExpandedOld,BOOL bExpandedNew) override;

        int GetTotalHeight() const override;

        int GetTotalWidth() const override;

        int GetScrollLineSize() const override;

        int Item2Position(HTREEITEM hItem) const override;

        HTREEITEM Position2Item(int position) const override;

        void SetItemWidth(HTREEITEM hItem,int nWidth) override;

        void SetItemHeight(HTREEITEM hItem,int nHeight) override;

        int GetItemWidth(HTREEITEM hItem) const override;

        int GetItemHeight(HTREEITEM hItem) const override;

        int GetItemIndent(HTREEITEM hItem) const override;
    protected:
        BOOL IsItemExpanded(HTREEITEM hItem) const;

        //更新hItem所在的父窗口中分枝宽度数据
        //hItem:显示宽度发生变化的节点，可以是节点本身宽度变化，也可能是子节点宽度发生了变化
        //nOldWidth：原显示宽度
        //nNewWidth: 新显示宽度
        void _UpdateBranchWidth(HTREEITEM hItem,int nOldWidth,int nNewWidth);

        int _GetBranchWidth(HTREEITEM hBranch) const;

        void _SetBranchWidth(HTREEITEM hBranch,int nWidth);

        void _SetItemWidth(HTREEITEM hItem,int nWidth);


        int _GetBranchHeight(HTREEITEM hItem) const;

        void _SetBranchHeight(HTREEITEM hItem ,int nHeight);

        void _UpdateBranchHeight(HTREEITEM hItem,int nDiff);

        //向后更新兄弟结点的偏移量
        void _UpdateSiblingsOffset(HTREEITEM hItem);

        int _GetItemOffset(HTREEITEM hItem) const;

        void _SetItemOffset(HTREEITEM hItem, int nOffset);

        void _SetItemHeight(HTREEITEM hItem,int nHeight);


        int _GetItemVisibleHeight(HTREEITEM hItem) const;

        int _GetItemVisibleWidth(HTREEITEM hItem) const;

        HTREEITEM _Position2Item(int position,HTREEITEM hParent,int nParentPosition) const;

        BOOL _IsItemVisible(HTREEITEM hItem) const;

        void _InitBranch(HTREEITEM hItem);


        CAutoRefPtr<ITvAdapter> m_adapter;
        int                     m_nLineHeight;
        int                     m_nIndent;
        CSize                   m_szDef;
    };


	class SOUI_EXP STreeView : public SPanel, protected IItemContainer
	{
		SOUI_CLASS_NAME_DECL(STreeView, L"treeview")
		
	public:
		STreeView();
		~STreeView() override;
			
		BOOL SetAdapter(ITvAdapter * adapter);
		ITvAdapter * GetAdapter () { return m_adapter; }
		void SetItemLocator(ITreeViewItemLocator *pItemLocator)
		{
		    m_tvItemLocator = pItemLocator;
		}
		
		ITreeViewItemLocator * GetItemLocator() const
		{
		    return m_tvItemLocator;
		}
		
		void onBranchChanged(HTREEITEM hBranch);
		void onBranchInvalidated(HTREEITEM hBranch);
        void onBranchExpandedChanged(HTREEITEM hBranch,BOOL bExpandedOld,BOOL bExpandedNew);
        
        void SetSel(HTREEITEM hItem,BOOL bNotify=FALSE);
        HTREEITEM  GetSel()const{return m_hSelected;}
        SItemPanel * HitTest(CPoint & pt);

    protected:
        bool OnItemClick(EventArgs *pEvt);
        bool OnItemDblClick(EventArgs *pEvt);

    protected:
		void OnPaint(IRenderTarget * pRT);
		void OnSize(UINT nType, CSize size);
		void OnDestroy();
 		void OnKeyDown(TCHAR nChar, UINT nRepCnt, UINT nFlags);//实现键盘选择
		LRESULT OnKeyEvent( UINT uMsg,WPARAM wParam,LPARAM lParam );
		
		void OnMouseLeave();
		BOOL OnMouseWheel(UINT nFlags, short zDelta, CPoint pt);
		LRESULT OnMouseEvent(UINT uMsg,WPARAM wParam,LPARAM lParam);

		void OnKillFocus(SWND wndFocus);
		void OnSetFocus(SWND wndOld);
		

		SOUI_MSG_MAP_DECL() 
		
    protected:
        HRESULT OnAttrIndent(const SStringW & strValue,BOOL bLoading);
        
        SOUI_ATTRS_DECL() 
	protected:
        UINT OnGetDlgCode() override;
        BOOL OnSetCursor(const CPoint &pt) override;
        BOOL OnUpdateToolTip(CPoint pt, SwndToolTipInfo & tipInfo) override;
        void OnColorize(COLORREF cr) override;
		void OnScaleChanged(int nScale) override;
		HRESULT OnLanguageChanged() override;

		BOOL OnScroll(BOOL bVertical,UINT uCode,int nPos) override;
		int  GetScrollLineSize(BOOL bVertical) override;
		BOOL CreateChildren(pugi::xml_node xmlNode) override;
	
		void OnItemSetCapture(SItemPanel *pItem,BOOL bCapture) override; //设置or释放鼠标捕获
		BOOL OnItemGetRect(SItemPanel *pItem,CRect &rcItem) override;    //获得表项的显示位置
		BOOL IsItemRedrawDelay() override;                               //指示表项的更新方式
		void OnItemRequestRelayout(SItemPanel *pItem) override;          //列表项请求重新布局
	protected:

		void UpdateScrollBar();
		void UpdateVisibleItems();


		void RedrawItem(SItemPanel *pItem);
		void _SetSel(int iItem,BOOL bNotify, SWND hHitWnd);
		SItemPanel * GetItemPanel(HTREEITEM hItem);

		void EnsureVisible(HTREEITEM hItem);
		void DispatchMessage2Items(UINT uMsg,WPARAM wParam,LPARAM lParam);
	protected:
		CAutoRefPtr<ITvAdapter>		m_adapter;
		CAutoRefPtr<ITvDataSetObserver>   m_observer;
		CAutoRefPtr<ITreeViewItemLocator> m_tvItemLocator;
        
        struct ItemInfo
        {
            SItemPanel* pItem;
            int         nType;
        };
        SArray<SList<SItemPanel*> *>    m_itemRecycle;//item回收站,每一种样式在回收站中保持一个列表，以便重复利用
		SList<ItemInfo> m_visible_items; //可见元素
		
		typedef SMap<HTREEITEM,ItemInfo> VISIBLEITEMSMAP;
		VISIBLEITEMSMAP * m_pVisibleMap;
		
		pugi::xml_document m_xmlTemplate;

		SItemPanel * m_itemCapture;
		SItemPanel * m_pHoverItem;
        
        HTREEITEM    m_hSelected;               /**< 当前选择项 */ 
        
        BOOL            m_bWantTab;             /**< want tab */ 
    };
}