#include "WinBox.h"
#include "MainWnd.h"

using namespace SOUI;

EVENT_MAP_BEGIN(CWinBox)
	EVENT_NAME_COMMAND(L"btn_box_close", OnClose)
	EVENT_NAME_COMMAND(L"btn_box_back", OnBtnBack)
	EVENT_NAME_COMMAND(L"btn_box_forward", OnBtnForward)
	EVENT_NAME_COMMAND(L"btn_box_refresh", OnBtnRefresh)
	EVENT_NAME_COMMAND(L"btn_box_maximize", OnBtnMaximize)
	EVENT_NAME_COMMAND(L"btn_box_restore", OnBtnRestore)
EVENT_MAP_END()

//窗口消息处理映射表
BEGIN_MSG_MAP_EX(CWinBox)
	MSG_WM_INITDIALOG(OnInitDialog)
	MSG_WM_CLOSE(OnClose)
	CHAIN_MSG_MAP(SHostWnd)//注意将没有处理的消息交给基类处理
	REFLECT_NOTIFICATIONS_EX()
END_MSG_MAP()

CWinBox::CWinBox(void) : SHostWnd(_T("LAYOUT:XML_WINBOX"))
{
	m_bLayoutInited=FALSE;
	m_boxParent=NULL;
}

CWinBox::~CWinBox(void)
{
	m_boxParent=NULL;
}

BOOL CWinBox::OnInitDialog( HWND hWnd, LPARAM lParam )
{
	SetMsgHandled(FALSE);
	m_bLayoutInited=TRUE;

	

	return 0;
}

void CWinBox::OnClose()
{
	ShowWindow(SW_HIDE);
	CMainWnd* pTemp=(CMainWnd *)m_boxParent;
	pTemp->OnBtnBoxHide();
	pTemp=NULL;
}

void CWinBox::OnBtnBack()			//后退
{
	SMessageBox(NULL,_T("后退"),_T("啦啦啦"),MB_OK|MB_ICONEXCLAMATION);
}

void CWinBox::OnBtnForward()		//前进
{
	SMessageBox(NULL,_T("前进"),_T("啦啦啦"),MB_OK|MB_ICONEXCLAMATION);
}

void CWinBox::OnBtnRefresh()		//刷新
{
	SMessageBox(NULL,_T("刷新"),_T("啦啦啦"),MB_OK|MB_ICONEXCLAMATION);
}

void CWinBox::OnBtnMaximize()		//最大化
{
	RECT rt;
	::GetWindowRect(this->m_hWnd, &rt);
	::GetWindowRect(this->m_hWnd, &rect_box);

	
	int cx=GetSystemMetrics(SM_CYSCREEN);
	int offset_cx=GetSystemMetrics(SM_CYCAPTION);
	rt.top = 0;
	rt.bottom = cx - offset_cx;
	this->MoveWindow(&rt,TRUE);
	
	SWindow* pBtn = FindChildByName(L"btn_box_maximize");
	if(pBtn) pBtn->SetVisible(FALSE,TRUE);

	pBtn = FindChildByName(L"btn_box_restore");
	if(pBtn) pBtn->SetVisible(TRUE,TRUE);
}

void CWinBox::OnBtnRestore()		//还原
{
	//SendMessage(WM_SYSCOMMAND,SC_RESTORE);
	this->MoveWindow(&rect_box,TRUE);

	SWindow* pBtn = FindChildByName(L"btn_box_maximize");
	if(pBtn) pBtn->SetVisible(TRUE,TRUE);

	pBtn = FindChildByName(L"btn_box_restore");
	if(pBtn) pBtn->SetVisible(FALSE,TRUE);
}
