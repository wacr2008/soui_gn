#pragma once

namespace SOUI
{
    class SFreeMoveWindow : public SWindow
    {
    SOUI_CLASS_NAME_DECL(SFreeMoveWindow,L"freeMoveWindow")
    public:
        SFreeMoveWindow(void);
        ~SFreeMoveWindow(void);
        
    protected:
        virtual void OnUpdateFloatPosition(const CRect & rcParent);
    protected:
        void OnLButtonDown(UINT nFlags,CPoint pt);

        void OnLButtonUp(UINT nFlags,CPoint pt);

        void OnMouseMove(UINT nFlags,CPoint pt);

        SOUI_MSG_MAP_DECL()
		SOUI_ATTRS_DECL()
        
    protected:
        enum {
        HALIGN_LEFT = 0x01,
        HALIGN_RIGHT = 0x02,
        VALIGN_TOP   = 0x10,
        VALIGN_BOTTOM = 0x20,
        };
        
        
        int m_nFloatVAlign;
        int m_nFloatHAlign;
        int m_nDistX,m_nDistY;
        
        BOOL m_bDraging;
        CPoint m_ptClick;
    };

}
