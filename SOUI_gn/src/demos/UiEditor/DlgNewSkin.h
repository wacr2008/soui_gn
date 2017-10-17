#pragma once
#include "core/shostwnd.h"
#include "core/smsgloop.h"
#include "core/SHostDialog.h"
//#include "control/SRichEdit.h"
//#include "extend.ctrls/SImageEx.h"

namespace SOUI
{
	class SDlgNewSkin: public SHostDialog
	{
		SOUI_CLASS_NAME_DECL(SDlgNewSkin,L"dlgnewskin")
	public:
		SDlgNewSkin(LPCTSTR pszXmlName);

		~SDlgNewSkin(void)
		{

		}

		void OnBtnDlgOpenFile();

		BOOL OnInitDialog(HWND wndFocus, LPARAM lInitParam);
		//virtual INT_PTR DoModal(HWND hParent=NULL);

		//virtual void EndDialog(INT_PTR nResult);


	protected:
		//void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
		void OnOK();
		void OnCancel();
		//virtual SMessageLoop * GetMsgLoop(){return m_MsgLoop;}

		EVENT_MAP_DECL()

		BEGIN_MSG_MAP_EX_DECL()

	protected:

	public:
		SStringT m_strSkinName;	
		SListBox *m_lbMain;
	};

}