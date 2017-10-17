#include "DlgAbout.h"
#include "CDebug.h"

namespace SOUI
{
	SOUI_CLASS_NAME(SDlgAbout, L"dlgabout")

	EVENT_MAP_BEGIN(SDlgAbout) 
		EVENT_ID_COMMAND(IDOK, OnOK)
		//EVENT_ID_COMMAND(IDCANCEL,OnCancel)
	EVENT_MAP_END()

	BEGIN_MSG_MAP_EX(SDlgAbout)
		MSG_WM_INITDIALOG(OnInitDialog)
		//MSG_WM_CLOSE(OnCancel)
		//MSG_WM_KEYDOWN(OnKeyDown)
		CHAIN_MSG_MAP(SHostDialog)
		REFLECT_NOTIFICATIONS_EX()
	END_MSG_MAP()

	SDlgAbout::SDlgAbout():SHostDialog(_T("LAYOUT:UIDESIGNER_XML_ABOUT"))
	{

	}

	//TODO:消息映射
	void SDlgAbout::OnClose()
	{
		SHostDialog::OnCancel();
	}

	void SDlgAbout::OnOK()
	{



		SHostDialog::OnOK();
	}

	BOOL SDlgAbout::OnInitDialog(HWND wndFocus, LPARAM lInitParam)
	{


		return TRUE;
	}

}


