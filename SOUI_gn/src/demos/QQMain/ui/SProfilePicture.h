#pragma once

namespace SOUI
{
    class SProfilePicture : public SWindow
    {
        SOUI_CLASS_NAME_DECL(SProfilePicture, L"ProfilePic")
    public:
        SProfilePicture();
        ~SProfilePicture();

        void SetHeadPic(const SStringT& szPath);
        void InitHeadPic();

        enum eCusEvent
        {
            EVT_FRAMECHANGE = 90000
        };

        class EventSelFrameChange : public TplEventArgs<EventSelFrameChange>
        {
            SOUI_CLASS_NAME_DECL(EventSelFrameChange, L"on_headpic_framechange")
        public:
            EventSelFrameChange(SObject *pSender) :TplEventArgs<EventSelFrameChange>(pSender) {}
            enum {
                EventID = EVT_FRAMECHANGE
            };
            CAutoRefPtr<IBitmap>           iBmp;
        };

    protected:
        void OnLButtonDown(UINT nFlags, CPoint pt);
        void OnLButtonUp(UINT nFlags, CPoint pt);
        void OnMouseMove(UINT nFlags, CPoint pt);
        void OnPaint(IRenderTarget *pRT);

        SOUI_MSG_MAP_DECL() 
    private:
        enum eMoveType
        {
            TYPE_UNKNOW,
            TYPE_LEFTTOP,
            TYPE_LEFTBOTTOM,
            TYPE_RIGHTTOP,
            TYPE_RIGHTBOTTOM,
            TYPE_ALL,
        };
    public:
        CAutoRefPtr<IBitmap> m_bmpSelHead;

    private:
        CAutoRefPtr<IBitmap> m_bmpHead;
        CAutoRefPtr<IRenderTarget> m_pScreenRT;
        CAutoRefPtr<IRenderTarget> m_pHuiRT;
        CPoint m_BeginPoint;
        CPoint m_EndPoint;
        CRect m_PicRect;
        CRect m_FrameRect;
        BOOL m_bDraging;
        CPoint m_ptClick;
        int m_nY;
        int m_nX;
        eMoveType m_eMoveType;
    };
}
