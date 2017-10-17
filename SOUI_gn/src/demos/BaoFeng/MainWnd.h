#pragma once
#include "SkinMgr.h"
#include "WinBox.h"
#include "helper/SMenu.h"

class CMainWnd : public SOUI::SHostWnd
{
public:
	CMainWnd();
	~CMainWnd();

	void OnClose()
	{
		PostMessage(WM_QUIT);
	}
	void OnMaximize()
	{
		SendMessage(WM_SYSCOMMAND,SC_MAXIMIZE);
	}
	void OnRestore()
	{
		SendMessage(WM_SYSCOMMAND,SC_RESTORE);
	}
	void OnMinimize()
	{
		SendMessage(WM_SYSCOMMAND,SC_MINIMIZE);
	}

	void OnSize(UINT nType, SOUI::CSize size);
	BOOL OnInitDialog(HWND wndFocus, LPARAM lInitParam);

	//按钮控件的响应
	void OnBtnIcon();				//左上角icon按钮
	void OnBtnFeedback();			//意见反馈
	void OnBtnSkins();				//换肤按钮	
	void OnBtnBgOpen();				//播放区域打开文件
	void OnBtnBgOpenMenu();			//播放区域打开菜单
	void OnBtnTools();				//工具箱
	void OnBtnLEye();				//左眼
	void OnBtnLEyed();				//关闭左眼
	void OnBtnStop();				//停止
	void OnBtnPageUp();				//上一个
	void OnBtnPlay();				//播放
	void OnBtnPause();				//暂停
	void OnBtnPageDown();			//下一个
	void OnBtnOpen();				//打开文件
	void OnBtnVolume();				//静音
	void OnBtnVolumeQuit();				//静音
	void OnBtnFullscreen();			//全屏
	void OnBtnQuitFullscreen();		//关闭全屏
	void OnBtnListShow();			//显示播放列表
	void OnBtnListShowed();			//隐藏播放列表
	void OnBtnBox();				//打开暴风盒子
	void OnBtnBoxHide();				//关闭暴风盒子

	void OnBtnToolsWinClose();		//工具箱窗口的关闭按钮
	void OnBtnToolsWinPrev();		//上一个
	void OnBtnToolsWinNext();		//下一个
	void OnBtnTool3D();				//3D
	void OnBtnToolLefteye();		//左眼
	void OnBtnToolSurronudsound();	//环绕声
	void OnBtnToolFlyscreen();		//飞屏
	void OnBtnToolGame();			//游戏
	void OnBtnToolDownload();		//下载管理
	void OnBtnToolTranscode();		//转码
	void OnBtnToolMovielib();		//影视库
	void OnBtnToolBarrage();		//弹幕
	void OnBtnToolDlna();			//dlna
	void OnBtnToolNews();			//资讯
	void OnBtnToolScreebshots();	//截图
	void OnBtnToolShoot();			//连拍

	void OnBtnPage1SortordMenu();	//播放列表排序方式
	void OnBtnPage1Sortord();	//播放列表排序方向，向下或向上

	//播放列表tab页2
	void OnBtnAll()	;				//【全部】
	void OnBtnAdd()	;				//【+】
	void OnBtnDelete()	;			//【-】
	void OnBtnClear()	;			//清空列表按钮
	void OnBtnOrderPlay();			//顺序播放
	void OnBtnSinglePlay()	;		//单个播放
	void OnBtnRandomPlay()	;		//随机播放
	void OnBtnSingleCycle()	;		//单个循环
	void OnBtnListCycle()	;		//列表循环
	char * THCAR2char(TCHAR* tchStr) ;

	//DUI菜单响应函数
	void OnCommand(UINT uNotifyCode, int nID, HWND wndCtl);

	SOUI::SMenu menu_sortord;				//tab页1中列表排序方式菜单
	SOUI::SMenu menu_icon;				//icon按钮的弹出菜单
	SOUI::SMenu menu_PlayArea;			//播放区域打开文件按钮的弹出菜单
	SOUI::SMenu menu_PlayMode;			//播放模式菜单

	int up_or_down;					//排序方式向上或向下
	BOOL popularity_up_or_down;		//排序方式为“观众”时，向上或向下

protected:
	//按钮事件处理映射表
	EVENT_MAP_DECL()

	//窗口消息处理映射表
	BEGIN_MSG_MAP_EX_DECL()
private:
	BOOL            m_bLayoutInited;
	CSkinMgr		m_dlgSkinMgr;		//皮肤管理窗口
	CWinBox			m_winBox;				//暴风盒子
};