#include "SCaptureButton.h"

namespace SOUI
{
	SOUI_CLASS_NAME(EventCapture, L"on_capture")

	SOUI_CLASS_NAME(EventCaptureFinish, L"on_capture_finish")

	SOUI_CLASS_NAME(SCaptureButton, L"captureButton")

	SOUI_MSG_MAP_BEGIN(SCaptureButton)
		MSG_WM_LBUTTONDOWN(OnLButtonDown)
		MSG_WM_LBUTTONUP(OnLButtonUp)
		MSG_WM_MOUSEMOVE(OnMouseMove)
		MSG_WM_MOUSELEAVE(OnMouseLeave)
		MSG_WM_PAINT_EX(OnPaint)
	SOUI_MSG_MAP_END()

    SCaptureButton::SCaptureButton(void)
    {
        m_evtSet.addEvent(EVENTID(EventCapture));
        m_evtSet.addEvent(EVENTID(EventCaptureFinish));
    }

    SCaptureButton::~SCaptureButton(void)
    {
    }

    void SCaptureButton::OnLButtonDown( UINT nFlags, CPoint point )
    {
        SWindow::OnLButtonDown(nFlags,point);
        HCURSOR hCursor=GETRESPROVIDER->LoadCursor(_T("target"));
        ::SetCursor(hCursor);
    }

    void SCaptureButton::OnLButtonUp( UINT nFlags, CPoint point )
    {
        SWindow::OnLButtonUp(nFlags,point);
        EventCaptureFinish evt(this,point);
        FireEvent(evt);
    }

    void SCaptureButton::OnMouseMove( UINT nFlags, CPoint point )
    {
        if(IsChecked())
        {
            EventCapture evt(this,point);
            FireEvent(evt);
        }
    }

    void SCaptureButton::OnPaint( IRenderTarget *pRT )
    {
        if(!m_pBgSkin) return;
        m_pBgSkin->Draw(pRT,GetWindowRect(),IsChecked()?1:0);
    }

    CSize SCaptureButton::GetDesiredSize( LPCRECT pRcContainer )
    {
        if(!m_pBgSkin) return CSize();
        return m_pBgSkin->GetSkinSize();
    }

    BOOL SCaptureButton::IsChecked()
    {
        return m_dwState & WndState_PushDown;
    }

    void SCaptureButton::OnMouseLeave()
    {
        
    }

}
