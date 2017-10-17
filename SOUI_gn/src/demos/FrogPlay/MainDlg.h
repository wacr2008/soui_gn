// MainDlg.h : interface of the CMainDlg class
//
/////////////////////////////////////////////////////////////////////////////
#pragma once
#include <set>
#include <vector>
#include <list>
#include <deque>
#include "AVPlayer.h"
using namespace std;
enum enum_PlayMode
{
	EM_PLAY_MODE_SEQUENCE,      // 顺序播放
	EM_PLAY_MODE_RANDOM,        // 随机播放
	EM_PLAY_MODE_SINGLE_CIRCLE  // 单曲循环
};
class CMainDlg : public SHostWnd
{
public:
	CMainDlg();
	~CMainDlg();

	void OnClose();
	void OnMaximize();
	void OnRestore();
	void OnMinimize();
	void OnSize(UINT nType, CSize size);

	void OnBtnMsgBox();
	int OnCreate(LPCREATESTRUCT lpCreateStruct);
	BOOL OnInitDialog(HWND wndFocus, LPARAM lInitParam);
	void OnTabPageRadioSwitch(EventArgs *pEvt);
	void OnLButtonUp(UINT nFlags, CPoint pt);
	void OnLButtonDown(UINT nFlags, CPoint pt);
	void OnMouseMove(UINT nFlags, CPoint pt);
	void OnShowPlayList();//打开关闭播放列表
	void OnCommand(UINT uNotifyCode, int nID, HWND wndCtl);
	LRESULT OnPlaying(UINT uMsg, WPARAM wp, LPARAM lp, BOOL & bHandled);     // 文件头读取完毕，开始播放
	LRESULT OnPosChanged(UINT uMsg, WPARAM wp, LPARAM lp, BOOL & bHandled);  // 进度改变，播放器传回来的进度
	LRESULT OnEndReached(UINT uMsg, WPARAM wp, LPARAM lp, BOOL & bHandled);  // 文件播放完毕

	LRESULT OnMyMsg_REALWND(UINT uMsg, WPARAM wp, LPARAM lp, BOOL & bHandled);//真窗口处理
	LRESULT OnMyMsg_PLAY_FILE(UINT uMsg, WPARAM wp, LPARAM lp, BOOL & bHandled);//播放文件
	LRESULT OnMyMsg_ADD_FILED(UINT uMsg, WPARAM wp, LPARAM lp, BOOL & bHandled);//增加文件完成后的通知
	LRESULT OnMyMsg_REALWND_URLPLAY(UINT uMsg, WPARAM wp, LPARAM lp, BOOL & bHandled);//url播放
	bool LoadhistoryXml();
	void OnBtnPlay();
	void OnBtnPause();
	void OnBtnOpen();
	void OnBtnStop();
	void OnBtnPlayPrev();
	void OnBtnPlayNext();
	void OnSeekBackwardBtn();
	void OnSeekForwardBtn();
	void OnBtnVolum_mute();    //静音
	void OnOpenPlayListLoop_Menu();
	void OnOpenMainBtn_Menu();
	void Play(bool bPlay);                                          // 播放或暂停
	void Play(LPCTSTR pszPath);                                     // 播放路径为pszPath的文件

	void On_directories();  //打开目录
	void FullScreen(bool bFull);                                  // 全屏
	void OnFullScreenBtn();
	void OnBtn_Menu_History();                                    //打开播放痕迹菜单
	void Ondellfiles_MenuBtn();                                    //打开删除菜单
	void OnAddfiles_MenuBtn();                                     //打开增加菜单
	SStringT playNext(bool bNext);                                  //得到播放下一个路径
	void OnBtnSnapshot();

	//win7 任务栏消息
	LRESULT  MsgProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
protected:
	//soui消息
	EVENT_MAP_BEGIN()
		EVENT_NAME_COMMAND(L"btn_close", OnClose)
		EVENT_NAME_COMMAND(L"btn_min", OnMinimize)
		EVENT_NAME_COMMAND(L"btn_max", OnMaximize)
		EVENT_NAME_COMMAND(L"btn_restore", OnRestore)
		EVENT_ID_RANGE_HANDLER(10000,10004, EventSwndStateChanged::EventID, OnTabPageRadioSwitch)    //10000-10005是XML中定义的radio2的ID
		EVENT_ID_COMMAND(124,OnShowPlayList)
		EVENT_ID_COMMAND(200, OnBtnPlay)
		EVENT_ID_COMMAND(201, OnBtnPause)
		EVENT_ID_COMMAND(202, OnBtnStop)
		EVENT_ID_COMMAND(203, OnBtnOpen)
		EVENT_ID_COMMAND(204, OnBtnPlayPrev)
		EVENT_ID_COMMAND(205, OnBtnPlayNext)
		EVENT_ID_COMMAND(610, OnSeekForwardBtn)
		EVENT_ID_COMMAND(611, OnSeekBackwardBtn)
		EVENT_ID_COMMAND(206, OnBtnVolum_mute)
		EVENT_ID_COMMAND(300, OnOpenPlayListLoop_Menu)
		EVENT_ID_COMMAND(501, OnOpenMainBtn_Menu)
	   EVENT_ID_COMMAND(600, OnFullScreenBtn)
	   EVENT_ID_COMMAND(250, OnBtn_Menu_History)
	   EVENT_ID_COMMAND(701, Ondellfiles_MenuBtn)
	   EVENT_ID_COMMAND(700, OnAddfiles_MenuBtn)
	   EVENT_ID_COMMAND(251, OnBtnSnapshot)
		EVENT_MAP_END()
	//HostWnd真实窗口消息处理
	BEGIN_MSG_MAP_EX(CMainDlg)
		MSG_WM_CREATE(OnCreate)
		MSG_WM_INITDIALOG(OnInitDialog)
		MSG_WM_CLOSE(OnClose)
		MSG_WM_SIZE(OnSize)
		MSG_WM_LBUTTONDOWN(OnLButtonDown)
		MSG_WM_LBUTTONUP(OnLButtonUp)
		MSG_WM_MOUSEMOVE(OnMouseMove)
		MSG_WM_COMMAND(OnCommand)
		MESSAGE_HANDLER(WM_USER_PLAYING, OnPlaying)
		MESSAGE_HANDLER(WM_USER_POS_CHANGED, OnPosChanged)
		MESSAGE_HANDLER(WM_USER_END_REACHED, OnEndReached)

		MESSAGE_HANDLER(MS_REALWND, OnMyMsg_REALWND)
		MESSAGE_HANDLER(MS_PLAYING_PATHNAME, OnMyMsg_PLAY_FILE)
		MESSAGE_HANDLER(MS_ADD_FILESED, OnMyMsg_ADD_FILED)
		MESSAGE_HANDLER(MS_REALWND_URLPLAY, OnMyMsg_REALWND_URLPLAY)
		
		if (uMsg == WM_TASKBARBUTTONCREATED ) //win7任务栏通知
		{ 
			SetMsgHandled(TRUE); 
			MsgProc(hWnd,uMsg,wParam,lParam);
			lResult = 0; 
			if(IsMsgHandled()) 
				return TRUE; 
		}
		CHAIN_MSG_MAP(SHostWnd)
		REFLECT_NOTIFICATIONS_EX()
	END_MSG_MAP()
private:
	BOOL			m_bLayoutInited;
	UINT WM_TASKBARBUTTONCREATED;        //win7任务栏
	ITaskbarList3 *g_pTaskbar;
	SSliderBar   *m_Sliderbarpos;
	SSliderBar   *m_VolumeSlider;
	WINDOWPLACEMENT m_OldWndPlacement;  // 保存窗口原来的位置
	bool            m_bFullScreenMode;  // 是否在全屏模式
	int             m_iPlaylistIndex;
	bool            m_bPlayList_ShowWnd; //保存播放列表显示状态
	CAVPlayer       m_cAVPlayer;        // 播放器类
	enum_PlayMode   m_emPlayMode;       // 播放模式
	SStringT      m_strPath;          // 当前文件的路径
	SListView       *m_Play_List_Wnd; //播放列表控件
	//配置文件
	SStringT config_file;            //配置文件路径
	set<SStringT> Hstory_List;     //这里保存历史播放文件
	bool        m_Exit_Save_HistroyList;  //退出时是否保存播放痕迹
    std::deque<unsigned>   m_queRand;   // 随机播放模式的文件序号
};
