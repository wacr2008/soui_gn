#include "DlgCreatePro.h"

namespace SOUI
{
	SOUI_CLASS_NAME(SDlgCreatePro, L"dlgcreatepro")

	EVENT_MAP_BEGIN(SDlgCreatePro)
		EVENT_ID_COMMAND(IDOK, OnOK)
		//EVENT_ID_COMMAND(IDCANCEL,OnCancel)
	EVENT_MAP_END()

	BEGIN_MSG_MAP_EX(SDlgCreatePro)
		//MSG_WM_CLOSE(OnCancel)
		//MSG_WM_KEYDOWN(OnKeyDown)
		CHAIN_MSG_MAP(SHostDialog)
		REFLECT_NOTIFICATIONS_EX()
	END_MSG_MAP()

void SDlgCreatePro::OnOK()
{
	SEdit *edit = FindChildByName2<SEdit>(L"UIDESIGNER_edit_input");
	m_strinput = edit->GetWindowText();
	SHostDialog::OnOK();
}
}