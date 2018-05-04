#pragma once
#include "QR_Encode.h"
#include "control/SCmnCtrl.h"

class SQrCtrl :public SOUI::SImageWnd
{
	SOUI_CLASS_NAME_DECL(SQrCtrl, L"qrctrl")
public:
	SQrCtrl();
	~SQrCtrl();

	virtual void SetWindowText(LPCTSTR lpszText)override;
	virtual BOOL OnRelayout(const  SOUI::CRect &rcWnd)override;
protected:
	void CreateQrImg(SOUI::SStringT strContent);

	void MakeCacheApha(SOUI::ISkinObj *pSkin, SOUI::IBitmap *_pBitCache, SOUI::IBitmap *_pBitMask);

	SOUI_ATTRS_DECL()
private:
	SOUI::CRect m_QrRect;
};

