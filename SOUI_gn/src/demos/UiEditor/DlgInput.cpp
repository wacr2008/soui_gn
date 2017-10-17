#include "DlgInput.h"
#include "CDebug.h"

namespace SOUI
{
	SOUI_CLASS_NAME(SDlgInput, L"dlginput")

	EVENT_MAP_BEGIN(SDlgInput)

		EVENT_NAME_COMMAND(L"btnOK", OnOK)
		EVENT_NAME_COMMAND(L"btnCancel", OnClose)
	EVENT_MAP_END()

	BEGIN_MSG_MAP_EX(SDlgInput)
		MSG_WM_INITDIALOG(OnInitDialog)
		CHAIN_MSG_MAP(SHostDialog)
		REFLECT_NOTIFICATIONS_EX()
	END_MSG_MAP()


	SDlgInput::SDlgInput():SHostDialog(_T("LAYOUT:UIDESIGNER_XML_INPUT"))
	{

	}

	//TODO:消息映射
	void SDlgInput::OnClose()
	{
		SHostDialog::OnCancel();
	}

	void SDlgInput::OnOK()
	{
	
		m_strValue = m_edt->GetWindowText();
		if (m_strValue.IsEmpty())
		{
			CDebug::Debug(_T("请输入内容"));
			return;
		}
		SHostDialog::OnOK();
	}

	BOOL SDlgInput::OnInitDialog(HWND wndFocus, LPARAM lInitParam)
	{
		m_edt = FindChildByName2<SEdit>(L"edtInput");

		return TRUE;
	}

}


