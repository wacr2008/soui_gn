#pragma once

#include <interface/sinterpolator-i.h>
namespace SOUI
{
	class SInterpolatorView : public SSliderBar
		,protected ITimelineHandler
	{
		SOUI_CLASS_NAME_DECL(SInterpolatorView,L"interpolatorView")
	public:
		SInterpolatorView(void);
		~SInterpolatorView(void);

		void SetInterpolator(IInterpolator *pInterpolator);
	public:
		int OnCreate(void*);
		void OnDestroy();
		void OnPaint(IRenderTarget * pRT);
		SOUI_MSG_MAP_DECL()
	protected:
		virtual void OnNextFrame();
		
		SOUI_ATTRS_DECL()
		
		CAutoRefPtr<IInterpolator> m_interpolator;
		int			m_nSpeed;
		int			m_iFrame;
		float		m_fTime;
	};
}
