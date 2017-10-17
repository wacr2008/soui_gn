#include "SRotateWindow.h"
 
namespace SOUI
{


SOUI_CLASS_NAME(SRotateWindow, L"RotateWindow");

SOUI_MSG_MAP_BEGIN(SRotateWindow)
	MSG_WM_PAINT_EX(OnPaint)
	MSG_WM_TIMER_EX(OnTimer)
	MSG_WM_CREATE(OnCreate)
SOUI_MSG_MAP_END()

SOUI_ATTRS_BEGIN(SRotateWindow)
	ATTR_IMAGEAUTOREF(L"AnimImg",   m_pAnimImg, TRUE)
	ATTR_INT(L"speed", m_nSpeed,FALSE)
	ATTR_ENUM_BEGIN(L"turn",DWORD,FALSE)
		ATTR_ENUM_VALUE(L"left",TURN_LEFT)
		ATTR_ENUM_VALUE(L"right",TURN_RIGHT)
	ATTR_ENUM_END(m_nTurn)
SOUI_ATTRS_END()
		 

}