#pragma once

namespace SOUI
{
    class SRatingBar : public SWindow
    {
    SOUI_CLASS_NAME_DECL(SRatingBar,L"ratingbar")
    public:
        SRatingBar(void);
        ~SRatingBar(void);
        
        void SetValue(float fValue);
    protected:
        void DrawStars(IRenderTarget *pRT,CRect rc,BOOL bForeground);
        
        virtual CSize GetDesiredSize(LPCRECT pRcContainer);
        
        void OnPaint(IRenderTarget *pRT);
        
        SOUI_MSG_MAP_DECL()
        
        SOUI_ATTRS_DECL() 
        
    protected:
        ISkinObj * m_pStar;
        int     m_nStars;
        float   m_fValue;
    };

}
