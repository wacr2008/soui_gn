#pragma once

namespace SOUI
{
    class SScrollText : public SStatic , public ITimelineHandler
    {
        SOUI_CLASS_NAME_DECL(SScrollText,L"scrolltext")
    public:
        SScrollText(void);
        ~SScrollText(void);
        
        void SetWindowText(const SStringT & strText);
    protected:
        virtual void OnNextFrame();
    protected:
        void OnPaint(IRenderTarget *pRT);
        void OnSize(UINT nType, CSize size);
        void OnShowWindow(BOOL bShow, UINT nStatus);
        void OnDestroy();

        void UpdateScrollInfo(CSize size);
        
        SOUI_MSG_MAP_DECL()
        
        SOUI_ATTRS_DECL()
        
        int m_nSpeed;
        int m_nOffset;
        int m_nScrollWidth;
        int m_nNextInterval;
		int m_nRollType;//0首位衔接 1 非衔接
    };

}
