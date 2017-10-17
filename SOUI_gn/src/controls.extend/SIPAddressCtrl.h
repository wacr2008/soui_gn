/********************************************************************
	created:	2014/11/03
	created:	3:11:2014   16:13
	filename: 	SIPAddressCtrl.h
	author:		冰
	
	purpose:	SOUI版的IP控件
*********************************************************************/
#pragma once

namespace SOUI
{
	
	class SEditIP;
	
	class SIPAddressCtrl :
		public SWindow
	{
		SOUI_CLASS_NAME_DECL(SIPAddressCtrl,L"ipctrl")
	public:
		SIPAddressCtrl(void);
		~SIPAddressCtrl(void);

		BOOL IsBlank() const;
		void ClearAddress();
		int GetAddress(_Out_ BYTE& nField0,_Out_  BYTE& nField1,_Out_  BYTE& nField2,_Out_  BYTE& nField3) const;
		int GetAddress(_Out_ DWORD& dwAddress) const;

		void SetAddress(_In_ DWORD dwAddress);
		void SetAddress(_In_ BYTE nField0,_In_ BYTE nField1,_In_ BYTE nField2,_In_ BYTE nField3);

		void SetFieldFocus(WORD nField);
		void SetFieldRange(int nField, BYTE nLower, BYTE nUpper);
	protected:
		void OnPaint(IRenderTarget *pRT);
		LRESULT OnCreate(LPVOID); 
		void OnSize( UINT nType, CSize size );
		
		SOUI_MSG_MAP_DECL()
	private:
		SEditIP * m_editFields[4];
	};
}
