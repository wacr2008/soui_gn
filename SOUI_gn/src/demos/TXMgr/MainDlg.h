// MainDlg.h : interface of the CMainDlg class
//
/////////////////////////////////////////////////////////////////////////////
#pragma once

#define close_animation_timer		101
#define switch_mode_pioneer			102
#define switch_mode_classic			103

using namespace SOUI;
class CMainDlg : public SHostWnd
{
public:
	CMainDlg();
	~CMainDlg();

	void OnClose();
	void OnMaximize();
	void OnRestore();
	void OnMinimize();
	void OnSize(UINT nType, CSize size);

	void OnTimer(char nIDEvent);	

	void OnBtnMsgBox();
	int OnCreate(LPCREATESTRUCT lpCreateStruct);
	BOOL OnInitDialog(HWND wndFocus, LPARAM lInitParam);

	enum { SENDER_ID = 30000 };
	virtual int GetID() const { return SENDER_ID; }

	void OnMainTabSelChange(EventArgs *pEvt);

	void OnSwitchModePioneer();
protected:
	//soui消息
	EVENT_MAP_DECL()
	//HostWnd真实窗口消息处理
	BEGIN_MSG_MAP_EX_DECL()
private:
	BOOL			m_bLayoutInited;
	int				m_nCloseAnime;

	int				m_nMoveNumber;
};
