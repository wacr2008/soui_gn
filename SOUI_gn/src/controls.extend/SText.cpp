
#include "SText.h"
using namespace SOUI;

SOUI_CLASS_NAME(SText, L"textex")

void SText::DrawText(IRenderTarget *pRT,LPCTSTR pszBuf,int cchText,LPRECT pRect,UINT uFormat)
{
    pRT->DrawText(pszBuf,cchText,pRect,uFormat|DT_WORDBREAK|DT_EDITCONTROL);
}
