#pragma once

class CSkinMgr : public SOUI::SHostWnd
{
public:
	CSkinMgr(void);
	~CSkinMgr(void);

	void OnClose()
	{
		ShowWindow(SW_HIDE);
	}

	BOOL OnInitDialog(HWND wndFocus, LPARAM lInitParam);

	void OnBtnMaxspeed();			//极速
	void OnBtnDeepblue();			//深湖蓝
	void OnBtnSelfdefine();			//自定义
	void OnBtnBigbang();			//大片风暴
	void OnBtnPrev();				//上一个皮肤
	void OnBtnChoosing1();			//已有的皮肤1
	void OnBtnChoosing2();			//已有的皮肤2
	void OnBtnNext();				//下一个皮肤
	void OnBtnColor1();				//配色1
	void OnBtnColor2();				//配色2
	void OnBtnColor3();				//配色3
	void OnBtnColor4();				//配色4
	void OnBtnColor5();				//配色5
	void OnBtnColor6();				//配色6
	void OnBtnColor7();				//配色7
	void OnBtnColor8();				//配色8
	void OnBtnColor9();				//配色9
	void OnBtnColor10();			//配色10
	void OnBtnColor11();			//配色11
	void OnBtnColor12();			//配色12

protected:
	//按钮事件处理映射表
	EVENT_MAP_DECL() 

	//窗口消息处理映射表
	BEGIN_MSG_MAP_EX_DECL()
private:
	BOOL            m_bLayoutInited;
};