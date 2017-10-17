// MainDlg.h : interface of the CMainDlg class
//
/////////////////////////////////////////////////////////////////////////////
#pragma once

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
	
	void OnBtnMsgBox();
	int OnCreate(LPCREATESTRUCT lpCreateStruct);
	BOOL OnInitDialog(HWND wndFocus, LPARAM lInitParam);

	void OnSelectMenu(EventArgs * pEvt);

protected:
	//soui消息
	EVENT_MAP_DECL()
		
	//HostWnd真实窗口消息处理
	BEGIN_MSG_MAP_EX_DECL()
private:
	BOOL			m_bLayoutInited;
};
