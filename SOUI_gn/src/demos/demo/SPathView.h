#pragma once
namespace SOUI{

	class EventPath : public TplEventArgs<EventPath>
	{
		SOUI_CLASS_NAME_DECL(EventPath,L"on_event_path")
	public:
		enum {EventID=EVT_EXTERNAL_BEGIN+23451};
		EventPath(SObject *pSender):TplEventArgs<EventPath>(pSender){}

		float fLength;
	};

	class SPathView : public SWindow
	{
		SOUI_CLASS_NAME_DECL(SPathView,L"pathView")
	public:
		SPathView(void);
		~SPathView(void);


		SOUI_ATTRS_DECL()
	protected:
		void OnLButtonDown(UINT nFlags,CPoint pt);
		void OnRButtonDown(UINT nFlags, CPoint point);
		void OnPaint(IRenderTarget *pRT);
		void OnPathChanged();
		SOUI_MSG_MAP_DECL()
	protected:
		int m_nLineWidth;
		int m_nLineStyle;
		COLORREF m_crLine;
		int m_nFrameSize;
		float m_fCornerRadius;

		SArray<POINT> m_lstPoints;
		CAutoRefPtr<IPath> m_path;
		CAutoRefPtr<IPathMeasure> m_pathMeasure;
	};


}
