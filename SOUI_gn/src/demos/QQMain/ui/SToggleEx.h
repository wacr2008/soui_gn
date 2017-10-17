
#pragma once
#include "core/SWnd.h"

namespace SOUI
{

	class SToggleEx : public SToggle
	{
		SOUI_CLASS_NAME_DECL(SToggleEx, L"toggle_ex")
	public:
		void OnLButtonUp(UINT nFlags, CPoint pt);

		SOUI_MSG_MAP_DECL()

	};
}