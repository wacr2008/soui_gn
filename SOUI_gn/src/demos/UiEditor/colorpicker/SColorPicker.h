#pragma once
#include "ColourPopup.h"

namespace SOUI
{
    class EventColorChange : public TplEventArgs<EventColorChange>
    {
        SOUI_CLASS_NAME_DECL(EventColorChange,L"on_color_changed")
    public:
        EventColorChange(SObject *pSender,COLORREF _crSel):TplEventArgs<EventColorChange>(pSender),crSel(_crSel){}
        enum{EventID=EVT_EXTERNAL_BEGIN+100};
        COLORREF crSel;
    };

class SColorPicker :
	public SButton ,
	public IColorPicker
{
	SOUI_CLASS_NAME_DECL(SColorPicker, L"colorpicker")

public:
	SColorPicker(void);
	~SColorPicker(void);

	COLORREF GetColor(){return m_crCur;}
protected://IColorPicker
	virtual void OnColorChanged(COLORREF cr);
	virtual void OnColorEnd(BOOL bCancel,COLORREF cr);
    virtual SMessageLoop * GetMsgLoop();
protected:
	void OnPaint(IRenderTarget *pRT);
	void OnLButtonUp(UINT nFlags,CPoint pt);

	SOUI_MSG_MAP_DECL()

	SOUI_ATTRS_DECL()
	
	COLORREF	m_crDef;
	COLORREF	m_crCur;
};

}
