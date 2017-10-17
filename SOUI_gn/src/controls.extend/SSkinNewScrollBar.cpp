 #include "SSkinNewScrollBar.h"
 
 SOUI_CLASS_NAME(SOUI::SSkinNewScrollbar, L"newScrollbar")
 
SOUI_ATTRS_BEGIN(SOUI::SSkinNewScrollbar)
    ATTR_IMAGE(L"srcVert", m_pImgVert, FALSE)    //skinObj引用的图片文件定义在uires.idx中的name属性。
    ATTR_IMAGE(L"srcHorz", m_pImgHorz, FALSE)    //skinObj引用的图片文件定义在uires.idx中的name属性。
SOUI_ATTRS_END()
