/**
* Copyright (C) 2014-2050 SOUI团队
* All rights reserved.
* 
* @file       SAnimImg.h
* @brief      
* @version    v1.0      
* @author     水木之     
* @date       2014-07-06
* 
* Describe    动作图片
*/
#pragma once
#include <core/swnd.h>

namespace SOUI
{
 
    class SAnimImg : public SWindow , protected ITimelineHandler
    {
        SOUI_CLASS_NAME_DECL(SAnimImg, L"anmimg")
	public:
		SAnimImg(void);
		~SAnimImg(void);
    protected:
        virtual void OnNextFrame();
        
        virtual CSize GetDesiredSize(LPCRECT pRcContainer);
        
        void NextImage();
        
        void OnDestroy();
		int  OnCreate(void*);
        void OnPaint(IRenderTarget *pRT);
        void OnMouseHover(WPARAM wParam, CPoint ptPos);
        void OnMouseLeave();
        
        SOUI_MSG_MAP_DECL()
 
        SOUI_ATTRS_DECL() 
	public:
		int m_iInterval;//动画间隔 单位毫秒
		int m_iAutorun;//自动运行模式
		//-1:默认，不自动运行
		//0:连续动画（使用ani_in）
		//大于0：间隔动画的暂停时间，单位秒
		int m_iAutorun1000;
		bool m_bWaitrun;
		int m_iHitTest;//记录鼠标位置（大于0表示鼠标还在里面）
		enum ANI_STATUS{
		STATUS_NOR=0,
		STATUS_IN,
		STATUS_OUT,
		} m_aniStatus;
		
		int          m_iFrame;
		
		int          m_nElapseTime;
		int m_nAutoElapseTime;
		ISkinObj    *m_pAniIn;
		ISkinObj    *m_pAniOut;
    };

}//namespace SOUI