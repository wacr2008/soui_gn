#pragma once
#include "droptarget.h"
#include "SFolderList.h"
#include "SEdit2.h"

class CFolderScanHandler : public IFileDropHandler
{
    friend class CMainDlg;
    friend class CDropTarget_Dir2;
public:
    CFolderScanHandler(void);
    ~CFolderScanHandler(void);
    
    void OnInit(SOUI::SWindow *pRoot);
protected:
    virtual void OnFileDropdown(HDROP hDrop);

	void OnGo(SOUI::EventArgs *pEvt);
	bool OnTreeDbclick(SOUI::EventArgs *pEvt);
	BOOL EnumFiles(SOUI::SStringT strPath, HSTREEITEM hParent);
    BOOL DoSomething();
	void InitDir(const SOUI::SStringT & strPath);

    EVENT_MAP_DECL_EX()

	SOUI::SWindow *m_pPageRoot;
	SOUI::SFolderTreeList *m_pTreelist;
};

