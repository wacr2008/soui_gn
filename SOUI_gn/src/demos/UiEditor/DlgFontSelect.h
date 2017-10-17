#pragma once
#include "core/shostwnd.h"
#include "core/smsgloop.h"
#include "core/SHostDialog.h"
#include "DesignerView.h"

#ifdef _UNICODE  
#define tstring wstring  
#else  
#define tstring string  
#endif  


namespace SOUI
{
	class SDlgFontSelect: public SHostDialog
	{
		SOUI_CLASS_NAME_DECL(SDlgFontSelect,L"dlgfontselect")
	public:
		SDlgFontSelect(SStringT strFont, SDesignerView *pDesignerView);

		~SDlgFontSelect(void)
		{

		}

		BOOL OnInitDialog(HWND wndFocus, LPARAM lInitParam);
		//virtual INT_PTR DoModal(HWND hParent=NULL);

		//virtual void EndDialog(INT_PTR nResult);


	protected:
		//void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
		void OnOK();
		void OnCancel();
		void OnCKClick();


		bool OnReNotify(EventArgs *pEvt);
		bool OnSizeReNotify(EventArgs *pEvt);

		bool OnLBSelChanged(EventArgs *pEvt);
		bool OnCBSelChanged(EventArgs *pEvt);

		//virtual SMessageLoop * GetMsgLoop(){return m_MsgLoop;}

		EVENT_MAP_DECL()

		BEGIN_MSG_MAP_EX_DECL()

	public:
		
		 static int CALLBACK EnumFontFamProc(LPENUMLOGFONT lpelf,LPNEWTEXTMETRIC lpntm,DWORD nFontType,long lparam)
		{

			SMap<SStringT, SStringT> *map = (SMap<SStringT, SStringT>*) lparam;
			SStringT str = lpelf ->elfLogFont.lfFaceName;
			(*map)[str] = str;
			return TRUE;
		}

		static int GetLbIndexFromText(SListBox *lb, SStringT strText);


		void PreviewFont();

		void InitInfo(IFontPtr ft);
		SStringT GetFontStr();

	public:
		SListBox*     m_LbFont;
		SCheckBox*    m_chkBold;
		SCheckBox*    m_chkItalic;
		SCheckBox*    m_chkUnderline;
		SCheckBox*    m_chkStrike;

		SEdit*        m_edtSearch;
		SEdit*        m_edtSize;
		SWindow*      m_wndPreview;

		SStringT m_strFont;
		SMap<SStringT, SStringT> m_map;
		SDesignerView *m_pDesignerView;




	};

}