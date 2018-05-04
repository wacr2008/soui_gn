/**
* Copyright (C) 2014-2050 
* All rights reserved.
* 
* @file       MainDlg.h
* @brief      
* @version    v1.0      
* @author     SOUI group   
* @date       2014/08/15
* 
* Describe    主窗口实现
*/

#pragma once

using namespace SOUI;

#include "magnet/MagnetFrame.h"
#include "ThreadObject.h"
#include "skin/SDemoSkin.h"
#include "../../controls.extend/SMcListViewEx/STabCtrlHeaderBinder.h"
#include "event/NotifyCenter.h"
#include "res/R.h"
#include "SChromeTabCtrl.h"
extern UINT g_dwSkinChangeMessage;
//演示使用SNotifyCenter的异步事件
class EventThread : public TplEventArgs<EventThread>
{
	SOUI_CLASS_NAME_DECL(EventThread,L"on_event_thread")
public:
	EventThread(SObject *pSender):TplEventArgs<EventThread>(pSender){}
	enum{EventID=EVT_EXTERNAL_BEGIN+30000};
	
	int nData;
};

//演示使用SNotifyCenter的同步事件
class EventThreadStart : public TplEventArgs<EventThreadStart>
{
	SOUI_CLASS_NAME_DECL(EventThreadStart,L"on_event_thread_start")
public:
	EventThreadStart(SObject *pSender):TplEventArgs<EventThreadStart>(pSender){}
	enum{EventID=EVT_EXTERNAL_BEGIN+30001};
};

//演示使用SNotifyCenter的同步事件
class EventThreadStop : public TplEventArgs<EventThreadStop>
{
	SOUI_CLASS_NAME_DECL(EventThreadStop,L"on_event_thread_stop")
public:
	EventThreadStop(SObject *pSender):TplEventArgs<EventThreadStop>(pSender){}
	enum{EventID=EVT_EXTERNAL_BEGIN+30002};
};


/**
* @class      CMainDlg
* @brief      主窗口实现
* 
* Describe    非模式窗口从SHostWnd派生，模式窗口从SHostDialog派生
*/
class CMainDlg : public SHostWnd
			   , public CMagnetFrame	//磁力吸附
			   //, public ISetSkinHandler	//皮肤处理
			   , public CThreadObject	//线程对象
			   , public TAutoEventMapReg<CMainDlg>//通知中心自动注册
			   , public ISetOrLoadSkinHandler
{
public:

    /**
     * CMainDlg
     * @brief    构造函数
     * Describe  使用uires.idx中定义的maindlg对应的xml布局创建UI
     */    
    CMainDlg() : SHostWnd(UIRES.LAYOUT.maindlg),m_bLayoutInited(FALSE)
    {
    } 

protected:
    //////////////////////////////////////////////////////////////////////////
    //  Window消息响应函数
    LRESULT OnInitDialog(HWND hWnd, LPARAM lParam);
    void OnDestory();

	void OnClose()
	{
		AnimateHostWindow(200,AW_CENTER|AW_HIDE);
        DestroyWindow();
	}
	void OnMaximize()
	{
		GetNative()->SendMessage(WM_SYSCOMMAND,SC_MAXIMIZE);
	}
	void OnRestore()
	{
		GetNative()->SendMessage(WM_SYSCOMMAND,SC_RESTORE);
	}
	void OnMinimize()
	{
		GetNative()->SendMessage(WM_SYSCOMMAND,SC_MINIMIZE);
	}

	void OnSize(UINT nType, CSize size)
	{
		SetMsgHandled(FALSE);   //这一行很重要，保证消息继续传递给SHostWnd处理，当然也可以用SHostWnd::OnSize(nType,size);代替，但是这里使用的方法更简单，通用
		if(!m_bLayoutInited) return;
		if(nType==SIZE_MAXIMIZED)
		{
			FindChildByID(3)->SetVisible(TRUE);
			FindChildByID(2)->SetVisible(FALSE);
		}else if(nType==SIZE_RESTORED)
		{
			FindChildByID(3)->SetVisible(FALSE);
			FindChildByID(2)->SetVisible(TRUE);
		}
	}
    
	int OnCreate(LPCREATESTRUCT lpCreateStruct);
    
    //演示如何在应用层使用定时器
	void OnTimer(UINT_PTR idEvent);

    //DUI菜单响应函数
    void OnCommand(UINT uNotifyCode, int nID, HWND wndCtl);
        

protected:
    //virtual void OnSetSkin(int iSkin);

    //////////////////////////////////////////////////////////////////////////
    // SOUI事件处理函数
	//演示屏蔽指定edit控件的右键菜单
	BOOL OnEditMenu(CPoint pt)
	{
		return TRUE;
	}

    //按钮控件的响应
    void OnBtnSelectGIF();
    void OnBtnMenu();

    void OnBtnInsertGif2RE();
    void OnBtnAppendMsg();
    void OnBtnRtfSave();
    void OnBtnRtfOpen();
    
    void OnBtnHideTest();
    void OnBtnMsgBox();

    void OnBtnWebkitGo();
    void OnBtnWebkitBackward();
    void OnBtnWebkitForeward();
    void OnBtnWebkitRefresh();

	void OnBtnLRC();
    
	bool LoadSkin();

	//演示如何使用subscribeEvent来不使用事件映射表实现事件响应
    bool OnListHeaderClick(EventArgs *pEvt);

        
    void OnChromeTabNew(EventArgs *pEvt);

    void OnTabPageRadioSwitch(EventArgs *pEvt);
    
    void OnBtnFileWnd();

    void OnUrlReNotify(EventArgs *pEvt);
    
    void OnMclvCtxMenu(EventArgs *pEvt);
    
    //处理模拟菜单中控件的事件
    void OnMenuSliderPos(EventArgs *pEvt);
    
    void OnMatrixWindowReNotify(EventArgs *pEvt);

    void OnBtnCreateChildren();
    void OnBtnClock();
    void OnBtnSkin();
	void OnInitListBox();

	void OnBtnTip();

	virtual UINT Run();

	//Event Sender ID
	enum {SENDER_ID = 30000};
	virtual int GetID() const {return SENDER_ID;}

	void OnBtnStartNotifyThread();
	void OnBtnStopNotifyThread();

	bool OnEventThreadStart(EventArgs *e);
	bool OnEventThreadStop(EventArgs *e);
	bool OnEventThread(EventArgs *e);
	void OnBtnOpenWrapContent();
	
	void OnCbxInterpolotorChange(EventArgs *e);

	void OnEventPath(EventArgs *e);

	HRESULT OnSkinChangeMessage(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL bHandled);
    //UI控件的事件及响应函数映射表
	EVENT_MAP_DECL()	

    //HOST消息及响应函数映射表
	BEGIN_MSG_MAP_EX_DECL()

protected:
    //////////////////////////////////////////////////////////////////////////
    //  辅助函数
    void InitListCtrl();

	virtual bool SaveSkin(SkinType skinType, SkinSaveInf & skinSaveInf);

private:
	BOOL			m_bLayoutInited;/**<UI完成布局标志 */
	HWND			m_hSetSkinWnd;
	STabCtrlHeaderBinder* m_pTabBinder;
	STabCtrlHeaderBinder* m_pTabBinder2;
};
