#pragma once
#include "core/SWnd.h"

namespace SOUI
{
class SWindowEx : public SWindow
{
public:
    SOUI_CLASS_NAME_DECL(SWindowEx, L"windowex")

protected:
    SOUI_MSG_MAP_DECL()
};

};