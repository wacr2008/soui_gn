#pragma once

namespace SOUI
{
    class SButtonEx : public SButton
    {
    SOUI_CLASS_NAME_DECL(SButtonEx,L"buttonex")
    
    enum{
    FREE_DRAW,
    VERT_ICON_TEXT,
    VERT_TEXT_ICON,
    HORZ_ICON_TEXT,
    HORZ_TEXT_ICON,
    };
    
    public:
        SButtonEx(void);
        ~SButtonEx(void);
        
        HICON SetIcon(HICON hIcon,int nIconSize);
        void  SetIconVisible(bool bVisible);
    public:
        SOUI_ATTRS_DECL()
		SOUI_MSG_MAP_DECL()
        
    protected:
        virtual CSize GetDesiredSize(LPCRECT pRcContainer);
        
        CSize GetDesiredSize(IRenderTarget *pRT,LPCRECT pRcContainer);
        CSize GetIconSize();
        void DrawIcon(IRenderTarget *pRT,CRect rcIcon);
    protected:
        void OnPaint(IRenderTarget *pRT);
        
        
        
    protected:
        HICON       m_hIcon;
        int         m_nIconSize;
        
        ISkinObj * m_pIcon;
        int        m_iIcon;//-1代表m_pIcon是一个独占的皮肤
        CPoint     m_ptIcon;
        CPoint     m_ptText;
        CPoint     m_ptPushOffet;
        int        m_nSepSize;
        int         m_drawMode;
        bool        m_bIconVisible;
    };

}
