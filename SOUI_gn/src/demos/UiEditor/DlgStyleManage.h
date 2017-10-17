#pragma once
#include "core/shostwnd.h"
#include "core/smsgloop.h"
#include "core/SHostDialog.h"

namespace SOUI
{
	class SDlgStyleManage: public SHostDialog
	{
		SOUI_CLASS_NAME_DECL(SDlgStyleManage,L"dlgstylemanage")
	public:
		SDlgStyleManage(SStringT strClassName, SStringT strPath, BOOL bGetClass);

		~SDlgStyleManage(void)
		{

		}

		void OnClose();
		void OnBtnAdd();
		void OnBtnDel();
		void OnBtnSave();



		BOOL OnInitDialog(HWND wndFocus, LPARAM lInitParam);


	protected:

		void OnOK();


		EVENT_MAP_DECL()

		BEGIN_MSG_MAP_EX_DECL()

	protected:

	public:
		void LoadStyleFile();
		void InitStyleLB();
		SStringT GetLBCurSelText(SListBox * lb);

	public:

		pugi::xml_document m_xmlDocStyle;

		SListBox*  m_lbStyle;
		SEdit*     m_edtSearch;
		SRealWnd*  m_RealWnd;
		SWindow*   m_wndView;

		SStringT m_strProPath;
		SStringT m_strUIResFile;
		SStringT m_strStyleName;
		SStringT m_strStyleFile;
		BOOL m_bGetStyle;

	};

}