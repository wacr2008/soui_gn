#pragma once

#include "SGifPlayer.h"

namespace SOUI
{

	class SMyGifPlayer : public SGifPlayer
	{
		SOUI_CLASS_NAME_DECL(SMyGifPlayer, L"mygifplayer")
	public:
		SMyGifPlayer();
		virtual ~SMyGifPlayer();

		virtual CSize GetDesiredSize(LPCRECT pRcContainer);
	};

}//namespace SOUI
