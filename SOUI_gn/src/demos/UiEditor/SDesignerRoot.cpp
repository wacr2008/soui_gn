#include "SDesignerRoot.h"

namespace SOUI{
	SOUI_CLASS_NAME(SDesignerRoot, L"designerRoot")

	SDesignerRoot::SDesignerRoot(void)
	{
	}

	SDesignerRoot::~SDesignerRoot(void)
	{
	}

	void SDesignerRoot::BeforePaint(IRenderTarget *pRT, SPainter &painter)
	{
		pRT->SelectObject(m_defFont,(IRenderObj**)&painter.oldFont);
	}

	void SDesignerRoot::AfterPaint(IRenderTarget *pRT, SPainter &painter)
	{
		pRT->SelectObject(painter.oldFont);
	}

}
