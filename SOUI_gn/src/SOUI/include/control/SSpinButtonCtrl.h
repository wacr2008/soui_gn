#pragma once
#include "core/SWnd.h"

namespace SOUI
{
    class SSpinButtonCtrl : public SWindow
    {
    SOUI_CLASS_NAME_DECL(SSpinButtonCtrl,L"spinButton")
    public:
        SSpinButtonCtrl(void);
        ~SSpinButtonCtrl(void) override;
        
    protected:
        CSize GetDesiredSize(LPCRECT pRcContainer) override;
        void UpdateChildrenPosition() override;
        BOOL CreateChildren(pugi::xml_node xmlNode) override;
    protected:
        void OnValueChanged();
    
        bool OnUpDownClick(EventArgs *pEvt);
    protected:
        HRESULT OnAttrValue(const SStringW& strValue, BOOL bLoading);
        
        SOUI_ATTRS_DECL() 
        
        int m_nMax;
        int m_nMin;
        int m_nValue;
        UINT m_uStep;
        BOOL m_bCircle;
        SStringW m_strBuddy;
        
        SWindow * m_btnUp;
        SWindow * m_btnDown;
    };
}
