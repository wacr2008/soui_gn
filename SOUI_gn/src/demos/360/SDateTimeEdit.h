#ifndef __S_DATETIME_EDIT_H__
#define __S_DATETIME_EDIT_H__

#include "control/SRichEdit.h"
#include <vector>
#include <Windows.h>

/*
<date_edit font="face:寰蒋闆呴粦,adding:-3" colorText="#000000">2017-08-01 12:33:33</date_edit>
*/

namespace SOUI
{
	class SDateRichEdit :public SRichEdit
	{
	public:
		STextHost *GetTextHost()
		{
			return this->m_pTxtHost;
		}



		int SetSel(long nStartChar, long nEndChar)
		{
			CHARRANGE cr;
			cr.cpMin = nStartChar;
			cr.cpMax = nEndChar;
			LRESULT lResult;
			m_pTxtHost->GetTextService()->TxSendMessage(EM_EXSETSEL, 0, (LPARAM)&cr, &lResult);
			return (int)lResult;
		}

		void ReplaceSel(LPCTSTR lpszNewText, bool bCanUndo)
		{
#ifdef _UNICODE		
			m_pTxtHost->GetTextService()->TxSendMessage(EM_REPLACESEL, (WPARAM)bCanUndo, (LPARAM)lpszNewText, 0);
#else
			int iLen = _tcslen(lpszNewText);
			LPWSTR lpText = new WCHAR[iLen + 1];
			::ZeroMemory(lpText, (iLen + 1) * sizeof(WCHAR));
			::MultiByteToWideChar(CP_ACP, 0, lpszNewText, -1, (LPWSTR)lpText, iLen);
			m_pTxtHost->GetTextService()->TxSendMessage(EM_REPLACESEL, (WPARAM)bCanUndo, (LPARAM)lpText, 0);
			delete[] lpText;
#endif
		}


	};

    #define DateDelta 693594

    class  CDuiDateTime
    {
    public:
        CDuiDateTime();
        CDuiDateTime(const CDuiDateTime &dTime);
        CDuiDateTime(const double dt) ;
        CDuiDateTime(short year,short month,short day,short hour,short minute,short second,short minsecond=0);
        ~CDuiDateTime();     
        void GetAsSystemTime(SYSTEMTIME &sysTime);
        CDuiDateTime(tm *time);
        bool IsValid()  const;
         
        bool operator>(const CDuiDateTime &dt) const;
        bool operator<(const CDuiDateTime &dt) const;
        bool operator<=(const CDuiDateTime &dt) const;
        bool operator>=(const CDuiDateTime &dt) const;


        SStringT FormatDateString(const TCHAR date_sep=_T('-')) const;
        SStringT FormatDateTimeString(const TCHAR date_sep=_T('-'),const TCHAR time_sep=_T(':')) const ;
        void SetDate(int year,int month,int day);
        void SetTime(int hour,int minute,int second,int minsecond=0);
        void GetCurrentTime();
        bool IsLeapYear(int year)  const;
        int  GetMaxDayOfMonth(int month, int year)  const;
        void encodeDate(double &dt,short year,short month,short day) ;
        void decodeDate(const double dat,short& year,short& month,short& day) ;
        void encodeTime(double& dt,short h,short m,short s,short ms);
        void decodeTime(const double dt,short& h,short& m,short& s,short& ms) ;
        static void DivMod(int op1, int op2, int& div, int& mod);
        static int  IsLeapYear(const __int16 year);
    private:
        void SetTime(tm *time);
    public:  
        short GetYear()  const;
        short GetMonth()  const;
        short GetDay()  const;
        short GetHour()  const;
        short GetMinute() const;        
        short GetSecond() const;    
        short GetMilliseconds() const;
        //赂霉戮脻脩么脌煤脠脮脝脷拢卢路碌禄脴脨脟脝脷录赂
        int GetDayOfWeek();
    private:
        short nYear;
        short nMonth;
        short nDay;
        short nHour;
        short nMinute;
        short nSecond;
        short nMilliseconds;
        double  m_dateTime;
    };

	class  CAMSEdit : public SDateRichEdit
	{
		SOUI_CLASS_NAME_DECL(CAMSEdit, L"amsedit")
	public:
		// Construction/destruction
		CAMSEdit();
		virtual ~CAMSEdit();

		SOUI_MSG_MAP_DECL()

		// Operations 
		SStringT GetTrimmedText() ;

		void GetSel(long &start, long &end);
		
		void OnChar(UINT nChar, UINT nRepCnt, UINT nFlags);
		void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
		
		virtual void OnChar(UINT uChar,bool &bHandled);
		virtual void OnKeyDown(UINT uChar,bool &bHandled);
		virtual void OnKillFocus(bool &bHandled);

		void SetTextColor(COLORREF rgb);
		COLORREF GetTextColor() const; 
		 
		void SendMessage(UINT Msg,WPARAM wParam,LPARAM lParam=0);
		void PostMessage(UINT Msg,WPARAM wParam,LPARAM lParam=0);
	  
	protected:
		virtual void Redraw();
		virtual SStringT GetValidText(); 
		virtual bool ShouldEnter(TCHAR c) const; 

	public:
		// Class SelectionSaver is used to save an edit box's current
		// selection and then restore it on destruction.
		class  SelectionSaver
		{
		public:
			SelectionSaver(SDateRichEdit* pEdit);
			SelectionSaver(SDateRichEdit* pEdit, long nStart, long nEnd);
			~SelectionSaver();

			void MoveTo(int nStart, int nEnd);
			void MoveBy(int nStart, int nEnd);
			void MoveBy(int nPos);
			void operator+=(int nPos);

			int GetStart() const;
			int GetEnd() const;

			void Update();
			void Disable();

		protected:
			SDateRichEdit* m_pEdit;
			long m_nStart, m_nEnd;
		};


		// Class Behavior is an abstract base class used to define how an edit
		// box will behave when it is used.   Note that its virtual member functions start
		// with an underscore; this avoids naming conflicts when multiply inheriting.
		class  Behavior
		{
		protected:
			Behavior();
			virtual ~Behavior();
			void SetEdit(CAMSEdit* pEdit);
		public:
			bool ModifyFlags(UINT uAdd, UINT uRemove,bool bReDraw=true);
			UINT GetFlags() const;

		public:
			virtual SStringT _GetValidText()  = 0;

			virtual void _OnChar(UINT uChar,bool &bHandled) = 0;
			virtual void _OnKeyDown(UINT uChar,bool &bHandled);
			virtual void _OnKillFocus(bool &bHandled);
			virtual LONG _OnPaste();

		protected:
			// Wrappers to allow access to protected members of CAMSEdit
			virtual LRESULT _Default();		
			virtual void _Redraw();
			virtual bool _ShouldEnter(TCHAR c) const;

		protected:
			CAMSEdit* m_pEdit;
			UINT m_uFlags;
		};
		friend class Behavior;
 
		// The AlphanumericBehavior class is used to allow entry of alphanumeric
		// characters.  It can be restricted in terms of what characters cannot 
		// be inputed as well as how many are allowed altogether.
		class  AlphanumericBehavior : public Behavior
		{
		public:
			AlphanumericBehavior(int nMaxChars = 0, const SStringT& strInvalidChars = _T("%'*\"+?><:\\"));
			void SetEdit(CAMSEdit *pEdit);
			// Operations
			void SetInvalidCharacters(const SStringT& strInvalidChars);
			const SStringT& GetInvalidCharacters() const;

			void SetMaxCharacters(int nMaxChars);
			int GetMaxCharacters() const;

		protected:
			virtual SStringT _GetValidText();
			virtual void _OnChar(UINT uChar,bool &bHandled);

		protected:
			int m_nMaxChars;
			SStringT m_strInvalidChars;
		};
 
 
		// The MaskedBehavior class is used to allow entry of numeric characters
		// based on a given mask containing '#' characters to hold digits.
		class  MaskedBehavior : public Behavior
		{
		public:
			// Construction
			MaskedBehavior(const SStringT& strMask = _T(""));
			
			void SetEdit(CAMSEdit* pEdit);
		public:
			// Operations
			void SetMask(const SStringT& strMask);
			const SStringT& GetMask() const;

			SStringT GetNumericText() const;
		
			// The Symbol class represents a character which may be added to the mask and then interpreted by the 
			// MaskedBehavior class to validate the input from the user and possibly convert it to something else.
			class  Symbol
			{
			public: 
				#ifndef _UNICODE
					typedef int (*ValidationFunction)(UINT);	// designed for functions such as _istdigit, _istalpha
					typedef UINT (*ConversionFunction)(UINT);	// designed for functions such as _totupper, _totlower
				#else
					typedef int (*ValidationFunction)(WCHAR);		
					typedef WCHAR (*ConversionFunction)(WCHAR);		
				#endif
 
				Symbol();
				Symbol(TCHAR cSymbol, ValidationFunction fnValidation, ConversionFunction fnConversion = NULL);
				virtual ~Symbol();

				virtual bool Validate(TCHAR c) const;
				virtual TCHAR Convert(TCHAR c) const;

				void Set(TCHAR cSymbol);
				TCHAR Get() const;
				operator TCHAR() const;

			protected:
				TCHAR m_cSymbol;
				ValidationFunction m_fnValidation;
				ConversionFunction m_fnConversion;
			};

			typedef std::vector<Symbol> SymbolArray;

			SymbolArray& GetSymbolArray();

		protected:
			virtual SStringT _GetValidText() ;
			virtual void _OnChar(UINT uChar,bool &bHandled);
			virtual void _OnKeyDown(UINT uChar,bool &bHandled);

		protected:
			// Attributes
			SStringT m_strMask;
			SymbolArray m_arraySymbols;
		};
  

		// The NumericBehavior class is used to allow the entry of an actual numeric
	// value into the edit control.  It may be restricted by the number of digits
	// before or after the decimal point (if any).  If can also be set to use
	// commas to separate and group thousands.
	class NumericBehavior : public Behavior
	{
		public:
			// Construction
			NumericBehavior(int nMaxWholeDigits = 9, int nMaxDecimalPlaces = 4);
			void SetEdit(CAMSEdit *pEdit);
		public:
			// Operations
			void SetDouble(double dText, bool bTrimTrailingZeros = true);
			double GetDouble() const;

			void SetInt(int nText);
			int GetInt() const;
			
			void SetMaxWholeDigits(int nMaxWholeDigits);
			int GetMaxWholeDigits() const;
			
			void SetMaxDecimalPlaces(int nMaxDecimalPlaces);
			int GetMaxDecimalPlaces() const;
			
			void AllowNegative(bool bAllowNegative = true);
			bool IsNegativeAllowed() const;
			
			void SetDigitsInGroup(int nDigitsInGroup);
			int GetDigitsInGroup() const;
			
			void SetSeparators(TCHAR cDecimal, TCHAR cGroup);
			void GetSeparators(TCHAR* pcDecimal, TCHAR* pcGroup) const;

			void SetPrefix(const SStringT& strPrefix);
			const SStringT& GetPrefix() const;

			void SetMask(const SStringT& strMask);
			SStringT GetMask() const;

			void SetRange(double dMin, double dMax);
			void GetRange(double* pdMin, double* pdMax) const;

			virtual bool IsValid() const;
			bool CheckIfValid(bool bShowErrorIfNotValid = true);

			enum Flags
			{
				None										= 0x0000,
				CannotBeNegative							= 0x1000,
				AddDecimalAfterMaxWholeDigits				= 0x2000,
				PadWithZerosAfterDecimalWhenTextChanges		= 0x4000,
				PadWithZerosAfterDecimalWhenTextIsSet		= 0x8000,

				OnKillFocus_Beep_IfInvalid					= 0x0001,
				OnKillFocus_Beep_IfEmpty					= 0x0002,
				OnKillFocus_Beep							= 0x0003,
				OnKillFocus_SetValid_IfInvalid				= 0x0004,
				OnKillFocus_SetValid_IfEmpty				= 0x0008,
				OnKillFocus_SetValid						= 0x000C,
				OnKillFocus_SetFocus_IfInvalid				= 0x0010,
				OnKillFocus_SetFocus_IfEmpty				= 0x0020,
				OnKillFocus_SetFocus						= 0x0030,
				OnKillFocus_ShowMessage_IfInvalid			= 0x0050,
				OnKillFocus_ShowMessage_IfEmpty				= 0x00A0,
				OnKillFocus_ShowMessage						= 0x00F0,

				OnKillFocus_PadWithZerosBeforeDecimal		= 0x0100,
				OnKillFocus_PadWithZerosAfterDecimal		= 0x0200,
				OnKillFocus_DontPadWithZerosIfEmpty			= 0x0400,
				OnKillFocus_RemoveExtraLeadingZeros			= 0x0800,
				OnKillFocus_Max								= 0x0FFF
			};

		protected:
			virtual SStringT _GetValidText();
			virtual void _OnChar(UINT uChar,bool &bHandled);
			virtual void _OnKeyDown(UINT uChar,bool &bHandled);
			virtual void _OnKillFocus(bool &bHandled);

			int GetGroupSeparatorCount(const SStringT& strText) const;
			
			SStringT GetNumericText(const SStringT& strText, bool bUseMathSymbols = false) const;
			SStringT GetDoubleText(double dText, bool bTrimTrailingZeros = true) const;
			SStringT GetSeparatedText(const SStringT& strText) const;
			void AdjustSeparators(int nCurrentSeparatorCount);
			static void InsertZeros(SStringT* pStrText, int nPos, int nCount);

			virtual void ShowErrorMessage() const;
			void AdjustWithinRange();

		protected:
			// Attributes
			int m_nMaxWholeDigits;
			int m_nMaxDecimalPlaces;
			TCHAR m_cNegativeSign;
			TCHAR m_cDecimalPoint;
			TCHAR m_cGroupSeparator;
			int m_nDigitsInGroup;
			SStringT m_strPrefix;
			double m_dMin;
			double m_dMax;

		private:
			bool m_bAdjustingSeparators;
		};


		// The DateBehavior class is used to allow the entry of date values.
		class  DateBehavior : virtual public Behavior
		{
		public:
			// Construction
			DateBehavior();

			void SetEdit(CAMSEdit* pEdit);

		public:
			// Operations
			void SetDate(int nYear, int nMonth, int nDay);
			void SetDate(CDuiDateTime &dattime);
			void SetDateToToday();

			CDuiDateTime  GetDate() const; 

			int GetYear() const;
			int GetMonth() const;
			int GetDay() const;
			void SetYear(int nYear);
			void SetMonth(int nMonth);
			void SetDay(int nDay);
			virtual bool IsValid() const;
			bool CheckIfValid(bool bShowErrorIfNotValid = true);

			void SetRange(const CDuiDateTime& dateMin, const CDuiDateTime& dateMax); 
			void GetRange(CDuiDateTime* pDateMin, CDuiDateTime* pDateMax) const; 
			void SetSeparator(TCHAR cSep);
			TCHAR GetSeparator() const; 
		protected:
			virtual SStringT _GetValidText();
			virtual void _OnChar(UINT uChar,bool &bHandled);
			virtual void _OnKeyDown(UINT uChar,bool &bHandled);
			virtual void _OnKillFocus(bool &bHandled);

		protected:
			// Helpers
			bool AdjustMaxMonthAndDay();
			bool AdjustMaxDay();

			int GetValidMonth() const;
			int GetMaxMonth() const;
			int GetMinMonth() const;
			int GetMonthStartPosition() const;
			TCHAR GetMaxMonthDigit(int nPos) const;
			TCHAR GetMinMonthDigit(int nPos) const;
			bool IsValidMonthDigit(TCHAR c, int nPos) const;
			bool IsValidMonth(int nMonth) const;

			int GetValidDay() const;
			int GetMaxDay() const;
			int GetMinDay() const;
			int GetDayStartPosition() const;
			TCHAR GetMaxDayDigit(int nPos) const;
			TCHAR GetMinDayDigit(int nPos) const;
			bool IsValidDayDigit(TCHAR c, int nPos) const;
			bool IsValidDay(int nDay) const;
			
			int GetValidYear() const;
			int GetYearStartPosition() const;
			TCHAR GetMaxYearDigit(int nPos) const;
			TCHAR GetMinYearDigit(int nPos, bool bValidYear = false) const;
			bool IsValidYearDigit(TCHAR c, int nPos) const;
			bool IsValidYear(int nYear) const;

			virtual bool IsWithinRange(const CDuiDateTime& date, bool bDateOnly = true) const;
			SStringT GetFormattedDate(int nYear, int nMonth, int nDay) const;

		public:
			static bool IsLeapYear(int nYear);
			static SStringT GetString(int nValue, bool bTwoDigitWithLeadingZero = true);
			static int GetMaxDayOfMonth(int nMonth, int nYear);

		protected:
			// Attributes
			CDuiDateTime m_dateMin;
			CDuiDateTime m_dateMax;
			TCHAR m_cSep;
		}; 
 

		// The TimeBehavior class is used to allow the entry of time values.
		class  TimeBehavior : virtual public Behavior
		{
		public:
			// Construction
			TimeBehavior();
			
			void SetEdit(CAMSEdit* pEdit);

		public:
			// Operations
			void SetTime(int nHour, int nMinute, int nSecond = 0);
			void SetTime(const CDuiDateTime& time); 
			void SetTimeToNow();

			CDuiDateTime GetTime() const; 

			int GetHour() const;
			int GetMinute() const;
			int GetSecond() const;
			SStringT GetAMPM() const;
			void SetHour(int nYear);
			void SetMinute(int nMonth);
			void SetSecond(int nDay);
			void SetAMPM(bool bAM);
			virtual bool IsValid() const;
			bool IsValid(bool bCheckRangeAlso) const;
			bool CheckIfValid(bool bShowErrorIfNotValid = true);

			void SetRange(const CDuiDateTime& dateMin, const CDuiDateTime& dateMax); 
			void GetRange(CDuiDateTime* pDateMin, CDuiDateTime* pDateMax) const;
		
			void SetSeparator(TCHAR cSep);
			TCHAR GetSeparator() const;

			void Show24HourFormat(bool bShow24HourFormat = true,bool bReDraw=true);
			bool IsShowing24HourFormat() const;
			void ShowSeconds(bool bShowSeconds = true,bool bReDraw=true);
			bool IsShowingSeconds() const;
			void SetAMPMSymbols(const SStringT& strAM, const SStringT& strPM);
			void GetAMPMSymbols(SStringT* pStrAM, SStringT* pStrPM) const;
			
			enum Flags
			{
				None								= 0x0000,
				TwentyFourHourFormat				= 0x2000,
				WithSeconds							= 0x4000, 
			};

		protected:
			virtual SStringT _GetValidText();
			virtual void _OnChar(UINT uChar,bool &bHandled);
			virtual void _OnKeyDown(UINT uChar,bool &bHandled);
			virtual void _OnKillFocus(bool &bHandled);

		protected:
			// Helpers
			int GetValidHour(bool b24HourFormat = false) const;
			int GetMaxHour(bool b24HourFormat = false) const;
			int GetMinHour(bool b24HourFormat = false) const;
			int GetHourStartPosition() const;
			TCHAR GetMaxHourDigit(int nPos) const;
			TCHAR GetMinHourDigit(int nPos) const;
			bool IsValidHourDigit(TCHAR c, int nPos) const;
			bool IsValidHour(int nHour, bool b24HourFormat = false) const;
			int ConvertTo24Hour(int nHour, const SStringT& strAMPM) const;
			int ConvertToAMPMHour(int nHour, SStringT* pStrAMPM = NULL) const;

			int GetValidMinute() const;
			int GetMaxMinute() const;
			int GetMinMinute() const;
			int GetMaxSecond() const;
			int GetMinSecond() const;
			int GetMinuteStartPosition() const;
			TCHAR GetMaxMinuteDigit(int nPos) const;
			TCHAR GetMinMinuteDigit(int nPos) const;
			bool IsValidMinuteDigit(TCHAR c, int nPos) const;
			bool IsValidMinute(int nMinute) const;
			
			int GetValidSecond() const;
			int GetSecondStartPosition() const;
			TCHAR GetMaxSecondDigit(int nPos) const;
			TCHAR GetMinSecondDigit(int nPos) const;
			bool IsValidSecondDigit(TCHAR c, int nPos) const;
			bool IsValidSecond(int nSecond) const;

			void ShowAMPM();
			bool ChangeAMPM(TCHAR c);
			SStringT GetValidAMPM() const;
			int GetAMPMStartPosition() const;
			bool IsValidAMPM(const SStringT& strAMPM) const;
			int GetAMPMPosition(const SStringT& strText) const;

			virtual bool IsWithinRange(const CDuiDateTime& date, bool bDateOnly = true) const;
			SStringT GetFormattedTime(int nHour, int nMinute, int nSecond, const SStringT& strAMPM = _T("")) const;
			void AdjustWithinRange();
			
		protected:
			// Attributes
			CDuiDateTime m_timeMin;
			CDuiDateTime m_timeMax;
			TCHAR m_cSep;
			SStringT m_strAM;
			SStringT m_strPM;
			int m_nAMPMLength;
			int m_nHourStart;
		};

		// The DateTimeBehavior class is used to allow the entry of date and time values.
		class  DateTimeBehavior : public DateBehavior, public TimeBehavior
		{
		public:
			// Construction
			DateTimeBehavior();
			
			void SetEdit(CAMSEdit* pEdit);

			void SetDateTime(int nYear, int nMonth, int nDay, int nHour, int nMinute, int nSecond = 0);
			void SetDateTime(const CDuiDateTime& dt); 
			void SetToNow();

			CDuiDateTime GetDateTime() const; 
			virtual bool IsValid() const;

			void SetRange(const CDuiDateTime& dateMin, const CDuiDateTime& dateMax); 
			void GetRange(CDuiDateTime* pDateMin, CDuiDateTime* pDateMax) const; 
		
			void SetSeparator(TCHAR cSep, bool bDate);
			TCHAR GetSeparator(bool bDate) const;

			bool ModifyFlags(UINT uAdd, UINT uRemove,bool bReDraw=true);

			void ShowTime(bool bShowTime /*= true*/,bool bReDraw/*=true*/);
			bool IsShowingTime() const;

			enum Flags
			{
				DateOnly							= 0x0100,
				TimeOnly							= 0x0200,
			};

		protected:
			virtual SStringT _GetValidText();
			virtual void _OnChar(UINT uChar,bool &bHandled);
			virtual void _OnKeyDown(UINT uChar,bool &bHandled);
			virtual void _OnKillFocus(bool &bHandled);

		protected:
			virtual bool IsWithinRange(const CDuiDateTime& date, bool bDateOnly = true) const;
		};
	protected: 
		 LONG OnCut();
		 LONG OnPaste();
		 LONG OnClear(UINT wParam, LONG lParam);
		 LONG OnSetText(UINT wParam, LONG lParam);
	 
	};
 

	/////////////////////////////////////////////////////////////////////////////
	// CAMSAlphanumericEdit window

	// The CAMSAlphanumericEdit is a CAMSEdit control which supports the AlphanumericBehavior class.
	//
	class  CAMSAlphanumericEdit : public CAMSEdit,public CAMSEdit::AlphanumericBehavior
	{
	public:
		// Construction
		CAMSAlphanumericEdit(int nMaxChars = 0, const SStringT& strInvalidChars = _T("%'*\"+?><:\\"));

	protected:
		virtual SStringT GetValidText();
	protected: 
		 void OnChar(UINT uChar,bool &bHandled);  	
	};
  

	/////////////////////////////////////////////////////////////////////////////
	// CAMSMaskedEdit window

	// The CAMSMaskedEdit is a CAMSEdit control which supports the MaskedBehavior class.
	//
	class  CAMSMaskedEdit : public CAMSEdit,public CAMSEdit::MaskedBehavior
	{
	public:
		// Construction
		CAMSMaskedEdit(const SStringT& strMask = _T(""));

		void SetEdit(CAMSEdit* pEdit);
	protected:
		virtual SStringT GetValidText();
	protected: 
		 void OnChar(UINT uChar,bool &bHandled);
		 void OnKeyDown(UINT uChar,bool &bHandled);	
	};
 
 
	/////////////////////////////////////////////////////////////////////////////
	// CAMSDateEdit window

	// The CAMSDateEdit is a CAMSEdit control which supports the DateBehavior class.
	//
	class  CAMSDateEdit : public CAMSEdit, public CAMSEdit::DateBehavior
	{
		SOUI_CLASS_NAME_DECL(CAMSDateEdit, L"date_edit")
	public:
		// Construction
		CAMSDateEdit();

		void SetEdit(CAMSEdit* pEdit);

	protected:
		virtual SStringT GetValidText();
	protected: 
		 void OnChar(UINT uChar,bool &bHandled);
		 void OnKeyDown(UINT uChar,bool &bHandled);
		 void OnKillFocus(bool &bHandled); 

		 LONG OnPaste();

		
	}; 

	/////////////////////////////////////////////////////////////////////////////
	// CAMSTimeEdit window

	// The CAMSTimeEdit is a CAMSEdit control which supports the TimeBehavior class.
	//
	class  CAMSTimeEdit : public CAMSEdit, public CAMSEdit::TimeBehavior
	{
		SOUI_CLASS_NAME_DECL(CAMSTimeEdit, L"time_edit")
	public:
		// Construction
		CAMSTimeEdit();

		void SetEdit(CAMSEdit* pEdit);

	protected:
		virtual SStringT GetValidText();
	protected: 
		 void OnChar(UINT uChar,bool &bHandled);
		 void OnKeyDown(UINT uChar,bool &bHandled);
		 void OnKillFocus(bool &bHandled); 

		 LONG OnPaste();

		
	};  

	/////////////////////////////////////////////////////////////////////////////
	// CAMSNumericEdit window

	// The CNumericEditUI is a CAMSEdit control which supports the NumericBehavior class.
	//
	class CNumericEditUI : public CAMSEdit,public CAMSEdit::NumericBehavior
	{
	public:
		CNumericEditUI(int nMaxWholeDigits = 9, int nMaxDecimalPlaces = 4);
		void SetEdit(CAMSEdit* pEdit);
		LPCTSTR GetClass() const;
	protected:
		virtual SStringT GetValidText();
 
	protected: 
		 void OnChar(UINT uChar,bool &bHandled);
		 void OnKeyDown(UINT uChar,bool &bHandled);
		 void OnKillFocus(bool &bHandled);  
		 LONG OnPaste();
	};

	class CIntegerEditUI : public CNumericEditUI
	{
	public:
		// Construction
		CIntegerEditUI(int nMaxWholeDigits = 9);
		void SetEdit(CAMSEdit* pEdit);
		LPCTSTR GetClass() const;

	private:
		// Hidden members -- they don't make sense here
		void SetDouble(double dText, bool bTrimTrailingZeros = true);
		double GetDouble() const;
		void SetMaxDecimalPlaces(int nMaxDecimalPlaces);	// always 0 
	protected: 
		 void OnChar(UINT uChar,bool &bHandled);
		 void OnKeyDown(UINT uChar,bool &bHandled);
		 void OnKillFocus(bool &bHandled);  
	};


	#define AMS_MIN_NUMBER			-1.7976931348623158e+308
	#define AMS_MAX_NUMBER			 1.7976931348623158e+308
	#define AMS_MIN_CTIME			CDuiDateTime(1970, 1, 1, 0, 0, 0)
	#define AMS_MAX_CTIME			CDuiDateTime(2037, 12, 31, 23, 59, 59)
	#define AMS_MIN_OLEDATETIME		CDuiDateTime(1900, 1, 1, 0, 0, 0)
	#define AMS_MAX_OLEDATETIME		CDuiDateTime(9998, 12, 31, 23, 59, 59)
	#define AMS_AM_SYMBOL			_T("AM")
	#define AMS_PM_SYMBOL			_T("PM")
 

		

	class  CDateTimeUI :  public CAMSEdit, 
								   public CAMSEdit::AlphanumericBehavior, 
								   public CAMSEdit::MaskedBehavior,
								   public CAMSEdit::DateTimeBehavior
	{
		SOUI_CLASS_NAME_DECL(CDateTimeUI, L"datetime")
	public:
		const SStringT& GetMask() const;
		void SetMask(const SStringT& strMask); 
		void SetEdit(CAMSEdit* pEdit);
		bool IsValid() const;
	protected:
		virtual SStringT GetValidText();

		// Attributes
		Behavior* m_pCurrentBehavior;
 
	protected: 
		 void OnChar(UINT uChar,bool &bHandled);
		 void OnKeyDown(UINT uChar,bool &bHandled);
		 void OnKillFocus(bool &bHandled); 

		 LONG OnPaste(); 
	public:
		CDateTimeUI(); 

 
		bool Activate();
		void SetEnabled(bool bEnable = true);
		//void DoEvent(TEventUI& event); 
 
		void SetNowDate();
		void SetCalendarName(LPCTSTR pStrCalendarName);
		LPCTSTR GetCalendarName();
		void SetCalendarStyle(LPCTSTR pStrCalendarStyle);
		LPCTSTR GetCalendarStyle();
		void SetCalendarProfile(LPCTSTR pStrCalendarProfile);
		LPCTSTR GetCalendarProfile();
 
		void SetAttribute(LPCTSTR pstrName, LPCTSTR pstrValue);
 

		void BindTabIndex(int _BindTabIndex);
		void BindTabLayoutName(LPCTSTR _TabLayoutName);
		void BindTriggerTabSel(int _SetSelectIndex = -1);
		void RemoveBindTabIndex();
		int	 GetBindTabLayoutIndex();
		SStringT GetBindTabLayoutName();
	public:
		LPCTSTR GetNormalImage() const;
		void SetNormalImage(LPCTSTR pStrImage);
		LPCTSTR GetHotImage() const;
		void SetHotImage(LPCTSTR pStrImage);
		LPCTSTR GetPushedImage() const;
		void SetPushedImage(LPCTSTR pStrImage);
		LPCTSTR GetFocusedImage() const;
		void SetFocusedImage(LPCTSTR pStrImage);
		LPCTSTR GetDisabledImage() const;
		void SetDisabledImage(LPCTSTR pStrImage);

		//void PaintStatusImage(HDC hDC);
		BOOL PtInDropButtonRect(POINT pt);
		//drop button 
		int GetImageSplit();
		void SetImageSplit(int split_w);
		void SetShowTime(bool bShow,bool bReDraw=true);
		void SetShowSeconds(bool bShow,bool bReDraw=true);
		bool IsShowTime() const;
		bool IsShowSeconds() const;
	protected: 
		bool bShowTime;
		bool bShowSeconds;
		UINT m_uButtonState;
		int m_SplitWidth;

		SStringT m_sNormalImage;
		SStringT m_sHotImage;
		SStringT m_sPushedImage;
		SStringT m_sFocusedImage;
		SStringT m_sDisabledImage;

		SStringT	m_sCalendarName;
		SStringT	m_sCalendarStyle;
		SStringT	m_sCalendarProfile;


		int			m_iBindTabIndex;
		SStringT	m_sBindTabLayoutName;
	};

}	// namespace SOUI

#endif // __S_DATETIME_EDIT_H__