
#include "ExtendCtrls.h"


namespace SOUI
{
	SOUI_CLASS_NAME(SWindowEx, L"windowex")

	SOUI_MSG_MAP_BEGIN(SWindowEx)
		MSG_WM_LBUTTONDBLCLK(OnLButtonDown) //将双击消息处理为单击
	SOUI_MSG_MAP_END()
}