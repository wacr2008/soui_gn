#pragma once
#include <richedit.h>
#include "wtl.mini\souimisc.h"

class IRichEditObjHost
{
public:
	virtual SOUI::ISwndContainer * GetHostContainer() = 0;
    virtual SOUI::CRect   GetHostRect() = 0;
	virtual SOUI::CRect   GetAdjustedRect() = 0;
    virtual int     GetContentLength() = 0;
	virtual void    DirectDraw(const SOUI::CRect& rc) = 0;
	virtual void    DelayDraw(const SOUI::CRect& rc) = 0;
    virtual HRESULT SendMessage(UINT uMsg, WPARAM wParam, LPARAM lParam, LRESULT *pRet=NULL) = 0;
    virtual ITextDocument* GetTextDoc() = 0;
};
