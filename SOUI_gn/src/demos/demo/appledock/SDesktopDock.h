#pragma once

#define MAX_COUNT 10 

/*
by 多点
@20150510 qq:4361031
*/
using namespace SOUI;

class SDesktopDock : public SWindow
{
	SOUI_CLASS_NAME_DECL(SDesktopDock, L"deskdock")
public:
	SDesktopDock();
protected:
	virtual void OnPaint(IRenderTarget *pRT);
	virtual void OnMouseMove(UINT nFlags,CPoint pt);
	virtual void OnLButtonUp(UINT nFlags, CPoint point);

	void GetImageRate();
	void GetDockLen();
	void GetRTRect();
	void initDockRect();

protected:
	SOUI_ATTRS_DECL()

	SOUI_MSG_MAP_DECL()
		//////////////////////////////////////////////////////////////////////////

private:
	ISkinObj *m_pSkin[MAX_COUNT];

	float m_iRotate;
	int   m_CPX;
	int   m_CPY;
	double m_DockLen;
	int   m_Width;
	int   m_Height;
	double m_MaxDisc;
	double m_MinDisc;
	double m_MaxRate;
	double m_MinRate;
	int m_gap;

	double m_dRate[MAX_COUNT];
	CRect  m_RTRect[MAX_COUNT];

	BOOL m_Init;

};
