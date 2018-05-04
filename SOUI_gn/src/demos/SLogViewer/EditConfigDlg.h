#pragma once
#include "whwindow.h"
#include "ScintillaWnd.h"

class CEditConfigDlg : public SHostDialog	, public CWHRoundRectFrameHelper<CEditConfigDlg>
{
public:
	CEditConfigDlg(void);
	~CEditConfigDlg(void);

	BOOL OnInitDialog(HWND wndFocus, LPARAM lInitParam);

	BEGIN_MSG_MAP_EX_DECL()


	void OnSave();

	EVENT_MAP_DECL()
private:
	CScintillaWnd *			 m_pSciter;

};

