#pragma once

#include <helper/SMenuEx.h>

namespace SOUI
{
	class SMenuItem;

	class SOUI_EXP SMenuBar : 
		public SWindow
	{
		SOUI_CLASS_NAME_DECL(SMenuBar, L"menubar")
		friend class SMenuItem;
	public:
		SMenuBar();
		~SMenuBar() override;

		BOOL Init(SHostWnd *pHostWnd);
		BOOL Insert(LPCTSTR pszTitle, LPCTSTR pszResName, int iPos = -1);

	protected:
		BOOL CreateChildren(pugi::xml_node xmlNode) override;
		void UpdateChildrenPosition() override;

		SArray<SMenuItem*> m_lstMenuItem;
		HWND m_hWnd;
		pugi::xml_document  m_xmlStyle;
		BOOL m_bIsShow;
		SMenuItem *m_pNowMenu;
	};

}