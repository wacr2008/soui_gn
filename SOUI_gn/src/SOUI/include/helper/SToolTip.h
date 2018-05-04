#pragma once

#include "interface/stooltip-i.h"
#include "core/SimpleWnd.h"

namespace SOUI
{
    class STipCtrl : public IToolTip
                   , public CSimpleWnd 
    {
    public:
        STipCtrl(void);
        ~STipCtrl(void) override;

        BOOL Create();

    public://IToolTip
        /*virtual*/ void RelayEvent(const MSG *pMsg) override;

        /*virtual*/ void UpdateTip(const TIPID &id, CRect rc,LPCTSTR pszTip,int nScale)  override;

        /*virtual*/ void ClearTip() override;

        /*virtual*/ BOOL PreTranslateMessage(MSG* pMsg) override;
    protected:
        void OnFinalMessage(HWND hWnd) override;

        void OnTimer(UINT_PTR idEvent);
        void OnPaint(HDC dc);
        void ShowTip(BOOL bShow);

        BEGIN_MSG_MAP_EX_DECL()

    protected:
        int            m_nDelay;
        int            m_nShowSpan;
        SStringT       m_strTip;
        int            m_nScale;
        CRect          m_rcTarget;
        HFONT          m_font;

        TIPID          m_id;
    };
}

