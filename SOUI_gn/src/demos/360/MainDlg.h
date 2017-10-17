// MainDlg.h : interface of the CMainDlg class
//
/////////////////////////////////////////////////////////////////////////////
#pragma once

class CMainDlg : public SOUI::SHostWnd
{
public:
	CMainDlg();
	~CMainDlg();

	void OnClose()
	{
		//AnimateHostWindow(200,AW_CENTER|AW_HIDE);
        DestroyWindow();
	}
	void OnMaximize()
	{
		SendMessage(WM_SYSCOMMAND,SC_MAXIMIZE);
	}
	void OnRestore()
	{
		SendMessage(WM_SYSCOMMAND,SC_RESTORE);
	}
	void OnMinimize()
	{
		SendMessage(WM_SYSCOMMAND,SC_MINIMIZE);
	}

	void OnSize(UINT nType, SOUI::CSize size)
	{
		SetMsgHandled(FALSE);
		if(!m_bLayoutInited) return;
		if(nType==SIZE_MAXIMIZED)
		{
			FindChildByName(L"btn_restore")->SetVisible(TRUE);
			FindChildByName(L"btn_max")->SetVisible(FALSE);
		}else if(nType==SIZE_RESTORED)
		{
            FindChildByName(L"btn_restore")->SetVisible(FALSE);
            FindChildByName(L"btn_max")->SetVisible(TRUE);
		}
	}
    void OnBtnMsgBox()
    {
		SOUI::SMessageBox(NULL, _T("this is a message box"), _T("haha"), MB_OK | MB_ICONEXCLAMATION);
		SOUI::SMessageBox(NULL, _T("this message box includes two buttons"), _T("haha"), MB_YESNO | MB_ICONQUESTION);
		SOUI::SMessageBox(NULL, _T("this message box includes three buttons"), NULL, MB_ABORTRETRYIGNORE);
    }
    
	int OnCreate(LPCREATESTRUCT lpCreateStruct);
	void OnShowWindow(BOOL bShow, UINT nStatus);
    BOOL OnInitDialog(HWND wndFocus, LPARAM lInitParam);


protected:

	EVENT_MAP_DECL()

	BEGIN_MSG_MAP_EX_DECL()
private:
	BOOL			m_bLayoutInited;
};
