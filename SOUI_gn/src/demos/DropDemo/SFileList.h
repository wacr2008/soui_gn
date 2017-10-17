/**
* Copyright (C) 2014-2050 SOUI团队
* All rights reserved.
* 
* @file       SListCtrl.h
* @brief      
* @version    v1.0      
* @author     soui      
* @date       2014-07-06
* 
* Describe    ListCtrl控件 
*/
#pragma once
#include "core/SPanel.h"
#include "control/SHeaderCtrl.h"

namespace SOUI
{   
/////////////FileList 控件  左键 单击事件 
class EventFLClick : public TplEventArgs<EventFLClick>
{
	SOUI_CLASS_NAME(EventFLClick, L"on_filelist_click")
public:
	EventFLClick(SObject *pSender) :TplEventArgs<EventFLClick>(pSender){}
	enum{ EventID = EVT_LC_SELCHANGING + 20 };
	int		iItem;
};
/////////////FileList 控件  左键 双击事件 
class EventFLDBClick : public TplEventArgs<EventFLDBClick>
{
	SOUI_CLASS_NAME(EventFLDBClick, L"on_filelist_dbclick")
public:
	EventFLDBClick(SObject *pSender) :TplEventArgs<EventFLDBClick>(pSender){}
	enum{ EventID = EVT_LC_SELCHANGING + 21 };
	int		iItem;
};
/////////////FileList 控件 右键菜单 事件
class EventFLMenu : public TplEventArgs<EventFLMenu>
{
	SOUI_CLASS_NAME(EventFLMenu, L"on_filelist_menu")
public:
	EventFLMenu(SObject *pSender) :TplEventArgs<EventFLMenu>(pSender){}
	enum{ EventID = EVT_LC_SELCHANGING + 22 };
	int		iItem;
	CPoint pt;
};
/////////////FileList 控件 列头 点击事件
class EventFLColClick : public TplEventArgs<EventFLColClick>
{
	SOUI_CLASS_NAME(EventFLColClick, L"on_filelist_colclick")
public:
	EventFLColClick(SObject *pSender) :TplEventArgs<EventFLColClick>(pSender){}
	enum{ EventID = EVT_LC_SELCHANGING + 23 };
	int		iCol;				//点击的列数
	bool		bAscOrder;	//升序
};
/////////////FileList控件 选中项 拖拽 事件
class EventFLBeginDrag : public TplEventArgs<EventFLBeginDrag>
{
	SOUI_CLASS_NAME(EventFLBeginDrag, L"on_filelist_begindrag")
public:
	EventFLBeginDrag(SObject *pSender) :TplEventArgs<EventFLBeginDrag>(pSender){}
	enum{ EventID = EVT_LC_SELCHANGING + 25 };
	int		iItem;
};

// FileList 每列 的数据 
typedef struct _FLSubData
{
	_FLSubData()
	{
        lpszText = NULL;
        nTextLen = 0;
	}

	LPTSTR  lpszText;      /**< 文本 */
	int			nTextLen;   /**< 文本数 */
} FLSubData;

// FileList 每行 的数据 
typedef struct _FLItemData
{    
	_FLItemData()
	{
		bChecked = false;
		nImage = 0;
		dwData = 0;
		arrSubItems = NULL;
	}
				
	bool							bChecked;
	int								nImage;
	DWORD						dwData;
	SArray<FLSubData>*	arrSubItems;
} FLItemData;

typedef int (__cdecl  *pFileListSortFun)(void* pThis, const FLItemData*, const FLItemData*);//使用快速排序算法中的比较函数,参考qsort_s
	
//  SFileList
class SFileList : public SPanel
{
    SOUI_CLASS_NAME(SFileList, L"filelist")
	friend class SFileListDataSet;
public:
	SFileList();
	~SFileList();
	int InsertColumn(int nIndex, LPCTSTR pszText, int nWidth, LPARAM lParam=0);
	void DeleteColumn(int iCol);
	int InsertItem(int nItem, LPCTSTR pszText, int nImage=-1);
	BOOL SetItemData(int nItem, DWORD dwData);
	DWORD GetItemData(int nItem);
	BOOL SetSubItemText(int nItem, int nSubItem, LPCTSTR pszText);
	SStringT GetSubItemText(int nItem, int nSubItem) const;
	void DeleteItem(int nItem);
	void DeleteAllItems();
	int GetItemCount() const;

	int GetSelectedItem();
	void SetSelectedItem(int nItem);
		
	int GetColumnCount() const;
	int GetCountPerPage(BOOL bPartial);
	
	virtual BOOL CreateChildren(pugi::xml_node xmlNode);
	int HitTest(const CPoint& pt);
	bool SetHeaderItemSort(int nCol, bool bAsc);		//设置列头 排序标志
	BOOL SortItems(pFileListSortFun pfnCompare, void * pContext );
	bool GetCheckState(int nItem);  
	bool SetCheckState(int nItem, bool bCheck);  
	int GetCheckedItemCount();
	int GetFirstCheckedItem();
	int GetLastCheckedItem();
	void EnableMultiSelection(BOOL enable) { m_bMultiSelection = enable; }
	void EnableCheckBox(BOOL enable) { m_bCheckBox = enable; }
	void EnableHotTrack(BOOL enable) { m_bHotTrack = enable; }
protected:
	int GetTopIndex() const;
	CRect GetItemRect(int nItem, int nSubItem=0);
	virtual void DrawItem(IRenderTarget *pRT, CRect rcItem, int nItem);
	void RedrawItem(int nItem);
	void NotifySelChange(int nOldSel, int nNewSel, BOOL checkBox = FALSE);
	void OnPaint(IRenderTarget *pRT);
	void OnDestroy();
	bool OnHeaderClick(EventHeaderClick* pEvt);
	bool OnHeaderSizeChanging(EventHeaderItemChanging* pEvt);
	bool OnHeaderSwap(EventHeaderItemSwap* pEvt);
	virtual BOOL OnScroll(BOOL bVertical,UINT uCode,int nPos);

	void OnLButtonDown(UINT nFlags, CPoint pt);
	void OnLButtonUp(UINT nFlags, CPoint pt);
	void OnMouseMove(UINT nFlags, CPoint pt);
	void OnMouseLeave();
	void OnLButtonDbClick(UINT nFlags, CPoint point);
	void OnRButtonDown(UINT nFlags, CPoint pt);
	void OnRButtonUp(UINT nFlags, CPoint pt);
	void OnSize(UINT nType, CSize size);
	virtual void UpdateChildrenPosition();
	CRect GetListRect();
	void UpdateScrollBar();
    void UpdateHeaderCtrl();
	//BOOL HitCheckBox(const CPoint& pt);
	enum EnHitItemPos
	{
		eHIP_NULL = 0,				//空白处
		eHIP_CheckBox,				// checkbox 
		eHIP_TextContent,			//text 正文上 
	};
	// 根据 pt  判断鼠标位置 
	EnHitItemPos HitItemPos(int nItem, const CPoint& pt);
protected:
    int					m_nHeaderHeight;  /**< 列表头高度 */
    int					m_nItemHeight;  /**< 条目高度 */

    int					m_nSelectItem;  /**< 选中项 */
    int					m_nHoverItem;  /**< Hover状态项 */
	int					m_nClickItem;	/**< 点击项 */
	int					m_nFirstColOffsetX;			// 第一列 的x 偏移量
    BOOL				m_bHotTrack;  /**<  */
	BOOL				m_bCheckBox;
	BOOL				m_bMultiSelection;
	BOOL				m_bStartSelect;				
	BOOL				m_bDroped;			//已经在 拖放了 
	bool				m_bLdbClicked;			//双击了 记录 

    CPoint          m_ptIcon;  /**< 图标位置 */
    CPoint          m_ptText;  /**< 文本位置 */
	// by bin at 2016 11 17
	CPoint          m_ptClick;   /**< 当前点击坐标 */
	CPoint          m_ptMove;   /**< 当前坐标 */
	

    COLORREF        m_crItemBg;  /**< 背景色 */
    COLORREF        m_crItemBg2;  /**< 背景色 */
    COLORREF        m_crItemSelBg;  /**< 选中背景色 */
	COLORREF        m_crItemHotBg;  /**< Hot背景色 */
    COLORREF        m_crText;  /**< 文本颜色 */
    COLORREF        m_crSelText;  /**< 选中文本颜色 */

    ISkinObj*		m_pItemSkin;  /**< */
    ISkinObj*		m_pIconSkin;  /**< */
    ISkinObj*		m_pCheckSkin; /**< */
    
protected:
	SArray<FLItemData>	m_arrItems;
	CPoint          m_ptOrigin;  /**< */
	SHeaderCtrl*  m_pHeader;  /**< 列表头控件 */
	//IFLAdapter*	m_iFLAdapter;
	//IListDataSet*	m_iListDataSet;
protected:
    SOUI_ATTRS_BEGIN()
        ATTR_INT(L"headerHeight", m_nHeaderHeight, FALSE)
        ATTR_INT(L"itemHeight", m_nItemHeight, FALSE)
        ATTR_INT(L"checkBox", m_bCheckBox, TRUE)
        ATTR_INT(L"multiSelection", m_bMultiSelection, TRUE)
        ATTR_SKIN(L"itemSkin", m_pItemSkin, TRUE)
        ATTR_SKIN(L"iconSkin", m_pIconSkin, TRUE)
        ATTR_SKIN(L"checkSkin", m_pCheckSkin, TRUE)
        ATTR_COLOR(L"colorItemBkgnd", m_crItemBg, FALSE)
        ATTR_COLOR(L"colorItemBkgnd2", m_crItemBg2, FALSE)
        ATTR_COLOR(L"colorItemHotBkgnd", m_crItemHotBg, FALSE)
        ATTR_COLOR(L"colorItemSelBkgnd", m_crItemSelBg, FALSE)
        ATTR_COLOR(L"colorText", m_crText, FALSE)
        ATTR_COLOR(L"colorSelText", m_crSelText, FALSE)
        ATTR_INT(L"icon-x", m_ptIcon.x, FALSE)
        ATTR_INT(L"icon-y", m_ptIcon.y, FALSE)
        ATTR_INT(L"text-x", m_ptText.x, FALSE)
        ATTR_INT(L"text-y", m_ptText.y, FALSE)
        ATTR_INT(L"hotTrack", m_bHotTrack, FALSE)
    SOUI_ATTRS_END()

    SOUI_MSG_MAP_BEGIN()
        MSG_WM_PAINT_EX(OnPaint)
        MSG_WM_DESTROY(OnDestroy)
        MSG_WM_SIZE(OnSize)
        MSG_WM_LBUTTONDOWN(OnLButtonDown)
        MSG_WM_LBUTTONUP(OnLButtonUp)
		MSG_WM_LBUTTONDBLCLK(OnLButtonDbClick)
		MSG_WM_RBUTTONDOWN(OnRButtonDown)
		MSG_WM_RBUTTONUP(OnRButtonUp)
        MSG_WM_MOUSEMOVE(OnMouseMove)
        MSG_WM_MOUSELEAVE(OnMouseLeave)
    SOUI_MSG_MAP_END()
};

}//end of namespace
