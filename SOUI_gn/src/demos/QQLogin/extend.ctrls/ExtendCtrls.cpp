#include "ExtendCtrls.h"


SOUI_CLASS_NAME(SOUI::SWindowEx, L"windowex")

SOUI_MSG_MAP_BEGIN(SOUI::SWindowEx)
	MSG_WM_LBUTTONDBLCLK(OnLButtonDown) //将双击消息处理为单击
SOUI_MSG_MAP_END()