#pragma once
#include "../controls.extend/SRadioBox2.h"
namespace SOUI
{

class SRadioEx: public SRadioBox2
{
    SOUI_CLASS_NAME_DECL(SRadioEx, L"radioex")
    
public:
    SRadioEx();
    ~SRadioEx();
    
    virtual void OnStateChanged(DWORD dwOldState, DWORD dwNewState);
    
};

}