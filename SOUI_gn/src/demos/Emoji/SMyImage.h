#pragma once

#include "control\SCmnCtrl.h"

namespace SOUI
{

	class SMyImage : public SImageWnd
	{
		SOUI_CLASS_NAME(SMyImage, L"myimg")
	public:
		SMyImage();
		virtual ~SMyImage();

		virtual CSize GetDesiredSize(LPCRECT pRcContainer);
	};

}//namespace SOUI
