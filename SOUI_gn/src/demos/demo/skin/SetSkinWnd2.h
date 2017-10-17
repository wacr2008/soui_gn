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
	//TODO:消息映射
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
	EVENT_MAP_DECL()
	BEGIN_MSG_MAP_EX_DECL()
private:
	SOUI::SList<SKIN_CONFIG_INF> m_skinConfigInf;
};

