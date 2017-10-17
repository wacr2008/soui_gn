
#pragma once
#include "core/SWnd.h"

namespace SOUI
{

class SText : public SStatic
{
    SOUI_CLASS_NAME_DECL(SText, L"textex")
public:
    virtual void DrawText(IRenderTarget *pRT,LPCTSTR pszBuf,int cchText,LPRECT pRect,UINT uFormat);
};

};