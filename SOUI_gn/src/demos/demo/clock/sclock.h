#pragma once

using namespace SOUI;

#include "helper/SMatrix.h"

namespace SOUI{

class SClock : public SWindow
{
	SOUI_CLASS_NAME_DECL(SClock, L"clock")

public:
	SClock();

	enum {TIMER_REFRESH = 1};

protected:
    SMatrix InitMatrix(double angle, CPoint &center);

    double GetMinuteSecondAngle(int nValue);
    double GetHourAngle(int nHour,int nMinute);

protected:
	int  OnCreate(void*);
	void OnPaint(SOUI::IRenderTarget * pRT);
	void OnTimer(char cTimerID);

	SOUI_MSG_MAP_DECL()

protected:
	SOUI_ATTRS_DECL()

	CAutoRefPtr<IBitmap> pointer_hour;
	CAutoRefPtr<IBitmap> pointer_minute;
	CAutoRefPtr<IBitmap> pointer_second;
};

}