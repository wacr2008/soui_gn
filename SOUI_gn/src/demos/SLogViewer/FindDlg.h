#pragma once
#include "res/R.h"
namespace SOUI
{
	struct IFindListener{
		virtual bool OnFind(const SStringT & strText, bool bFindNext, bool bMatchCase, bool bMatchWholeWord) PURE;
	};

	class CFindDlg : public SHostWnd
	{
	public:
		CFindDlg(IFindListener *pFindListener);
		~CFindDlg(void);

	protected:
		void OnClose();
		void OnFindNext();
		void OnFindPrev();
		
		void OnFind(bool bNext);
		
		void OnInit(EventArgs *e);
		EVENT_MAP_DECL()

		virtual void OnFinalMessage(HWND hWnd);

		IFindListener * m_pFindListener;

		SEdit *	m_pEditTarget;
		SCheckBox * m_pMatchCase;
		SCheckBox * m_pMatchWholeWord;
	};

}
