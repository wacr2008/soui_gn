#pragma once

#include "core/Swnd.h"
#include "core/SItemPanel.h"
#include "interface/Adapter-i.h"
#include "interface/LvItemLocator-i.h"
namespace SOUI
{
    
    class SOUI_EXP SListView : public SPanel
        , protected IItemContainer
    {
        SOUI_CLASS_NAME_DECL(SListView,L"listview")

        friend class SListViewDataSetObserver;
    public:
        SListView();
        ~SListView() override;

        BOOL SetAdapter(ILvAdapter * adapter);
        
        ILvAdapter * GetAdapter() {
            return m_adapter;
        }
        
        IListViewItemLocator * GetItemLocator(){
            return m_lvItemLocator;
        }
        
        void SetItemLocator(IListViewItemLocator *pItemLocator);
        void EnsureVisible( int iItem );
        
        void SetSel(int iItem,BOOL bNotify=FALSE);
        int  GetSel()const{return m_iSelItem;}
        
        SItemPanel * HitTest(CPoint & pt);
    protected:
        void OnItemSetCapture(SItemPanel *pItem,BOOL bCapture) override;
        BOOL OnItemGetRect(SItemPanel *pItem,CRect &rcItem) override;
        BOOL IsItemRedrawDelay() override;
        void OnItemRequestRelayout(SItemPanel *pItem) override;
        
    protected:
        void onDataSetChanged();
        void onDataSetInvalidated();

    protected:
        bool OnItemClick(EventArgs *pEvt);
        
    protected:
        BOOL OnScroll(BOOL bVertical,UINT uCode,int nPos) override;
        int  GetScrollLineSize(BOOL bVertical) override;
        BOOL CreateChildren(pugi::xml_node xmlNode) override;

        BOOL OnUpdateToolTip(CPoint pt, SwndToolTipInfo & tipInfo) override;
        UINT OnGetDlgCode() override;
        BOOL OnSetCursor(const CPoint &pt) override;

		void OnColorize(COLORREF cr) override;
		void OnScaleChanged(int nScale) override;
		HRESULT OnLanguageChanged() override;
    protected:
		void DispatchMessage2Items(UINT uMsg,WPARAM wParam,LPARAM lParam);

        void UpdateScrollBar();
        void RedrawItem(SItemPanel *pItem);
        SItemPanel * GetItemPanel(int iItem);
        
        void UpdateVisibleItems();
        
        void OnPaint(IRenderTarget *pRT);
        void OnSize(UINT nType, CSize size);
        void OnDestroy();

        LRESULT OnMouseEvent(UINT uMsg,WPARAM wParam,LPARAM lParam);

        LRESULT OnKeyEvent( UINT uMsg,WPARAM wParam,LPARAM lParam );
        void OnKeyDown( TCHAR nChar, UINT nRepCnt, UINT nFlags );

        void OnMouseLeave();

        BOOL OnMouseWheel(UINT nFlags, short zDelta, CPoint pt);
        
        void OnKillFocus(SWND wndFocus);
        
        void OnSetFocus(SWND wndOld);

        SOUI_MSG_MAP_DECL() 

        SOUI_ATTRS_DECL() 
	protected:
        CAutoRefPtr<ILvAdapter>           m_adapter;
        CAutoRefPtr<ILvDataSetObserver>   m_observer;
        CAutoRefPtr<IListViewItemLocator>  m_lvItemLocator;//列表项定位接口
        struct ItemInfo
        {
            SItemPanel *pItem;
            int nType;
        };
        
        int                             m_iFirstVisible;//第一个显示项索引
        SList<ItemInfo>                 m_lstItems; //当前正在显示的项
        SItemPanel*                     m_itemCapture;//The item panel that has been set capture.
        
        int                             m_iSelItem;
        SItemPanel*                     m_pHoverItem;
        BOOL                            m_bDataSetInvalidated;
        
        SArray<SList<SItemPanel*> *>    m_itemRecycle;//item回收站,每一种样式在回收站中保持一个列表，以便重复利用
                
        pugi::xml_document              m_xmlTemplate;
        ISkinObj*                       m_pSkinDivider;
        SLayoutSize                     m_nDividerSize;
        BOOL                            m_bWantTab;
    };
}