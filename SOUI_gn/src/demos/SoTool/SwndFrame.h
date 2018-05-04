#pragma once

#include <core/SimpleWnd.h>

namespace SOUI
{
    class SwndFrame : public CSimpleWnd
    {
    public:
        SwndFrame(void);
        ~SwndFrame(void);
        
        BOOL Create(HWND hOwner=NULL);
		void Hide();
        void Show(RECT rc,HWND hWnd=HWND_TOPMOST);
    protected:
        void OnPaint(HDC hdc);
        void OnTimer(UINT_PTR nIDEvent);
        
        BEGIN_MSG_MAP_EX_DECL()
    };

}
