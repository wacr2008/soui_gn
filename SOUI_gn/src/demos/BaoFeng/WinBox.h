#pragma once

class CWinBox : public SOUI::SHostWnd
{
public:
	CWinBox(void);
	~CWinBox(void);

	void OnClose();				//关闭暴风盒子
	void OnBtnBack();			//后退
	void OnBtnForward();		//前进
	void OnBtnRefresh();		//刷新
	void OnBtnMaximize();		//最大化
	void OnBtnRestore();		//还原

	BOOL OnInitDialog(HWND wndFocus, LPARAM lInitParam);

protected:
	//按钮事件处理映射表
	EVENT_MAP_DECL() 

	//窗口消息处理映射表
	BEGIN_MSG_MAP_EX_DECL()
private:
	BOOL            m_bLayoutInited;
public:
	void*			m_boxParent;
	RECT			rect_box;
};