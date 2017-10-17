#pragma once
#include <helper/SMatrix.h>
namespace SOUI
{
class SMatrixWindow : public SWindow
{
SOUI_CLASS_NAME_DECL(SMatrixWindow,L"matrixWindow")
public:
    SMatrixWindow(void);
    ~SMatrixWindow(void);
    
protected:
    void OnPaint(IRenderTarget *pRT);
    BOOL OnEraseBkgnd(IRenderTarget *pRT){return TRUE;}

    SOUI_MSG_MAP_DECL()
protected:
    HRESULT OnAttrRotate(const SStringW & strValue,BOOL bLoading);
    HRESULT OnAttrScale(const SStringW & strValue,BOOL bLoading);
    HRESULT OnAttrSkew(const SStringW & strValue,BOOL bLoading);
    HRESULT OnAttrTranslate(const SStringW & strValue,BOOL bLoading);
    
    SOUI_ATTRS_DECL()
    
    float m_fRotate;
    float m_fScaleX,m_fScaleY;
    float m_fSkewX, m_fSkewY;
    float m_fTransX, m_fTransY;
};

}