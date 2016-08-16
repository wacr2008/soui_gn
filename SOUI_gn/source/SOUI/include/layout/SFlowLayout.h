#pragma once
#include "core/SWnd.h"


namespace SOUI
{  
	/// <summary>
	///		流式布局基类
	/// </summary>
	class SOUI_EXP SFlowLayout : public SWindow
	{
		SOUI_CLASS_NAME(SFlowLayout, L"FlowLayout")
	public:
		SFlowLayout();
		bool DV_IsStateChangeRedraw(){return false;}

	public:
		SOUI_ATTRS_BEGIN()
			ATTR_INT(L"childpaddlen", m_iChildPaddLen, 0)
		SOUI_ATTRS_END()
	public:
		int                            m_iChildPaddLen;		///<子控件之间的额外距离	
	};

	/// <summary>
	///		竖直流式布局
	/// </summary>
	class SOUI_EXP SVBox : public SFlowLayout
	{
		SOUI_CLASS_NAME(SVBox, L"VBox")
	public:
		void UpdateChildrenPosition();
	};

	/// <summary>
	///		水平流式布局
	/// </summary>
	class SOUI_EXP SHBox:public SFlowLayout
	{
		SOUI_CLASS_NAME(SHBox, L"VBox")
	public:
		void UpdateChildrenPosition();
	};

	/// <summary>
	///		tab流式布局，大小相同
	/// </summary>
	class SOUI_EXP STableLayout : public SFlowLayout
	{
		SOUI_CLASS_NAME(STableLayout, L"TableLayout") 
	public:
		void UpdateChildrenPosition();

	public:
		SOUI_ATTRS_BEGIN()
			ATTR_INT(L"itemsize", m_szItem, 3)
		SOUI_ATTRS_END() 
	public:
		CSize                          m_szItem;
	};

	/// <summary>
	///		Warp流式布局
	/// </summary>
	class SOUI_EXP SWrapLayout : public STableLayout
	{
		SOUI_CLASS_NAME(STableLayout, L"WrapLayout")
	public:
		void UpdateChildrenPosition();

	public:
		SOUI_ATTRS_BEGIN()
			ATTR_INT(L"colcount", m_nColumns, 0) // 在没有设置size时，依赖它来自动设置宽度
		SOUI_ATTRS_END()
	public:
		int                            m_nColumns;
	};

	// <summary>
	///		 SSplitLayout分割布局的内置实现，属性：<see cref="DMAttr::DUISplitterAttr"/>
	/// 简化:仅两个窗口（A,B）构成,当整个外部窗口size变化时，要么A窗口变化，要么B窗口变化，2选一
	/// </summary>
	class SSplitLayout:public SFlowLayout
	{
		SOUI_CLASS_NAME(SSplitLayout, L"splitlayout")
	public:
		SSplitLayout();
	public: 
		SOUI_MSG_MAP_BEGIN()
			MSG_WM_PAINT_EX(OnPaint)
			MSG_WM_LBUTTONDBLCLK(OnLButtonDown) //将双击消息处理为单击
			MSG_WM_LBUTTONUP(OnLButtonUp)
			MSG_WM_MOUSEMOVE(OnMouseMove)
		SOUI_MSG_MAP_END() 
	public:
		void OnPaint(IRenderTarget *pRT);
		void OnLButtonDown(UINT nFlags, CPoint pt);
		void OnLButtonUp(UINT nFlags,CPoint pt);
		void OnMouseMove(UINT nFlags,CPoint pt);

	public: 
		virtual BOOL CreateChildren(pugi::xml_node xmlNode); 
		void UpdateChildrenPosition();
		virtual BOOL OnSetCursor(const CPoint &pt);

	public:// 辅助      
		BOOL UpdateFixWidth();
		void UpdateDrag(int iDiff);
		CRect GetSliderRect();
	protected:
		HRESULT OnAttrVert(const SStringW& strValue, BOOL bLoading);
		HRESULT OnAttrFirstchange(const SStringW& strValue, BOOL bLoading);
		HRESULT OnAttrSliderSkin(const SStringW& strValue, BOOL bLoading);
		
	public: 
		SOUI_ATTRS_BEGIN()
			ATTR_CUSTOM(L"bvert", OnAttrVert)
			ATTR_CUSTOM(L"bfirstchange", OnAttrFirstchange)
			ATTR_INT(L"sliderwidth", m_iSliderWid, TRUE)
			ATTR_INT(L"firstchildwidth", m_iFirstChildWidth, TRUE)
			ATTR_CUSTOM(L"sliderskin", OnAttrSliderSkin)
			ATTR_COLOR(L"clrslider", m_ClrSlider, FALSE)
		SOUI_ATTRS_END() 
	public:
		bool                             m_bVert;                ///< 是否竖直
		int                              m_iSliderWid;           ///< 中间可拖动块的宽度(水平)或高度(竖直)
		ISkinObj                         *m_pSliderSkin;
		COLORREF                         m_ClrSlider;
		bool                             m_bFirstChange;
		int                              m_iFirstChildWidth;     ///< 第一个窗口的初始值
		int                              m_iFixWid;              ///< 固定的宽度，为0表示未初始化,其余表示size变化时，固定size的那个窗口
		bool                             m_bDrag;
		CPoint                           m_ptDrag;
		SStringT                         m_strPos;
	};
}
//namespace SOUI