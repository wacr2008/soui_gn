// MainDlg.h : interface of the CMainDlg class
//
/////////////////////////////////////////////////////////////////////////////
#pragma once


#include "SProfilePicture.h"
#include "res/R.h"
using namespace SOUI;

class ChooseAvatarDlg : public SHostDialog
{
public:
    ChooseAvatarDlg();
    ~ChooseAvatarDlg();

    void OnClose();
    void OnMaximize();
    void OnRestore();
    void OnMinimize();
    void OnSize(UINT nType, CSize size);

    void OnBtnMsgBox();
    int OnCreate(LPCREATESTRUCT lpCreateStruct);
    BOOL OnInitDialog(HWND wndFocus, LPARAM lInitParam);
    bool OnPicFrameChange(SOUI::EventArgs * pEvt);
    void OnChooseHeadPic();
    void OnSaveHeadPic();


    SImageWnd* m_img_HeadPic_Large;
    SImageWnd* m_img_HeadPic_Middle;
    SImageWnd* m_img_HeadPic_Small;
    SProfilePicture* m_pHeadPic;

protected:
    //soui消息

    EVENT_MAP_DECL() 

        //HostWnd真实窗口消息处理
    BEGIN_MSG_MAP_EX_DECL() 
private:
    BOOL			m_bLayoutInited;
};
