#pragma once

#include "SSearchDropdownList.h"
#include "res/R.h"
using namespace SOUI;

struct IStudentCheckChanged
{
    virtual void OnStudentCheckChanged(int nSelCurrent, int nSelExpired) PURE;
};

class CStudentSmsDlg
	: public SOUI::SHostDialog
	, public IStudentCheckChanged
{
public:
    CStudentSmsDlg(void);
    ~CStudentSmsDlg(void);
    
protected:
    void OnBtnSmsRecord();
    
    void OnSearchFillList(EventArgs *e);
    void OnSearchValue(EventArgs *e);
    void OnSmsInputNotify(EventArgs *e);
    EVENT_MAP_DECL()
protected:
    BOOL OnInitDialog(HWND wndFocus, LPARAM lInitParam);
    void OnLButtonDown(UINT nFlags, CPoint point);

    BEGIN_MSG_MAP_EX_DECL()

protected:
    virtual void OnStudentCheckChanged(int nSelCurrent, int nSelExpired);

protected:
	
    SWindow     * m_wndSmsRecord;
	SMCListView * m_tvStudent;
	SListView   * m_lvSmsRecord;
};

