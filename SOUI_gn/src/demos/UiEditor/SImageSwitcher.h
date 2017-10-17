#pragma once

/**
by 多点免费WIFI
 */
#include <core/Swnd.h>

namespace SOUI
{
	class SImageSwitcher : public SWindow
	{
		SOUI_CLASS_NAME_DECL(SImageSwitcher,L"imageSwitcher")
	public:
		SImageSwitcher();
		virtual ~SImageSwitcher();

	public:
		void  Switch(int iSelect);
		void  InsertImage(int iTo, IBitmap * pImage);
		void  RemoveAll();
		
	private:
	    
	    SArray<IBitmap *> m_lstImages;
	    
		BOOL m_bWantMove;
		int  m_iDownX;
		BOOL m_bTimerMove;
		int  m_iMoveWidth;
		int  m_iSelected;
		int m_iTimesMove;

	protected:
		void OnPaint(IRenderTarget *pRT);
		void OnLButtonDown(UINT nFlags, CPoint point);
		void OnLButtonUp(UINT nFlags, CPoint point);
		void OnMouseMove(UINT nFlags,CPoint pt);
		void OnTimer(char nIDEvent);
	protected:
		SOUI_MSG_MAP_DECL()

		SOUI_ATTRS_DECL()

        HRESULT OnAttrImages(const SStringW strValue,BOOL bLoading);
        
	};
}