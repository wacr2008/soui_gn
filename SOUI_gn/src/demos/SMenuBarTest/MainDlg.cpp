// MainDlg.cpp : implementation of the CMainDlg class
//
/////////////////////////////////////////////////////////////////////////////

#include "MainDlg.h"

	
#ifdef DWMBLUR	//win7毛玻璃开关
#include <dwmapi.h>
#pragma comment(lib,"dwmapi.lib")
#endif
	
EVENT_MAP_BEGIN(CMainDlg)
	EVENT_NAME_COMMAND(L"btn_close", OnClose)
	EVENT_NAME_COMMAND(L"btn_min", OnMinimize)
	EVENT_NAME_COMMAND(L"btn_max", OnMaximize)
	EVENT_NAME_COMMAND(L"btn_restore", OnRestore)
	EVENT_NAME_HANDLER(L"menu_test", EventSelectMenu::EventID, OnSelectMenu)
EVENT_MAP_END()

//HostWnd真实窗口消息处理
BEGIN_MSG_MAP_EX(CMainDlg)
	MSG_WM_CREATE(OnCreate)
	MSG_WM_INITDIALOG(OnInitDialog)
	MSG_WM_CLOSE(OnClose)
	MSG_WM_SIZE(OnSize)
	CHAIN_MSG_MAP(SHostWnd)
	REFLECT_NOTIFICATIONS_EX()
END_MSG_MAP()

CMainDlg::CMainDlg() : SHostWnd(_T("LAYOUT:XML_MAINWND"))
{
	m_bLayoutInited = FALSE;
}

CMainDlg::~CMainDlg()
{
}

int CMainDlg::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	#ifdef DWMBLUR	//win7毛玻璃开关
	MARGINS mar = {5,5,30,5};
	DwmExtendFrameIntoClientArea ( m_hWnd, &mar );
	#endif

	SetMsgHandled(FALSE);
	return 0;
}

BOOL CMainDlg::OnInitDialog(HWND hWnd, LPARAM lParam)
{
	m_bLayoutInited = TRUE;

	// 重要！ 
	SMenuBar *pMenuBar = FindChildByName2<SMenuBar>(_T("menu_test"));
	if (pMenuBar)
	{
		pMenuBar->Init(this);
	}

	return 0;
}
void CMainDlg::OnSelectMenu(EventArgs * pEvt)
{
	EventSelectMenu *pEvtSel = (EventSelectMenu *)pEvt;
	SMenuEx *pMenu = pEvtSel->m_pMenu;
	(void)pMenu;
	switch (pEvtSel->m_id)
	{
	case 11:
		break;
	case 12://退出
		DestroyWindow();
		break;
	}
}
//TODO:消息映射
void CMainDlg::OnClose()
{
	CSimpleWnd::DestroyWindow();
}

void CMainDlg::OnMaximize()
{
	SendMessage(WM_SYSCOMMAND, SC_MAXIMIZE);
}
void CMainDlg::OnRestore()
{
	SendMessage(WM_SYSCOMMAND, SC_RESTORE);
}
void CMainDlg::OnMinimize()
{
	SendMessage(WM_SYSCOMMAND, SC_MINIMIZE);
}

void CMainDlg::OnSize(UINT nType, CSize size)
{
	SetMsgHandled(FALSE);
	if (!m_bLayoutInited) return;
	
	SWindow *pBtnMax = FindChildByName(L"btn_max");
	SWindow *pBtnRestore = FindChildByName(L"btn_restore");
	if(!pBtnMax || !pBtnRestore) return;
	
	if (nType == SIZE_MAXIMIZED)
	{
		pBtnRestore->SetVisible(TRUE);
		pBtnMax->SetVisible(FALSE);
	}
	else if (nType == SIZE_RESTORED)
	{
		pBtnRestore->SetVisible(FALSE);
		pBtnMax->SetVisible(TRUE);
	}
}

