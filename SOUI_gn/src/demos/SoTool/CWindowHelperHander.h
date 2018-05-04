#pragma once
#include "SwndFrame.h"
#include "SCaptureButton.h"
typedef struct _tagStyleInf
{
	SOUI::SStringT strStyle;
	SOUI::SStringT strDes;
	_tagStyleInf(){}
	_tagStyleInf(LPCTSTR style, LPCTSTR des):strStyle(style),strDes(des){}
}StyleInf,*PStyleInf;
class CWindowHelperHander
{
	friend class CMainDlg;
public:
	CWindowHelperHander();
	~CWindowHelperHander();
	void OnInit(SOUI::SWindow *pPageRoot); 
protected:
	EVENT_MAP_DECL_EX()

protected:
	void OnEventCaptureHost(SOUI::EventArgs *pEvt);
	void OnEventCaptureHostFinish(SOUI::EventArgs *pEvt);
	void UpdataWindowInf(HWND hWnd);
	void GetStyleList(LONG lStyle, SOUI::SArray<StyleInf> &styleList);
	void GetExStyleList(LONG lStyle, SOUI::SArray<StyleInf> &styleList);
private:
	SOUI::SwndFrame       m_wndFrame;
	HWND m_hHostWnd,m_hLastHwnd;
	SOUI::SWindow	*m_HostRoot;
};