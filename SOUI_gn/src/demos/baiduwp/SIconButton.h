#pragma once

#include <control/SCmnCtrl.h>

namespace SOUI
{
	class SIconButton : public SImageButton
	{
		SOUI_CLASS_NAME_DECL(SIconButton,L"iconbtn")
	protected:
		ISkinObj *m_pSkinIcon; /**< ISkibObj对象  */
		CPoint m_ptIcon;   /**< 图标位置 */
		CPoint m_ptText;   /**< 标题位置 */
	public:
		SIconButton(void);
		~SIconButton(void);

	protected:
		virtual void GetTextRect(LPRECT pRect);
		void OnPaint(IRenderTarget *pRT);

		SOUI_MSG_MAP_DECL()

		SOUI_ATTRS_DECL()
	};
}

