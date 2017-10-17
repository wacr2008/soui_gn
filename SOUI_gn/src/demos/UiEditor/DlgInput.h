#pragma once
#include "core/shostwnd.h"
#include "core/smsgloop.h"
#include "core/SHostDialog.h"

namespace SOUI
{
	class SDlgInput: public SHostDialog
	{
		SOUI_CLASS_NAME_DECL(SDlgInput,L"dlginput")
	public:
		SDlgInput();

		~SDlgInput(void)
		{

		}


		void OnBtnDlgOpenFile();

		BOOL OnInitDialog(HWND wndFocus, LPARAM lInitParam);



	protected:
		void OnOK();
		void OnClose();

		EVENT_MAP_DECL()

		BEGIN_MSG_MAP_EX_DECL()

	protected:

	public:
		SStringT m_strValue;	
		SEdit *m_edt;
	};

}