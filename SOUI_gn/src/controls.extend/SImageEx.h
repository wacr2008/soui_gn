#pragma once
#include "core/SWnd.h"

namespace SOUI
{
class SImageEx : public SImageWnd
{
    SOUI_CLASS_NAME_DECL(SImageWnd, L"imgex")
public:
    SImageEx();
    ~SImageEx();

protected:
    HRESULT OnSrc(const SStringW& strValue, BOOL bLoading);

    SOUI_ATTRS_DECL()
};

};