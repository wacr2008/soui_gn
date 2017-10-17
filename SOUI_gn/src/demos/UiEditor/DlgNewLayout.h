#pragma once
#include "core/shostwnd.h"
#include "core/smsgloop.h"
#include "core/SHostDialog.h"
#include "control/SRichEdit.h"
#include "SImageEx.h"

namespace SOUI
{
	class SDlgNewLayout: public SHostDialog
	{
		SOUI_CLASS_NAME_DECL(SDlgNewLayout,L"dlgnewlayout")
	public:
		SDlgNewLayout(LPCTSTR pszXmlName, SStringT strProPath);

		~SDlgNewLayout(void)
		{

		}


		void OnClose();
		void OnBtnDlgOpenFile();

		BOOL OnInitDialog(HWND wndFocus, LPARAM lInitParam);
		//virtual INT_PTR DoModal(HWND hParent=NULL);

		//virtual void EndDialog(INT_PTR nResult);


	protected:
		//void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
		void OnOK();
		//void OnCancel();
		//virtual SMessageLoop * GetMsgLoop(){return m_MsgLoop;}

		EVENT_MAP_DECL()

		BEGIN_MSG_MAP_EX_DECL()

	protected:
		SStringT m_strProPath;

		SEdit *m_edtName;
		SEdit *m_edtPath;




	public:
		SStringT m_strPath;
		SStringT m_strName;		
	};

}