﻿/**
* Copyright (C) 2014-2050 
* All rights reserved.
* 
* @file       SHostDialog.h
* @brief      
* @version    v1.0      
* @author     SOUI group   
* @date       2014/08/02
* 
* Describe    SOUI的Dialog模块
*/

#pragma once
#include "core/shostwnd.h"
#include "core/smsgloop.h"
#include "core/SHostDialog.h"
#include "control/SRichEdit.h"

namespace SOUI
{
	class SDlgCreatePro: public SHostDialog
	{
		SOUI_CLASS_NAME_DECL(SDlgCreatePro,L"dlgcreatepro")
	public:
		SDlgCreatePro(LPCTSTR pszXmlName):SHostDialog(pszXmlName)
		{

		}
		~SDlgCreatePro(void)
		{

		}

		//virtual INT_PTR DoModal(HWND hParent=NULL);

		//virtual void EndDialog(INT_PTR nResult);

	protected:
		//void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
		void OnOK();
		//void OnCancel();
		//virtual SMessageLoop * GetMsgLoop(){return m_MsgLoop;}

		EVENT_MAP_DECL()

		BEGIN_MSG_MAP_EX_DECL()

	public:
		SStringT m_strinput;
	};

}