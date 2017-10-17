#pragma once
#include <core/swnd.h>

namespace SOUI
{
    //
    // 图片显示控件，包括GIF
    //

    class SImageView : public SWindow, public ITimelineHandler
    {
        SOUI_CLASS_NAME_DECL(SImageView, L"image")   //定义GIF控件在XM加的标签

    public:

        SImageView();
        ~SImageView();

        BOOL        ShowImageFile(LPCTSTR pszFileName);
        BOOL        IsPlaying();
        int         GetFrameCount();
        SIZE        GetImageSize();
        void        SetImageSize(SIZE size);
        void        Pause();
        void        Resume();
        void        ShowFrame(int frame, BOOL update = FALSE);
        SStringW    GetRealPath();
        void        SetSkin(ISkinObj* pSkin);
        ISkinObj*   GetSkin();

    protected:

        //SWindow的虚函数
        virtual CSize GetDesiredSize(LPCRECT pRcContainer);

        //ITimerLineHander
        virtual void OnNextFrame();

    protected:

        int  GetFrameDelay();

        HRESULT OnAttrSkin(const SStringW & strValue, BOOL bLoading);



    protected:

        void OnPaint(IRenderTarget *pRT);
        void OnShowWindow(BOOL bShow, UINT nStatus);
        void OnDestroy();

		SOUI_ATTRS_DECL()
        //SOUI控件消息映射表
        SOUI_MSG_MAP_DECL()

    protected:

        ISkinObj *  _pImageSkin;
        BOOL        _isPlaying;
        int	        _currentFrame;
        int         _nextFrameInterval;
        SIZE        _imageSize;
        SStringW    _realPath;      /*< 最终显示的图片路径 */
    };
}