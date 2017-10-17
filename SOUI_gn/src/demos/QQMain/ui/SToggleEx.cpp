
#include "SToggleEx.h"

SOUI_CLASS_NAME(SOUI::SToggleEx, L"toggle_ex")

SOUI_MSG_MAP_BEGIN(SOUI::SToggleEx)
	MSG_WM_PAINT_EX(OnPaint)
	MSG_WM_LBUTTONUP(OnLButtonUp)
SOUI_MSG_MAP_END()

void SOUI::SToggleEx::OnLButtonUp(UINT nFlags,CPoint pt)
{
	if(GetWindowRect().PtInRect(pt)) m_bToggled=!m_bToggled;
	__super::OnLButtonUp(nFlags,pt);
} 