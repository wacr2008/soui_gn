// MainDlg.h : interface of the CMainDlg class
//
/////////////////////////////////////////////////////////////////////////////
#pragma once

#include "SLogAdapter.h"

#include "FilterDlg.h"
#include "FindDlg.h"
#include "magnet/MagnetFrame.h"
#include "droptarget.h"
#include "whwindow.h"

class CMainDlg : public SHostWnd
	, public CMagnetFrame
	, public IFileDropHandler 
	, public IFindListener
	, public CWHRoundRectFrameHelper<CMainDlg>
{
public:
	CMainDlg();
	~CMainDlg();

	int FindInTarget(std::string findWhatText, int startPosition, int endPosition);
	int FindNext(const std::string &findWhat,bool bMatchCase, bool bMatchWholeWord, bool reverseDirection, bool showWarnings, bool allowRegExp);
	Sci_CharacterRange GetSelection();
	int LengthDocument();
	void EnsureRangeVisible(int posStart, int posEnd, bool enforcePolicy=true);
	void SetSelection(int anchor, int currentPos);


	void UpdateFilterTags(const SArray<SStringW>& lstTags);
protected:
	void OnSize(UINT nType, CSize size);

	BOOL OnInitDialog(HWND wndFocus, LPARAM lInitParam);

    void OnContextMenu(HWND hwnd, CPoint point);
protected:
	virtual void OnFileDropdown(HDROP hDrop);
	virtual bool OnFind(const SStringT & strText, bool bFindNext, bool bMatchCase, bool bMatchWholeWord);
	
	void OpenFile(LPCTSTR pszFileName);

	void OnClose();
	void OnMaximize();
	void OnRestore();
	void OnMinimize();

	void OnLanguage(const SStringT & strLang);
	void OnLanguageBtnCN();
	void OnLanguageBtnEN();
	void OnOpenFile();
	void OnClear();

	void OnFilterInputChange(EventArgs *e);
	void OnLevelsChange(EventArgs *e);
	bool OnLvContextMenu(CPoint pt);
	void OnOpenFindDlg();
	//soui消息
	EVENT_MAP_DECL()
		//HostWnd真实窗口消息处理
	BEGIN_MSG_MAP_EX_DECL()
	void UpdateFilterPids(const SArray<UINT> & lstPid);
	void UpdateFilterTids(const SArray<UINT> & lstTid);


protected:
	CAutoRefPtr<SLogAdapter> m_logAdapter;
	SComboBox	*			 m_cbxLevels;
	SMCListView	*			 m_lvLogs;	
	CFilterDlg *			 m_pFilterDlg;
	CScintillaWnd *			 m_pSciter;
	CFindDlg   *			 m_pFindDlg;
};
