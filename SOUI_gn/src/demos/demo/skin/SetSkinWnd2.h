#pragma once

#define MagicNumber 9527
extern UINT g_dwSkinChangeMessage;
struct SKIN_CONFIG_INF
{
	int id;
	SOUI::CRect margin;
};
class CSetSkinWnd :
	public SOUI::SHostWnd
{
	//TODO:œ˚œ¢”≥…‰
	void OnClose()
	{
		CSimpleWnd::DestroyWindow();
	}
	HRESULT OnSkinChangeMessage(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL bHandled);
	
	void OnColor(SOUI::EventArgs * e);
	BOOL OnInitDialog(HWND wndFocus, LPARAM lInitParam);
protected:
	virtual void OnFinalMessage(HWND hWnd) {
		__super::OnFinalMessage(hWnd);
		delete this;
	}
	long NotifUpdataWindow();
	void LoadSkinConfigFormXml();
	SOUI::CRect GetMargin(int id);	
public:
	CSetSkinWnd();
	~CSetSkinWnd();
	void OnSetSkin(SOUI::EventArgs *e);
	void OnActivate(UINT nState, BOOL bMinimized, HWND wndOther);
	EVENT_MAP_BEGIN()
		EVENT_NAME_COMMAND(L"btn_close", OnClose)
		EVENT_ID_RANGE_HANDLER(10, 27, SOUI::EVT_CMD, OnSetSkin)
		EVENT_ID_RANGE_HANDLER(30,48,SOUI::EVT_CMD, OnColor)		
	EVENT_MAP_END()
		BEGIN_MSG_MAP_EX(CSetSkinWnd)
		MSG_WM_INITDIALOG(OnInitDialog)
		MESSAGE_HANDLER(g_dwSkinChangeMessage, OnSkinChangeMessage)
		//MSG_WM_ACTIVATE(OnActivate)
		CHAIN_MSG_MAP(SOUI::SHostWnd)
		REFLECT_NOTIFICATIONS_EX()
		END_MSG_MAP()
private:
	SOUI::SList<SKIN_CONFIG_INF> m_skinConfigInf;
};

