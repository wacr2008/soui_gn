#pragma once

#include <control/SListbox.h>
#include <souicoll.h>
#include "SPropertyItemBase.h"

namespace SOUI
{
    #define EVT_PG_VALUECHANGED (EVT_EXTERNAL_BEGIN+100)
	//ADD
    #define EVT_PG_ITEMCLICK (EVT_EXTERNAL_BEGIN+110)
    #define EVT_PG_ITEMACTIVE (EVT_EXTERNAL_BEGIN+101)

    class EventPropGridValueChanged : public TplEventArgs<EventPropGridValueChanged>
    {
        SOUI_CLASS_NAME_DECL(EventPropGridValueChanged,L"on_propgrid_value_changed")
    public:
        EventPropGridValueChanged(SObject *pWnd):TplEventArgs<EventPropGridValueChanged>(pWnd){}
        enum{EventID=EVT_PG_VALUECHANGED};

        IPropertyItem * pItem;
    };



	class EventPropGridItemClick : public TplEventArgs<EventPropGridItemClick>
	{
		SOUI_CLASS_NAME_DECL(EventPropGridItemClick,L"on_propgrid_item_click")
	public:
		EventPropGridItemClick(SObject *pWnd):TplEventArgs<EventPropGridItemClick>(pWnd){}
		enum{EventID=EVT_PG_ITEMCLICK};

		IPropertyItem * pItem;
		SStringT strType;
	};


	class EventPropGridItemActive : public TplEventArgs<EventPropGridItemActive>
	{
		SOUI_CLASS_NAME_DECL(EventPropGridItemActive,L"on_propgrid_item_active")
	public:
		EventPropGridItemActive(SObject *pWnd):TplEventArgs<EventPropGridItemActive>(pWnd){}
		enum{EventID=EVT_PG_ITEMACTIVE};

		IPropertyItem * pItem;
	};

    class SPropertyGroup : public SPropertyItemBase
    {
        SOUI_CLASS_NAME_DECL(SPropertyGroup,L"propgroup")
    public:
        virtual BOOL IsGroup() const {return TRUE;}
        virtual void DrawItem(IRenderTarget *pRT,CRect rc);
                
        static IPropertyItem * CreatePropItem(SPropertyGrid *pOwner)
        {
            return new SPropertyGroup(pOwner);
        }
        
    protected:
        SPropertyGroup(SPropertyGrid *pOwner):SPropertyItemBase(pOwner)
        {
        }
    };
    
    typedef IPropertyItem * (__cdecl *FunCreatePropItem)(SPropertyGrid *);

    template<class T>
    T * CreatePropItem(SPropertyGrid *pOwner)
    {
        return static_cast<T*>(T::CreatePropItem(pOwner));
    }
    
    class SPropItemMap : public SMap<SStringW,FunCreatePropItem>
    {
    public:
        static void RegPropItem(const SStringW & strName, FunCreatePropItem funCreate);
        static IPropertyItem * CreatePropItem(const SStringW & strName,SPropertyGrid *pOwner );
    protected:
        SPropItemMap();
        
        static SPropItemMap s_mapPropItem;
    };
    
    #define IG_FIRST (SPropertyGroup*)0
    #define IG_LAST  (SPropertyGroup*)1
    
    class SPropertyGrid : public SListBox
    {
        SOUI_CLASS_NAME_DECL(SPropertyGrid, L"propgrid")
    public:
        enum EXPSTATE
        {
            GROUP_EXPANDED,
            GROUP_COLLAPSED,
            ITEM_EXPANDED,
            ITEM_EXCOLLAPSED,
        };

        enum ORDERTYPE
        {
            OT_NULL,
            OT_GROUP,
            OT_NAME,
        };
        SPropertyGrid(void);
        ~SPropertyGrid(void);
        
        int GetIndent();
        
        void OnItemExpanded(IPropertyItem *pItem);
        CRect GetItemRect(IPropertyItem *pItem) const;
        
        void SortInsert(IPropertyItem *pItem);
        
        BOOL InsertGroup(SPropertyGroup * pGroup,SPropertyGroup* pInertAfter=IG_LAST);

		//add
		 BOOL AddGridItem(IPropertyItem* Item);
		 BOOL RemoveGridItem(IPropertyItem *Item);
		 BOOL RemoveAllGridItem();
		 void ClearAllGridItemValue();
		 IPropertyItem * GetGridItem(SStringT strName2);

		 //SMap<SStringT, IPropertyItem*>* GetItemMap();
        
        SOUI_ATTRS_DECL()
        
		SOUI_MSG_MAP_DECL()
    protected:
        enum ITEMPART
        {
            IP_NULL,
            IP_SWITCH,
            IP_NAME,
            IP_VALUE,
        };
        ITEMPART HitTest(int iItem, const CPoint &pt);
        void SortItems(SList<IPropertyItem*> & lstItems);

        virtual BOOL CreateChildren(pugi::xml_node xmlNode);
        
        virtual void DrawItem(IRenderTarget *pRT, CRect &rc, int iItem);
        virtual UINT OnGetDlgCode(){return SC_WANTALLKEYS;}
        virtual BOOL OnSetCursor(const CPoint &pt);
        virtual BOOL OnScroll(BOOL bVertical,UINT uCode,int nPos);




        
        void OnLButtonDown(UINT nFlags,CPoint pt);
        void OnLButtonUp(UINT nFlags,CPoint pt);
        void OnMouseMove(UINT nFlags,CPoint pt);
        void OnLButtonDbClick(UINT nFlags, CPoint point);
        void OnSize(UINT nType, CSize size);
        
    public:
        void OnInplaceActiveWndCreate(IPropertyItem *pItem,SWindow *pWnd,pugi::xml_node xmlInit);
        void OnInplaceActiveWndDestroy(IPropertyItem *pItem,SWindow *pWnd);
        void OnItemValueChanged(IPropertyItem *pItem);
        void OnItemButtonClick(IPropertyItem *pItem, SStringT strType);
    protected:
        SWindow *   m_pInplaceActiveWnd;    //属性内嵌的窗口
        
    protected:
        bool OnSelChanged(EventArgs *pEvt);
        bool OnCmdBtnClicked(EventArgs *pEvt);
        
        int ExpandChildren(const IPropertyItem *pItem,int iInsert);
        void CollapseChildren(const IPropertyItem *pItem,int idx);
        
        int IndexOfPropertyItem(const IPropertyItem *pItem) const;
        enum {CHILD_CMDBTN=1,CHILD_INPLACEWND=2};
        void UpdateChildrenPos(UINT childs=CHILD_CMDBTN|CHILD_INPLACEWND);
        
        int m_nIndent;          //缩进大小
        int m_nNameWidth;    //属性名占用空间
        ORDERTYPE   m_orderType;
        SList<SPropertyGroup *> m_lstGroup; //根分类列表
        ISkinObj  *  m_switchSkin;
        SWindow   *  m_pCmdBtn; //有弹出按钮的表项使用的按钮
                
        CPoint      m_ptDrag;
        BOOL        m_bDraging;

		COLORREF m_crGroup;       //Group背景颜色
		COLORREF m_crItem;        //Item背景颜色
		COLORREF m_crItemText;    //Item文本颜色
		COLORREF m_crItemSel;     //Item选中时的背景色
		SStringT m_strEditBkgndColor; //edit的背景色;
		SStringT m_strEditTextColor; //edit的文本颜色;
		COLORREF m_crBorder;      //边框颜色
		SStringT    m_strEnableAutoWordSel;    /**< enable Word style auto word selection?  */
        
		//add
        SMap<SStringT, IPropertyItem*> m_mapItem;
        static SMap<SStringW, FunCreatePropItem> s_mapProps;
    };
    
}
