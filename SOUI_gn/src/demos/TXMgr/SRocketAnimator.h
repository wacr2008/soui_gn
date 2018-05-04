#pragma once

namespace SOUI
{
	class SRocketAnimator : public SImageWnd, protected ITimelineHandler
	{
		SOUI_CLASS_NAME_DECL(SRocketAnimator,L"rocketAnimator")
	public:
		SRocketAnimator(void);
		~SRocketAnimator(void);

		void Fire();

		SOUI_ATTRS_DECL()

	protected:
		virtual void OnNextFrame();

		void OnPaint(IRenderTarget *pRT);

		void OnDestroy();

		SOUI_MSG_MAP_DECL()
	protected:

		CAutoRefPtr<IInterpolator> m_aniInterpolator;
		int						   m_nSpeed;
		int						   m_iTimeStep;
		float					   m_iStep;
		int						   m_nSteps;
	};


}
