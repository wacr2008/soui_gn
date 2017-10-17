// MainDlg.cpp : implementation of the CMainDlg class
//
/////////////////////////////////////////////////////////////////////////////

#include "MainDlg.h"

#include <dwmapi.h>
#pragma comment(lib,"dwmapi.lib")

EVENT_MAP_BEGIN(CMainDlg)
	EVENT_NAME_COMMAND(L"btn_close", OnClose)
	EVENT_NAME_COMMAND(L"btn_min", OnMinimize)
	EVENT_NAME_COMMAND(L"btn_max", OnMaximize)
	EVENT_NAME_COMMAND(L"btn_restore", OnRestore)

	EVENT_NAME_COMMAND(L"btn_msgbox", OnBtnMsgBox)
EVENT_MAP_END()

BEGIN_MSG_MAP_EX(CMainDlg)
	MSG_WM_CREATE(OnCreate)
	MSG_WM_INITDIALOG(OnInitDialog)
	MSG_WM_CLOSE(OnClose)
	MSG_WM_SIZE(OnSize)
	MSG_WM_SHOWWINDOW(OnShowWindow)
	CHAIN_MSG_MAP(SHostWnd)
	REFLECT_NOTIFICATIONS_EX()
END_MSG_MAP()

CMainDlg::CMainDlg() : SHostWnd(_T("LAYOUT:XML_MAINWND"))
{
	m_bLayoutInited=FALSE;
} 

CMainDlg::~CMainDlg()
{
}

int CMainDlg::OnCreate( LPCREATESTRUCT lpCreateStruct )
{
	// 		MARGINS mar = {5,5,30,5};
	// 		DwmExtendFrameIntoClientArea ( m_hWnd, &mar );
	SetMsgHandled(FALSE);
	return 0;
}

void CMainDlg::OnShowWindow( BOOL bShow, UINT nStatus )
{
	if(bShow)
	{
 		//AnimateHostWindow(200,AW_CENTER);
	}
}


BOOL CMainDlg::OnInitDialog( HWND hWnd, LPARAM lParam )
{
    m_bLayoutInited=TRUE;

    return 0;
}

