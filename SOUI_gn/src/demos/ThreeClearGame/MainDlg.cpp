// MainDlg.cpp : implementation of the CMainDlg class
//
/////////////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "MainDlg.h"
#include "NetAdapter.h"
	
#ifdef DWMBLUR	//win7毛玻璃开关
#include <dwmapi.h>
#pragma comment(lib,"dwmapi.lib")
#endif
	
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
	// 初始化刷新事件
	m_NetMatrix.SetEvent(this);
	// 初始化窗口
	assert(GetRoot());
	MyHelper::Instance()->InitWindow(GetRoot());
	// 初始化网格
	m_NetMatrix.Init();
	// 初始化 tileview
	SOUI::STileView* pTileView = FindChildByName2<SOUI::STileView>(L"tv_net");
	assert(pTileView);
	CNetAdapter* pAdapter = new CNetAdapter(m_NetMatrix.GetNet());
	pTileView->SetAdapter(pAdapter);
	pAdapter->SetEvent(&m_NetMatrix);
	pAdapter->Release();
	return 0;
}

void CMainDlg::OnTimer(UINT_PTR idEvent)
{
	// 降落计算
	if (idEvent == TIMER_LAND) {
		// 清除计数器
		KillTimer(TIMER_LAND);
		// 是否有需要降落的点
		if (m_NetMatrix.LandOneGrid()) {
			RefreshNet(m_NetMatrix.GetNet());
		} 
		// 没有需要降落的点
		else {
			// 是否产生了自动消除
			// 如果没有产生自动消除，则意味着操作结束，可以开始随机补充了
			if (!m_NetMatrix.AutoDelete()) {
				// 随机补充一行
				m_NetMatrix.AddRandomGrid();
			}
		}
	}else
	{
		SetMsgHandled(FALSE);
	}
}

// 刷新网格
void CMainDlg::RefreshNet(std::vector<std::vector<Grid>> vecNet)
{
	// 删除计时器
	KillTimer(TIMER_LAND);
	// 刷新网格
	SOUI::STileView* pTileView = FindChildByName2<SOUI::STileView>(L"tv_net");
	assert(pTileView);
	CNetAdapter* pAdapter = static_cast<CNetAdapter*>(pTileView->GetAdapter());
	if (pAdapter != NULL) {
		pAdapter->UpdateNet(vecNet);
		pAdapter->notifyDataSetChanged();
	}	
	// 设置分数
	SetScore();
	// 定时计算降落
	SetTimer(TIMER_LAND, 500);
}

// 重新开始
void CMainDlg::OnBtnRestart()
{
	// 初始化网格
	m_NetMatrix.Init();
	// 刷新网格
	RefreshNet(m_NetMatrix.GetNet());
}

// 设置分数
void CMainDlg::SetScore()
{
	SOUI::SWindow* pTextScore = FindChildByName2<SOUI::SWindow>(L"text_score");
	assert(pTextScore);
	SOUI::SStringW strScore;
	strScore.Format(L"分数：%d 分", m_NetMatrix.GetScore());
	pTextScore->SetWindowTextW(strScore);
}

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

