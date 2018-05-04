#pragma once
#include "droptarget.h"
#include "SImgCanvas.h"

class CImageMergerHandler : public IFileDropHandler
{
friend class CMainDlg;
public:
    CImageMergerHandler(void);
    ~CImageMergerHandler(void);
    
    void OnInit(SOUI::SWindow *pRoot);
    
    void AddFile(LPCWSTR pszFileName);
protected:
    virtual void OnFileDropdown(HDROP hDrop);

    void OnSave();
	void OnSaveToIco();
    void OnClear();
    void OnModeHorz();
    void OnModeVert();
    void OnSplit();
    EVENT_MAP_DECL_EX()
    
    SOUI::SWindow *m_pPageRoot;
    SOUI::SImgCanvas *m_pImgCanvas;
};
