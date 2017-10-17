#pragma once
#include <core/Swnd.h>

namespace SOUI
{
	class  SSwitch : public SWindow
	{
		SOUI_CLASS_NAME_DECL(SSwitch,L"switch")
	public:
		SSwitch();
		~SSwitch();
	protected://SWindow的虚函数
		virtual CSize GetDesiredSize(LPCRECT pRcContainer);
	public://属性处理
		BOOL IsOpen() {return m_BOpen;}
	protected://消息处理，SOUI控件的消息处理和WTL，MFC很相似，采用相似的映射表，相同或者相似的消息映射宏
		void OnPaint(IRenderTarget *pRT);
		void OnTimer(char cTimerID);
		void OnLButtonUp(UINT nFlags, CPoint point);
		void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
		HRESULT OnAttrOpen(const SStringW& strValue, BOOL bLoading);
		void SetOpen(BOOL bOpen);
		UINT _GetDrawState();
		virtual void OnStateChanged(DWORD dwOldState,DWORD dwNewState);

		//SOUI控件消息映射表
		SOUI_MSG_MAP_DECL()

		SOUI_ATTRS_DECL()

		ISkinObj *m_pSkin;  /**< ISkinObj对象 */
		ISkinObj *m_pSkinForce; //

	private:
		BOOL m_BOpen;			//是否为打开状态
		BOOL m_BOpenTarget;     //目标状态
		BOOL m_BChangeing;      //正在改变状态..
		int  m_Iinterval;		//动画间隔
		int  m_FrameCount;		//动画帧数
		int  m_FrameNow;		//当前帧

	};

}