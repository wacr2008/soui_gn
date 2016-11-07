#include "SMyImage.h"


namespace SOUI
{
	SMyImage::SMyImage()
	{
	}


	SMyImage::~SMyImage()
	{
	}

	CSize SMyImage::GetDesiredSize(LPCRECT pRcContainer)
	{
		CSize size = SImageWnd::GetDesiredSize(pRcContainer);

		if (size.cx < pRcContainer->right - pRcContainer->left
			&& size.cy < pRcContainer->bottom - pRcContainer->top)
			return size;

		CSize szRet;

		float scale1 = 1.0f * size.cx / size.cy;
		float scale2 = 1.0f * (pRcContainer->right - pRcContainer->left) / (pRcContainer->bottom - pRcContainer->top);
		if (scale1 > scale2)
		{
			// 原图的长宽比大于矩形的长宽比  4:3    16:9
			szRet.cx = pRcContainer->right - pRcContainer->left;
			szRet.cy = (pRcContainer->right - pRcContainer->left) / scale1;
		}
		else
		{
			// 原图的长宽比小于矩形的长宽比
			szRet.cy = pRcContainer->bottom - pRcContainer->top;
			szRet.cx = (pRcContainer->bottom - pRcContainer->top) * scale1;
		}
		return szRet;
	}

}
