#pragma once

#include "res/R.h"
#include "SSearchDropdownList.h"
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
    
    void OnSearchFillList(SOUI::EventArgs *e);
    void OnSearchValue(SOUI::EventArgs *e);
    void OnSmsInputNotify(SOUI::EventArgs *e);
    EVENT_MAP_BEGIN()
        EVENT_ID_HANDLER(SOUI::R.id.edit_sms_input,SOUI::EventRENotify::EventID,OnSmsInputNotify)
        EVENT_ID_COMMAND(SOUI::R.id.btn_sms_record,OnBtnSmsRecord);
        EVENT_ID_HANDLER(SOUI::R.id.edit_search,SOUI::EventFillSearchDropdownList::EventID,OnSearchFillList)
        EVENT_ID_HANDLER(SOUI::R.id.edit_search,SOUI::EventDropdownListSelected::EventID,OnSearchValue)
    EVENT_MAP_END()
protected:
    BOOL OnInitDialog(HWND wndFocus, LPARAM lInitParam);
    void OnLButtonDown(UINT nFlags, SOUI::CPoint point);

    BEGIN_MSG_MAP_EX(CStudentSmsDlg)
        MSG_WM_LBUTTONDOWN(OnLButtonDown)
        MSG_WM_INITDIALOG(OnInitDialog)
        CHAIN_MSG_MAP(SOUI::SHostDialog)
    END_MSG_MAP()

protected:
    virtual void OnStudentCheckChanged(int nSelCurrent, int nSelExpired);

protected:
	
    SOUI::SWindow     * m_wndSmsRecord;
	SOUI::SMCListView * m_tvStudent;
	SOUI::SListView   * m_lvSmsRecord;
};

