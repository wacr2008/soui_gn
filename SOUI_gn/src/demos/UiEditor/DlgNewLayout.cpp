#include "DlgNewLayout.h"
#include "CDebug.h"
#include "FileHelper.h"

namespace SOUI
{

	SOUI_CLASS_NAME(SDlgNewLayout, L"dlgnewlayout")

	EVENT_MAP_BEGIN(SDlgNewLayout)
		EVENT_NAME_COMMAND(L"NAME_UIDESIGNER_btn_close", OnClose)

		EVENT_NAME_COMMAND(L"NAME_UIDESIGNER_btn_dlg", OnBtnDlgOpenFile)
		EVENT_NAME_COMMAND(L"NAME_UIDESIGNER_btn_OK", OnOK)
		//EVENT_NAME_COMMAND(L"NAME_UIDESIGNER_btn_ZY_NEW", OnZYNew)
		//EVENT_NAME_COMMAND(L"NAME_UIDESIGNER_btn_ZY_DEL", OnZYDel)
		//EVENT_NAME_COMMAND(L"NAME_UIDESIGNER_btn_SKIN_NEW", OnSkinNew)
		//EVENT_NAME_COMMAND(L"NAME_UIDESIGNER_btn_SKIN_DEL", OnSkinDel)

		//EVENT_ID_COMMAND(IDOK,OnOK)
		//EVENT_ID_COMMAND(IDCANCEL,OnCancel)
	EVENT_MAP_END()

	BEGIN_MSG_MAP_EX(SDlgNewLayout)
		MSG_WM_INITDIALOG(OnInitDialog)
		//MSG_WM_CLOSE(OnCancel)
		//MSG_WM_KEYDOWN(OnKeyDown)
		CHAIN_MSG_MAP(SHostDialog)
		REFLECT_NOTIFICATIONS_EX()
	END_MSG_MAP()

	SDlgNewLayout::SDlgNewLayout(LPCTSTR pszXmlName, SStringT strProPath):SHostDialog(pszXmlName)
	{
		m_strProPath = strProPath;
	}

	//TODO:消息映射
	void SDlgNewLayout::OnClose()
	{
		SHostDialog::OnCancel();
	}

	void SDlgNewLayout::OnOK()
	{
		m_strPath = m_edtPath->GetWindowText();
		m_strName = m_edtName->GetWindowText();
		if (m_strPath.IsEmpty() || m_strName.IsEmpty())
		{
			CDebug::Debug(_T("资源名称或路径不能为空"));
			return;

		}

		int n = m_strPath.Find(m_strProPath);
		if (n != 0)
		{
			CDebug::Debug(_T("请将资源保存到uires目录下"));
			return;
		}

		SHostDialog::OnOK();
	}

	BOOL SDlgNewLayout::OnInitDialog(HWND wndFocus, LPARAM lInitParam)
	{
		
		m_edtName = FindChildByName2<SEdit>(L"NAME_UIDESIGNER_edit_ZY");
		m_edtPath = FindChildByName2<SEdit>(L"NAME_UIDESIGNER_edit_Path");
		

		return TRUE;
	}

    void SDlgNewLayout::OnBtnDlgOpenFile()	
	{
		CFileDialogEx OpenDlg(FALSE, NULL, NULL, 6, _T("所有文件 (*.*)\0*.*\0\0"));
		if (IDOK ==OpenDlg.DoModal())
		{
			SStringT strFileName = OpenDlg.m_szFileName;
			int n = strFileName.Find(m_strProPath);
			if (n != 0)
			{
				SMessageBox(NULL, _T("请将资源保存到uires目录下"), _T("提示"), MB_OK);
				return;
			}


			n = strFileName.Find(_T(".xml"));
			if(n == -1)
			{
				strFileName = strFileName + _T(".xml");
			}

			m_edtPath->SetWindowText(strFileName);

		}
	}
}


