
#include "DlgNewSkin.h"
#include "CDebug.h"

namespace SOUI
{
	SOUI_CLASS_NAME(SDlgNewSkin, L"dlgnewskin")

	EVENT_MAP_BEGIN(SDlgNewSkin)

		EVENT_NAME_COMMAND(L"btnOK", OnOK)
		EVENT_NAME_COMMAND(L"btnCancel", OnCancel)
	EVENT_MAP_END()

	BEGIN_MSG_MAP_EX(SDlgNewSkin)
		MSG_WM_INITDIALOG(OnInitDialog)
		//MSG_WM_CLOSE(OnCancel)
		//MSG_WM_KEYDOWN(OnKeyDown)
		CHAIN_MSG_MAP(SHostDialog)
		REFLECT_NOTIFICATIONS_EX()
	END_MSG_MAP()

	SDlgNewSkin::SDlgNewSkin(LPCTSTR pszXmlName):SHostDialog(pszXmlName)
	{

	}

	//TODO:消息映射
	void SDlgNewSkin::OnCancel()
	{
		SHostDialog::OnCancel();
	}

	void SDlgNewSkin::OnOK()
	{
		int n = m_lbMain->GetCurSel();
		if (n >= 0)
		{
			m_lbMain->GetText(n, m_strSkinName);
		}
		else
		{
			CDebug::Debug(_T("请选择其中一项"));
			return;
		}
				

		SHostDialog::OnOK();
	}

	BOOL SDlgNewSkin::OnInitDialog(HWND wndFocus, LPARAM lInitParam)
	{
		m_lbMain = FindChildByName2<SListBox>(L"NAME_UIDESIGNER_NEW_SKIN_LB");


		pugi::xml_document doc;
		pugi::xml_parse_result result = doc.load_file(_T("Config\\SkinProperty.xml"));
		if (!result)
		{
			CDebug::Debug(_T("Config\\SkinProperty.xml加载失败"));
			return TRUE;
		}

		pugi::xml_node Node = doc.child(_T("root")).first_child();
		while (Node)
		{
			m_lbMain->AddString(Node.name());
			Node = Node.next_sibling();
		}

		return TRUE;
	}

}


