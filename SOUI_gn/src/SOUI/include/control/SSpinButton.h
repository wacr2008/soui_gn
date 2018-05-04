#pragma once
#include "core/swnd.h"

namespace SOUI
{
class SSpinButton : public SWindow, public ITimelineHandler
{
	SOUI_CLASS_NAME_DECL(SSpinButton, L"spin")
public:
	SSpinButton();
	~SSpinButton() override;
	void SetBuddy(SWindow* pBuddy);
protected:
	int HitTest(CPoint pt);
	void Start();
	void Stop();
	bool IsPlaying();
	void ChangeValue(int nHover);
protected:
	void OnNextFrame() override;
protected:
    LRESULT OnCreate(LPVOID);
	void OnShowWindow(BOOL bShow, UINT nStatus);
	void OnDestroy();
	void OnPaint(IRenderTarget *pRT);
	void OnLButtonDown(UINT nFlags, CPoint pt);
	void OnLButtonUp(UINT nFlags, CPoint pt);
	void OnMouseMove(UINT nFlags, CPoint point);
	void OnMouseLeave();
    //void ResizeHostWindow(int nOffset);
	HRESULT OnAttrBuddy(const SStringW& strValue, BOOL bLoading);

    SOUI_ATTRS_DECL()

	SOUI_MSG_MAP_DECL()

    int										m_nMinValue;         /**< 最小大小 */
    int										m_nMaxValue;         /**< 最大大小 */
	UINT									m_uStep;
	bool									m_bCircle;
	ISkinObj*							m_pSpinSkin;
	int										m_nHover;			// -1 none  1 left top		2 right bottom
	int										m_nPush;

	SWindow*							m_pBuddy;

	bool									m_bFirst;
	int										m_iNextTime;
};

};