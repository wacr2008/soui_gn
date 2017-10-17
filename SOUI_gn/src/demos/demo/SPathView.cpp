#include "SPathView.h"

namespace SOUI
{
	SOUI_CLASS_NAME(EventPath, L"on_event_path")

	SOUI_CLASS_NAME(SPathView, L"pathView")

	SOUI_ATTRS_BEGIN(SPathView)
		ATTR_INT(L"lineWidth", m_nLineWidth, TRUE)
		ATTR_INT(L"lineStyle", m_nLineStyle, TRUE)
		ATTR_COLOR(L"lineColor", m_crLine, TRUE)
		ATTR_INT(L"frameSize", m_nFrameSize, TRUE)
		ATTR_FLOAT(L"cornerRadius", m_fCornerRadius, TRUE)
	SOUI_ATTRS_END()

	SOUI_MSG_MAP_BEGIN(SPathView)
		MSG_WM_LBUTTONDOWN(OnLButtonDown)
		MSG_WM_RBUTTONDOWN(OnRButtonDown)
		MSG_WM_PAINT_EX(OnPaint)
	SOUI_MSG_MAP_END()

	SPathView::SPathView(void)
		:m_nLineWidth(2)
		,m_nLineStyle(PS_DASH)
		,m_nFrameSize(9)
		,m_crLine(RGBA(255,0,0,255))
		,m_fCornerRadius(5.0f)
	{
		GetEventSet()->addEvent(EVENTID(EventPath));
		GETRENDERFACTORY->CreatePath(&m_path);
		GETRENDERFACTORY->CreatePathMeasure(&m_pathMeasure);
	}

	SPathView::~SPathView(void)
	{
	}

	void SPathView::OnLButtonDown(UINT nFlags,CPoint pt)
	{
		if(!m_path || !m_pathMeasure)
			return;
		CRect rc = GetClientRect();
		pt -= rc.TopLeft();
		m_lstPoints.Add(pt);
		m_path->reset();
		m_path->addPoly(m_lstPoints.GetData(),m_lstPoints.GetCount(),false);
		OnPathChanged();
	}

	void SPathView::OnRButtonDown(UINT nFlags, CPoint point)
	{
		if(!m_path || !m_pathMeasure)
			return;

		CRect rc=GetClientRect();
		point-=rc.TopLeft();
		for(unsigned int i=0;i<m_lstPoints.GetCount();i++)
		{
			POINT pt = m_lstPoints[i];
			CRect rcFrame(pt,CSize(m_nFrameSize,m_nFrameSize));
			rcFrame.OffsetRect(-(m_nFrameSize-1)/2,-(m_nFrameSize-1)/2);
			if(rcFrame.PtInRect(point))
			{
				m_lstPoints.RemoveAt(i);
				m_path->reset();
				m_path->addPoly(m_lstPoints.GetData(),m_lstPoints.GetCount(),false);
				OnPathChanged();
				break;
			}
		}
	}

	void SPathView::OnPaint(IRenderTarget *pRT)
	{
		if(!m_path || !m_pathMeasure)
		{
			__super::OnPaint(pRT);
			return;
		}

		int count = m_lstPoints.GetCount();
		CRect rc=GetClientRect();

		if(count>1)
		{
			CAutoRefPtr<ICornerPathEffect> pathEffect;
			GETRENDERFACTORY->CreatePathEffect(__uuidof(ICornerPathEffect),(IPathEffect**)&pathEffect);
			pathEffect->Init(m_fCornerRadius);

			CAutoRefPtr<IPen> pen,oldPen;
			pRT->CreatePen(m_nLineStyle,m_crLine,m_nLineWidth,&pen);
			pRT->SelectObject(pen,(IRenderObj**)&oldPen);

			m_path->offset(rc.left,rc.top);

			pRT->DrawPath(m_path,pathEffect);

			m_path->offset(-rc.left,-rc.top);

			pRT->SelectObject(oldPen);
		}

		for(int i=0;i<count;i++)
		{
			POINT pt = m_lstPoints[i];
			CRect rcFrame(pt,CSize(m_nFrameSize,m_nFrameSize));
			rcFrame.OffsetRect(-(m_nFrameSize-1)/2,-(m_nFrameSize-1)/2);
			rcFrame.OffsetRect(rc.TopLeft());
			pRT->DrawRectangle(&rcFrame);
		}
	}

	void SPathView::OnPathChanged()
	{
		EventPath evt(this);
		m_pathMeasure->setPath(m_path,false);
		evt.fLength = m_pathMeasure->getLength();
		FireEvent(evt);
		Invalidate();
	}

}
