
// ------------------------------------------------------------------------------
//
// RichEditObj.h : interface of the RichEditObj class
//
// SImRichEdit对象的基类头文件定义，SImRichEdit对象包括但不仅限于以下对象
// 
// - 气泡, 非OLE对象
// - 头像, 非OLE对象
// - 文本, 非OLE对象
// - 图片, OLE对象
// - 文件消息, OLE对象
// - 以上是历史消息, OLE对象
// - 获取更多, OLE对象
//
// 该文件只定义了非OLE对象的RichEdit对象，OLE对象的定义见 RichEditOleCtrls.h
// 
// ------------------------------------------------------------------------------

#pragma once
#include <vector>
#include <TOM.h>
#include "unknown/obj-ref-impl.hpp"
#include "res.mgr/SFontPool.h"
#include "interface/render-i.h"
#include <atlcomcli.h>
#include "IRichEditObjHost.h"
#include <layout/SouiLayoutParamStruct.h>

namespace SOUI
{

#define REOBJ_FIRST   ((RichEditObj*)-1)    /*子对象插入在开头*/
#define REOBJ_LAST    NULL                  /*子对象插入在末尾*/

#define DECLARE_REOBJ(obj,name) \
    SOUI_CLASS_NAME(obj,name) \
    RichEditObj*obj::CreateObject(){ return new obj; }


#define DECLARE_REOBJ_DECL(obj,name) \
    SOUI_CLASS_NAME_DECL(obj,name) \
    static RichEditObj*CreateObject();


    class RichEditObj : public SObject
    {
    public:

        enum AlignType
        {
            ALIGN_LEFT,
            ALIGN_CENTER,
            ALIGN_RIGHT
        };

        // ------------------------------------------------------------------------------
        //
        // methods for user
        //
        // ------------------------------------------------------------------------------

        RichEditObj();
        virtual ~RichEditObj();

        ULONG AddRef();
        ULONG Release();

        virtual BOOL InitFromXml(pugi::xml_node xmlNode);
        virtual void DrawObject(IRenderTarget *);
        virtual LRESULT ProcessMessage(UINT msg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
        virtual BOOL OnUpdateToolTip(CPoint pt, SwndToolTipInfo &tipInfo);
        virtual BOOL InsertIntoHost(IRichEditObjHost * pHost);
        virtual void UpdatePosition();
        virtual void SetDirty(BOOL);
        virtual void OffsetCharRange(int nOffset, BOOL bUpdate = FALSE);
        virtual void ExpandCharRange(int startCp, int nOffset, BOOL bUpdate = FALSE);
        virtual BOOL NeedToProcessMessage() { return FALSE; }
        virtual BOOL GetHitTestable() { return TRUE; }
        virtual AlignType GetAlign() { return _alignType; }
        virtual void SetAlign(AlignType align);
        virtual CRect GetRect() { return _objRect; }
        virtual BOOL PointInObject(POINT pt) { return _objRect.PtInRect(pt); }
        virtual SStringW GetObjType() { return GetClassName(); }
        CHARRANGE GetCharRange() { return _contentChr; }
        void AdjustMessageParam(UINT msg, WPARAM& wParam, LPARAM& lParam);

        SStringW GetName() { return _objName; }
        INT64 GetId() { return _objId; }
        SStringW GetData() { return _userData; }
        int GetScale() const { return 100; }

        //
        // 树操作
        //

        UINT GetChildrenCount();
        void InsertChild(RichEditObj *pNewChild, RichEditObj *pInsertAfter = REOBJ_LAST);
        BOOL RemoveChild(RichEditObj *pChild);
        BOOL CreateChildren(pugi::xml_node xmlNode);
        RichEditObj* GetById(INT64 nId);
        RichEditObj* GetByName(LPCWSTR lpszName);
        RichEditObj* FindChildByName(LPCWSTR pszName, int nDeep = -1);
        RichEditObj* GetParent() const { return _pParent; }
        RichEditObj* GetNext() const { return _pNextSibling; }
        RichEditObj* GetPrev() const { return _pPrevSibling; }
        RichEditObj* GetLastChild()  const { return _pLastChild; }
        RichEditObj* GetFirstChild() const { return _pFirstChild; }
        void DestroyObject();
        BOOL DestroyChild(RichEditObj * pChild);
        void OnDestroy();

    protected:

        // ------------------------------------------------------------------------------
        //
        // internal event handlers
        //
        // ------------------------------------------------------------------------------

		SOUI_ATTRS_DECL()

		RichEditObj *       _pParent;       // 父节点 
        RichEditObj *       _pFirstChild;   // 第一子节点 
        RichEditObj *       _pLastChild;    // 最后节点 
        RichEditObj *       _pNextSibling;  // 前一兄弟节点 
        RichEditObj *       _pPrevSibling;  // 后一兄弟节点 
        UINT                _childrenCount; // 子节点数量 
        ULONG               _references;    // 引用计数器
        INT64					_objId;         // 对象Id
        SStringW            _objName;       // 对象名称 
        SStringW            _userData;      // 用户数据
        SStringW            _cursorName;    // 光标名称 
        IRichEditObjHost *  _pObjHost;      // 宿主richedit 
        CHARRANGE           _contentChr;    // 在richedit里面的字符下标,这个信息很重要
        CRect               _marginRect;    // 对象的外边距 
        CRect               _objRect;       // 在richedit里面的位置 
        BOOL                _isDirty;       // 位置信息改变了 
        AlignType           _alignType;     // 对齐方式,特指横向的对齐方式
    };

    // ------------------------------------------------------------------------------
    //
    // RichEditText interface
    // 
    // RichEdit文本，可设字体、颜色等属性
    //
    // ------------------------------------------------------------------------------

    class RichEditText : public RichEditObj
    {
		DECLARE_REOBJ_DECL(RichEditText, L"text")

    public:

        RichEditText();
        ~RichEditText() {}

        static SStringW MakeFormatedText(const SStringW& text, int fontSize = 10);

        virtual BOOL InitFromXml(pugi::xml_node xmlNode);
        virtual void DrawObject(IRenderTarget *);
        virtual void UpdatePosition();
        virtual CRect GetRect();
        virtual BOOL PointInObject(POINT pt);
        virtual BOOL GetHitTestable();
        virtual BOOL NeedToProcessMessage();
        virtual LRESULT ProcessMessage(UINT msg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
        virtual BOOL InsertIntoHost(IRichEditObjHost * pHost);
        int GetLineCount() { return _lineCount; }
        SStringW GetType() { return GetClassName(); }
        SStringW GetText() { return _text; }
        SStringW GetLinkData() { return _linkData; }
        SStringW GetTextType() { return _textType; }
        void SetText(LPCWSTR pszText);
        void SetLink(BOOL isLink);
        void SetTextStyle(BOOL underline, BOOL bold, BOOL italic, COLORREF color);

    protected:

        void FixText();

        SOUI_ATTRS_DECL()

    private:

        typedef std::vector<CRect> RectVec;

        RectVec     _objRects;
        DWORD       _status;
        COLORREF    _textColor;
        SStringW    _font;
        SStringW    _text;
        SStringW    _linkData;
        SStringW    _textType;
        int         _lineCount;
        BOOL        _isUnderline;
        BOOL        _isBold;
        BOOL        _isItalic;
        BOOL        _isLink;
        int         _fontSize;
    };

    //------------------------------------------------------------------------------
    //
    // RichEditBkElement interface
    // 
    // 背景元素
    //
    //------------------------------------------------------------------------------
    class RichEditBkElement : public RichEditObj
    {
		DECLARE_REOBJ_DECL(RichEditBkElement, L"bkele")
    public:

        RichEditBkElement();
        ~RichEditBkElement();

        void        SetVisible(BOOL visible) { _bVisible = visible; }
        void        SetInteractive(BOOL b) { _isInteractive = b; }
        SStringW    GetType() { return GetClassName(); }
        BOOL        GetHitTestable() { return _bVisible && _hittestable; }
        BOOL        NeedToProcessMessage() { return _bVisible && _isInteractive; }
        void        CalcPosition(POS_INFO * pItemsPos, int nPosCount);
        CRect       GetRect();
        void        SetText(const SStringW& text);
        void        SetSkin(ISkinObj* pSkin, BOOL bAutoFree = TRUE);
        void        SetTextColor(COLORREF cr) { _textColor = cr; }
    protected:

        LRESULT ProcessMessage(UINT msg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
        void    BeforePaint(IRenderTarget *pRT, SPainter &painter);
        void    AfterPaint(IRenderTarget *pRT, SPainter &painter);
        void    DrawObject(IRenderTarget *);
        int     PositionItem2Value(const POS_INFO &pos, int nMin, int nMax, BOOL bX);
        BOOL    ParsePosition34(POS_INFO* pPosItem, const SStringW & strPos3, const SStringW &strPos4);
        BOOL    ParsePosition12(POS_INFO* pPosItem, const SStringW & strPos1, const SStringW &strPos2);
        BOOL    StrPos2ItemPos(const SStringW &strPos, POS_INFO & pos);
        HRESULT OnAttrSkin(const SStringW& strValue, BOOL bLoading);
        HRESULT OnAttrPos(const SStringW& strValue, BOOL bLoading);
        HRESULT OnAttrPosLeft(const SStringW& strValue, BOOL bLoading);
        HRESULT OnAttrPosCenter(const SStringW& strValue, BOOL bLoading);
        HRESULT OnAttrPosRight(const SStringW& strValue, BOOL bLoading);
        HRESULT OnInternalAttrPos(POS_INFO* pPosItem, int& nPosCount, const SStringW& strValue, BOOL bLoading);

        SOUI_ATTRS_DECL() 

    protected:

        int             _textFormat;
        SStringW        _font;
        SStringW        _text;
        COLORREF        _textColor;
        BOOL            _bVisible;          // 是否显示
        DWORD           _status;            // 标记鼠标状态，用来辅助判断是否点击了区域
        BOOL            _isInteractive;     // 是否需要接受消息，比如WM_MOUSEMOVE
        BOOL            _hittestable;       // 能否被hittest

        int             _defPosCount;       // 定义左对齐时的坐标个数 */
        POS_INFO        _defPosItems[4];    // 由pos属性定义的值, _defPosCount >0 时有效*/
        int             _centerPosCount;    // 定义居中对齐时的坐标个数 */
        POS_INFO        _centerPosItems[4]; // 由pos属性定义的值, _centerPosCount >0 时有效*/
        int             _rightPosCount;     // 定义右对齐时的坐标个数 */
        POS_INFO        _rightPosItems[4];  // 由pos属性定义的值, _rightPosCount >0 时有效*/

        ISkinObj *      _pLeftSkin;         // 默认图片，一般是左对齐的skin
        ISkinObj *      _pCenterSkin;       // 居中对齐的skin
        ISkinObj *      _pRightSkin;        // 右对齐的skin

        SStringW        _data;              // 用户数据
    };

    // ------------------------------------------------------------------------------
    //
    // RichEditPara interface
    // 
    // 段落。主要实现了左右缩进效果，右对齐效果采用左缩进模拟
    //
    // ------------------------------------------------------------------------------

    class RichEditPara : public RichEditObj
    {
		DECLARE_REOBJ_DECL(RichEditPara, L"para")

    public:

        RichEditPara();
        ~RichEditPara() {}

        SStringW    GetType() { return GetClassName(); }
        BOOL        GetHitTestable() { return FALSE; }
        CRect       GetRect();
        void        UpdatePosition();
        BOOL        InsertIntoHost(IRichEditObjHost * pHost);
        void        SetAlign(AlignType align);
        BOOL        IsWrapped();
        void        OffsetCharRange(int nOffset, BOOL bUpdate = FALSE);
        void        SetCharRange(const CHARRANGE& chr);

    protected:

        BOOL    GetAutoWrapped();
        BOOL    CalculateRect();
        BOOL    GetLineRect(int nLineNo, CRect& rcLine);

        SOUI_ATTRS_DECL()

            BOOL    _autoWrapped;      /**< 是否一行显示不下,自动换行了*/
        BOOL    _needUpdateLayout; /**< 标记是否需要重新设置缩进*/
        BOOL    _simulateAlign;    /**< 是否模拟右对齐。即设置左缩进,达到右对齐效果*/
        int     _breakAtTheEnd;    /**< 是否在段落后加上一个回车*/
        int     _lineCount;        /**< 文本的行数,用来判断是否自动换行了*/
        BOOL    _initialized;
        BOOL    _disableLayout;    /**< 不需要布局 */
    };

    // ------------------------------------------------------------------------------
    //
    // RichEditContent interface
    // 
    // RichEdit内容的容器。所有的对象在插入RichEdit前需要放置在该容器下。
    //
    // ------------------------------------------------------------------------------

    class RichEditContent : public RichEditObj
    {
#define THRESHOLD_FOR_AUTOLAYOUT 1924 // 自动布局的阀值

		DECLARE_REOBJ_DECL(RichEditContent, L"RichEditContent")

    public:

        RichEditContent() :_autoLayout(FALSE) {}
        ~RichEditContent() {}

        virtual void  UpdatePosition();
        virtual BOOL  GetHitTestable() { return FALSE; }
        virtual CRect GetRect();
        SStringW    GetObjType() { return GetClassName(); }
        SStringW    GetContentType() { return _contentType; }
        time_t      GetTimestamp() { return _timestamp; }

    protected:

        BOOL OnTimestampAttr(const SStringW& attr, BOOL bLoading);

        SOUI_ATTRS_DECL()

            SStringW    _contentType;
        BOOL        _autoLayout;
        time_t      _timestamp;
    };

} // namespace SOUI