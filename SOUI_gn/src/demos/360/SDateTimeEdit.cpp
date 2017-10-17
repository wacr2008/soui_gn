#include "SDateTimeEdit.h" 
#include "SCalendar.h"
#include <assert.h>

namespace SOUI
{
	static const short _monthDays[2][13] = {
                                                   {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31},
                                                   {31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31}
                                               };

    static const short _monthDaySums[2][13] = {
                {0, 31, 59, 90, 120, 151, 181, 212, 243, 273, 304, 334, 365},
                {0, 31, 60, 91, 121, 152, 182, 213, 244, 274, 305, 335, 366}
            };


    CDuiDateTime::CDuiDateTime()
    { 
        GetCurrentTime();
    }

    CDuiDateTime::CDuiDateTime(const CDuiDateTime &dTime)
    {
        this->nYear  = dTime.nYear;
        this->nMonth = dTime.nMonth;
        this->nDay   = dTime.nDay;
        this->nHour  = dTime.nHour;
        this->nMinute= dTime.nMinute;
        this->nSecond= dTime.nSecond; 
        this->nMilliseconds= dTime.nMilliseconds; 
         
        m_dateTime = dTime.m_dateTime;
    } 

    CDuiDateTime::CDuiDateTime(const double dt) 
    {
        m_dateTime = dt;
 
        decodeDate(m_dateTime,nYear,nMonth,nDay) ; 
        decodeTime(m_dateTime,nHour,nMinute,nMinute,nMilliseconds) ;
    }

    CDuiDateTime::CDuiDateTime(short year,short month,short day,short hour,short minute,short second,short minsecond)
    { 
        this->nYear  = year;
        this->nMonth = month;
        this->nDay   = day;
        this->nHour  = hour;
        this->nMinute= minute;
        this->nSecond= minute; 
        this->nMilliseconds= minsecond;

        double t;
        encodeDate(m_dateTime,nYear,nMonth,nDay);
        encodeTime(t,nHour,nMinute,nSecond,nMilliseconds);
        m_dateTime += t;
    } 

    CDuiDateTime::~CDuiDateTime()
    {

    }
    
    SStringT CDuiDateTime::FormatDateString(const TCHAR date_sep) const
    {
        SStringT dateString;
        dateString.Format(_T("%d%c%d%c%d"),
            this->GetYear(),date_sep,this->GetMonth(),date_sep,this->GetDay()
            );
        return dateString;      
    }

    SStringT CDuiDateTime::FormatDateTimeString(const TCHAR date_sep,const TCHAR time_sep) const 
    { 
        SStringT dateString;
        dateString.Format(_T("%d%c%d%c%d%c %d%c%d%c%d%c"),
            this->GetYear(),date_sep,this->GetMonth(),date_sep,this->GetDay(),
            this->GetHour(),time_sep,this->GetSecond(),time_sep,this->GetSecond()
            );
        return dateString;
    }

    void CDuiDateTime::GetCurrentTime()
    {
        //char *wday[]={隆掳Sun隆卤,隆卤Mon隆卤,隆卤Tue隆卤,隆卤Wed隆卤,隆卤Thu隆卤,隆卤Fri隆卤,隆卤Sat隆卤};
        time_t timep;
        struct tm *p;
        time(&timep);
        p=localtime(&timep); /*脠隆碌脙碌卤碌脴脢卤录盲*/
        //printf (隆掳%d%d%d 隆卤, (1900+p->tm_year),( l+p->tm_mon), p->tm_mday);
        //printf(隆掳%s%d:%d:%d\n隆卤, wday[p->tm_wday],p->tm_hour, p->tm_min, p->tm_sec);

        SetTime(p);
    }

    void CDuiDateTime::GetAsSystemTime(SYSTEMTIME &sysTime)
    { 
        sysTime.wYear = (WORD) nYear;
        sysTime.wMonth = (WORD) nMonth;
        sysTime.wDayOfWeek = (WORD)GetDayOfWeek();
        sysTime.wDay = (WORD) nDay;
        sysTime.wHour = (WORD) nHour;
        sysTime.wMinute = (WORD) nMinute;
        sysTime.wSecond = (WORD) nSecond;
        sysTime.wMilliseconds = (WORD) nMilliseconds;  
    }

    CDuiDateTime::CDuiDateTime(tm *time)
    { 
        SetTime(time);
    }

    void CDuiDateTime::SetDate(int year,int month,int day)
    {
        this->nYear  = year;
        this->nMonth = month;
        this->nDay   = day; 
    }

    void CDuiDateTime::SetTime(int hour,int minute,int second,int minsecond)
    {
        this->nHour     = hour;
        this->nMinute   = minute;
        this->nSecond   = second; 
        this->nMilliseconds   = minsecond; 
    }
    
    bool CDuiDateTime::operator>(const CDuiDateTime &dt) const
    {
        if(this->nYear<= dt.nYear)
            return false;
        if(this->nMonth<= dt.nMonth)
            return false;
        if(this->nDay<= dt.nDay)
            return false;
        if(this->nHour<= dt.nHour)
            return false;
        if(this->nMinute<= dt.nMinute)
            return false;
        if(this->nSecond<= dt.nSecond)
            return false;
        if(this->nMilliseconds<= dt.nMilliseconds)
            return false;
        return true;
    }

    bool CDuiDateTime::operator<(const CDuiDateTime &dt) const
    {
        if(this->nYear>= dt.nYear)
            return false;
        if(this->nMonth>= dt.nMonth)
            return false;
        if(this->nDay>= dt.nDay)
            return false;
        if(this->nHour>= dt.nHour)
            return false;
        if(this->nMinute>= dt.nMinute)
            return false;
        if(this->nSecond>= dt.nSecond)
            return false;
        if(this->nMilliseconds>= dt.nMilliseconds)
            return false; 
        return true;
    }

    bool CDuiDateTime::operator<=(const CDuiDateTime &dt) const
    {
        if(this->nYear> dt.nYear)
            return false;
        if(this->nMonth> dt.nMonth)
            return false;
        if(this->nDay> dt.nDay)
            return false;
        if(this->nHour> dt.nHour)
            return false;
        if(this->nMinute> dt.nMinute)
            return false;
        if(this->nSecond> dt.nSecond)
            return false;
        if(this->nMilliseconds> dt.nMilliseconds)
            return false;
        return true;
    }

    bool CDuiDateTime::operator>=(const CDuiDateTime &dt) const
    {
        if(this->nYear< dt.nYear)
            return false;
        if(this->nMonth< dt.nMonth)
            return false;
        if(this->nDay< dt.nDay)
            return false;
        if(this->nHour< dt.nHour)
            return false;
        if(this->nMinute< dt.nMinute)
            return false;
        if(this->nSecond< dt.nSecond)
            return false;
        if(this->nMilliseconds< dt.nMilliseconds)
            return false;
        return true;
    }

    void CDuiDateTime::SetTime(tm *time)
    {  
        nYear = 1900+time->tm_year;     /* years since 1900 */
        nMonth = 1+time->tm_mon;        /* months since January - [0,11] */
        nDay = time->tm_mday;           /* day of the month - [1,31] */
        nHour = time->tm_hour;          /* hours since midnight - [0,23] */
        nMinute = time->tm_min;         /* minutes after the hour - [0,59] */
        nSecond = time->tm_sec;         /* seconds after the minute - [0,59] */
        //nDay = time->tm_wday;         /* days since Sunday - [0,6] */
        //nDay = time->tm_yday;         /* days since January 1 - [0,365] */ 
        nMilliseconds =0;

        double t;
        encodeDate(m_dateTime,nYear,nMonth,nDay);
        encodeTime(t,nHour,nMinute,nSecond,nMilliseconds);
        m_dateTime += t;
    } 
    
    bool CDuiDateTime::IsValid()  const
    {
        if(nYear <1899||nYear>9999)
            return false;
        
        if(nMonth <1 || nMonth>12)
            return false;
        
        int nMonthDays =GetMaxDayOfMonth(nMonth,nYear);

        if(nDay <1 || nDay>nMonthDays)
            return false;
 
        if(nHour>24)
            return false;
        
        if(nMinute>59)
            return false;
        
        if(nSecond>59)
            return false;   
        
        return true;
    }

         
    bool CDuiDateTime::IsLeapYear(int year)  const
    {
        return (year & 3) == 0 && (year % 100 != 0 || year % 400 == 0); 
    }
        
    // Returns the maximum value for the day based on the given month and year.
    int CDuiDateTime::GetMaxDayOfMonth(int month, int year)  const
    {
        assert(month >= 1 && month <= 12);

        switch (month)
        {
            case 4:
            case 6:
            case 9:
            case 11:
                return 30;

            case 2:
                return IsLeapYear(year) ? 29 : 28;
        }
        return 31;
    }

    short CDuiDateTime::GetYear() const
    {
        return nYear;
    }

    short CDuiDateTime::GetMonth() const
    {
        return nMonth;
    }
    
    short CDuiDateTime::GetDay() const
    {
        return nDay;
    }
        
    short CDuiDateTime::GetHour()  const
    {
        return nHour;
    }

    short CDuiDateTime::GetMinute() const
    {
        return nMinute;
    }
        
    short CDuiDateTime::GetSecond() const
    {
        return nSecond;
    }
        
    short CDuiDateTime::GetMilliseconds() const
    {
        return nMilliseconds;
    }
        
    int CDuiDateTime::GetDayOfWeek()
    {
        short Month;
        short Year;

        Month = nMonth;
        Year  = nYear;

        if(Month==1||Month==2)
        {
            Month+=12;
            Year--;
        }

        int weekNum = (nDay+1+2*Month+3*(Month+1)/5+Year+Year/4-Year/100+Year/400)%7;
        return weekNum+1; 
    }

    int  CDuiDateTime::IsLeapYear(const __int16 year) 
    {
        return ((year&3) == 0 && year%100) || ((year%400) == 0);
    }

    void CDuiDateTime::encodeTime(double& dt,short h,short m,short s,short ms) 
    {
        dt = (h + ((m + (s + ms / 1000.0) / 60.0) / 60.0)) / 24.0;
    }

    void CDuiDateTime::decodeTime(const double dt,short& h,short& m,short& s,short& ms) 
    {
        const int S1 = 24 * 3600; // seconds in 1 day

        double t = dt - (int) dt;

        if (t < 0)
            t++;

        double floatSecs = t * S1;
        int secs = (int)floatSecs;
        h = short(secs / 3600);
        secs = secs % 3600;
        m = short(secs / 60);
        secs = secs % 60;
        s = short(secs);
        ms = int((floatSecs - secs) * 1000);
    }

    void CDuiDateTime::encodeDate(double &dt,short year,short month,short day) 
    { 
        if (year == 0 && month == 0 && day == 0) {
            dt = 0;
            return;
        }
        if (month < 1 || month > 12)
        {
            dt = 0;
            return;
        }

        int yearKind = IsLeapYear(year);
        month--;
        if (day < 1 || day > _monthDays[yearKind][month])
        {
            dt = 0;
            return;
        }

        if (year <= 0 || year > 9999)
        {
            dt = 0;
            return;
        }

        day += _monthDaySums[yearKind][month];
        int i = year - 1;
        dt = i * 365 + i / 4 - i / 100 + i / 400 + day - DateDelta;
    }
        
    void CDuiDateTime::DivMod(int op1, int op2, int& div, int& mod) 
    {
        div = op1 / op2;
        mod = op1 % op2;
    }

    void CDuiDateTime::decodeDate(const double dat,short& year,short& month,short& day) 
    { 
        const int D1 = 365;              // Days in 1 year
        const int D4 = D1 * 4 + 1;       // Days in 4 years
        const int D100 = D4 * 25 - 1;    // Days in 100 years
        const int D400 = D100 * 4 + 1;   // Days in 400 years

        int M, D, I;
        int T = (int) dat + DateDelta - 1;

        int fourCenturiesCount = T / D400;
        T %= D400;
        int Y = fourCenturiesCount * 400 + 1;

        DivMod(T, D100, I, D);
        if (I == 4) {
            I--;
            D += D100;
        }

        Y += I * 100;
        DivMod(D, D4, I, D);
        Y += I * 4;
        DivMod(D, D1, I, D);
        if (I == 4) {
            I--;
            D += D1;
        }
        Y += I;
        year = Y;
        //year  = short (Y + 1900);

        int leapYear = IsLeapYear(short(year));
        M = D / 31;
        int mds = _monthDaySums[leapYear][M+1];
        if (mds <= D)
            M++;
        else
            mds = _monthDaySums[leapYear][M];

        D -= mds;

        month = short(M + 1);
        day   = short(D + 1);
    }
    	
	SOUI_MSG_MAP_BEGIN(CAMSEdit)
		MSG_WM_KEYDOWN(OnKeyDown)
		MSG_WM_CHAR(OnChar)
		MSG_WM_PASTE(OnPaste)
		MSG_WM_CUT(OnCut)
	SOUI_MSG_MAP_END()

	SOUI_CLASS_NAME(CAMSEdit, L"amsedit")
	// Constructs the object with the default attributes
	CAMSEdit::CAMSEdit()
	{
	}

	// Destroys the object (virtual).
	CAMSEdit::~CAMSEdit()
	{
	}
 
	void CAMSEdit::SendMessage(UINT Msg,WPARAM wParam,LPARAM lParam)
	{
		LRESULT result;
		m_pTxtHost->GetTextService()->TxSendMessage(Msg,wParam,lParam,&result);
	}

	void CAMSEdit::PostMessage(UINT Msg,WPARAM wParam,LPARAM lParam)
	{
		LRESULT result;
		m_pTxtHost->GetTextService()->TxSendMessage(Msg,wParam,lParam,&result);
	} 

	void CAMSEdit::OnChar(UINT nChar, UINT nRepCnt, UINT nFlags)
	{
		bool bHandled = true;
		OnChar(nChar, bHandled);
		if(!bHandled)		
			m_pTxtHost->GetTextService()->TxSendMessage(GetCurMsg()->uMsg, GetCurMsg()->wParam, GetCurMsg()->lParam, NULL);
	}

	void CAMSEdit::OnChar(UINT uChar,bool &bHandled)
	{
		 
	}

	void CAMSEdit::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
	{
		bool bHandled = true;
		OnKeyDown(nChar,bHandled);
		if(!bHandled)
		{
           if(!bHandled)		m_pTxtHost->GetTextService()->TxSendMessage(GetCurMsg()->uMsg, GetCurMsg()->wParam, GetCurMsg()->lParam, NULL);
		}
	}

	void CAMSEdit::OnKeyDown(UINT uChar,bool &bHandled)
	{
	 
	}

	void CAMSEdit::OnKillFocus(bool &bHandled)
	{
		 
	} 

	// Returns the control's text without leading or trailing blanks.
	SStringT CAMSEdit::GetTrimmedText() 
	{
		SStringT strText = GetWindowText();
		return strText;
	} 

	// Returns the control's value in a valid format.
	SStringT CAMSEdit::GetValidText() 
	{
		return GetWindowText();
	}
 
	void CAMSEdit::Redraw()
	{ 
		SStringT strText = GetValidText();
		if (strText != GetWindowText())
			SetWindowText(strText);
	}

	// Returns true if the given character should be entered into the control.
	bool CAMSEdit::ShouldEnter(TCHAR) const
	{
		return true;
	}

	void CAMSEdit::GetSel(long &start, long &end)
	{
		LRESULT lResult;
		m_pTxtHost->GetTextService()->TxSendMessage(EM_GETSEL, (WPARAM)&start, (LPARAM)&end, &lResult);

		//SSendMessage(EM_GETSEL, (WPARAM)&start, (LPARAM)&end);
	}
	// Cuts the current selection into the clipboard.
	LONG CAMSEdit::OnCut()
	{
		long nStart = 0, nEnd = 0;

		GetSel(nStart,nEnd );

		if (nStart < nEnd)
		{
			//SendMessage(WM_COPY);				// copy the selection and...
			ReplaceSel(_T(""),true);					// delete it
		}
		
		return 0;
	}
		
	// Clears the current selection.
	LONG CAMSEdit::OnClear(UINT, LONG)
	{
		long nStart = 0, nEnd = 0;
		GetSel(nStart, nEnd);

		if (nStart < nEnd)
		{
			m_pTxtHost->GetTextService()->TxSendMessage(WM_KEYDOWN, VK_DELETE, 0, NULL);
			//SSendMessage(WM_KEYDOWN, VK_DELETE,0); // delete the selection
		}
		return 0;
	}

	// Pastes the text from the clipboard onto the current selection.
	LONG CAMSEdit::OnPaste()
	{
		long nStart = 0, nEnd = 0;
		GetSel(nStart, nEnd);
	 
		SStringT strText = GetValidText();

		if (strText != GetWindowText())
		{
			SetWindowText(strText);
			SetSel(nStart, nEnd);
		}

		return 0;
	} 

	// Handles the WM_SETTEXT message to ensure that text (set via SetWindowText) is valid.
	LONG CAMSEdit::OnSetText(UINT, LONG lParam)
	{
		LONG nResult =0;

		SStringT strText = GetValidText();
		if (strText != (LPCTSTR)lParam)
			SetWindowText(strText);

		return nResult;
	}


	/////////////////////////////////////////////////////////////////////////////
	// CAMSEdit::SelectionSaver

	// Constructs the selection saver object for the given edit control.
	// It then saves the edit control's current selection.
	CAMSEdit::SelectionSaver::SelectionSaver(SDateRichEdit* pEdit) :
		m_pEdit(pEdit)
	{
		assert(pEdit);


		LRESULT result;
		pEdit->GetTextHost()->GetTextService()->TxSendMessage(EM_GETSEL, (WPARAM)&m_nStart, (LPARAM)&m_nEnd,&result);
	}

	// Constructs the selection saver object for the given edit control.
	// It then saves the given nStart and nEnd values.
	CAMSEdit::SelectionSaver::SelectionSaver(SDateRichEdit* pEdit, long nStart, long nEnd) :
		m_pEdit(pEdit),
		m_nStart(nStart),
		m_nEnd(nEnd)
	{
		assert(pEdit);
		assert(nStart <= nEnd);
	}

	// Destroys the object and restores the selection to the saved start and end values.
	CAMSEdit::SelectionSaver::~SelectionSaver()
	{
		if (m_pEdit)
			m_pEdit->SetSel(m_nStart, m_nEnd);
	}

	// Changes the start and end values to nStart and nEnd respectively.
	void CAMSEdit::SelectionSaver::MoveTo(int nStart, int nEnd)
	{
		assert(nStart <= nEnd);

		m_nStart = nStart;
		m_nEnd = nEnd;
	}

	// Changes the start and end values by nStart and nEnd respectively.
	void CAMSEdit::SelectionSaver::MoveBy(int nStart, int nEnd)
	{
		m_nStart += nStart;
		m_nEnd += nEnd;

		assert(m_nStart <= m_nEnd);
	}

	// Changes both the start and end values by nPos.
	void CAMSEdit::SelectionSaver::MoveBy(int nPos)
	{
		m_nStart += nPos;
		m_nEnd += nPos;
	}

	// Changes both the start and end values by nPos.
	void CAMSEdit::SelectionSaver::operator+=(int nPos)
	{
		MoveBy(nPos);
	}

	// Returns the value for the selection's start.
	int CAMSEdit::SelectionSaver::GetStart() const
	{
		return m_nStart;
	}

	// Returns the value for the selection's end.
	int CAMSEdit::SelectionSaver::GetEnd() const
	{
		return m_nEnd;
	}

	// Updates the selection's start and end with the current selection.
	void CAMSEdit::SelectionSaver::Update()
	{
		m_pEdit->SSendMessage(EM_GETSEL, (WPARAM)&m_nStart, (LPARAM)&m_nEnd);
	}

	// Disables resetting the selection in the destructor
	void CAMSEdit::SelectionSaver::Disable()
	{
		m_pEdit = NULL;
	}


	/////////////////////////////////////////////////////////////////////////////
	// CAMSEdit::Behavior

	// Constructs the object from the given control.
	CAMSEdit::Behavior::Behavior() :
			m_uFlags(0)
	{
		assert(m_pEdit); 
	}
		
	void CAMSEdit::Behavior::SetEdit(CAMSEdit* pEdit)
	{
		m_pEdit = pEdit;
	} 

	// Destroys the object (virtual).
	CAMSEdit::Behavior::~Behavior()
	{
	}

	// Adds and removes flags from the behavior and then redraws the control
	bool CAMSEdit::Behavior::ModifyFlags(UINT uAdd, UINT uRemove,bool bReDraw)
	{
		UINT uFlags = (m_uFlags & ~uRemove) | uAdd;

		if (m_uFlags == uFlags)
			return false;

		m_uFlags = uFlags;
		if(bReDraw)
			_Redraw();
		return true;
	}

	// Returns the flags
	UINT CAMSEdit::Behavior::GetFlags() const
	{
		return m_uFlags;
	}

	// Handles the WM_CHAR message by passing it to the control.
	void CAMSEdit::Behavior::_OnChar(UINT uChar,bool &bHandled)
	{ 
		bHandled =false; 
	}

	// Handles the WM_KEYDOWN message by passing it to the control.
	void CAMSEdit::Behavior::_OnKeyDown(UINT uChar,bool &bHandled)
	{
		bHandled =false; 
	}

	// Handles the WM_KILLFOCUS message by passing it to the control.
	void CAMSEdit::Behavior::_OnKillFocus(bool &bHandled) 
	{
		bHandled =false; 
	}

	// Handles the WM_PASTE message by passing it to the control.
	LONG CAMSEdit::Behavior::_OnPaste()
	{
		return m_pEdit->OnPaste();
	}

	// Calls the default handler for the current message
	LRESULT CAMSEdit::Behavior::_Default()
	{
		return 0;// 
	}

	// Redraws the control so that its value is valid
	void CAMSEdit::Behavior::_Redraw()
	{
		m_pEdit->Redraw();
	}

	// Returns true if the given character should be entered into the control.
	bool CAMSEdit::Behavior::_ShouldEnter(TCHAR c) const
	{
		return m_pEdit->ShouldEnter(c);
	}

 

	/////////////////////////////////////////////////////////////////////////////
	// CAMSEdit::AlphanumericBehavior

	// Constructs the object using the given set of strInvalidChars
	CAMSEdit::AlphanumericBehavior::AlphanumericBehavior(int nMaxChars /*= 0*/, const SStringT& strInvalidChars /*= _T("%'*\"+?><:\\")*/) :
		m_nMaxChars(nMaxChars),
		m_strInvalidChars(strInvalidChars)
	{
		assert(m_nMaxChars >= 0);
	}

	void CAMSEdit::AlphanumericBehavior::SetEdit(CAMSEdit *pEdit)
	{
		Behavior::SetEdit(pEdit);
	}

	// Sets the characters to be considered invalid for text input.
	void CAMSEdit::AlphanumericBehavior::SetInvalidCharacters(const SStringT& strInvalidChars)
	{
		if (m_strInvalidChars == strInvalidChars)
			return;

		m_strInvalidChars = strInvalidChars;
		_Redraw();
	}

	// Returns the characters considered invalid for text input.
	const SStringT& CAMSEdit::AlphanumericBehavior::GetInvalidCharacters() const
	{
		return m_strInvalidChars;
	}

	// Sets the maximum number of characters to allow for input.
	void CAMSEdit::AlphanumericBehavior::SetMaxCharacters(int nMaxChars)
	{
		if (m_nMaxChars == nMaxChars)
			return;

		m_nMaxChars = nMaxChars;
		_Redraw();
	}

	// Returns the characters considered invalid for input.
	int CAMSEdit::AlphanumericBehavior::GetMaxCharacters() const
	{
		return m_nMaxChars;
	}

	// Returns the control's value in a valid format.
	SStringT CAMSEdit::AlphanumericBehavior::_GetValidText() 
	{
		SStringT strText = m_pEdit->GetWindowText();
		SStringT strNewText = strText.Left(m_nMaxChars ? m_nMaxChars : strText.GetLength());

		// Remove any invalid characters from the control's text
		for (int iPos = strNewText.GetLength() - 1; iPos >= 0; iPos--)
		{
			if (m_strInvalidChars.Find(strNewText[iPos]) >= 0)
				strNewText = strNewText.Left(iPos) + strNewText.Mid(iPos + 1);
		}

		return strNewText;
	}

	// Handles the WM_CHAR message, which is called when the user enters a regular character or Backspace
	void CAMSEdit::AlphanumericBehavior::_OnChar(UINT uChar,bool &bHandled)
	{
		// Check to see if it's read only
		if (m_pEdit->GetReadOnly()) 
			return;

		if (!m_strInvalidChars.IsEmpty())
		{
			// Check if the character is invalid
			if (m_strInvalidChars.Find((TCHAR)uChar) >= 0)
			{
				//MessageBeep(MB_ICONEXCLAMATION);
				return;
			}
		}

		TCHAR c = static_cast<TCHAR>(uChar);
		
		// If the number of characters is already at Max, overwrite
		SStringT strText = m_pEdit->GetWindowText();
		if (strText.GetLength() == m_nMaxChars && m_nMaxChars && _istprint(c))
		{
			long nStart = 0, nEnd = 0;
			m_pEdit->GetSel(nStart, nEnd);

			if (nStart < m_nMaxChars && _ShouldEnter(c))
			{
				m_pEdit->SetSel(nStart, nStart + 1);
				m_pEdit->ReplaceSel(SStringT(c), true);
			}
			return;
		}

		if (_ShouldEnter(c))
			Behavior::_OnChar(uChar,bHandled);
	}
  

	/////////////////////////////////////////////////////////////////////////////
	// CAMSEdit::MaskedBehavior

	// Constructs the object using the given mask.
	CAMSEdit::MaskedBehavior::MaskedBehavior(const SStringT& strMask /*= _T("")*/) :		m_strMask(strMask)
	{ 
		m_arraySymbols.push_back(Symbol(_T('#'), (Symbol::ValidationFunction)_istdigit));  // default mask symbol
	}

	void CAMSEdit::MaskedBehavior::SetEdit(CAMSEdit* pEdit)
	{
		Behavior::SetEdit(pEdit);
	}

	// Returns the mask
	const SStringT& CAMSEdit::MaskedBehavior::GetMask() const
	{
		return m_strMask;
	}

	// Sets the mask and redraws the control to accomodate it
	void CAMSEdit::MaskedBehavior::SetMask(const SStringT& strMask)
	{
		if (m_strMask == strMask)
			return;

		m_strMask = strMask;
		_Redraw();
	}

	// Returns the numeric portion of the control's value as a string
	SStringT CAMSEdit::MaskedBehavior::GetNumericText() const
	{
		SStringT strText = m_pEdit->GetWindowText();
		SStringT strResult;

		for (int iPos = 0, nLen = strText.GetLength(); iPos < nLen; iPos++)
		{
			TCHAR c = strText[iPos];
			if (_istdigit(c))
				strResult += c;
		}

		return strResult;	
	}

	// Returns the control's value in a valid format.
	SStringT CAMSEdit::MaskedBehavior::_GetValidText()
	{
		SStringT strText = m_pEdit->GetWindowText();
		int nMaskLen = m_strMask.GetLength();
		
		// If the mask is empty, allow anything
		if (!nMaskLen)
			return strText;

		SStringT strNewText;
		
		// Accomodate the text to the mask as much as possible
		for (int iPos = 0, iMaskPos = 0, nLen = strText.GetLength(); iPos < nLen; iPos++, iMaskPos++)
		{
			TCHAR c = strText[iPos];
			TCHAR cMask = static_cast<TCHAR>(iMaskPos < nMaskLen ? m_strMask[iMaskPos] : 0);

			// If we've reached the end of the mask, break
			if (!cMask)
				break;

			int nSymbolCount=0;
			int iSymbol=0;
			// Match the character to any of the symbols
			for ( iSymbol = 0, nSymbolCount = m_arraySymbols.size(); iSymbol < nSymbolCount; iSymbol++)
			{
				const Symbol& symbol = m_arraySymbols[iSymbol];

				// Find the symbol that applies for the given character
				if (cMask != symbol || !symbol.Validate(c))
					continue;

				// Try to add matching characters in the mask until a different symbol is reached
				for (; iMaskPos < nMaskLen; iMaskPos++)
				{
					cMask = m_strMask[iMaskPos];
					if (cMask == symbol)
					{
						strNewText += symbol.Convert(c);
						break;
					} 
					else
					{
						int iSymbol2=0;
						for ( iSymbol2 = 0; iSymbol2 < nSymbolCount; iSymbol2++)
						{
							if (cMask == m_arraySymbols[iSymbol2])
							{
								strNewText += symbol.Convert(c);
								break;
							}
						}

						if (iSymbol2 < nSymbolCount)
							break;

						strNewText += cMask;
					}
				}

				break;
			}

			// If the character was not matched to a symbol, stop
			if (iSymbol == nSymbolCount)
			{
				if (c == cMask)
				{
					// Match the character to any of the symbols
					for (iSymbol = 0; iSymbol < nSymbolCount; iSymbol++)
					{
						if (cMask == m_arraySymbols[iSymbol])
							break;
					}

					if (iSymbol == nSymbolCount)
					{
						strNewText += c;
						continue;
					}
				}

				break;
			}
		}

		return strNewText;
	}

	// Handles the WM_CHAR message, which is called when the user enters a regular character or Backspace
	void CAMSEdit::MaskedBehavior::_OnChar(UINT uChar,bool &bHandled)
	{
		// Check to see if it's read only
		if (m_pEdit->GetReadOnly())
			return;

		TCHAR c = static_cast<TCHAR>(uChar);

		// If the mask is empty, allow anything
		int nMaskLen = m_strMask.GetLength();
		if (!nMaskLen)
		{
			if (_ShouldEnter(c))
				Behavior::_OnChar(uChar,bHandled);
			return;
		}

		// Check that we haven't gone past the mask's length
		long nStart = 0, nEnd = 0;
		m_pEdit->GetSel(nStart, nEnd);
		if (nStart >= nMaskLen && c != VK_BACK)
			return;

		SStringT strText = m_pEdit->GetWindowText();
		int nLen = strText.GetLength();

		// Check for a non-printable character (such as Ctrl+C)
		if (!_istprint(c))
		{
			if (c == VK_BACK && nStart != nLen)
			{
				m_pEdit->GetTextHost()->GetTextService()->TxSendMessage(WM_KEYDOWN, VK_LEFT, 0, NULL);
				//m_pEdit->SSendMessage(WM_KEYDOWN, VK_LEFT,0); // move the cursor left 
				return;
			}
			
			// Allow backspace only if the cursor is all the way to the right
			if (_ShouldEnter(c))
				Behavior::_OnChar(uChar,bHandled);
			return;
		}

		int iSymbol=0;
		int nSymbolCount=0;
		TCHAR cMask = m_strMask[nStart];

		// Check if the mask's character matches with any of the symbols in the array.
		for ( iSymbol = 0, nSymbolCount = m_arraySymbols.size(); iSymbol < nSymbolCount; iSymbol++)
		{
			const Symbol& symbol = m_arraySymbols[iSymbol];
			if (cMask == symbol)
			{
				if (symbol.Validate(c) && _ShouldEnter(c))
				{
					nEnd = (nEnd == nLen ? nEnd : (nStart + 1));
					m_pEdit->SetSel(nStart, nEnd);
					m_pEdit->ReplaceSel(SStringT(symbol.Convert(c)), true);
				}
				return;
			}
		}

		// Check if it's the same character as the mask.
		if (cMask == c && _ShouldEnter(c))
		{
			nEnd = (nEnd == nLen ? nEnd : (nStart + 1));
			m_pEdit->SetSel(nStart, nEnd);
			m_pEdit->ReplaceSel(SStringT(c), true);
			return;
		}

		// Concatenate all the mask symbols
		SStringT strSymbols;
		for (iSymbol = 0; iSymbol < nSymbolCount; iSymbol++)
			strSymbols += m_arraySymbols[iSymbol];

		// If it's a valid character, find the next symbol on the mask and add any non-mask characters in between.
		for (iSymbol = 0; iSymbol < nSymbolCount; iSymbol++)
		{
			const Symbol& symbol = m_arraySymbols[iSymbol];

			// See if the character is valid for any other symbols
			if (!symbol.Validate(c))
				continue;

			// Find the position of the next symbol 
			SStringT strMaskPortion = m_strMask.Mid(nStart);
			int nMaskPos = strMaskPortion.Find(strSymbols);
				
			// Enter the character if there isn't another symbol before it
			if (nMaskPos >= 0 && strMaskPortion[nMaskPos] == symbol && _ShouldEnter(c))
			{
				m_pEdit->SetSel(nStart, nStart + nMaskPos);
				m_pEdit->ReplaceSel(strMaskPortion.Left(nMaskPos), true);

				_OnChar(uChar,bHandled);
				return;
			}
		}
	}

	// Handles the WM_KEYDOWN message, which is called when the user enters a special character such as Delete or the arrow keys.
	void CAMSEdit::MaskedBehavior::_OnKeyDown(UINT uChar,bool &bHandled) 
	{
		switch (uChar)
		{
			case VK_DELETE:
			{
				// If deleting make sure it's the last character or that
				// the selection goes all the way to the end of the text

				long nStart = 0, nEnd = 0;
				m_pEdit->GetSel(nStart, nEnd);

				SStringT strText = m_pEdit->GetWindowText();
				int nLen = strText.GetLength();

				if(nEnd -nStart >=  nLen)
				{ 
					bHandled =false;	 
				}
				else if (nEnd != nLen)
				{
					if (!(nEnd == nStart && nEnd == nLen - 1))
						return;
				}
				break;
			}
		}

		Behavior::_OnKeyDown(uChar,bHandled);
	}

	// Returns a reference to the array of symbols that may be found on the mask.
	// This allows adding, editing, or deleting symbols for the mask.
	CAMSEdit::MaskedBehavior::SymbolArray& CAMSEdit::MaskedBehavior::GetSymbolArray()
	{
		return m_arraySymbols;
	}


	/////////////////////////////////////////////////////////////////////////////
	// CAMSEdit::MaskedBehavior::Symbol

	// Constructs the object -- needed for CArray
	CAMSEdit::MaskedBehavior::Symbol::Symbol() :
		m_cSymbol(0),
		m_fnValidation(NULL),
		m_fnConversion(NULL)
	{
	}	

	// Constructs the object with the given character and set of functions
	CAMSEdit::MaskedBehavior::Symbol::Symbol(TCHAR cSymbol, ValidationFunction fnValidation, ConversionFunction fnConversion /*= NULL*/) :
		m_cSymbol(cSymbol),
		m_fnValidation(fnValidation),
		m_fnConversion(fnConversion)
	{
	}	

	// Destroys the object (virtual).
	CAMSEdit::MaskedBehavior::Symbol::~Symbol()
	{
	}

	// Returns true if the given character (usually just entered by the user) is a match for self's symbol.
	// This is tested by passing it to the validation function passed in the constructor (if valid).
	bool CAMSEdit::MaskedBehavior::Symbol::Validate(TCHAR c) const
	{
		if (m_fnValidation)
			return (m_fnValidation(c) != 0);
		return true;
	}

	// Returns the given character converted as a result of calling the conversion function was passed in the constructor.
	// If no conversion function was passed, the character is returned intact.
	TCHAR CAMSEdit::MaskedBehavior::Symbol::Convert(TCHAR c) const
	{
		if (m_fnConversion)
			return (TCHAR)m_fnConversion(c);
		return c;
	}

	// Sets the character for the symbol to be used in the mask.
	void CAMSEdit::MaskedBehavior::Symbol::Set(TCHAR cSymbol)
	{
		m_cSymbol = cSymbol;
	}

	// Returns the character for the symbol to be used in the mask.
	TCHAR CAMSEdit::MaskedBehavior::Symbol::Get() const
	{
		return m_cSymbol;
	}

	// Returns the character for the symbol to be used in the mask.
	CAMSEdit::MaskedBehavior::Symbol::operator TCHAR() const
	{
		return m_cSymbol;
	} 
 

	/////////////////////////////////////////////////////////////////////////////
	// CAMSEdit::NumericBehavior

	// Constructs the object using the given nMaxWholeDigits and nMaxDecimalPlaces.
	CAMSEdit::NumericBehavior::NumericBehavior(int nMaxWholeDigits /*= 9*/, int nMaxDecimalPlaces /*= 4*/) :
		m_nMaxWholeDigits(nMaxWholeDigits >= 0 ? nMaxWholeDigits : -nMaxWholeDigits),
		m_nMaxDecimalPlaces(nMaxDecimalPlaces),
		m_cNegativeSign(_T('-')),
		m_cDecimalPoint(_T('.')),
		m_cGroupSeparator(_T(',')),
		m_nDigitsInGroup(0),
		m_dMin(AMS_MIN_NUMBER),	
		m_dMax(AMS_MAX_NUMBER),
		m_bAdjustingSeparators(false)
	{
		assert(m_nMaxWholeDigits > 0);		// must have at least 1 digit to the left of the decimal
		assert(m_nMaxDecimalPlaces >= 0);	// decimal places must be positive

		if (nMaxWholeDigits < 0)
			m_uFlags |= CannotBeNegative;

		// Get the system's negative sign
		if (::GetLocaleInfo(LOCALE_USER_DEFAULT, LOCALE_SNEGATIVESIGN, NULL, 0))
			::GetLocaleInfo(LOCALE_USER_DEFAULT, LOCALE_SNEGATIVESIGN, &m_cNegativeSign, sizeof(m_cNegativeSign));

		// Get the system's decimal point	
		if (::GetLocaleInfo(LOCALE_USER_DEFAULT, LOCALE_SDECIMAL, NULL, 0))
			::GetLocaleInfo(LOCALE_USER_DEFAULT, LOCALE_SDECIMAL, &m_cDecimalPoint, sizeof(m_cDecimalPoint));

		// Get the system's group separator
		if (::GetLocaleInfo(LOCALE_USER_DEFAULT, LOCALE_STHOUSAND, NULL, 0))
			::GetLocaleInfo(LOCALE_USER_DEFAULT, LOCALE_STHOUSAND, &m_cGroupSeparator, sizeof(m_cGroupSeparator));

		// Ensure the separators are not the same
		if (m_cDecimalPoint == m_cGroupSeparator)
			m_cGroupSeparator = (m_cDecimalPoint == _T(',') ? _T('.') : _T(','));
	}

	void CAMSEdit::NumericBehavior::SetEdit(CAMSEdit *pEdit)
	{	
		CAMSEdit::Behavior::SetEdit(pEdit);
	}

	// Sets the maximum number of digits before the decimal point.
	// If nMaxWholeDigits is negative, then negative numbers will NOT be allowed.
	void CAMSEdit::NumericBehavior::SetMaxWholeDigits(int nMaxWholeDigits)
	{
		assert(nMaxWholeDigits);

		// If nMaxWholeDigits is negative, don't allow negatives
		bool bAllowNegative = (nMaxWholeDigits >= 0);
		if (nMaxWholeDigits < 0)
			nMaxWholeDigits = -nMaxWholeDigits;
			
		if (m_nMaxWholeDigits == nMaxWholeDigits && IsNegativeAllowed() == bAllowNegative)
			return;

		m_nMaxWholeDigits = nMaxWholeDigits;
		if (!ModifyFlags(bAllowNegative ? 0 : CannotBeNegative, bAllowNegative ? CannotBeNegative : 0))
			_Redraw();
	}

	// Returns the maximum number of digits before the decimal point.
	int CAMSEdit::NumericBehavior::GetMaxWholeDigits() const
	{
		return m_nMaxWholeDigits;
	}

	// Sets the maximum number of digits after the decimal point.
	void CAMSEdit::NumericBehavior::SetMaxDecimalPlaces(int nMaxDecimalPlaces)
	{
		assert(nMaxDecimalPlaces >= 0);
		if (m_nMaxDecimalPlaces == nMaxDecimalPlaces)
			return;

		m_nMaxDecimalPlaces = nMaxDecimalPlaces;
		_Redraw();
	}

	// Returns the maximum number of digits after the decimal point.
	int CAMSEdit::NumericBehavior::GetMaxDecimalPlaces() const
	{
		return m_nMaxDecimalPlaces;
	}

	// Sets whether the negative sign is allowed in the number or not.
	void CAMSEdit::NumericBehavior::AllowNegative(bool bAllowNegative /*= true*/)
	{
		ModifyFlags(bAllowNegative ? 0 : CannotBeNegative, bAllowNegative ? CannotBeNegative : 0);
	}

	// Returns true if the negative sign is allowed in the number.
	bool CAMSEdit::NumericBehavior::IsNegativeAllowed() const
	{
		return !(m_uFlags & CannotBeNegative);
	}

	// Sets the number of digits to be grouped together (if any).
	void CAMSEdit::NumericBehavior::SetDigitsInGroup(int nDigitsInGroup)
	{
		assert(nDigitsInGroup >= 0);
		if (m_nDigitsInGroup == nDigitsInGroup)
			return;

		m_nDigitsInGroup = nDigitsInGroup;
		_Redraw();
	}

	// Returns the number of digits to be grouped together (if any).
	int CAMSEdit::NumericBehavior::GetDigitsInGroup() const
	{
		return m_nDigitsInGroup;
	}

	// Sets the character to use for the decimal point and the group separator (thousands)
	void CAMSEdit::NumericBehavior::SetSeparators(TCHAR cDecimal, TCHAR cGroup)
	{
		assert(cDecimal);
		assert(cGroup);

		// If nothing's changing, leave
		if (m_cDecimalPoint == cDecimal && m_cGroupSeparator == cGroup)
			return;

		// Set them
		m_cDecimalPoint = cDecimal;
		m_cGroupSeparator = cGroup;

		// Ensure they're not the same
		if (m_cDecimalPoint == m_cGroupSeparator)
			m_cGroupSeparator = (m_cDecimalPoint == _T(',') ? _T('.') : _T(','));

		_Redraw();
	}

	// Retrieves the character being used for the decimal point and group separator (thousands).
	void CAMSEdit::NumericBehavior::GetSeparators(TCHAR* pcDecimal, TCHAR* pcGroup) const
	{
		if (pcDecimal)
			*pcDecimal = m_cDecimalPoint;
		if (pcGroup)
			*pcGroup = m_cGroupSeparator;
	}	

	// Sets the text to be automatically inserted in front of the number (such as a currency sign).
	void CAMSEdit::NumericBehavior::SetPrefix(const SStringT& strPrefix)
	{
		if (m_strPrefix == strPrefix)
			return;

		m_strPrefix = strPrefix;
		_Redraw();
	}

	// Returns the text to be automatically inserted in front of the number (such as a currency sign).
	const SStringT& CAMSEdit::NumericBehavior::GetPrefix() const
	{
		return m_strPrefix;
	}

	// Parses the given strMask to set the control's configuration.
	void CAMSEdit::NumericBehavior::SetMask(const SStringT& strMask)
	{
		int nDecimalPos = -1;
		int nLen = strMask.GetLength();

		m_nMaxWholeDigits = 0;
		m_nMaxDecimalPlaces = 0;
		m_nDigitsInGroup = 0;
		m_uFlags = (m_uFlags & ~CannotBeNegative);  // allow it to be negative
		m_strPrefix = _T("");

		for (int iPos = nLen - 1; iPos >= 0; iPos--)
		{
			TCHAR c = strMask[iPos];
			if (c == '#')
			{
				if (nDecimalPos >= 0)
					m_nMaxWholeDigits++;
				else
					m_nMaxDecimalPlaces++;
			}
			else if ((c == '.' || c == m_cDecimalPoint) && nDecimalPos < 0)
			{
				nDecimalPos = iPos;
				m_cDecimalPoint = c;
			}
			else if (c == ',' || c == m_cGroupSeparator)
			{
				if (!m_nDigitsInGroup)
				{
					m_nDigitsInGroup = (((nDecimalPos >= 0) ? nDecimalPos : nLen) - iPos) - 1;
					m_cGroupSeparator = c;
				}
			}
			else
			{
				m_strPrefix = strMask.Left(iPos + 1);
				break;
			}
		}

		if (nDecimalPos < 0)
		{
			m_nMaxWholeDigits = m_nMaxDecimalPlaces;
			m_nMaxDecimalPlaces = 0;
		}

		assert(m_nMaxWholeDigits > 0);	// must have at least one digit on left side of decimal point
		_Redraw();
	}

	// Gets the mask corresponding to the maximum number than can be entered into the control
	SStringT CAMSEdit::NumericBehavior::GetMask() const
	{
		SStringT strMask;

		int iDigit=0;
		for ( iDigit = 0; iDigit < m_nMaxWholeDigits; iDigit++)
			strMask += '0';

		if (m_nMaxDecimalPlaces)
			strMask += m_cDecimalPoint;

		for (iDigit = 0; iDigit < m_nMaxDecimalPlaces; iDigit++)
			strMask += '0';

		strMask = GetSeparatedText(strMask);

		for (int iPos = 0, nLen = strMask.GetLength(); iPos < nLen; iPos++)
		{
			if (strMask[iPos] == '0')
				strMask.SetAt(iPos, '#');
		}

		return strMask;
	}

	// Sets the range of allowed values to the given minimum and maximum double values.
	void CAMSEdit::NumericBehavior::SetRange(double dMin, double dMax)
	{
		assert(dMin <= dMax);

		m_dMin = dMin;
		m_dMax = dMax;

		_Redraw();
	}

	// Retrieves the range of allowed values inside the given set of double pointers.
	void CAMSEdit::NumericBehavior::GetRange(double* pdMin, double* pdMax) const
	{
		if (pdMin)
			*pdMin = m_dMin;
		if (pdMax)
			*pdMax = m_dMax;
	}

	// Returns the number of group separator characters in the given strText.
	int CAMSEdit::NumericBehavior::GetGroupSeparatorCount(const SStringT& strText) const
	{
		int nSepCount=0;
		int iPos=0;
		int nLen=0;

		for ( iPos = 0, nSepCount = 0, nLen = strText.GetLength(); iPos < nLen; iPos++)
		{
			if (strText[iPos] == m_cGroupSeparator)
				nSepCount++;
		}

		return nSepCount;
	}

	// Returns the given strText as a numeric string.
	SStringT CAMSEdit::NumericBehavior::GetNumericText(const SStringT& strText, bool bUseMathSymbols /*= false*/) const
	{
		SStringT strNewText;
		bool bIsNegative = false;
		bool bHasDecimalPoint = false;

		for (int iPos = 0, nLen = strText.GetLength(); iPos < nLen; iPos++)
		{
			TCHAR c = strText[iPos];
			if (_istdigit(c))
				strNewText += c;
			else if (c == m_cNegativeSign)
				bIsNegative = true;
			else if (c == m_cDecimalPoint && !bHasDecimalPoint)
			{
				bHasDecimalPoint = true;
				strNewText += (bUseMathSymbols ? _T('.') : m_cDecimalPoint);
			}
		}

		// Add the negative sign to the front of the number
		if (bIsNegative)
			strNewText.Insert(0, bUseMathSymbols ? _T('-') : m_cNegativeSign);

		return strNewText;
	}

	// Returns the current double as a text value.
	// If bTrimTrailingZeros is true, any insignificant zeros after the decimal point are removed.
	SStringT CAMSEdit::NumericBehavior::GetDoubleText(double dText, bool bTrimTrailingZeros /*= true*/) const
	{
		SStringT strText;
		strText.Format(_T("%lf"), dText);

		if (m_cDecimalPoint != _T('.'))		
			strText.Replace(SStringT(_T('.')), SStringT(m_cDecimalPoint));

		if (bTrimTrailingZeros)
		{
			strText.TrimRight(_T('0'));
			strText.TrimRight(m_cDecimalPoint);
		}

		return strText;
	}

	// Sets the control's text to the given double value.
	// If bTrimTrailingZeros is true, any insignificant zeros after the decimal point are removed.
	void CAMSEdit::NumericBehavior::SetDouble(double dText, bool bTrimTrailingZeros /*= true*/)
	{
		m_pEdit->SetWindowText(GetDoubleText(dText, bTrimTrailingZeros));
	}

	// Returns the current text as a double value.
	double CAMSEdit::NumericBehavior::GetDouble() const
	{
		return _tcstod(GetNumericText(m_pEdit->GetWindowText()), NULL);
	}

	// Sets the control's text to the given integer value.
	void CAMSEdit::NumericBehavior::SetInt(int nText)
	{
		SStringT strText;
		strText.Format(_T("%d"), nText);
		m_pEdit->SetWindowText(strText);
	}

	// Returns the current text as an integer value.
	int CAMSEdit::NumericBehavior::GetInt() const
	{
		return _ttoi(GetNumericText(m_pEdit->GetWindowText()));
	}

	// Adjusts the location of separators based on the nCurrentSeparatorCount.
	void CAMSEdit::NumericBehavior::AdjustSeparators(int nCurrentSeparatorCount)
	{
		SelectionSaver selection = m_pEdit;
		m_bAdjustingSeparators = true;

		SStringT strText = _GetValidText();
		if (strText != m_pEdit->GetWindowText())
			m_pEdit->SetWindowText(strText);

		// Adjust the current selection if separators were added/removed
		int nNewSeparatorCount = GetGroupSeparatorCount(strText);
		if (nCurrentSeparatorCount != nNewSeparatorCount && selection.GetStart() > m_strPrefix.GetLength())
			selection += (nNewSeparatorCount - nCurrentSeparatorCount);

		m_bAdjustingSeparators = false;
	}

	// Returns the given text with the group separator characters inserted in the proper places.
	SStringT CAMSEdit::NumericBehavior::GetSeparatedText(const SStringT& strText) const
	{
		SStringT strNumericText = GetNumericText(strText);
		SStringT strNewText = strNumericText;
		
		// Retrieve the number without the decimal point
		int nDecimalPos = strNumericText.Find(m_cDecimalPoint);
		if (nDecimalPos >= 0)
			strNewText = strNewText.Left(nDecimalPos);

		if (m_nDigitsInGroup > 0)
		{
			int nLen = strNewText.GetLength();
			BOOL bIsNegative = (!strNewText.IsEmpty() && strNewText[0] == m_cNegativeSign);

			// Loop in reverse and stick the separator every m_nDigitsInGroup digits.
			for (int iPos = nLen - (m_nDigitsInGroup + 1); iPos >= bIsNegative; iPos -= m_nDigitsInGroup)
				strNewText = strNewText.Left(iPos + 1) + SStringT(m_cGroupSeparator) + strNewText.Mid(iPos + 1);
		}

		// Prepend the prefix, if the number is not empty.
		if (!strNewText.IsEmpty() || nDecimalPos >= 0)
		{
			strNewText = m_strPrefix + strNewText;

			if (nDecimalPos >= 0)
				strNewText += strNumericText.Mid(nDecimalPos);
		}

		return strNewText;
	}

	// Inserts nCount zeros into the given string at the given position.
	// If nPos is less than 0, the zeros are appended.
	void CAMSEdit::NumericBehavior::InsertZeros(SStringT* pStrText, int nPos, int nCount)
	{
		assert(pStrText);

		if (nPos < 0 && nCount > 0)
			nPos = pStrText->GetLength();

		for (int iZero = 0; iZero < nCount; iZero++)
			pStrText->Insert(nPos, '0');
	}

	// Returns the control's value in a valid format.
	SStringT CAMSEdit::NumericBehavior::_GetValidText() 
	{
		SStringT strText = m_pEdit->GetWindowText();
		SStringT strNewText;
		bool bIsNegative = false;
		int nNewLen=0;
		int nLen=0;
		int nDecimalPos=0;
		int iPos=0;

		// Remove any invalid characters from the number
		for ( iPos = 0, nDecimalPos = -1, nNewLen = 0, nLen = strText.GetLength(); iPos < nLen; iPos++)
		{
			TCHAR c = strText[iPos];

			// Check for a negative sign
			if (c == m_cNegativeSign && IsNegativeAllowed())
				bIsNegative = true;

			// Check for a digit
			else if (_istdigit(c))
			{
				// Make sure it doesn't go beyond the limits
				if (nDecimalPos < 0 && nNewLen == m_nMaxWholeDigits)
					continue;

				if (nDecimalPos >= 0 && nNewLen > nDecimalPos + m_nMaxDecimalPlaces)
					break;

				strNewText += c;
				nNewLen++;
			}
			// Check for a decimal point
			else if (c == m_cDecimalPoint && nDecimalPos < 0)
			{
				if (m_nMaxDecimalPlaces == 0)
					break;

				strNewText += c;
				nDecimalPos = nNewLen;
				nNewLen++;
			}
		}
		
		// Check if we need to pad the number with zeros after the decimal point
		if (m_nMaxDecimalPlaces > 0 && nNewLen > 0 &&
			((m_uFlags & PadWithZerosAfterDecimalWhenTextChanges) ||
			(!m_bAdjustingSeparators && (m_uFlags & PadWithZerosAfterDecimalWhenTextIsSet))))
		{
			if (nDecimalPos < 0)
			{
				if (nNewLen == 0 || strNewText == SStringT(_T('-')))
				{
					strNewText = _T('0');
					nNewLen = 1;
				}
				strNewText += m_cDecimalPoint;
				nDecimalPos = nNewLen++;
			}

			InsertZeros(&strNewText, -1, m_nMaxDecimalPlaces - (nNewLen - nDecimalPos - 1));
		}

		// Insert the negative sign if it's there
		if (bIsNegative)
			strNewText.Insert(0, m_cNegativeSign);

		return GetSeparatedText(strNewText);
	}

	// Handles the WM_CHAR message, which is called when the user enters a regular character or Backspace
	void CAMSEdit::NumericBehavior::_OnChar(UINT uChar,bool &bHandled)
	{
		// Check to see if it's read only
		if (m_pEdit->GetReadOnly())
			return;

		TCHAR c = static_cast<TCHAR>(uChar);

		long nStart = 0, nEnd = 0;
		m_pEdit->GetSel(nStart, nEnd);

		SStringT strText = m_pEdit->GetWindowText();
		SStringT strNumericText = GetNumericText(strText);
		int nDecimalPos = strText.Find(m_cDecimalPoint);
		int nNumericDecimalPos = strNumericText.Find(m_cDecimalPoint);
		int nLen = strText.GetLength();
		int nNumericLen = strNumericText.GetLength();
		int nPrefixLen = m_strPrefix.GetLength();
		int nSepCount = GetGroupSeparatorCount(strText);
		bool bNeedAdjustment = false;

		// Check if we're in the prefix's location
		if (nStart < nPrefixLen && _istprint(c))
		{
			TCHAR cPrefix = m_strPrefix[nStart];

			// Check if it's the same character as the prefix.
			if (cPrefix == c && _ShouldEnter(c))
			{
				if (nLen > nStart)
				{
					nEnd = (nEnd == nLen ? nEnd : (nStart + 1));
					m_pEdit->SetSel(nStart, nEnd);
					m_pEdit->ReplaceSel(SStringT(c), true);
				}
				else
					Behavior::_OnChar(uChar, bHandled);
			}
			// If it's a part of the number, enter the prefix
			else if ((_istdigit(c) || c == m_cNegativeSign || c == m_cDecimalPoint) && _ShouldEnter(c))
			{
				nEnd = (nEnd == nLen ? nEnd : (nPrefixLen));
				m_pEdit->SetSel(nStart, nEnd);
				m_pEdit->ReplaceSel(m_strPrefix.Mid(nStart), true);

				NumericBehavior::_OnChar(uChar,bHandled);
			}
			
			return;
		}

		// Check if it's a negative sign
		if (c == m_cNegativeSign && IsNegativeAllowed())
		{
			// If it's at the beginning, determine if it should overwritten
			if (nStart == nPrefixLen)
			{
				if (!strNumericText.IsEmpty() && strNumericText[0] == m_cNegativeSign && _ShouldEnter(c))
				{
					nEnd = (nEnd == nLen ? nEnd : (nStart + 1));
					m_pEdit->SetSel(nStart, nEnd);
					m_pEdit->ReplaceSel(SStringT(m_cNegativeSign), true);
					return;
				}
			}
			// If we're not at the beginning, toggle the sign
			else if (_ShouldEnter(c))
			{
				if (strNumericText[0] == m_cNegativeSign)
				{
					m_pEdit->SetSel(nPrefixLen, nPrefixLen + 1);
					m_pEdit->ReplaceSel(_T(""), true);
					m_pEdit->SetSel(nStart - 1, nEnd - 1);
				}
				else
				{
					m_pEdit->SetSel(nPrefixLen, nPrefixLen);
					m_pEdit->ReplaceSel(SStringT(m_cNegativeSign), true);
					m_pEdit->SetSel(nStart + 1, nEnd + 1);
				}

				return;
			}
		}

		// Check if it's a decimal point (only one is allowed).
		else if (c == m_cDecimalPoint && m_nMaxDecimalPlaces > 0)
		{
			if (nDecimalPos >= 0)
			{
				// Check if we're replacing the decimal point
				if (nDecimalPos >= nStart && nDecimalPos < nEnd)
					bNeedAdjustment = true;
				else
				{	// Otherwise, put the caret on it
					if (_ShouldEnter(c))
						m_pEdit->SetSel(nDecimalPos + 1, nDecimalPos + 1);
					return;
				}
			}
			else
				bNeedAdjustment = true;
		}

		// Check if it's a digit
		else if (_istdigit(c))
		{
			// Check if we're on the right of the decimal point.
			if (nDecimalPos >= 0 && nDecimalPos < nStart)
			{
				if (strNumericText.Mid(nNumericDecimalPos + 1).GetLength() == m_nMaxDecimalPlaces)
				{
					if (nStart <= nDecimalPos + m_nMaxDecimalPlaces && _ShouldEnter(c))
					{
						nEnd = (nEnd == nLen ? nEnd : (nStart + 1));
						m_pEdit->SetSel(nStart, nEnd);
						m_pEdit->ReplaceSel(SStringT(c), true);
					}
					return;
				}
			}

			// We're on the left side of the decimal point
			else 
			{
				bool bIsNegative = (!strNumericText.IsEmpty() && strNumericText[0] == m_cNegativeSign);

				// Make sure we can still enter digits.
				if (nStart == m_nMaxWholeDigits + bIsNegative + nSepCount + nPrefixLen)
				{
					if (m_uFlags & AddDecimalAfterMaxWholeDigits && m_nMaxDecimalPlaces > 0)
					{
						nEnd = (nEnd == nLen ? nEnd : (nStart + 2));
						m_pEdit->SetSel(nStart, nEnd);
						m_pEdit->ReplaceSel(SStringT(m_cDecimalPoint) + SStringT(c), true);
					}
					return;
				}

				if (strNumericText.Mid(0, nNumericDecimalPos >= 0 ? nNumericDecimalPos : nNumericLen).GetLength() == m_nMaxWholeDigits + bIsNegative)
				{
					if (_ShouldEnter(c))
					{
						if (strText[nStart] == m_cGroupSeparator)
							nStart++;

						nEnd = (nEnd == nLen ? nEnd : (nStart + 1));
						m_pEdit->SetSel(nStart, nEnd);
						m_pEdit->ReplaceSel(SStringT(c), true);
					}
					return;
				}

				bNeedAdjustment = true;
			}
		}

		// Check if it's a non-printable character, such as Backspace or Ctrl+C
		else if (!_istprint(c))
			bNeedAdjustment = true;
		else
			return;

		// Check if the character should be entered
		if (!_ShouldEnter(c))
			return;
		
		Behavior::_OnChar(uChar,bHandled);

		// If the decimal point was added/removed or a separator needs adding/removing, adjust the text
		if (bNeedAdjustment)
			AdjustSeparators(nSepCount);
	}

	// Handles the WM_KEYDOWN message, which is called when the user enters a special character such as Delete or the arrow keys.
	void CAMSEdit::NumericBehavior::_OnKeyDown(UINT uChar,bool &bHandled) 
	{
		switch (uChar)
		{
			case VK_DELETE:
			{
				long nStart = 0, nEnd = 0;
				m_pEdit->GetSel(nStart, nEnd);

				SStringT strText = m_pEdit->GetWindowText();
				int nLen = strText.GetLength();

				// If deleting the prefix, don't allow it if there's a number after it.
				int nPrefixLen = m_strPrefix.GetLength();
				if (nStart < nPrefixLen && nLen > nPrefixLen)
				{
					if (nEnd == nLen)
						break;
					return;
				}

				if (nStart < nLen && strText[nStart] == m_cGroupSeparator && nStart == nEnd)
					Behavior::_OnKeyDown(VK_RIGHT, bHandled);

				// Allow the deletion and then adjust the value
				int nSepCount = GetGroupSeparatorCount(strText);
				Behavior::_OnKeyDown(uChar, bHandled);

				AdjustSeparators(nSepCount);

				// If everything on the right was deleted, put the selection on the right
				if (nEnd == nLen)
					m_pEdit->SetSel(nStart, nStart);

				return;
			}
		}

		Behavior::_OnKeyDown(uChar,bHandled);
	}

	// Handles the WM_KILLFOCUS message, which is called when the user leaves the control.
	// It's used here to check if zeros need to be added to the value.
	void CAMSEdit::NumericBehavior::_OnKillFocus(bool &bHandled) 
	{
		Behavior::_OnKillFocus(bHandled);

		// Check if the value is empty and we don't want to touch it
		SStringT strOriginalText = GetNumericText(m_pEdit->GetWindowText());
		SStringT strText = strOriginalText;
		int nLen = strText.GetLength();

		// If desired, remove any extra leading zeros but always leave one in front of the decimal point
		if (m_uFlags & OnKillFocus_RemoveExtraLeadingZeros && nLen > 0)
		{
			bool bIsNegative = (strText[0] == m_cNegativeSign);
			if (bIsNegative)
				strText.Delete(0);
			strText.TrimLeft(_T('0'));
			if (strText.IsEmpty() || strText[0] == m_cDecimalPoint)
				strText.Insert(0, _T('0'));
			if (bIsNegative)
				strText.Insert(0, m_cNegativeSign);
		}
		else if (!(m_uFlags & OnKillFocus_Max) || (nLen == 0 && m_uFlags & OnKillFocus_DontPadWithZerosIfEmpty))
			return;

		int nDecimalPos = strText.Find(m_cDecimalPoint);

		// Check if we need to pad the number with zeros after the decimal point
		if (m_uFlags & OnKillFocus_PadWithZerosAfterDecimal && m_nMaxDecimalPlaces > 0)
		{
			if (nDecimalPos < 0)
			{
				if (nLen == 0 || strText == SStringT(_T('-')))
				{
					strText = _T('0');
					nLen = 1;
				}
				strText += m_cDecimalPoint;
				nDecimalPos = nLen++;
			}

			InsertZeros(&strText, -1, m_nMaxDecimalPlaces - (nLen - nDecimalPos - 1));
		}

		// Check if we need to pad the number with zeros before the decimal point
		if (m_uFlags & OnKillFocus_PadWithZerosBeforeDecimal && m_nMaxWholeDigits > 0)
		{
			if (nDecimalPos < 0)
				nDecimalPos = nLen;

			if (nLen && strText[0] == _T('-'))
				nDecimalPos--;

			InsertZeros(&strText, (nLen ? strText[0] == _T('-') : -1), m_nMaxWholeDigits - nDecimalPos);
		}

		if (strText != strOriginalText)
		{
			SelectionSaver selection = m_pEdit;	// remember the current selection 
			m_pEdit->SetWindowText(strText);
		}

		// If it's empty, take action based on the flag
		if (strText.IsEmpty())
		{
			if (m_uFlags & OnKillFocus_Beep_IfEmpty)
				MessageBeep(MB_ICONEXCLAMATION);
				
			if (m_uFlags & OnKillFocus_SetValid_IfEmpty)
				AdjustWithinRange();

			if ((m_uFlags & OnKillFocus_ShowMessage_IfEmpty) == OnKillFocus_ShowMessage_IfEmpty)
				ShowErrorMessage();		

			if (m_uFlags & OnKillFocus_SetFocus_IfEmpty)
				m_pEdit->SetFocus();

			return;
		}
			
		if (!IsValid())
		{
			if (m_uFlags & OnKillFocus_Beep_IfInvalid)
				MessageBeep(MB_ICONEXCLAMATION);
				
			if (m_uFlags & OnKillFocus_SetValid_IfInvalid)
				AdjustWithinRange();
			
			if ((m_uFlags & OnKillFocus_ShowMessage_IfInvalid) == OnKillFocus_ShowMessage_IfInvalid)
				ShowErrorMessage();		

			if (m_uFlags & OnKillFocus_SetFocus_IfInvalid)
				m_pEdit->SetFocus();
		}
	}

	// Returns true if the control's value is valid and falls within the allowed range.
	bool CAMSEdit::NumericBehavior::IsValid() const
	{
		double dValue = GetDouble();
		return (dValue >= m_dMin && dValue <= m_dMax);
	}

	// Returns true if the control's value is valid and falls within the allowed range.
	// If bShowErrorIfNotValid is true, an error message box is shown and the control gets the focus.
	bool CAMSEdit::NumericBehavior::CheckIfValid(bool bShowErrorIfNotValid /*= true*/)
	{
		if (m_pEdit->GetReadOnly())
			return true;

		bool bValid = IsValid();
		if (!bValid && bShowErrorIfNotValid)
		{
			ShowErrorMessage();
			m_pEdit->SetFocus();
		}
		
		return bValid;
	}

	// Shows a message box informing the user to enter a valid value within the allowed range.
	void CAMSEdit::NumericBehavior::ShowErrorMessage() const
	{
		 
	}

	// Adjusts the control's value to be within the range of allowed numeric values.
	void CAMSEdit::NumericBehavior::AdjustWithinRange()
	{
		// Check if it's already within the range
		if (IsValid())
			return;

		// If it's empty, set it a valid number
		if (m_pEdit->GetWindowText().IsEmpty())
			m_pEdit->SetWindowText(_T(" "));
		else
			_Redraw();

		// Make it fall within the range
		double dValue = GetDouble();
		if (dValue < m_dMin)
			SetDouble(m_dMin);
		else if (dValue > m_dMax)
			SetDouble(m_dMax);
	}
	/////////////////////////////////////////////////////////////////////////////
	// CAMSEdit::DateBehavior

	// Constructs the object with the given control.
	CAMSEdit::DateBehavior::DateBehavior() :m_dateMin(AMS_MIN_OLEDATETIME),
											m_dateMax(AMS_MAX_OLEDATETIME),
											m_cSep(_T('/'))
	{ 
		// Get the system's date separator
		if (::GetLocaleInfo(LOCALE_USER_DEFAULT, LOCALE_SDATE, NULL, 0))
			::GetLocaleInfo(LOCALE_USER_DEFAULT, LOCALE_SDATE, &m_cSep, sizeof(m_cSep));

		// Determine if the day should go before the month
		TCHAR szShortDate[MAX_PATH];
		if (::GetLocaleInfo(LOCALE_USER_DEFAULT, LOCALE_SSHORTDATE, NULL, 0))
		{
			::GetLocaleInfo(LOCALE_USER_DEFAULT, LOCALE_SSHORTDATE, szShortDate, sizeof(szShortDate));

			for (int iPos = 0; szShortDate[iPos]; iPos++)
			{
				TCHAR c = static_cast<TCHAR>(_totupper(szShortDate[iPos]));
				if (c == _T('M'))	// see if the month is first
					break;
				if (c == _T('D'))	// see if the day is first, and then set the flag
				{ 
					break;
				}
			}
		}
	}

	void CAMSEdit::DateBehavior::SetEdit(CAMSEdit* pEdit)
	{
		Behavior::SetEdit(pEdit);
	}

	// Handles the WM_CHAR message, which is called when the user enters a regular character or Backspace
	void CAMSEdit::DateBehavior::_OnChar(UINT uChar,bool &bHandled) 
	{
		// Check to see if it's read only
		if (m_pEdit->GetReadOnly())
			return;

		TCHAR c = static_cast<TCHAR>(uChar);

		long nStart = 0, nEnd = 0;
		m_pEdit->GetSel(nStart, nEnd);

		SStringT strText = m_pEdit->GetWindowText();
		int nLen = strText.GetLength();

		// Check for a non-printable character (such as Ctrl+C)
		if (!_istprint(c))
		{
			if (c == VK_BACK && nStart != nLen)
			{
				m_pEdit->SSendMessage(WM_KEYDOWN, VK_LEFT); // move the cursor left 
				return;
			}
			
			// Allow backspace only if the cursor is all the way to the right
			if (_ShouldEnter(c))
				Behavior::_OnChar(uChar,bHandled);
			if(VK_TAB == uChar)
				bHandled = true;
			return;
		}

		// Add the digit depending on its location
		switch (nStart)
		{
			case 0:		// YEAR (all 4 digits)
			case 1:
			case 2:
			case 3:
			{
				int year_start_pos = GetYearStartPosition();

				if (IsValidYearDigit(c, nStart - year_start_pos) && _ShouldEnter(c))
				{
					if (nLen > nStart)
					{
						m_pEdit->SetSel(nStart, nStart + 1);
						m_pEdit->ReplaceSel(SStringT(c), true);

						for (int i= nStart+1; i < nLen && i < 4; i++)
						{
							TCHAR ch = strText.GetAt(i);
							if (!IsValidYearDigit(ch, i - year_start_pos))
							{ 
								m_pEdit->SetSel(i + 1, 4);
								
								SStringT strPortion;
								for (int iPos = i + 1; iPos < nLen && iPos < 4; iPos++)
									strPortion += GetMinYearDigit(iPos - year_start_pos, true);
								
								m_pEdit->ReplaceSel(strPortion, true);
								m_pEdit->SetSel(i , i+1);
								break;
							}
						}
					}
					else
						Behavior::_OnChar(uChar,bHandled);

					if (IsValidYear(GetYear()))
					{
						AdjustMaxDay();			// adjust the day first
						AdjustMaxMonthAndDay();	// then adjust the month and the day, if necessary
					}
				}
				break;
			}
			break;

			case 4:		// SECOND SLASH	(year's first digit)
			{
				int nSlash = 0;
				if (c == m_cSep)
					nSlash = 1;
				else
					nSlash = (IsValidMonthDigit(c, 0) || (nLen == nStart && GetMinMonthDigit(0) == _T('0') && IsValidMonthDigit(c, 1))) ? 2 : 0; 

				// If we need the slash, enter it
				if (nSlash && _ShouldEnter(c))
				{
					m_pEdit->SetSel(nStart, nStart + 1);
					m_pEdit->ReplaceSel(SStringT(m_cSep), true);
				}

				// If the slash is to be preceded by a valid digit, "type" it in.
				if (nSlash == 2)
				{
					keybd_event((BYTE)c, 0, 0, 0); 
				}
				break;			
			}
			
			case 5:		// FIRST DIGIT
			{ 
				if (IsValidMonthDigit(c, 0) && _ShouldEnter(c))
				{
					if (nLen > nStart)
					{
						m_pEdit->SetSel(nStart, nStart + 1);
						m_pEdit->ReplaceSel(SStringT(c), true);

						if (nLen > nStart + 1)
						{
							if (!IsValidMonth(GetMonth()))
							{
								m_pEdit->SetSel(nStart + 1, nStart + 2);
								m_pEdit->ReplaceSel(SStringT(GetMinMonthDigit(1)), true);
								m_pEdit->SetSel(nStart + 1, nStart + 2);
							}
						}
						AdjustMaxDay();
					}
					else
						Behavior::_OnChar(uChar,bHandled);
				}
				// Check if we can insert the digit with a leading zero
				else if (nLen == nStart && GetMinMonthDigit(0) == _T('0') && IsValidMonthDigit(c, 1) && _ShouldEnter(c))
				{
					m_pEdit->SetSel(nStart, nStart + 2);
					SStringT str = _T('0');
					str +=c;
					m_pEdit->ReplaceSel(str, true);					
				} 
			}
			break;
			case 6:		// SECOND DIGIT
			{ 
				if (IsValidMonthDigit(c, 1) && _ShouldEnter(c))
				{
					if (nLen > nStart)
					{
						m_pEdit->SetSel(nStart, nStart + 1);
						m_pEdit->ReplaceSel(SStringT(c), true);

						if (GetDay() > 0 && AdjustMaxDay())
							m_pEdit->SetSel(GetDayStartPosition(), GetMonthStartPosition() + 2);
					}
					else
						Behavior::_OnChar(uChar,bHandled);
				}				
				// Check if it's a slash and the first digit (preceded by a zero) is a valid month
				else if (c == m_cSep && nLen == nStart && GetMinMonthDigit(0) == _T('0') && IsValidMonth(_ttoi(SStringT(SStringT(_T('0')) + SStringT(strText[3])))) && _ShouldEnter(c))
				{
					m_pEdit->SetSel(0, nStart);
					
					SStringT str = _T('0');
					str +=strText[3];
					str +=c;
					m_pEdit->ReplaceSel(str, true);					
				} 
			}
			break;
			
			case 7:		// FIRST SLASH
			{
				int nSlash = 0;
				if (c == m_cSep)
					nSlash = 1;
				else
				{
					nSlash = (IsValidDayDigit(c, 0) || (nLen == nStart && GetMinDayDigit(0) == _T('0') && IsValidDayDigit(c, 1))) ? 2 : 0;
				}

				// If we need the slash, enter it
				if (nSlash && _ShouldEnter(c))
				{
					m_pEdit->SetSel(nStart, nStart + 1);
					m_pEdit->ReplaceSel(SStringT(m_cSep), true);
				}

				// If the slash is to be preceded by a valid digit, "type" it in.
				if (nSlash == 2)
					keybd_event((BYTE)c, 0, 0, 0);
				break;
			}

			case 8:		// THIRD DIGIT
			{ 
				if (IsValidDayDigit(c, 0) && _ShouldEnter(c))
				{
					if (nLen > nStart)
					{
						m_pEdit->SetSel(nStart, nStart + 1);
						m_pEdit->ReplaceSel(SStringT(c), true);

						if (nLen > nStart + 1)
						{
							if (!IsValidDay(GetDay()))
							{
								m_pEdit->SetSel(nStart + 1, nStart + 2);
								m_pEdit->ReplaceSel(SStringT(GetMinDayDigit(0)), true);
								m_pEdit->SetSel(nStart + 1, nStart + 2);
							}
						}
					}
					else
						Behavior::_OnChar(uChar,bHandled);
				}
				// Check if we can insert the digit with a leading zero
				else if (nLen == nStart && GetMinDayDigit(0) == _T('0') && IsValidDayDigit(c, 1) && _ShouldEnter(c))
				{
					m_pEdit->SetSel(nStart, nStart + 2);
					
					SStringT str = _T('0'); 
					str +=c;
					m_pEdit->ReplaceSel(str, true);					
				} 		
			}
			break; 
			case 9:		// FOURTH DIGIT
			{ 
				if (IsValidDayDigit(c, 1) && _ShouldEnter(c))
				{
					if (nLen > nStart)
					{
						m_pEdit->SetSel(nStart, nStart + 1);
						m_pEdit->ReplaceSel(SStringT(c), true);
					}
					else
						Behavior::_OnChar(uChar,bHandled);
				}
				// Check if we can insert the digit with a leading zero
				else if (nLen == nStart && GetMinDayDigit(0) == '0' && IsValidDayDigit(c, 1) && _ShouldEnter(c))
				{
					m_pEdit->SetSel(nStart, nStart + 2);
					m_pEdit->ReplaceSel(SStringT('0') + SStringT(c), true);					
				}
			}
			break;
		}
	}

	// Handles the WM_KEYDOWN message, which is called when the user enters a special character such as Delete or the arrow keys.
	void CAMSEdit::DateBehavior::_OnKeyDown(UINT uChar,bool &bHandled) 
	{
		// Check to see if it's read only
		if (m_pEdit->GetReadOnly())
			return;


		switch (uChar)
		{
			case VK_BACK:
			{  
				long nStart = 0, nEnd = 0;
				m_pEdit->GetSel(nStart, nEnd);

				SStringT strText = m_pEdit->GetWindowText();
				int nLen = strText.GetLength();

				// Check for a non-printable character (such as Ctrl+C)
				 
				if(nEnd - nStart >=nLen)
				{
					bHandled =false;	
				}
				else if (nStart != nLen)
				{
					m_pEdit->SSendMessage(WM_KEYDOWN, VK_LEFT); // move the cursor left 
					return;
				} 
			}
			break;

			case VK_DELETE:
			{
				// If deleting make sure it's the last character or that
				// the selection goes all the way to the end of the text

				long nStart = 0, nEnd = 0;
				m_pEdit->GetSel(nStart, nEnd);

				SStringT strText = m_pEdit->GetWindowText();
				int nLen = strText.GetLength();

				if(nEnd -nStart >=  nLen)
				{ 
					bHandled =false;	 
				}
				else if (nEnd != nLen)
				{
					if (!(nEnd == nStart && nEnd == nLen - 1))
						return;
				}
				break;
			}

			case VK_UP:
			{
				// If pressing the UP arrow, increment the corresponding value.

				long nStart = 0, nEnd = 0;
				m_pEdit->GetSel(nStart, nEnd);

				if (nStart >= GetYearStartPosition() && nStart <= GetYearStartPosition() + 4)
				{
					int nYear = GetYear();
					if (nYear >= m_dateMin.GetYear() && nYear < m_dateMax.GetYear())
						SetYear(++nYear);
				}

				else if (nStart >= GetMonthStartPosition() && nStart <= GetMonthStartPosition() + 2)
				{
					int nMonth = GetMonth();
					if (nMonth >= GetMinMonth() && nMonth < GetMaxMonth())
						SetMonth(++nMonth);
				}

				else if (nStart >= GetDayStartPosition() && nStart <= GetDayStartPosition() + 2)
				{
					int nDay = GetDay();
					if (nDay >= GetMinDay() && nDay < GetMaxDay())
						SetDay(++nDay);
				}
				
				return;
			}

			case VK_DOWN:
			{
				// If pressing the DOWN arrow, decrement the corresponding value.

				long nStart = 0, nEnd = 0;
				m_pEdit->GetSel(nStart, nEnd);

				if (nStart >= GetYearStartPosition() && nStart <= GetYearStartPosition() + 4)
				{
					int nYear = GetYear();
					if (nYear > m_dateMin.GetYear())
						SetYear(--nYear);
				}

				else if (nStart >= GetMonthStartPosition() && nStart <= GetMonthStartPosition() + 2)
				{
					int nMonth = GetMonth();
					if (nMonth > GetMinMonth())
						SetMonth(--nMonth);
				}

				else if (nStart >= GetDayStartPosition() && nStart <= GetDayStartPosition() + 2)
				{
					int nDay = GetDay();
					if (nDay > GetMinDay())
						SetDay(--nDay);
				}
				
				return;
			}
		}

		Behavior::_OnKeyDown(uChar,bHandled);
	}

	// Handles the WM_KILLFOCUS message, which is called when the user leaves the control.
	// It's used here to check if any action needs to be taken based on the control's value.
	void CAMSEdit::DateBehavior::_OnKillFocus(bool &bHandled) 
	{
		Behavior::_OnKillFocus(bHandled);
 

		SStringT strText = m_pEdit->GetWindowText();

		// If it's empty, take action based on the flag
		if (strText.IsEmpty())
		{ 
			return;
		}
			
		if (!IsValid())
		{ 
			_Redraw(); 
		}
	}

	// Returns the given value as a string with or without leading zeros.
	SStringT CAMSEdit::DateBehavior::GetString(int nValue, bool bTwoDigitWithLeadingZero /*= true*/)
	{
		SStringT strValue;
		if (bTwoDigitWithLeadingZero)
			strValue.Format(_T("%02d"), nValue);
		else
			strValue.Format(_T("%d"), nValue);
		return strValue;
	}

	// Returns the zero-based position of the month inside the control.
	// This is based on whether the month is shown before or after the day.
	int CAMSEdit::DateBehavior::GetMonthStartPosition() const
	{
		return  5;
	}

	// Returns the zero-based position of the day inside the control.
	// This is based on whether the day is shown before or after the month.
	int CAMSEdit::DateBehavior::GetDayStartPosition() const
	{
		return 8;
	}

	// Returns the zero-based position of the year inside the control.
	int CAMSEdit::DateBehavior::GetYearStartPosition() const
	{
		return 0;
	}

	// Returns the maximum value for the month based on the allowed range.
	int CAMSEdit::DateBehavior::GetMaxMonth() const
	{
		if (GetValidYear() == m_dateMax.GetYear())
			return m_dateMax.GetMonth();
		return 12;
	}

	// Returns the minimum value for the month based on the allowed range.
	int CAMSEdit::DateBehavior::GetMinMonth() const
	{
		if (GetValidYear() == m_dateMin.GetYear())
			return m_dateMin.GetMonth();
		return 1;
	}

	// Returns the maximum value for the day based on the allowed range.
	int CAMSEdit::DateBehavior::GetMaxDay() const
	{
		int nYear = GetValidYear();
		int nMonth = GetValidMonth();

		if (nYear == m_dateMax.GetYear() && nMonth == m_dateMax.GetMonth())
			return m_dateMax.GetDay();

		return GetMaxDayOfMonth(nMonth, nYear);
	}

	// Returns the minimum value for the day based on the allowed range.
	int CAMSEdit::DateBehavior::GetMinDay() const
	{
		int nYear = GetValidYear();
		int nMonth = GetValidMonth();

		if (nYear == m_dateMin.GetYear() && nMonth == m_dateMin.GetMonth())
			return m_dateMin.GetDay();

		return 1;
	}

	// Returns the maximum value for the day based on the given month and year.
	int CAMSEdit::DateBehavior::GetMaxDayOfMonth(int nMonth, int nYear)
	{
		assert(nMonth >= 1 && nMonth <= 12);

		switch (nMonth)
		{
			case 4:
			case 6:
			case 9:
			case 11:
				return 30;

			case 2:
				return IsLeapYear(nYear) ? 29 : 28;
		}
		return 31;
	}

	// Returns the digit at the given position (0 or 1) for the maximum value of the month allowed.
	TCHAR CAMSEdit::DateBehavior::GetMaxMonthDigit(int nPos) const
	{
		assert(nPos >= 0 && nPos <= 1);

		int nYear = GetValidYear();
		int nMaxMonth = m_dateMax.GetMonth();
		int nMaxYear = m_dateMax.GetYear();

		// First digit
		if (nPos == 0)
		{
			// If the year is at the max, then use the first digit of the max month
			if (nYear == nMaxYear)
				return GetString(nMaxMonth)[0];

			// Otherwise, it's always '1'
			return _T('1');
		}

		// Second digit
		SStringT strText = m_pEdit->GetWindowText();
		TCHAR cFirstDigit = (strText.GetLength() > GetMonthStartPosition()) ? strText[GetMonthStartPosition()] : _T('0');
		assert(cFirstDigit);  // must have a valid first digit at this point

		// If the year is at the max, then check if the first digits match
		if (nYear == nMaxYear && (IsValidYear(GetYear()) || nMaxYear == m_dateMin.GetYear()))
		{
			// If the first digits match, then use the second digit of the max month
			if (GetString(nMaxMonth)[0] == cFirstDigit)
				return GetString(nMaxMonth)[1];

			// Assuming the logic for the first digit is correct, then it must be '0'
			assert(cFirstDigit == _T('0'));
			return _T('9');  
		}

		// Use the first digit to determine the second digit's max
		return (cFirstDigit == _T('1') ? _T('2') : _T('9'));
	}

	// Returns the digit at the given position (0 or 1) for the minimum value of the month allowed.
	TCHAR CAMSEdit::DateBehavior::GetMinMonthDigit(int nPos) const
	{
		assert(nPos >= 0 && nPos <= 1);

		int nYear = GetValidYear();
		int nMinMonth = m_dateMin.GetMonth();
		int nMinYear = m_dateMin.GetYear();

		// First digit
		if (nPos == 0)
		{
			// If the year is at the min, then use the first digit of the min month
			if (nYear == nMinYear)
				return GetString(nMinMonth)[0];

			// Otherwise, it's always '0'
			return _T('0');
		}

		// Second digit
		SStringT strText = m_pEdit->GetWindowText();
		TCHAR cFirstDigit = (strText.GetLength() > GetMonthStartPosition()) ? strText[GetMonthStartPosition()] : _T('0');
		if (!cFirstDigit)
			return _T('1');

		// If the year is at the max, then check if the first digits match
		if (nYear == nMinYear && (IsValidYear(GetYear()) || nMinYear == m_dateMax.GetYear()))
		{
			// If the first digits match, then use the second digit of the max month
			if (GetString(nMinMonth)[0] == cFirstDigit)
				return GetString(nMinMonth)[1];

			return _T('0');  
		}

		// Use the first digit to determine the second digit's min
		return (cFirstDigit == _T('1') ? _T('0') : _T('1'));
	}

	// Returns true if the digit at the given position (0 or 1) is within the allowed range for the month.
	bool CAMSEdit::DateBehavior::IsValidMonthDigit(TCHAR c, int nPos) const
	{
		return (c >= GetMinMonthDigit(nPos) && c <= GetMaxMonthDigit(nPos));
	}

	// Returns true if the given month is valid and falls within the range.
	bool CAMSEdit::DateBehavior::IsValidMonth(int nMonth) const
	{
		int nYear = GetValidYear();
		int nDay = GetValidDay();
		return IsWithinRange(CDuiDateTime(nYear, nMonth, nDay, 0, 0, 0));
	}

	// Returns the digit at the given position (0 or 1) for the maximum value of the day allowed.
	TCHAR CAMSEdit::DateBehavior::GetMaxDayDigit(int nPos) const
	{
		assert(nPos >= 0 && nPos <= 1);

		int nMonth = GetValidMonth();
		int nYear = GetValidYear();
		int nMaxDay = m_dateMax.GetDay();
		int nMaxMonth = m_dateMax.GetMonth();
		int nMaxYear = m_dateMax.GetYear();

		// First digit
		if (nPos == 0)
		{
			// If the year and month are at the max, then use the first digit of the max day
			if (nYear == nMaxYear && nMonth == nMaxMonth)
				return GetString(nMaxDay)[0];
			return GetString(GetMaxDayOfMonth(nMonth, nYear))[0];
		}

		// Second digit
		SStringT strText = m_pEdit->GetWindowText();
		TCHAR cFirstDigit = (strText.GetLength() > GetDayStartPosition()) ? strText[GetDayStartPosition()] : '0';
		assert(cFirstDigit);  // must have a valid first digit at this point

		// If the year and month are at the max, then use the second digit of the max day
		if (nYear == nMaxYear && nMonth == nMaxMonth && GetString(nMaxDay)[0] == cFirstDigit)
			return GetString(nMaxDay)[1];

		if (cFirstDigit == _T('0') || 
			cFirstDigit == _T('1') || 
			(cFirstDigit == _T('2') && nMonth != 2) || 
			(nMonth == 2 && !IsValidYear(GetYear())))
			return _T('9');
		return GetString(GetMaxDayOfMonth(nMonth, nYear))[1];
	}

	// Returns the digit at the given position (0 or 1) for the minimum value of the day allowed.
	TCHAR CAMSEdit::DateBehavior::GetMinDayDigit(int nPos) const
	{
		assert(nPos >= 0 && nPos <= 1);

		int nMonth = GetValidMonth();
		int nYear = GetValidYear();
		int nMinDay = m_dateMin.GetDay();
		int nMinMonth = m_dateMin.GetMonth();
		int nMinYear = m_dateMin.GetYear();

		// First digit
		if (nPos == 0)
		{
			// If the year and month are at the min, then use the first digit of the min day
			if (nYear == nMinYear && nMonth == nMinMonth)
				return GetString(nMinDay)[0];
			return _T('0');
		}

		// Second digit
		SStringT strText = m_pEdit->GetWindowText();
		TCHAR cFirstDigit = (strText.GetLength() > GetDayStartPosition()) ? strText[GetDayStartPosition()] : _T('0');
		if (!cFirstDigit)  // must have a valid first digit at this point
			return _T('1');

		// If the year and month are at the max, then use the first second of the max day
		if (nYear == nMinYear && nMonth == nMinMonth && GetString(nMinDay)[0] == cFirstDigit)
			return GetString(nMinDay)[1];

		// Use the first digit to determine the second digit's min
		return (cFirstDigit == _T('0') ? _T('1') : _T('0'));
	}

	// Returns true if the digit at the given position (0 or 1) is within the allowed range for the day.
	bool CAMSEdit::DateBehavior::IsValidDayDigit(TCHAR c, int nPos) const
	{
		return (c >= GetMinDayDigit(nPos) && c <= GetMaxDayDigit(nPos));
	}

	// Returns true if the given day is valid and falls within the range.
	bool CAMSEdit::DateBehavior::IsValidDay(int nDay) const
	{
		return IsWithinRange(CDuiDateTime(GetValidYear(), GetValidMonth(), nDay, 0, 0, 0));
	}

	// Returns true if the given year is valid and falls within the range.
	bool CAMSEdit::DateBehavior::IsValidYear(int nYear) const
	{
		return (nYear >= m_dateMin.GetYear() && nYear <= m_dateMax.GetYear());
	}

	// Adjusts the month (to the minimum) if not valid; otherwise adjusts the day (to the maximum) if not valid.
	bool CAMSEdit::DateBehavior::AdjustMaxMonthAndDay()
	{
		int nMonth = GetMonth();	
		if (nMonth && !IsValidMonth(nMonth))
		{
			SetMonth(GetMinMonth());  // this adjusts the day automatically
			return true;
		}

		return AdjustMaxDay();
	}

	// Adjusts the day (to the maximum) if not valid.
	bool CAMSEdit::DateBehavior::AdjustMaxDay()
	{
		int nDay = GetDay();
		if (nDay && !IsValidDay(nDay))
		{
			SetDay(GetMaxDay());
			return true;
		}
		
		return false;	// nothing had to be adjusted
	}

	// Returns the digit at the given position (0 to 3) for the maximum value of the year allowed.
	TCHAR CAMSEdit::DateBehavior::GetMaxYearDigit(int nPos) const
	{
		assert(nPos >= 0 && nPos <= 3);

		SStringT strYear = GetString(GetYear(), false);
		SStringT strMaxYear = GetString(m_dateMax.GetYear(), false);

		if (nPos == 0 || _ttoi(strMaxYear.Left(nPos)) <= _ttoi(strYear.Left(nPos)))
			return strMaxYear[nPos];
		return _T('9');
	}

	// Returns the digit at the given position (0 to 3) for the minimum value of the year allowed.
	// If bValidYear is true, the current year is made sure to be valid.
	TCHAR CAMSEdit::DateBehavior::GetMinYearDigit(int nPos, bool bValidYear /*= false*/) const
	{
		assert(nPos >= 0 && nPos <= 3);

		int nYear = GetYear();
		if (!IsValidYear(nYear) && bValidYear)
			nYear = GetValidYear();

		SStringT strYear = GetString(nYear, false);
		SStringT strMinYear = GetString(m_dateMin.GetYear(), false);

		if (nPos == 0 || _ttoi(strMinYear.Left(nPos)) >= _ttoi(strYear.Left(nPos)))
			return strMinYear[nPos];
		
		if(bValidYear)
			return strMinYear[nPos];

		return _T('0');
	}

	// Returns true if the digit at the given position (0 to 3) is within the allowed range for the year.
	bool CAMSEdit::DateBehavior::IsValidYearDigit(TCHAR c, int nPos) const
	{
		return (c >= GetMinYearDigit(nPos) && c <= GetMaxYearDigit(nPos));
	}

	// Returns the month currently shown on the control or 0.
	int CAMSEdit::DateBehavior::GetMonth() const
	{
		SStringT strText = m_pEdit->GetWindowText();

		int nStartPos = GetMonthStartPosition();
		if (strText.GetLength() >= nStartPos + 2)
			return _ttoi(strText.Mid(nStartPos, 2));
		return 0;
	}

	// Returns the current month as a valid value.  
	// If it is less than the minimum allowed, the minimum is returned; 
	// if it is more than the maximum allowed, the maximum is returned.
	int CAMSEdit::DateBehavior::GetValidMonth() const
	{
		int nMonth = GetMonth();
		
		// It it's outside the range, fix it
		if (nMonth < GetMinMonth())
			nMonth = GetMinMonth();
		else if (nMonth > GetMaxMonth())
			nMonth = GetMaxMonth();

		return nMonth;
	}

	// Returns the day currently shown on the control or 0.
	int CAMSEdit::DateBehavior::GetDay() const
	{
		SStringT strText = m_pEdit->GetWindowText();

		int nStartPos = GetDayStartPosition();
		if (strText.GetLength() >= nStartPos + 2)
			return _ttoi(strText.Mid(nStartPos, 2));
		return 0;
	}

	// Returns the current day as a valid value.  
	// If it is less than the minimum allowed, the minimum is returned; 
	// if it is more than the maximum allowed, the maximum is returned.
	int CAMSEdit::DateBehavior::GetValidDay() const
	{
		int nDay = GetDay();

		// It it's outside the range, fix it
		if (nDay < GetMinDay())
			nDay = GetMinDay();
		else if (nDay > GetMaxDay())
			nDay = GetMaxDay();

		return nDay;
	}

	// Returns the year currently shown on the control or 0.
	int CAMSEdit::DateBehavior::GetYear() const
	{
		SStringT strText = m_pEdit->GetWindowText();

		int nStartPos = GetYearStartPosition();
		if (strText.GetLength() > 0)
			return _ttoi(strText.Mid(nStartPos, 4));
		return 0;
	}

	// Returns the current year as a valid value.  
	// If it is less than the minimum allowed, the minimum is returned; 
	// if it is more than the maximum allowed, the maximum is returned.
	int CAMSEdit::DateBehavior::GetValidYear() const
	{
		CDuiDateTime datetime;
		int nYear = GetYear();
		if (nYear < m_dateMin.GetYear())
		{
			nYear = datetime.GetYear();
			if (nYear < m_dateMin.GetYear())
				nYear = m_dateMin.GetYear();
		}
		if (nYear > m_dateMax.GetYear())
			nYear = m_dateMax.GetYear();

		return nYear;
	}

	// Sets the control's month to the given value, which must be valid.
	void CAMSEdit::DateBehavior::SetMonth(int nMonth)
	{
		SelectionSaver selection = m_pEdit;	// remember the current selection
		
		if (GetMonth() > 0)		// see if there's already a month
			m_pEdit->SetSel(GetMonthStartPosition(), GetMonthStartPosition() + 3);

		SStringT strText;
		strText.Format(_T("%02d%c"), nMonth, m_cSep);
		m_pEdit->ReplaceSel(strText, TRUE);	// set the month

		AdjustMaxDay();	// adjust the day if it's out of range
		assert(IsValidMonth(nMonth));
	}

	// Sets the control's day to the given value, which must be valid.
	void CAMSEdit::DateBehavior::SetDay(int nDay)
	{
		assert(IsValidDay(nDay));

		SelectionSaver selection = m_pEdit;	// remember the current selection
		
		if (GetDay() > 0)		// see if there's already a day
			m_pEdit->SetSel(GetDayStartPosition(), GetDayStartPosition() + 3);

		SStringT strText;
		strText.Format(_T("%02d%c"), nDay, m_cSep);

		m_pEdit->ReplaceSel(strText, TRUE);	// set the day
	}

	// Sets the control's year to the given value, which must be valid.
	void CAMSEdit::DateBehavior::SetYear(int nYear)
	{
		assert(IsValidYear(nYear));

		SelectionSaver selection = m_pEdit;	// remember the current selection

		if (GetYear() > 0)		// see if there's already a year
			m_pEdit->SetSel(GetYearStartPosition(), GetYearStartPosition() + 4);

		SStringT strText;
		strText.Format(_T("%4d"), nYear);
		m_pEdit->ReplaceSel(strText, TRUE);	// set the year
		
		AdjustMaxMonthAndDay();	// adjust the month and/or day if they're out of range
	}

	// Returns the date on the control as a CDuiDateTime object.
	CDuiDateTime CAMSEdit::DateBehavior::GetDate() const
	{
		return CDuiDateTime(GetYear(), GetMonth(), GetDay(), 0, 0, 0);
	}
	 

	// Sets the month, day, and year on the control to the given values, which must be valid.
	void CAMSEdit::DateBehavior::SetDate(int nYear, int nMonth, int nDay)
	{ 
		m_pEdit->SetWindowText(GetFormattedDate(nYear, nMonth, nDay));
	}
	  
	void CAMSEdit::DateBehavior::SetDate(CDuiDateTime &dattime)
	{
		SetDate(dattime.GetYear(),dattime.GetMonth(),dattime.GetDay());	
	}

	// Sets the month, day, and year on the control to today's date.
	void CAMSEdit::DateBehavior::SetDateToToday()
	{
		CDuiDateTime dattime;
		SetDate(dattime);
	}

	// Returns true if the given year is a leap year.
	bool CAMSEdit::DateBehavior::IsLeapYear(int nYear)
	{
		return (nYear & 3) == 0 && (nYear % 100 != 0 || nYear % 400 == 0); 
	}

	// Returns true if the control's date is valid and falls within the allowed range.
	bool CAMSEdit::DateBehavior::IsValid() const
	{
		return IsWithinRange(CDuiDateTime(GetYear(), GetMonth(), GetDay(), 0, 0, 0));
	}

	// Returns true if the control's date is valid and falls within the allowed range.
	// If bShowErrorIfNotValid is true, an error message box is shown and the control gets the focus.
	bool CAMSEdit::DateBehavior::CheckIfValid(bool bShowErrorIfNotValid /*= true*/)
	{
		//if (!m_pEdit->IsEnabled())
		if (m_pEdit->GetReadOnly())
			return true;

		bool bValid = IsValid();
		if (!bValid && bShowErrorIfNotValid)
		{ 
		}
		
		return bValid;
	}
 
	// Sets the range of allowed date values to the given minimum and maximum CDuiDateTime values.
	void CAMSEdit::DateBehavior::SetRange(const CDuiDateTime& dateMin, const CDuiDateTime& dateMax)
	{
		assert(dateMin >= AMS_MIN_CTIME);
		assert(dateMax <= AMS_MAX_CTIME);
		assert(dateMin <= dateMax);

		m_dateMin.SetDate(dateMin.GetYear(), dateMin.GetMonth(), dateMin.GetDay());
		m_dateMax.SetDate(dateMax.GetYear(), dateMax.GetMonth(), dateMax.GetDay());

		_Redraw();
	}
	 

	// Retrieves the range of allowed date values inside the given set of CDuiDateTime pointers.
	void CAMSEdit::DateBehavior::GetRange(CDuiDateTime* pDateMin, CDuiDateTime* pDateMax) const
	{
		if (pDateMin)
			*pDateMin = CDuiDateTime(m_dateMin.GetYear(), m_dateMin.GetMonth(), m_dateMin.GetDay(), 0, 0, 0);
		if (pDateMax)
			*pDateMax = CDuiDateTime(m_dateMax.GetYear(), m_dateMax.GetMonth(), m_dateMax.GetDay(), 0, 0, 0);
	}
	 

	// Returns true if the given date is valid and falls within the range.
	bool CAMSEdit::DateBehavior::IsWithinRange(const CDuiDateTime& date, bool /*= true*/) const
	{
		return (date.IsValid() && date >= m_dateMin && date <= m_dateMax);
	}

	// Sets the character used to separate the month, day, and year values.
	void CAMSEdit::DateBehavior::SetSeparator(TCHAR cSep)
	{
		assert(cSep);
		assert(!_istdigit(cSep));

		if (m_cSep != cSep)
		{
			m_cSep = cSep;
			_Redraw();
		}
	}

	// Returns the character used to separate the month, day, and year values.
	TCHAR CAMSEdit::DateBehavior::GetSeparator() const
	{
		return m_cSep;
	} 

	// Returns the control's value in a valid format.
	SStringT CAMSEdit::DateBehavior::_GetValidText() 
	{
		SStringT strText = m_pEdit->GetWindowText();

		if (strText.IsEmpty())
			return strText;

		if (IsValid())
			return GetFormattedDate(GetYear(), GetMonth(), GetDay());

		// If the date is empty, try using today
		if (GetYear() == 0 && GetMonth() == 0 && GetDay() == 0)
			((CAMSEdit::DateBehavior*)this)->SetDateToToday();

		int nYear = GetValidYear();
		int nMonth = GetValidMonth();
		int nDay = GetValidDay();

		if (!IsWithinRange(CDuiDateTime(nYear, nMonth, nDay, 0, 0, 0)))
			nMonth = GetMinMonth();

		if (!IsWithinRange(CDuiDateTime(nYear, nMonth, nDay, 0, 0, 0)))
			nDay = GetMaxDay();

		return GetFormattedDate(nYear, nMonth, nDay);
	}

	// Formats the given year, month, and day values into a string based on the proper format.
	SStringT CAMSEdit::DateBehavior::GetFormattedDate(int nYear, int nMonth, int nDay) const
	{
		SStringT strText;	
		strText.Format(_T("%4d%c%02d%c%02d"),nYear,m_cSep, nMonth, m_cSep, nDay);

		return strText;
	}
  
	/////////////////////////////////////////////////////////////////////////////
	// CAMSEdit::TimeBehavior

	#define AMS_DEFAULT_DATE		1899, 12, 30

	// Constructs the object with the given control.
	CAMSEdit::TimeBehavior::TimeBehavior() :
		m_timeMin(AMS_DEFAULT_DATE, 0, 0, 0),
		m_timeMax(AMS_DEFAULT_DATE, 23, 59, 59),
		m_cSep(':'),
		m_strAM(AMS_AM_SYMBOL),
		m_strPM(AMS_PM_SYMBOL),
		m_nAMPMLength(m_strAM.GetLength()),
		m_nHourStart(0)
	{
		// Get the system's time separator
		if (::GetLocaleInfo(LOCALE_USER_DEFAULT, LOCALE_STIME, NULL, 0))
			::GetLocaleInfo(LOCALE_USER_DEFAULT, LOCALE_STIME, &m_cSep, sizeof(m_cSep));

		// Determine if it's in 24-hour format
		TCHAR szBuffer[3];
		if (::GetLocaleInfo(LOCALE_USER_DEFAULT, LOCALE_ITIME, NULL, 0))
		{
			::GetLocaleInfo(LOCALE_USER_DEFAULT, LOCALE_ITIME, szBuffer, sizeof(szBuffer));
			if (_ttoi(szBuffer))
				m_uFlags |= TwentyFourHourFormat;
		}

		// Get the AM symbol
		if (::GetLocaleInfo(LOCALE_USER_DEFAULT, LOCALE_S1159, NULL, 0))
		{
			::GetLocaleInfo(LOCALE_USER_DEFAULT, LOCALE_S1159, szBuffer, sizeof(szBuffer));
			m_strAM = szBuffer;
		}

		// Get the PM symbol
		if (::GetLocaleInfo(LOCALE_USER_DEFAULT, LOCALE_S2359, NULL, 0))
		{
			::GetLocaleInfo(LOCALE_USER_DEFAULT, LOCALE_S2359, szBuffer, sizeof(szBuffer));
			m_strPM = szBuffer;
		}

		m_nAMPMLength = m_strAM.GetLength();

		// Verify the lengths are the same; otherwise use the default
		if (m_nAMPMLength == 0 || m_nAMPMLength != m_strPM.GetLength())
		{
			m_strAM = AMS_AM_SYMBOL;
			m_strPM = AMS_PM_SYMBOL;
			m_nAMPMLength = m_strAM.GetLength();
		}
	}

	void CAMSEdit::TimeBehavior::SetEdit(CAMSEdit* pEdit)
	{
		Behavior::SetEdit(pEdit);
	}

	// Handles the WM_CHAR message, which is called when the user enters a regular character or Backspace
	void CAMSEdit::TimeBehavior::_OnChar(UINT uChar,bool &bHandled) 
	{
		// Check to see if it's read only
		if (m_pEdit->GetReadOnly())
			return;

		TCHAR c = static_cast<TCHAR>(uChar);
		
		long nStart = 0, nEnd = 0;
		m_pEdit->GetSel(nStart, nEnd);
		
		SStringT strText = m_pEdit->GetWindowText();
		int nLen = strText.GetLength();
		
		// Check for a non-printable character (such as Ctrl+C)
		if (!_istprint(c))
		{
			if (c == VK_BACK && nStart != nLen)
			{
				m_pEdit->SSendMessage(WM_KEYDOWN, VK_LEFT); // move the cursor left 
				return;
			}
			
			// Allow backspace only if the cursor is all the way to the right
			if (_ShouldEnter(c))
				Behavior::_OnChar(uChar,bHandled);
			return;
		}
		
		// Add the digit depending on its location
		if (nStart == m_nHourStart)		// FIRST DIGIT
		{
			if (IsValidHourDigit(c, 0) && _ShouldEnter(c))
			{
				if (nLen > nStart)
				{
					m_pEdit->SetSel(nStart, nStart + 1);
					m_pEdit->ReplaceSel(SStringT(c), true);
					
					if (nLen > nStart + 1)
					{
						// If the second digit is no longer valid, correct and select it
						if (!IsValidHour(GetHour()))
						{
							m_pEdit->SetSel(nStart + 1, nStart + 2);
							m_pEdit->ReplaceSel(SStringT(GetMinHourDigit(1)), true);
							m_pEdit->SetSel(nStart + 1, nStart + 2);
						}
					}
				}
				else
					Behavior::_OnChar(uChar,bHandled);
			}
			else if (nLen == nStart && IsValidHourDigit(c, 1) && _ShouldEnter(c))
			{
				m_pEdit->SetSel(nStart, nStart + 2);
				m_pEdit->ReplaceSel(SStringT(_T('0')) + SStringT(c), true);					
			}
			else
				ChangeAMPM(c);	// allow changing AM/PM (if it's being shown) by pressing A or P
		}

		else if (nStart == m_nHourStart + 1)	// SECOND DIGIT
		{
			if (IsValidHourDigit(c, 1) && _ShouldEnter(c))
			{
				if (nLen > nStart)
				{
					m_pEdit->SetSel(nStart, nStart + 1);
					m_pEdit->ReplaceSel(SStringT(c), true);					
				}
				else
					Behavior::_OnChar(uChar,bHandled);
			}
			else if (c == m_cSep && nLen == nStart && IsValidHour(_ttoi(SStringT(SStringT('0') + SStringT(strText[m_nHourStart])))) && _ShouldEnter(c))
			{
				m_pEdit->SetSel(m_nHourStart, nStart);
				m_pEdit->ReplaceSel(SStringT('0') + SStringT(strText[m_nHourStart]) + SStringT(c), true);					
			}
			else
				ChangeAMPM(c);	// allow changing AM/PM (if it's being shown) by pressing A or P
		}
		
		else if (nStart == m_nHourStart + 2)	// FIRST COLON
		{
			int nColon = 0;
			if (c == m_cSep)
				nColon = 1;
			else
				nColon = (IsValidMinuteDigit(c, 0) ? 2 : 0);
			
			// If we need the colon, enter it
			if (nColon && _ShouldEnter(c))
			{
				m_pEdit->SetSel(nStart, nStart + 1);
				m_pEdit->ReplaceSel(SStringT(m_cSep), true);
			}
			
			// If the colon is to be preceded by a valid digit, "type" it in.
			if (nColon == 2)
				keybd_event((BYTE)c, 0, 0, 0);
			else
				ChangeAMPM(c);	// allow changing AM/PM (if it's being shown) by pressing A or P
		}
				
		else if (nStart == m_nHourStart + 3)	// THIRD DIGIT
		{
			if (IsValidMinuteDigit(c, 0) && _ShouldEnter(c))
			{
				if (nLen > nStart)
				{
					m_pEdit->SetSel(nStart, nStart + 1);
					m_pEdit->ReplaceSel(SStringT(c), true);
					
					if (nLen > nStart + 1)
					{
						if (!IsValidMinute(GetMinute()))
						{
							m_pEdit->SetSel(nStart + 1, nStart + 2);
							m_pEdit->ReplaceSel(SStringT(GetMinMinuteDigit(1)), true);
							m_pEdit->SetSel(nStart + 1, nStart + 2);
						}
					}
				}
				else
					Behavior::_OnChar(uChar,bHandled);
			}
			else
				ChangeAMPM(c);	// allow changing AM/PM (if it's being shown) by pressing A or P
		}
		
		else if (nStart == m_nHourStart + 4)	// FOURTH DIGIT
		{
			if (IsValidMinuteDigit(c, 1) && _ShouldEnter(c))
			{
				if (nLen > nStart)
				{
					m_pEdit->SetSel(nStart, nStart + 1);
					m_pEdit->ReplaceSel(SStringT(c), true);
				}
				else
					Behavior::_OnChar(uChar,bHandled);
				
				// Show the AM/PM symbol if we're not showing seconds
				if (!IsShowingSeconds())
					ShowAMPM();
			}				
			else
				ChangeAMPM(c);	// allow changing AM/PM (if it's being shown) by pressing A or P
		}
				
		else if (nStart == m_nHourStart + 5)	// SECOND COLON	OR FIRST SPACE (seconds' first digit or AM/PM)
		{
			if (IsShowingSeconds())
			{
				int nColon = 0;
				if (c == m_cSep)
					nColon = 1;
				else
					nColon = (IsValidSecondDigit(c, 0) ? 2 : 0);
				
				// If we need the slash, enter it
				if (nColon && _ShouldEnter(c))
				{					
					int nReplace = (nStart < nLen && strText[nStart] != _T(' '));
					m_pEdit->SetSel(nStart, nStart + nReplace);
					m_pEdit->ReplaceSel(SStringT(m_cSep), true);
				}
				
				// If the colon is to be preceded by a valid digit, "type" it in.
				if (nColon == 2)
					keybd_event((BYTE)c, 0, 0, 0);
			}
			else if (!IsShowing24HourFormat())
			{
				if (c == _T(' '))
				{
					m_pEdit->SetSel(nStart, nStart + 1);
					m_pEdit->ReplaceSel(SStringT(c),true);
				}
				ShowAMPM();
			}

			ChangeAMPM(c);	// allow changing AM/PM (if it's being shown) by pressing A or P
		}

		else if (nStart == m_nHourStart + 6)	// FIFTH DIGIT - first digit of seconds or AM/PM
		{
			if (IsShowingSeconds())
			{
				if (IsValidSecondDigit(c, 0) && _ShouldEnter(c))
				{
					if (nLen > nStart)
					{
						int nReplace = (nStart < nLen && strText[nStart] != _T(' '));
						m_pEdit->SetSel(nStart, nStart + nReplace);
						m_pEdit->ReplaceSel(SStringT(c),true);
					}
					else
						Behavior::_OnChar(uChar,bHandled);
				}
			}
			
			ChangeAMPM(c);	// allow changing AM/PM (if it's being shown) by pressing A or P
		}

		else if (nStart == m_nHourStart + 7)	// SIXTH DIGIT - second digit of seconds or AM/PM
		{
			if (IsShowingSeconds())
			{
				if (IsValidSecondDigit(c, 1) && _ShouldEnter(c))
				{
					if (nLen > nStart)
					{
						int nReplace = (nStart < nLen && strText[nStart] != _T(' '));
						m_pEdit->SetSel(nStart, nStart + nReplace);
						m_pEdit->ReplaceSel(SStringT(c), true);
					}
					else
						Behavior::_OnChar(uChar,bHandled);

					// Show the AM/PM symbol if we're not in 24-hour format
					ShowAMPM();
				}
			}

			ChangeAMPM(c);	// allow changing AM/PM (if it's being shown) by pressing A or P
		}
			
		else if (nStart == m_nHourStart + 8)	// FIRST SPACE (with seconds showing)
		{
			if (IsShowingSeconds() && !IsShowing24HourFormat())
			{
				if (c == _T(' '))
				{
					m_pEdit->SetSel(nStart, nStart + 1);
					m_pEdit->ReplaceSel(SStringT(c), true);
					ShowAMPM();
				}
			} 

			ChangeAMPM(c);	// allow changing AM/PM (if it's being shown) by pressing A or P
		}

		else 		// AM/PM
			ChangeAMPM(c);
	}

	// Handles the WM_KEYDOWN message, which is called when the user enters a special character such as Delete or the arrow keys.
	void CAMSEdit::TimeBehavior::_OnKeyDown(UINT uChar,bool &bHandled) 
	{
		// Check to see if it's read only
		if (m_pEdit->GetReadOnly())
			return;

		switch (uChar)
		{
			case VK_DELETE:
			{
				// If deleting make sure it's the last character or that
				// the selection goes all the way to the end of the text
				
				long nStart = 0, nEnd = 0;
				m_pEdit->GetSel(nStart, nEnd);
				
				SStringT strText = m_pEdit->GetWindowText();
				int nLen = strText.GetLength();
				
				if(nEnd -nStart >=  nLen)
				{ 
					bHandled =false;	 
				}
				else if (nEnd != nLen)
				{
					if (!(nEnd == nStart && nEnd == nLen - 1))
						return;
				}
				break;
			}
				
			case VK_UP:
			{
				// If pressing the UP arrow, increment the corresponding value.
				
				long nStart=0, nEnd=0;
				m_pEdit->GetSel(nStart, nEnd);
				
				if (nStart >= GetHourStartPosition() && nStart <= GetHourStartPosition() + 2)
				{
					int nHour = GetHour();
					if (nHour >= GetMinHour())
					{
						// Handle moving up through the noon hour
						SStringT strAMPM = GetAMPM();
						if (IsValidAMPM(strAMPM))
						{
							if (nHour == 11)
							{
								if (strAMPM == m_strPM)  // stop at midnight
									return;
								SetAMPM(false); 
							}
							else if (nHour == 12)
								nHour = 0;
						}

						if (nHour < GetMaxHour())
							SetHour(++nHour);
					}
				}			
				else if (nStart >= GetMinuteStartPosition() && nStart <= GetMinuteStartPosition() + 2)
				{
					int nMinute = GetMinute();
					if (nMinute >= GetMinMinute() && nMinute < GetMaxMinute())
						SetMinute(++nMinute);
				}
				else if (nStart >= GetAMPMStartPosition() && nStart <= GetAMPMStartPosition() + m_nAMPMLength)
				{
					SStringT strAMPM = GetAMPM();
					SetAMPM(!IsValidAMPM(strAMPM) || strAMPM == m_strPM);
				}
				else if (nStart >= GetSecondStartPosition() && nStart <= GetSecondStartPosition() + 2)
				{
					int nSecond = GetSecond();
					if (nSecond >= GetMinSecond() && nSecond < GetMaxSecond())
						SetSecond(++nSecond);
				}

				return;
			}
				
			case VK_DOWN:
			{
				// If pressing the DOWN arrow, decrement the corresponding value.
				
				long nStart = 0, nEnd = 0;
				m_pEdit->GetSel(nStart, nEnd);
				
				if (nStart >= GetHourStartPosition() && nStart <= GetHourStartPosition() + 2)
				{
					int nHour = GetHour();
					if (nHour <= GetMaxHour())
					{
						// Handle moving up through the noon hour
						SStringT strAMPM = GetAMPM();
						if (IsValidAMPM(strAMPM))
						{
							if (nHour == 12)
							{
								if (strAMPM == m_strAM)	// stop at midnight
									return;
								SetAMPM(true);
							}
							else if (nHour == 1)
								nHour = 13;
						}

						if (nHour > GetMinHour())
							SetHour(--nHour);
					}
				}			
				else if (nStart >= GetMinuteStartPosition() && nStart <= GetMinuteStartPosition() + 2)
				{
					int nMinute = GetMinute();
					if (nMinute > GetMinMinute() && nMinute <= GetMaxMinute())
						SetMinute(--nMinute);
				}
				else if (nStart >= GetAMPMStartPosition() && nStart <= GetAMPMStartPosition() + m_nAMPMLength)
				{
					SStringT strAMPM = GetAMPM();
					SetAMPM(!IsValidAMPM(strAMPM) || strAMPM == m_strPM);
				}
				else if (nStart >= GetSecondStartPosition() && nStart <= GetSecondStartPosition() + 2)
				{
					int nSecond = GetSecond();
					if (nSecond > GetMinSecond() && nSecond <= GetMaxSecond())
						SetSecond(--nSecond);
				}
				return;
			}
		}
		
		Behavior::_OnKeyDown(uChar,bHandled);
	}

	// Handles the WM_KILLFOCUS message, which is called when the user leaves the control.
	// It's used here to check if any action needs to be taken based on the control's value.
	void CAMSEdit::TimeBehavior::_OnKillFocus(bool &bHandled) 
	{
		Behavior::_OnKillFocus(bHandled);
 

		SStringT strText = m_pEdit->GetWindowText();

		// If it's empty, take action based on the flag
		if (strText.IsEmpty())
		{ 
			AdjustWithinRange();  
			return;
		}
			
		if (!IsValid())
		{ 
			AdjustWithinRange(); 
		}
	}

	// Returns the zero-based position of the hour inside the control.
	int CAMSEdit::TimeBehavior::GetHourStartPosition() const
	{
		return m_nHourStart;
	}

	// Returns the zero-based position of the minute inside the control.
	int CAMSEdit::TimeBehavior::GetMinuteStartPosition() const
	{
		return m_nHourStart + 3;
	}

	// Returns the zero-based position of the second inside the control.
	int CAMSEdit::TimeBehavior::GetSecondStartPosition() const
	{
		return m_nHourStart + 6;
	}

	// Returns the zero-based position of the AM/PM symbols inside the control.
	// This is based on whether the seconds are being shown or not.
	int CAMSEdit::TimeBehavior::GetAMPMStartPosition() const
	{
		return m_nHourStart + (IsShowingSeconds() ? 9 : 6);
	}

	// Returns the maximum value for the hour based on whether we're in 24-Hour format (or b24HourFormat is true) or not.
	// Note: This value is not based on the allowed range.
	int CAMSEdit::TimeBehavior::GetMaxHour(bool b24HourFormat /*= false*/) const
	{
		return (b24HourFormat || IsShowing24HourFormat()) ? 23 : 12;
	}

	// Returns the minimum value for the hour based on whether we're in 24-Hour format (or b24HourFormat is true) or not.
	// Note: This value is not based on the allowed range.
	int CAMSEdit::TimeBehavior::GetMinHour(bool b24HourFormat /*= false*/) const
	{
		return (b24HourFormat || IsShowing24HourFormat()) ? 0 : 1;
	}

	// Returns the maximum value for the minute.
	// Note: This value is not based on the allowed range.
	int CAMSEdit::TimeBehavior::GetMaxMinute() const
	{
		return 59;
	}

	// Returns the minimum value for the minute.
	// Note: This value is not based on the allowed range.
	int CAMSEdit::TimeBehavior::GetMinMinute() const
	{
		return 0;
	}

	// Returns the maximum value for the second.
	// Note: This value is not based on the allowed range.
	int CAMSEdit::TimeBehavior::GetMaxSecond() const
	{
		return 59;
	}

	// Returns the minimum value for the second.
	// Note: This value is not based on the allowed range.
	int CAMSEdit::TimeBehavior::GetMinSecond() const
	{
		return 0;
	}

	// Returns the digit at the given position (0 or 1) for the maximum value of the hour.
	TCHAR CAMSEdit::TimeBehavior::GetMaxHourDigit(int nPos) const
	{
		assert(nPos >= 0 && nPos <= 1);

		// First digit
		if (nPos == 0)
			return IsShowing24HourFormat() ? '2' : '1';

		// Second digit
		SStringT strText = m_pEdit->GetWindowText();
		TCHAR cFirstDigit = (strText.GetLength() > GetHourStartPosition()) ? strText[GetHourStartPosition()] : '0';
		assert(cFirstDigit);  // must have a valid first digit at this point

		// Use the first digit to determine the second digit's max
		if (cFirstDigit == '2')
			return '3';
		if (cFirstDigit == '1' && !IsShowing24HourFormat())
			return '2';
		return '9';
	}

	// Returns the digit at the given position (0 or 1) for the minimum value of the hour.
	TCHAR CAMSEdit::TimeBehavior::GetMinHourDigit(int nPos) const
	{
		assert(nPos >= 0 && nPos <= 1);

		// First digit
		if (nPos == 0)
			return '0';

		// Second digit
		SStringT strText = m_pEdit->GetWindowText();
		TCHAR cFirstDigit = (strText.GetLength() > GetHourStartPosition()) ? strText[GetHourStartPosition()] : '0';
		assert(cFirstDigit);  // must have a valid first digit at this point

		// If the first digit is a 0 and we're not in 24-hour format, don't allow 0
		if (cFirstDigit == '0' && !IsShowing24HourFormat())
			return '1';

		// For all other cases it's always 0
		return '0';
	}

	// Returns true if the digit at the given position (0 or 1) is valid for the hour.
	bool CAMSEdit::TimeBehavior::IsValidHourDigit(TCHAR c, int nPos) const
	{
		return (c >= GetMinHourDigit(nPos) && c <= GetMaxHourDigit(nPos));
	}

	// Returns true if the given hour is valid.
	// If b24HourFormat is true, the value is checked from 0 to 23 regardless of the format currently being shown.
	bool CAMSEdit::TimeBehavior::IsValidHour(int nHour, bool b24HourFormat /*= false*/) const
	{
		return (nHour >= GetMinHour(b24HourFormat) && nHour <= GetMaxHour(b24HourFormat));
	}

	// Returns the digit at the given position (0 or 1) for the maximum value of the minute.
	TCHAR CAMSEdit::TimeBehavior::GetMaxMinuteDigit(int nPos) const
	{
		assert(nPos >= 0 && nPos <= 1);
		return (nPos == 0 ? '5' : '9');
	}

	// Returns the digit at the given position (0 or 1) for the maximum value of the minute.
	TCHAR CAMSEdit::TimeBehavior::GetMinMinuteDigit(int) const
	{
		return '0';
	}

	// Returns true if the digit at the given position (0 or 1) is valid for the minute.
	bool CAMSEdit::TimeBehavior::IsValidMinuteDigit(TCHAR c, int nPos) const
	{
		return (c >= GetMinMinuteDigit(nPos) && c <= GetMaxMinuteDigit(nPos));
	}

	// Returns true if the given minute is valid.
	bool CAMSEdit::TimeBehavior::IsValidMinute(int nMinute) const
	{
		return (nMinute >= GetMinMinute() && nMinute <= GetMaxMinute());
	}

	// Returns the digit at the given position (0 or 1) for the maximum value of the second.
	TCHAR CAMSEdit::TimeBehavior::GetMaxSecondDigit(int nPos) const
	{
		assert(nPos >= 0 && nPos <= 1);
		return (nPos == 0 ? '5' : '9');
	}

	// Returns the digit at the given position (0 or 1) for the maximum value of the second.
	TCHAR CAMSEdit::TimeBehavior::GetMinSecondDigit(int) const
	{
		return '0';
	}

	// Returns true if the digit at the given position (0 or 1) is valid for the second.
	bool CAMSEdit::TimeBehavior::IsValidSecondDigit(TCHAR c, int nPos) const
	{
		return (c >= GetMinSecondDigit(nPos) && c <= GetMaxSecondDigit(nPos));
	}

	// Returns true if the given second is valid.
	bool CAMSEdit::TimeBehavior::IsValidSecond(int nSecond) const
	{
		return (nSecond >= GetMinSecond() && nSecond <= GetMaxSecond());
	}

	// Shows the AM symbol if not in 24-hour format and they're not already shown.
	void CAMSEdit::TimeBehavior::ShowAMPM()
	{
		if (!IsShowing24HourFormat() && !IsValidAMPM(GetAMPM()))
			SetAMPM(true);
	}

	// Sets the AM or PM symbol if not in 24-hour format.
	void CAMSEdit::TimeBehavior::SetAMPM(bool bAM)
	{
		if (IsShowing24HourFormat())
			return;

		SelectionSaver selection = m_pEdit;	// remember the current selection
		m_pEdit->SetSel(GetAMPMStartPosition() - 1, GetAMPMStartPosition() + m_nAMPMLength);
		
		SStringT strText;
		strText.Format(_T(" %s"), bAM ? m_strAM : m_strPM);
		m_pEdit->ReplaceSel(strText, TRUE);	// set the AM/PM
	}

	// Changes the AM/PM symbol based on the given character (entered by the user).
	bool CAMSEdit::TimeBehavior::ChangeAMPM(TCHAR c)
	{
		if (IsShowing24HourFormat())
			return false;

		SStringT strText = m_pEdit->GetWindowText();
		int nLen = strText.GetLength();

		int nPos = GetAMPMPosition(strText);
		if (nPos == 0)
			return false;

		long nStart = 0, nEnd = 0;
		m_pEdit->GetSel(nStart, nEnd);

		SStringT strAMPM = GetAMPM();
		TCHAR cUpper = static_cast<TCHAR>(_totupper(c));

		switch (cUpper)
		{
			case _T('A'):
			case _T('P'):
				SetAMPM(cUpper == _T('A'));

				if (cUpper == (TCHAR)_totupper(m_strAM[0]) || cUpper == (TCHAR)_totupper(m_strPM[0]))
				{
					// Move the cursor right, if we're in front of the AM/PM symbols
					if (nStart == nPos)
						m_pEdit->SSendMessage(WM_KEYDOWN, VK_RIGHT);

					// Move the cursor right twice, if we're in front of the space in front of the AM/PM symbols
					if (nStart + 1 == nPos)
					{
						m_pEdit->SSendMessage(WM_KEYDOWN, VK_RIGHT);
						m_pEdit->SSendMessage(WM_KEYDOWN, VK_RIGHT);
					}
				}
				return true;

			default:
				// Handle entries after the first character of the AM/PM symbol -- allow the user to enter each character
				if (nStart > nPos)
				{
					// Check if we're adding a character of the AM/PM symbol (after the first one)
					if ((nLen == nStart && !IsValidAMPM(strAMPM)) || (nLen == nEnd && nEnd != nStart))
					{
						const SStringT& strAMPMToUse = _totupper(strText[nPos]) == _totupper(m_strAM[0]) ? m_strAM : m_strPM;
						if (cUpper == (TCHAR)_totupper(strAMPMToUse[nStart - nPos]))
						{
							m_pEdit->ReplaceSel(strAMPMToUse.Mid(nStart - nPos), TRUE);	// set the rest of the AM/PM
							m_pEdit->SetSel(nStart, nStart);  // Reset the selection so that the cursor can be moved
							return ChangeAMPM(c); // move the cursor (below)
						}
					}

					// Check if the AM/PM symbol is OK and we just need to move over one
					if (nLen > nStart && nEnd == nStart && cUpper == (TCHAR)_totupper(strText[nStart]))
					{
						m_pEdit->SSendMessage(WM_KEYDOWN, VK_RIGHT);
						return true;
					}
				}
		}

		return false;
	}

	// Returns the zero-based position of the AM/PM symbol shown on the control.
	int CAMSEdit::TimeBehavior::GetAMPMPosition(const SStringT& strText) const
	{
		int nPos = strText.Find(_T(' ') + m_strAM);
		return ((nPos < 0) ? strText.Find(_T(' ') + m_strPM) : nPos) + 1;
	}

	// Returns true if the given AM/PM symbol is valid.
	bool CAMSEdit::TimeBehavior::IsValidAMPM(const SStringT& strAMPM) const
	{
		return (strAMPM == m_strAM || strAMPM == m_strPM);
	}

	// Returns the hour currently shown on the control or -1.
	int CAMSEdit::TimeBehavior::GetHour() const
	{
		SStringT strText = m_pEdit->GetWindowText();
		
		int nStartPos = GetHourStartPosition();
		if (strText.GetLength() >= nStartPos + 2)
			return _ttoi(strText.Mid(nStartPos, 2));

		return -1;
	}

	// Returns the current hour as a valid value.  
	int CAMSEdit::TimeBehavior::GetValidHour(bool b24HourFormat /*= false*/) const
	{
		int nHour = GetHour();
		
		// It it's outside the range, fix it
		if (nHour < GetMinHour(b24HourFormat))
			nHour = GetMinHour(b24HourFormat);
		else if (nHour > GetMaxHour(b24HourFormat))
			nHour = GetMaxHour(b24HourFormat);
		
		return nHour;
	}

	// Returns the minute currently shown on the control or -1.
	int CAMSEdit::TimeBehavior::GetMinute() const
	{
		SStringT strText = m_pEdit->GetWindowText();
		
		int nStartPos = GetMinuteStartPosition();
		if (strText.GetLength() >= nStartPos + 2)
			return _ttoi(strText.Mid(nStartPos, 2));
		
		return -1;
	}

	// Returns the current minute as a valid value.  
	int CAMSEdit::TimeBehavior::GetValidMinute() const
	{
		int nMinute = GetMinute();
		
		// It it's outside the range, fix it
		if (nMinute < GetMinMinute())
			nMinute = GetMinMinute();
		else if (nMinute > GetMaxMinute())
			nMinute = GetMaxMinute();
		
		return nMinute;
	}

	// Returns the second currently shown on the control or -1.
	int CAMSEdit::TimeBehavior::GetSecond() const
	{
		SStringT strText = m_pEdit->GetWindowText();

		int nStartPos = GetSecondStartPosition();
		if (strText.GetLength() >= nStartPos + 2 && _istdigit(strText[nStartPos]) && _istdigit(strText[nStartPos + 1]))
			return _ttoi(strText.Mid(nStartPos, 2));

		return -1;
	}

	// Returns the current second as a valid value.  
	int CAMSEdit::TimeBehavior::GetValidSecond() const
	{
		int nSecond = GetSecond();
		if (nSecond < GetMinSecond())
			nSecond = GetMinSecond();
		else if (nSecond > GetMaxSecond())
			nSecond = GetMaxSecond();
		
		return nSecond;
	}

	// Returns the AM/PM symbol currently shown on the control or an empty string.
	SStringT CAMSEdit::TimeBehavior::GetAMPM() const
	{
		SStringT strText = m_pEdit->GetWindowText();
		int nPos = GetAMPMPosition(strText);
		if (nPos > 0)
			return strText.Mid(nPos);
		return _T("");
	}

	// Returns the current AM/PM symbol as a valid value.
	SStringT CAMSEdit::TimeBehavior::GetValidAMPM() const
	{
		SStringT strAMPM = GetAMPM();
		if (!IsValidAMPM(strAMPM))
			return m_strAM;			
		
		return strAMPM;
	}

	// Sets the control's hour to the given value, which must be valid.
	void CAMSEdit::TimeBehavior::SetHour(int nHour)
	{
		assert(IsValidHour(nHour, false));
		
		SelectionSaver selection = m_pEdit;	// remember the current selection
		
		if (GetHour() >= 0)		// see if there's already an hour
			m_pEdit->SetSel(GetHourStartPosition(), GetHourStartPosition() + 3);
		
		// Convert it to AM/PM hour if necessary
		SStringT strAMPM;
		if (!IsShowing24HourFormat() && nHour > 12)
			nHour = ConvertToAMPMHour(nHour, &strAMPM);

		SStringT strText;
		strText.Format(_T("%02d%c"), nHour, m_cSep);
		m_pEdit->ReplaceSel(strText, TRUE);	// set the hour

		// Change the AM/PM if it's present
		if (!strAMPM.IsEmpty() && IsValidAMPM(GetAMPM()))
			SetAMPM(strAMPM == m_strAM);
	}

	// Sets the control's minute to the given value, which must be valid.
	void CAMSEdit::TimeBehavior::SetMinute(int nMinute)
	{
		assert(IsValidMinute(nMinute));
		
		SelectionSaver selection = m_pEdit;	// remember the current selection
		
		if (GetMinute() >= 0)		// see if there's already a minute
			m_pEdit->SetSel(GetMinuteStartPosition(), GetMinuteStartPosition() + 2 + IsShowingSeconds());
		
		SStringT strText;
		strText.Format(_T("%02d"), nMinute);
		if (IsShowingSeconds())
			strText += m_cSep;
		
		m_pEdit->ReplaceSel(strText, TRUE);	// set the minute

		// Append the AM/PM if no seconds come after and it's not in 24-hour format
		if (!IsShowingSeconds())
			ShowAMPM();
	}

	// Sets the control's second to the given value, which must be valid.
	void CAMSEdit::TimeBehavior::SetSecond(int nSecond)
	{
		assert(IsValidSecond(nSecond));
		
		if (!IsShowingSeconds())
			return;

		SelectionSaver selection = m_pEdit;	// remember the current selection
		
		if (GetSecond() >= 0)		// see if there's already a second
			m_pEdit->SetSel(GetSecondStartPosition(), GetSecondStartPosition() + 2);
		
		SStringT strText;
		strText.Format(_T("%02d"), nSecond);
		m_pEdit->ReplaceSel(strText, TRUE);	// set the second

		// Append the AM/PM if it's not in 24-hour format
		ShowAMPM();
	}

	// Returns the combination of the given hour and AM/PM symbol converted to 24-hour format.
	int CAMSEdit::TimeBehavior::ConvertTo24Hour(int nHour, const SStringT& strAMPM) const
	{
		if (strAMPM == m_strPM && nHour >= 1 && nHour <= 11)
			nHour += 12;
		else if (strAMPM == m_strAM && nHour == 12)
			nHour = 0;
		return nHour;
	}

	// Returns the given hour (in 24-hour format) to 12-Hour format and sets the optional 
	// string pointer to the resulting AM/PM symbol (if not NULL).
	int CAMSEdit::TimeBehavior::ConvertToAMPMHour(int nHour, SStringT* pStrAMPM /*= NULL*/) const
	{
		SStringT strAMPM = m_strAM;

		if (nHour >= 12)
		{
			nHour -= 12;
			strAMPM = m_strPM;
		}
		if (nHour == 0)
			nHour = 12;

		if (pStrAMPM)
			*pStrAMPM = strAMPM;

		return nHour;
	}

	// Returns the time on the control as a CDuiDateTime object.
	CDuiDateTime CAMSEdit::TimeBehavior::GetTime() const
	{
		if (IsShowing24HourFormat())
			return CDuiDateTime(1970, 1, 1, GetHour(), GetMinute(), GetValidSecond());
		return CDuiDateTime(1970, 1, 1, ConvertTo24Hour(GetHour(), GetAMPM()), GetMinute(), GetValidSecond());
	}
	 

	// Sets the hour, minute, and second on the control to the given values, which must be valid.
	void CAMSEdit::TimeBehavior::SetTime(int nHour, int nMinute, int nSecond /*= 0*/)
	{
		assert(IsValidHour(nHour, true));
		assert(IsValidMinute(nMinute));
		assert(IsValidSecond(nSecond));
		m_pEdit->SetWindowText(GetFormattedTime(nHour, nMinute, nSecond));
	}

	// Sets the hour, minute, and second on the control based on the given CDuiDateTime object, which must be valid.
	void CAMSEdit::TimeBehavior::SetTime(const CDuiDateTime& time)
	{
		SetTime(time.GetHour(), time.GetMinute(), time.GetSecond());
	}
	 
	// Sets the hour, minute, and second on the control to the current time.
	void CAMSEdit::TimeBehavior::SetTimeToNow()
	{
		CDuiDateTime datetime;
		SetTime(datetime);
	}

	// Returns true if the control's time is valid and falls within allowed range.
	bool CAMSEdit::TimeBehavior::IsValid() const
	{
		return IsValid(true);
	}

	// Returns true if the control's time is valid.
	// If bCheckRangeAlso is true, the time is also checked that it falls within allowed range.
	bool CAMSEdit::TimeBehavior::IsValid(bool bCheckRangeAlso) const
	{
		// Check that we have a valid hour and minute
		int nHour = GetHour();
		int nMinute = GetMinute();
		if (nHour < 0 || nMinute < 0)
			return false;
	    
		// Check that the seconds are valid if being shown
		int nSecond = GetSecond();
		bool bShowingSeconds = IsShowingSeconds();
		if (bShowingSeconds != (nSecond >= 0))
			return false;

		// Check the AM/PM portion
		SStringT strAMPM = GetAMPM();
		bool b24HourFormat = IsShowing24HourFormat();
		if ((b24HourFormat && !strAMPM.IsEmpty()) ||
			(!b24HourFormat && (strAMPM != m_strAM && strAMPM != m_strPM)))
			return false;

		if (!b24HourFormat && strAMPM == m_strPM)
		{
			nHour += 12;
			if (nHour == 24)
				nHour = 0;
		}
		if (!bShowingSeconds)
			nSecond = m_timeMin.GetSecond(); // avoids possible problem when checking range below

		// Check that it's valid
		CDuiDateTime date(AMS_DEFAULT_DATE, nHour, nMinute, nSecond);
		if (!date.IsValid())
			return false;

		// Check the range if desired
		if (bCheckRangeAlso)
			return IsWithinRange(date, false);
		return true;
	}

	// Returns true if the control's time is valid and falls within the allowed range.
	// If bShowErrorIfNotValid is true, an error message box is shown and the control gets the focus.
	bool CAMSEdit::TimeBehavior::CheckIfValid(bool bShowErrorIfNotValid /*= true*/)
	{
		//if (!m_pEdit->IsEnabled())
		if (m_pEdit->GetReadOnly())		
			return true;
		
		bool bValid = IsValid();
		if (!bValid && bShowErrorIfNotValid)
		{ 
		}
		
		return bValid;
	}
 

	// Sets the range of allowed time values to the given minimum and maximum CDuiDateTime values.
	void CAMSEdit::TimeBehavior::SetRange(const CDuiDateTime& dateMin, const CDuiDateTime& dateMax)
	{
		assert(dateMin >= AMS_MIN_CTIME);
		assert(dateMax <= AMS_MAX_CTIME);
		
		m_timeMin.SetTime(dateMin.GetHour(), dateMin.GetMinute(), dateMin.GetSecond());
		m_timeMax.SetTime(dateMax.GetHour(), dateMax.GetMinute(), dateMin.GetSecond());
		assert(m_timeMin <= m_timeMax);
		
		_Redraw();
	}
	 

	// Retrieves the range of allowed time values inside the given set of CDuiDateTime pointers.
	void CAMSEdit::TimeBehavior::GetRange(CDuiDateTime* pDateMin, CDuiDateTime* pDateMax) const
	{
		if (pDateMin)
			*pDateMin = CDuiDateTime(pDateMin->GetYear(), pDateMin->GetMonth(), pDateMin->GetDay(), m_timeMin.GetHour(), m_timeMin.GetMinute(), m_timeMin.GetSecond());
		if (pDateMax)
			*pDateMax = CDuiDateTime(pDateMin->GetYear(), pDateMin->GetMonth(), pDateMin->GetDay(), m_timeMax.GetHour(), m_timeMax.GetMinute(), m_timeMax.GetSecond());
	}
	 
	// Returns true if the given date is valid and falls within the range.
	bool CAMSEdit::TimeBehavior::IsWithinRange(const CDuiDateTime& date, bool /*= true*/) const
	{ 
		return (date.IsValid() && date >= m_timeMin && date <= m_timeMax);
	}

	// Sets the character used to separate the hour, minute, and second values.
	void CAMSEdit::TimeBehavior::SetSeparator(TCHAR cSep)
	{
		assert(cSep);
		assert(!_istdigit(cSep));
		
		if (m_cSep != cSep)
		{
			m_cSep = cSep;
			_Redraw();
		}
	}

	// Returns the character used to separate the hour, minute, and second values.
	TCHAR CAMSEdit::TimeBehavior::GetSeparator() const
	{
		return m_cSep;
	}

	// Sets whether the hour should be shown in 24-Hour format or in 12-Hour format with the AM/PM symbols.
	// Note: By default, this is based on the user's system configuration.
	void CAMSEdit::TimeBehavior::Show24HourFormat(bool bShow24HourFormat /*= true*/,bool bReDraw/*=true*/)
	{
		ModifyFlags(bShow24HourFormat ? TwentyFourHourFormat : 0, bShow24HourFormat ? 0 : TwentyFourHourFormat,bReDraw);
	}

	// Returns true if the hour will be shown in 24-Hour format (instead of 12-Hour format with the AM/PM symbols).
	bool CAMSEdit::TimeBehavior::IsShowing24HourFormat() const
	{
		return (m_uFlags & TwentyFourHourFormat) ? true : false;
	}

	// Sets whether the seconds will be shown.
	void CAMSEdit::TimeBehavior::ShowSeconds(bool bShowSeconds /*= true*/,bool bReDraw/*=true*/)
	{
		ModifyFlags(bShowSeconds ? WithSeconds : 0, bShowSeconds ? 0 : WithSeconds,bReDraw);
	}

	// Returns true if the seconds will be shown.
	bool CAMSEdit::TimeBehavior::IsShowingSeconds() const
	{
		return (m_uFlags & WithSeconds) ? true : false;
	}

	// Sets the symbols to display for AM and PM, which must each be of the same length.
	// Note: By default, these symbols are retrieved from the user's system configuration.
	void CAMSEdit::TimeBehavior::SetAMPMSymbols(const SStringT& strAM, const SStringT& strPM)
	{
		assert(strAM.GetLength() == strPM.GetLength());  // make sure they're the same length

		m_strAM = strAM;
		m_strPM = strPM;

		if (m_strAM == _T(""))
			m_strAM = AMS_AM_SYMBOL;
		if (m_strPM == _T(""))
			m_strPM = AMS_PM_SYMBOL;

		m_nAMPMLength = m_strAM.GetLength();
		_Redraw();
	}

	// Retrieves the symbols to display for AM and PM into the given string pointers, which must be valid.
	void CAMSEdit::TimeBehavior::GetAMPMSymbols(SStringT* pStrAM, SStringT* pStrPM) const
	{
		assert(pStrAM);
		assert(pStrPM);
		*pStrAM = m_strAM;
		*pStrPM = m_strPM;
	}

	// Returns the control's value in a valid format.
	SStringT CAMSEdit::TimeBehavior::_GetValidText() 
	{
		SStringT strText = m_pEdit->GetWindowText();
		
		// If it's empty or has a valid time, return it
		if (strText.IsEmpty())
			return strText;

		if (IsValid(false))
			return GetFormattedTime(GetHour(), GetMinute(), GetSecond(), GetAMPM());

		// If the hour, minute, and second are invalid, set it to the current time
		if (GetHour() < 0 && GetMinute() < 0 && GetSecond() < 0)
		{
			CDuiDateTime time;
			return GetFormattedTime(time.GetHour(), time.GetMinute(), time.GetSecond());
		}

		// Otherwise retrieve the validated time
		return GetFormattedTime(GetValidHour(true), GetValidMinute(), GetValidSecond(), GetAMPM());
	}

	// Formats the given hour, minute, second, and optional AM/PM symbol into a string based on the proper format.
	SStringT CAMSEdit::TimeBehavior::GetFormattedTime(int nHour, int nMinute, int nSecond, const SStringT& strAMPM /*= _T("")*/) const
	{
		if (IsShowing24HourFormat())
		{
			// Handle switching from AM/PM to 24-hour format
			if (IsValidAMPM(strAMPM))
				nHour = ConvertTo24Hour(nHour, strAMPM);
		}
		else
		{
			// Handle switching from 24-hour format to AM/PM
			if (!IsValidAMPM(strAMPM))
				nHour = ConvertToAMPMHour(nHour, const_cast<SStringT*>(&strAMPM));
		}

		SStringT strText;	
		if (IsShowingSeconds())
		{
			if (IsShowing24HourFormat())
				strText.Format(_T("%02d%c%02d%c%02d"), nHour, m_cSep, nMinute, m_cSep, nSecond);
			else 
				strText.Format(_T("%02d%c%02d%c%02d %s"), nHour, m_cSep, nMinute, m_cSep, nSecond, strAMPM);
		}
		else 
		{
			if (IsShowing24HourFormat())
				strText.Format(_T("%02d%c%02d"), nHour, m_cSep, nMinute);
			else 
				strText.Format(_T("%02d%c%02d %s"), nHour, m_cSep, nMinute, strAMPM);
		}
		
		return strText;
	}

	// Adjusts the control's value to be within the range of allowed time values.
	void CAMSEdit::TimeBehavior::AdjustWithinRange()
	{
		// Check if it's already within the range
		if (IsValid())
			return;

		// If it's empty, set it to the current time
		if (!m_pEdit->GetWindowText().IsEmpty())
			_Redraw();

		// Make it fall within the range
		CDuiDateTime date = GetTime();
		if (date < m_timeMin)
			SetTime(m_timeMin);
		else if (date > m_timeMax)
			SetTime(m_timeMax);
	}
 
 
	/////////////////////////////////////////////////////////////////////////////
	// CAMSEdit::DateTimeBehavior

	CAMSEdit::DateTimeBehavior::DateTimeBehavior()		
	{ 
		m_nHourStart = 11; 
	}

	

	// Sets whether the seconds will be shown.
	void CAMSEdit::DateTimeBehavior::ShowTime(bool bShowTime /*= true*/,bool bReDraw/*=true*/)
	{
		ModifyFlags(bShowTime ? 0 : DateOnly, bShowTime ? DateOnly : 0,bReDraw);
	}

	// Returns true if the seconds will be shown.
	bool CAMSEdit::DateTimeBehavior::IsShowingTime() const
	{
		return (m_uFlags & DateOnly) ? false : true;
	}
	
		
	void CAMSEdit::DateTimeBehavior::SetEdit(CAMSEdit* pEdit)
	{
		DateBehavior::SetEdit(pEdit);
		TimeBehavior::SetEdit(pEdit);
		Behavior::SetEdit(pEdit);
	}

	// Sets the month, day, year, hour, minute, and second on the control to the given values, which must be valid.
	void CAMSEdit::DateTimeBehavior::SetDateTime(int nYear, int nMonth, int nDay, int nHour, int nMinute, int nSecond /*= 0*/)
	{
		if (m_uFlags & DateOnly)
			SetDate(nYear, nMonth, nDay);
		else if (m_uFlags & TimeOnly)
			SetTime(nHour, nMinute, nSecond);
		else
		{
			assert(IsWithinRange(CDuiDateTime(nYear, nMonth, nDay, nHour, nMinute, nSecond))); 
			m_pEdit->SetWindowText(SStringT(GetFormattedDate(nYear, nMonth, nDay)) + SStringT(_T(' ')) + GetFormattedTime(nHour, nMinute, nSecond));
		}
	}

	// Sets the month, day, year, hour, minute, and second on the control to the CDuiDateTime object, which must be valid.
	void CAMSEdit::DateTimeBehavior::SetDateTime(const CDuiDateTime& dt)
	{
		SetDateTime(dt.GetYear(), dt.GetMonth(), dt.GetDay(), dt.GetHour(), dt.GetMinute(), dt.GetSecond());
	} 

	// Sets the month, day, year, hour, minute, and second on the control to the current date and time.
	void CAMSEdit::DateTimeBehavior::SetToNow()
	{
		CDuiDateTime datetime;
		SetDateTime(datetime);
	}

	// Returns the date and time on the control as a CDuiDateTime object.
	CDuiDateTime CAMSEdit::DateTimeBehavior::GetDateTime() const
	{
		CDuiDateTime date = GetDate();
		CDuiDateTime time = GetTime();
		
		if (m_uFlags & DateOnly)
			return date;
		if (m_uFlags & TimeOnly)
			return time;	
		return CDuiDateTime(date.GetYear(), date.GetMonth(), date.GetDay(), time.GetHour(), time.GetMinute(), time.GetSecond());
	}
	 

	// Returns true if the control's date and time is valid and falls within the allowed range.
	bool CAMSEdit::DateTimeBehavior::IsValid() const
	{
		if (m_uFlags & DateOnly)
			return DateBehavior::IsValid();
		if (m_uFlags & TimeOnly)
			return TimeBehavior::IsValid();
		return (DateBehavior::IsValid() && TimeBehavior::IsValid());
	}

	// Sets the range of allowed date values to the given minimum and maximum CDuiDateTime values.
	void CAMSEdit::DateTimeBehavior::SetRange(const CDuiDateTime & dateMin, const CDuiDateTime & dateMax)
	{
		DateBehavior::SetRange(dateMin, dateMax);
		TimeBehavior::SetRange(dateMin, dateMax);
	} 

	// Retrieves the range of allowed date and time values inside the given set of CDuiDateTime pointers.
	void CAMSEdit::DateTimeBehavior::GetRange(CDuiDateTime * pDateMin, CDuiDateTime * pDateMax) const
	{
		DateBehavior::GetRange(pDateMin, pDateMax);
		TimeBehavior::GetRange(pDateMin, pDateMax);
	}
	 
	// Returns true if the given date and time is valid and falls within the range.
	bool CAMSEdit::DateTimeBehavior::IsWithinRange(const CDuiDateTime& date, bool bDateOnly /*= true*/) const
	{
		if (bDateOnly)
			return DateBehavior::IsWithinRange(date);

		CDuiDateTime dt(GetYear(), GetMonth(), GetDay(), date.GetHour(), date.GetMinute(), date.GetSecond());
		CDuiDateTime dtMin(m_dateMin.GetYear(), m_dateMin.GetMonth(), m_dateMin.GetDay(), m_timeMin.GetHour(), m_timeMin.GetMinute(), m_timeMin.GetSecond());
		CDuiDateTime dtMax(m_dateMax.GetYear(), m_dateMax.GetMonth(), m_dateMax.GetDay(), m_timeMax.GetHour(), m_timeMax.GetMinute(), m_timeMax.GetSecond());
		return (dt.IsValid() && dt >= dtMin && dt <= dtMax);
	}

	// Sets the character used to separate the date or time values, depending on the flag.
	void CAMSEdit::DateTimeBehavior::SetSeparator(TCHAR cSep, bool bDate)
	{
		if (bDate)
			DateBehavior::SetSeparator(cSep);
		else
			TimeBehavior::SetSeparator(cSep);
	}

	// Returns the character used to separate the date or time values, depending on the flag.
	TCHAR CAMSEdit::DateTimeBehavior::GetSeparator(bool bDate) const
	{
		return (bDate ? DateBehavior::GetSeparator() : TimeBehavior::GetSeparator());
	}

	// Adds and removes flags from the behavior and then redraws the control
	bool CAMSEdit::DateTimeBehavior::ModifyFlags(UINT uAdd, UINT uRemove,bool bReDraw/*=true*/)
	{
		UINT uFlags = (m_uFlags & ~uRemove) | uAdd;
		m_nHourStart = (uFlags & TimeOnly) ? 0 : 11;

		return Behavior::ModifyFlags(uAdd, uRemove,bReDraw);
	}

	// Returns the control's value in a valid format.
	SStringT CAMSEdit::DateTimeBehavior::_GetValidText() 
	{
		// Check if we're showing the date only
		SStringT strDate = DateBehavior::_GetValidText();
		if (m_uFlags & DateOnly)
			return strDate;

		// Check if we're showing the time only
		SStringT strTime = TimeBehavior::_GetValidText();
		if (m_uFlags & TimeOnly)
			return strTime;

		SStringT strSpace = (!strDate.IsEmpty() && !strTime.IsEmpty() ? _T(" ") : _T(""));
		return strDate + strSpace + strTime;
	}

	// Handles the WM_CHAR message, which is called when the user enters a regular character or Backspace
	void CAMSEdit::DateTimeBehavior::_OnChar(UINT uChar,bool &bHandled)
	{
		// Check to see if it's read only
		if (m_pEdit->GetReadOnly())
			return;

		// Check if we're showing the date or the time only
		if (m_uFlags & DateOnly)
		{
			DateBehavior::_OnChar(uChar,bHandled);
			return;
		}
		if (m_uFlags & TimeOnly)
		{
			TimeBehavior::_OnChar(uChar,bHandled);
			return;
		}

		TCHAR c = static_cast<TCHAR>(uChar);
		
		long nStart = 0, nEnd = 0;
		DateBehavior::m_pEdit->GetSel(nStart, nEnd);

		SStringT strText = m_pEdit->GetWindowText();
		int nLen = strText.GetLength();

		if (nStart >= 0 && nStart <= 9)
		{
			DateBehavior::_OnChar(uChar,bHandled);
			ChangeAMPM(c);	// allow changing AM/PM (if it's being shown) by pressing A or P
		}
		else if (nStart == 10)
		{
			DateBehavior::_OnChar(uChar,bHandled);

			int nSpace = 0;
			if (c == _T(' '))
				nSpace = 1;
			else
				nSpace = (IsValidHourDigit(c, 0) || (IsValidHourDigit(c, 1) && nLen <= 11) ? 2 : 0);
			
			// If we need the space, enter it
			if (nSpace && _ShouldEnter(c))
			{
				DateBehavior::m_pEdit->SetSel(nStart, nStart + 1);
				DateBehavior::m_pEdit->ReplaceSel(SStringT(_T(' ')), true);
			}
			
			// If the space is to be preceded by a valid digit, "type" it in.
			if (nSpace == 2)
				keybd_event((BYTE)c, 0, 0, 0);
			else
				ChangeAMPM(c);	// allow changing AM/PM (if it's being shown) by pressing A or P
		}
		else
			TimeBehavior::_OnChar(uChar,bHandled);
	}

	// Handles the WM_KEYDOWN message, which is called when the user enters a special character such as Delete or the arrow keys.
	void CAMSEdit::DateTimeBehavior::_OnKeyDown(UINT uChar,bool &bHandled)
	{
		// Check if we're showing the time only
		if (m_uFlags & TimeOnly)
		{
			TimeBehavior::_OnKeyDown(uChar,bHandled);
			return;
		}

		DateBehavior::_OnKeyDown(uChar,bHandled);
		if ((uChar == VK_UP || uChar == VK_DOWN) && !(m_uFlags & DateOnly))
			TimeBehavior::_OnKeyDown(uChar,bHandled);
	}

	// Handles the WM_KILLFOCUS message, which is called when the user leaves the control.
	// It's used here to check if any action needs to be taken based on the control's value.
	void CAMSEdit::DateTimeBehavior::_OnKillFocus(bool &bHandled)
	{
		DateBehavior::_OnKillFocus(bHandled);
	}
  
	// Constructs the object using the given set of strInvalidChars
	CAMSAlphanumericEdit::CAMSAlphanumericEdit(int nMaxChars /*= 0*/, const SStringT& strInvalidChars /*= _T("%'*\"+?><:\\"")*/) :
		AlphanumericBehavior( nMaxChars, strInvalidChars)
	{
		AlphanumericBehavior::SetEdit(this);
	} 

	// Returns the control's value in a valid format.
	SStringT CAMSAlphanumericEdit::GetValidText() 
	{
		return _GetValidText();
	}

	// Handles the WM_CHAR message, which is called when the user enters a regular character or Backspace
	void CAMSAlphanumericEdit::OnChar(UINT uChar,bool &bHandled)
	{
		_OnChar(uChar,bHandled);
	}
  
	/////////////////////////////////////////////////////////////////////////////
	// CAMSMaskedEdit window

	// Constructs the object using the given numeric strMask.
	CAMSMaskedEdit::CAMSMaskedEdit(const SStringT& strMask /*= _T("")*/) :MaskedBehavior(strMask)
	{
	} 

	
	void CAMSMaskedEdit::SetEdit(CAMSEdit* pEdit)
	{
		MaskedBehavior::SetEdit(this);
	}
	// Returns the control's value in a valid format.
	SStringT CAMSMaskedEdit::GetValidText() 
	{
		return _GetValidText();
	}

	// Handles the WM_CHAR message, which is called when the user enters a regular character or Backspace
	void CAMSMaskedEdit::OnChar(UINT uChar,bool &bHandled)
	{
		_OnChar(uChar,bHandled);
	}

	// Handles the WM_KEYDOWN message, which is called when the user enters a special character such as Delete or the arrow keys.
	void CAMSMaskedEdit::OnKeyDown(UINT uChar,bool &bHandled)
	{
		_OnKeyDown(uChar,bHandled);
	}
  
	/////////////////////////////////////////////////////////////////////////////
	// CAMSDateEdit
	SOUI_CLASS_NAME(CAMSDateEdit, L"date_edit")

	CAMSDateEdit::CAMSDateEdit() // required because DateBehavior derives virtually from Behavior
	{
	}
	
	void CAMSDateEdit::SetEdit(CAMSEdit* pEdit)
	{
		CAMSEdit::DateBehavior::SetEdit(pEdit);
		CAMSEdit::Behavior::SetEdit(pEdit);
	}		 
 
	// Returns the control's value in a valid format.
	SStringT CAMSDateEdit::GetValidText() 
	{
		return _GetValidText();
	}

	// Handles the WM_CHAR message, which is called when the user enters a regular character or Backspace
	void CAMSDateEdit::OnChar(UINT uChar,bool &bHandled)
	{
		_OnChar(uChar,bHandled);
	}

	// Handles the WM_KEYDOWN message, which is called when the user enters a special character such as Delete or the arrow keys.
	void CAMSDateEdit::OnKeyDown(UINT uChar,bool &bHandled) 
	{
		_OnKeyDown(uChar,bHandled);
	}

	// Handles the WM_KILLFOCUS message, which is called when the user leaves the control.
	void CAMSDateEdit::OnKillFocus(bool &bHandled) 
	{
		_OnKillFocus(bHandled);
	}

	// Handles the WM_PASTE message to ensure that the text being pasted is a valid date.
	LONG CAMSDateEdit::OnPaste()
	{
		return _OnPaste();
	}

	/////////////////////////////////////////////////////////////////////////////
	// CAMSTimeEdit
	SOUI_CLASS_NAME(CAMSTimeEdit, L"time_edit")

	CAMSTimeEdit::CAMSTimeEdit() // required because TimeBehavior derives virtually from Behavior
	{
		SetEdit(this);
	}

	void CAMSTimeEdit::SetEdit(CAMSEdit* pEdit)
	{
		CAMSEdit::TimeBehavior::SetEdit(pEdit);
		CAMSEdit::Behavior::SetEdit(pEdit);
 
	} 

	// Returns the control's value in a valid format.
	SStringT CAMSTimeEdit::GetValidText() 
	{
		return _GetValidText();
	}

	// Handles the WM_CHAR message, which is called when the user enters a regular character or Backspace
	void CAMSTimeEdit::OnChar(UINT uChar,bool &bHandled)
	{
		_OnChar(uChar,bHandled);
	}

	// Handles the WM_KEYDOWN message, which is called when the user enters a special character such as Delete or the arrow keys.
	void CAMSTimeEdit::OnKeyDown(UINT uChar,bool &bHandled) 
	{
		_OnKeyDown(uChar,bHandled);
	}

	// Handles the WM_KILLFOCUS message, which is called when the user leaves the control.
	void CAMSTimeEdit::OnKillFocus(bool &bHandled) 
	{
		_OnKillFocus(bHandled);
	}

	// Handles the WM_PASTE message to ensure that the text being pasted is a valid time.
	LONG CAMSTimeEdit::OnPaste()
	{
		return _OnPaste();
	}

	/////////////////////////////////////////////////////////////////////////////
	// CAMSNumericEdit window

	// Constructs the object using the given nMaxWholeDigits and nMaxDecimalPlaces.
	CNumericEditUI::CNumericEditUI(int nMaxWholeDigits /*= 9*/, int nMaxDecimalPlaces /*= 4*/) :
		NumericBehavior(nMaxWholeDigits, nMaxDecimalPlaces)
	{
		SetEdit(this);
	}

	void CNumericEditUI::SetEdit(CAMSEdit* pEdit)
	{
		CAMSEdit::NumericBehavior::SetEdit(pEdit);
		CAMSEdit::Behavior::SetEdit(pEdit);
	}	

	LPCTSTR CNumericEditUI::GetClass() const
	{
		return _T("NumericEditUI");
	}

	// Handles the WM_CHAR message, which is called when the user enters a regular character or Backspace
	void CNumericEditUI::OnChar(UINT uChar,bool &bHandled)
	{
		_OnChar(uChar,bHandled);
	}

	// Handles the WM_KEYDOWN message, which is called when the user enters a special character such as Delete or the arrow keys.
	void CNumericEditUI::OnKeyDown(UINT uChar,bool &bHandled) 
	{
		_OnKeyDown(uChar,bHandled);
	}

	// Handles the WM_KILLFOCUS message, which is called when the user leaves the control.
	void CNumericEditUI::OnKillFocus(bool &bHandled) 
	{
		_OnKillFocus(bHandled);
	}

	// Handles the WM_PASTE message to ensure that the text being pasted is a valid date.
	LONG CNumericEditUI::OnPaste()
	{
		return _OnPaste();
	} 

	// Returns the control's value in a valid format.
	SStringT CNumericEditUI::GetValidText() 
	{
		return _GetValidText();
	}

	
	// Constructs the object allowing the negative sign or not.
	CIntegerEditUI::CIntegerEditUI(int nMaxWholeDigits /*= 9*/) :
		CNumericEditUI(nMaxWholeDigits, 0)
	{
		SetEdit(this);
	}

	void CIntegerEditUI::SetEdit(CAMSEdit* pEdit)
	{
		CAMSEdit::NumericBehavior::SetEdit(pEdit);
		CAMSEdit::Behavior::SetEdit(pEdit);
	}	

	LPCTSTR CIntegerEditUI::GetClass() const
	{
		return _T("IntegerEditUI");
	}

	// Handles the WM_CHAR message, which is called when the user enters a regular character or Backspace
	void CIntegerEditUI::OnChar(UINT uChar,bool &bHandled)
	{
		_OnChar(uChar,bHandled);
	}

	// Handles the WM_KEYDOWN message, which is called when the user enters a special character such as Delete or the arrow keys.
	void CIntegerEditUI::OnKeyDown(UINT uChar,bool &bHandled) 
	{
		_OnKeyDown(uChar,bHandled);
	}

	// Handles the WM_KILLFOCUS message, which is called when the user leaves the control.
	void CIntegerEditUI::OnKillFocus(bool &bHandled) 
	{
		_OnKillFocus(bHandled);
	}
 
	SOUI_CLASS_NAME(CDateTimeUI, L"datetime")

	CDateTimeUI::CDateTimeUI():m_uButtonState(0),m_SplitWidth(0)
	{
		SetShowTime(true,false);
		SetShowSeconds(true,false);

		SetEdit(this);
	}  

	void CDateTimeUI::SetEdit(CAMSEdit* pEdit)
	{
		CAMSEdit::DateTimeBehavior::SetEdit(pEdit);
		CAMSEdit::Behavior::SetEdit(pEdit);
	}

 
	// Returns the control's value in a valid format.
	SStringT CDateTimeUI::GetValidText() 
	{
		return CAMSEdit::DateTimeBehavior::_GetValidText();
	}

	// Handles the WM_CHAR message, which is called when the user enters a regular character or Backspace
	void CDateTimeUI::OnChar(UINT uChar,bool &bHandled)
	{
		CAMSEdit::DateTimeBehavior::_OnChar(uChar,bHandled);
	}

	// Handles the WM_KEYDOWN message, which is called when the user enters a special character such as Delete or the arrow keys.
	void CDateTimeUI::OnKeyDown(UINT uChar,bool &bHandled) 
	{
		CAMSEdit::DateTimeBehavior::_OnKeyDown(uChar,bHandled);
	}

	// Handles the WM_KILLFOCUS message, which is called when the user leaves the control.
	void CDateTimeUI::OnKillFocus(bool &bHandled) 
	{
		CAMSEdit::DateTimeBehavior::_OnKillFocus(bHandled);
	}

	// Handles the WM_PASTE message to ensure that the text being pasted is a valid date.
	LONG CDateTimeUI::OnPaste()
	{
		return CAMSEdit::DateTimeBehavior::_OnPaste();
	} 
 	
	BOOL CDateTimeUI::PtInDropButtonRect(POINT pt)
	{
		CRect rcItem = this->GetClientRect();
		RECT rcDropButton={ rcItem.right-m_SplitWidth,rcItem.top,rcItem.right,rcItem.bottom};
		return ::PtInRect(&rcDropButton, pt);
	}

	/*
	void CDateTimeUI::DoEvent(TEventUI& event)
	{   
		if( event.Type == UIEVENT_BUTTONDOWN)
		{
			if( IsEnabled() && PtInDropButtonRect(event.ptMouse) ) 
			{
				Activate();
				m_uButtonState |= UISTATE_PUSHED | UISTATE_CAPTURED;
				Invalidate();
			}  

			return;
		}
		if( event.Type == UIEVENT_MOUSEMOVE )
		{ 
			if(IsEnabled() &&  PtInDropButtonRect(event.ptMouse) )
			{ 
				m_uButtonState |= UISTATE_DROPBTN_ON; 
			}

			if(IsEnabled() &&  (m_uButtonState & UISTATE_CAPTURED) != 0 ) {
				if( ::PtInRect(&m_rcItem, event.ptMouse) ) m_uButtonState |= UISTATE_PUSHED;
				else m_uButtonState &= ~UISTATE_PUSHED;
				Invalidate();
			}  

			return;
		} 

		if( event.Type == UIEVENT_BUTTONUP )
		{
			if(IsEnabled() &&  (m_uButtonState & UISTATE_CAPTURED) != 0 ) 
			{
				m_uButtonState &= ~(UISTATE_PUSHED | UISTATE_CAPTURED);
				Invalidate();
			}
			return;
		}

		if( event.Type == UIEVENT_MOUSEENTER )
		{
			if( IsEnabled() ) 
			{
				if( PtInDropButtonRect(event.ptMouse) )
				{ 
					m_uButtonState |= UISTATE_HOT;
					m_uButtonState |= UISTATE_DROPBTN_ON; 
					Invalidate();
				}
			}
			//return;
		}

		if( event.Type == UIEVENT_MOUSELEAVE )
		{
			if( IsEnabled() ) 
			{
				m_uButtonState &= ~UISTATE_HOT;
				Invalidate(); 
			}
			//return;
		}

			
		if( event.Type == UIEVENT_SETCURSOR ) 
		{ 
			if( IsEnabled())
			{
				if(PtInDropButtonRect(event.ptMouse) ) 
				{  
					::SetCursor(::LoadCursor(NULL, MAKEINTRESOURCE(IDC_HAND)));
					return ;
				}
				else
				{
					
					return SDateRichEdit::DoEvent(event);  
				}
			} 
		} 

		return SDateRichEdit::DoEvent(event);  
	}*/

	bool CDateTimeUI::Activate()
	{
		/*
		if( !SWindow::Activate() ) return false;
		if( m_pManager != NULL ){
			m_pManager->SendNotify(this, NOTIFY_CLICK_VALUE);
			if(!m_sCalendarName.IsEmpty()){
				CCalendarUI::ShowCalendarDlg(this);
				m_pManager->SendNotify(this,NOTIFY_CALENDER_SEL_DATE_VALUE);
			}
			BindTriggerTabSel();
		}
		*/
		return true;
	}

	void CDateTimeUI::SetEnabled(bool bEnable)
	{
		//SWindow::SetEnabled(bEnable); 
	}

	
	void CDateTimeUI::SetShowTime(bool bShow,bool bReDraw)
	{
		bShowTime = bShow;

		ShowTime(bShow,bReDraw); 
	}

	void CDateTimeUI::SetShowSeconds(bool bShow,bool bReDraw)
	{
		bShowSeconds = bShow;
 
		ShowSeconds(bShow,bReDraw);
	}

	bool CDateTimeUI::IsShowTime() const
	{
		return bShowTime;
	}

	bool CDateTimeUI::IsShowSeconds() const
	{
		return bShowSeconds;
	}

	void CDateTimeUI::SetAttribute(LPCTSTR pstrName, LPCTSTR pstrValue)
	{
		if( _tcscmp(pstrName, _T("calendarname")) == 0 ) SetCalendarName(pstrValue);
		else if( _tcscmp(pstrName, _T("calendarstyle")) == 0 ) SetCalendarStyle(pstrValue);
		else if( _tcscmp(pstrName, _T("calendarprofile")) == 0 ) SetCalendarProfile(pstrValue);
		else if( _tcscmp(pstrName, _T("bindtabindex")) == 0 ) BindTabIndex(_ttoi(pstrValue));
		else if( _tcscmp(pstrName, _T("bindtablayoutname")) == 0 ) BindTabLayoutName(pstrValue);
		else if( _tcscmp(pstrName, _T("imagesplit")) == 0 ) SetImageSplit(_ttoi(pstrValue));
		else if( _tcscmp(pstrName, _T("showtime")) == 0 ) SetShowTime((_tcscmp(pstrValue, _T("true"))==0),false);
		else if( _tcscmp(pstrName, _T("showseconds")) == 0 ) SetShowSeconds((_tcscmp(pstrValue, _T("true"))==0),false);
		else if( _tcscmp(pstrName, _T("normalimage")) == 0 ) SetNormalImage(pstrValue);
		else if( _tcscmp(pstrName, _T("hotimage")) == 0 ) SetHotImage(pstrValue);
		else if( _tcscmp(pstrName, _T("pushedimage")) == 0 ) SetPushedImage(pstrValue);
		else if( _tcscmp(pstrName, _T("focusedimage")) == 0 ) SetFocusedImage(pstrValue);
		else if( _tcscmp(pstrName, _T("disabledimage")) == 0 ) SetDisabledImage(pstrValue);
		else CAMSEdit::SetAttribute(pstrName, pstrValue);
	}  
	
	void CDateTimeUI::SetNowDate()
	{
		CDuiDateTime date;
		this->SetWindowText(date.FormatDateString());
	}


	void CDateTimeUI::SetCalendarName( LPCTSTR pStrCalendarName )
	{
			m_sCalendarName = pStrCalendarName;
	}

	LPCTSTR CDateTimeUI::GetCalendarName()
	{
			return m_sCalendarName;
	}

	void CDateTimeUI::SetCalendarStyle( LPCTSTR pStrCalendarStyle )
	{
			m_sCalendarStyle = pStrCalendarStyle;
	}

	LPCTSTR CDateTimeUI::GetCalendarStyle()
	{
			return m_sCalendarStyle;
	}

	void CDateTimeUI::SetCalendarProfile( LPCTSTR pStrCalendarProfile )
	{
			m_sCalendarProfile = pStrCalendarProfile;
	}

	LPCTSTR CDateTimeUI::GetCalendarProfile()
	{
			return m_sCalendarProfile;
	}

	void CDateTimeUI::BindTabIndex(int _BindTabIndex )
	{
			if( _BindTabIndex >= 0)
				m_iBindTabIndex			= _BindTabIndex;
	}
	
	void CDateTimeUI::BindTabLayoutName( LPCTSTR _TabLayoutName )
	{
			if(_TabLayoutName)
				m_sBindTabLayoutName = _TabLayoutName;
	}

	void CDateTimeUI::BindTriggerTabSel( int _SetSelectIndex /*= -1*/ )
	{
		/*
			if(GetBindTabLayoutName().IsEmpty() || (GetBindTabLayoutIndex() < 0 && _SetSelectIndex < 0))
				return;

			CTabLayoutUI* pTabLayout = static_cast<CTabLayoutUI*>(GetManager()->FindControl(GetBindTabLayoutName()));
			if(!pTabLayout)
				return;

			pTabLayout->SelectItem(_SetSelectIndex >=0?_SetSelectIndex:GetBindTabLayoutIndex());
			*/
	}

	void CDateTimeUI::RemoveBindTabIndex()
	{
			m_iBindTabIndex	= -1;
			m_sBindTabLayoutName.Empty();
	}
	
	int CDateTimeUI::GetBindTabLayoutIndex()
	{
			return m_iBindTabIndex;
	}

	SStringT CDateTimeUI::GetBindTabLayoutName()
	{
			return m_sBindTabLayoutName;
	}

	LPCTSTR CDateTimeUI::GetNormalImage() const
	{
		return m_sNormalImage;
	}

	void CDateTimeUI::SetNormalImage(LPCTSTR pStrImage)
	{
		m_sNormalImage = pStrImage;
		Invalidate();
	}

	LPCTSTR CDateTimeUI::GetHotImage() const
	{
		return m_sHotImage;
	}

	void CDateTimeUI::SetHotImage(LPCTSTR pStrImage)
	{
		m_sHotImage = pStrImage;
		Invalidate();
	}

	LPCTSTR CDateTimeUI::GetPushedImage() const
	{
		return m_sPushedImage;
	}

	void CDateTimeUI::SetPushedImage(LPCTSTR pStrImage)
	{
		m_sPushedImage = pStrImage;
		Invalidate();
	}

	LPCTSTR CDateTimeUI::GetFocusedImage() const
	{
		return m_sFocusedImage;
	}

	void CDateTimeUI::SetFocusedImage(LPCTSTR pStrImage)
	{
		m_sFocusedImage = pStrImage;
		Invalidate();
	}

	LPCTSTR CDateTimeUI::GetDisabledImage() const
	{
		return m_sDisabledImage;
	}

	void CDateTimeUI::SetDisabledImage(LPCTSTR pStrImage)
	{
		m_sDisabledImage = pStrImage;
		Invalidate();
	}
	
	//drop button 
	int CDateTimeUI::GetImageSplit()
	{
		return m_SplitWidth;
	}

	void CDateTimeUI::SetImageSplit(int split_w)
	{
		m_SplitWidth		= split_w; 
	}   

	bool CDateTimeUI::IsValid() const
	{
		return CAMSEdit::DateTimeBehavior::IsValid();
	}

	/*
	void CDateTimeUI::PaintStatusImage(HDC hDC)
	{ 
		if( IsFocused() ) m_uButtonState |= UISTATE_FOCUSED;
		else m_uButtonState &= ~ UISTATE_FOCUSED;
		if( !IsEnabled() ) m_uButtonState |= UISTATE_DISABLED;
		else m_uButtonState &= ~ UISTATE_DISABLED;

		if( (m_uButtonState & UISTATE_DISABLED) != 0 ) {
			if( !m_sDisabledImage.IsEmpty() ) {
				if( !DrawImage(hDC, (LPCTSTR)m_sDisabledImage) ) m_sDisabledImage.Empty();
				else return;
			}
		}
		else if( (m_uButtonState & UISTATE_PUSHED) != 0 ) {
			if( !m_sPushedImage.IsEmpty() ) {
				if( !DrawImage(hDC, (LPCTSTR)m_sPushedImage) ) m_sPushedImage.Empty();
				else return;
			}
		}
		else if( (m_uButtonState & UISTATE_HOT) != 0 ) {
			if( !m_sHotImage.IsEmpty() ) {
				if( !DrawImage(hDC, (LPCTSTR)m_sHotImage) ) m_sHotImage.Empty();
				else return;
			}
		}
		else if( (m_uButtonState & UISTATE_FOCUSED) != 0 ) {
			if( !m_sFocusedImage.IsEmpty() ) {
				if( !DrawImage(hDC, (LPCTSTR)m_sFocusedImage) ) m_sFocusedImage.Empty();
				else return;
			}
		}

		if( !m_sNormalImage.IsEmpty() ) {
			if( !DrawImage(hDC, (LPCTSTR)m_sNormalImage) ) m_sNormalImage.Empty();
			else return;
    }
}

*/

}