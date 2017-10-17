// MainDlg.cpp : implementation of the CMainDlg class
//
/////////////////////////////////////////////////////////////////////////////

#include "MainDlg.h"
#include "FileHelper.h"
#include "LogParser.h"
#include <helper/SMenu.h>
#include "Scintilla.h"

EVENT_MAP_BEGIN(CMainDlg)
	EVENT_NAME_COMMAND(L"btn_close", OnClose)
	EVENT_NAME_COMMAND(L"btn_min", OnMinimize)
	EVENT_NAME_COMMAND(L"btn_max", OnMaximize)
	EVENT_NAME_COMMAND(L"btn_restore", OnRestore)
	EVENT_NAME_COMMAND(L"btn_lang_cn", OnLanguageBtnCN)
	EVENT_NAME_COMMAND(L"btn_lang_en", OnLanguageBtnEN)
	EVENT_ID_COMMAND(R.id.btn_open_file, OnOpenFile)
	EVENT_ID_COMMAND(R.id.btn_find, OnOpenFindDlg)
	EVENT_ID_COMMAND(R.id.btn_clear, OnClear)
	EVENT_ID_HANDLER(R.id.edit_filter, EventRENotify::EventID, OnFilterInputChange)
	EVENT_ID_HANDLER(R.id.cbx_levels, EventCBSelChange::EventID, OnLevelsChange)
	EVENT_ID_CONTEXTMENU(R.id.lv_log, OnLvContextMenu)
EVENT_MAP_END()
//HostWnd真实窗口消息处理
BEGIN_MSG_MAP_EX(CMainDlg)
	MSG_WM_INITDIALOG(OnInitDialog)
	MSG_WM_CLOSE(OnClose)
	MSG_WM_SIZE(OnSize)
	MSG_WM_CONTEXTMENU(OnContextMenu)
	CHAIN_MSG_MAP(CWHRoundRectFrameHelper<CMainDlg>)
	CHAIN_MSG_MAP(SHostWnd)
	REFLECT_NOTIFICATIONS_EX()
END_MSG_MAP()

CMainDlg::CMainDlg() 
: SHostWnd(_T("LAYOUT:XML_MAINWND"))
,m_lvLogs(NULL)
,m_cbxLevels(NULL)
,m_pFindDlg(NULL)
,m_pFilterDlg(NULL)
,m_pSciter(NULL)
{
	m_logAdapter.Attach(new SLogAdapter);
	IParserFactory * pParserFactory = new CParseFactory;
	m_logAdapter->SetParserFactory(pParserFactory);
	pParserFactory->Release();
}

CMainDlg::~CMainDlg()
{
}


BOOL CMainDlg::OnInitDialog(HWND hWnd, LPARAM lParam)
{
	//设置为磁吸主窗口
	SetMainWnd(m_hWnd);

	m_pFilterDlg = new CFilterDlg(this);
	m_pFilterDlg->Create(m_hWnd);
	AddSubWnd(m_pFilterDlg->m_hWnd,AM_LEFT,AA_TOP);

	m_pFilterDlg->ShowWindow(SW_SHOW);

	m_lvLogs = FindChildByID2<SMCListView>(R.id.lv_log);
	if(m_lvLogs)
	{
		m_lvLogs->SetAdapter(m_logAdapter);
	}

	m_cbxLevels = FindChildByID2<SComboBox>(R.id.cbx_levels);
	
	::RegisterDragDrop(m_hWnd,GetDropTarget());

	IDropTarget *pDT = new CDropTarget(this);
	GetContainer()->RegisterDragDrop(m_lvLogs->GetSwnd(),pDT);
	pDT->Release();

	SRealWnd * pRealWnd = FindChildByID2<SRealWnd>(R.id.real_scilexer);
	SASSERT(pRealWnd);
	m_pSciter = (CScintillaWnd *)pRealWnd->GetUserData();
	m_pSciter->SendMessage(SCI_USEPOPUP,0,0);
	m_logAdapter->SetScintillaWnd(m_pSciter);
	return 0;
}

void CMainDlg::OnLanguageBtnCN()
{
	OnLanguage(_T("lang_cn"));
}
void CMainDlg::OnLanguageBtnEN()
{
	OnLanguage(_T("lang_en"));
}

void CMainDlg::OnLanguage(const SStringT & strLang)
{
	ITranslatorMgr *pTransMgr = SApplication::getSingletonPtr()->GetTranslator();
	SASSERT(pTransMgr);

	pugi::xml_document xmlLang;
	if (SApplication::getSingletonPtr()->LoadXmlDocment(xmlLang, strLang,_T("languages")))
	{
		CAutoRefPtr<ITranslator> lang;
		pTransMgr->CreateTranslator(&lang);
		pugi::xml_node node = xmlLang.child(L"language");
		lang->Load(&node, 1);//1=LD_XML

		pTransMgr->SetLanguage(lang->name());
		pTransMgr->InstallTranslator(lang);
		SDispatchMessage(UM_SETLANGUAGE,0,0);
		m_pFilterDlg->SDispatchMessage(UM_SETLANGUAGE,0,0);
		if(m_pFindDlg) m_pFindDlg->SDispatchMessage(UM_SETLANGUAGE,0,0);
	}
}

void CMainDlg::OnClose()
{
	CSimpleWnd::DestroyWindow();
}

void CMainDlg::OnMaximize()
{
	SendMessage(WM_SYSCOMMAND, SC_MAXIMIZE);
}
void CMainDlg::OnRestore()
{
	SendMessage(WM_SYSCOMMAND, SC_RESTORE);
}
void CMainDlg::OnMinimize()
{
	SendMessage(WM_SYSCOMMAND, SC_MINIMIZE);
}

void CMainDlg::OnSize(UINT nType, CSize size)
{
	SetMsgHandled(FALSE);
	
	SWindow *pBtnMax = FindChildByName(L"btn_max");
	SWindow *pBtnRestore = FindChildByName(L"btn_restore");
	if(!pBtnMax || !pBtnRestore) return;
	
	if (nType == SIZE_MAXIMIZED)
	{
		pBtnRestore->SetVisible(TRUE);
		pBtnMax->SetVisible(FALSE);
	}
	else if (nType == SIZE_RESTORED)
	{
		pBtnRestore->SetVisible(FALSE);
		pBtnMax->SetVisible(TRUE);
	}
}

void CMainDlg::OnOpenFile()
{
	CFileDialogEx openDlg(TRUE,_T("log"),0,6,_T("log files(*.log)\0*.log\0txt files(*.txt)\0*.txt\0All files (*.*)\0*.*\0\0"));
	if(openDlg.DoModal()==IDOK)
	{
		OpenFile(openDlg.m_szFileName);
	}
}

void CMainDlg::OnClear()
{
	m_logAdapter->Clear();
	m_pSciter->SendMessage(SCI_CLEARALL);
	SArray<SStringW> lstTags;
	m_pFilterDlg->UpdateTags(lstTags);


	SArray<UINT> lstPid;
	m_pFilterDlg->UpdatePids(lstPid);

	SArray<UINT> lstTid;
	m_pFilterDlg->UpdateTids(lstTid);
}

void CMainDlg::OnFilterInputChange(EventArgs *e)
{
	EventRENotify *e2 = sobj_cast<EventRENotify>(e);
	SASSERT(e2);
	if(e2->iNotify == EN_CHANGE)
	{
		SEdit * pEdit = sobj_cast<SEdit>(e2->sender);
		SStringT str = pEdit->GetWindowText();
		m_logAdapter->SetFilter(str);
	}
}

void CMainDlg::OnLevelsChange(EventArgs *e)
{
	EventCBSelChange * e2 = sobj_cast<EventCBSelChange>(e);
	m_logAdapter->SetLevel(e2->nCurSel);
}


void CMainDlg::OnFileDropdown(HDROP hDrop)
{
	bool success = false;
	TCHAR filename[MAX_PATH];
	success=!!DragQueryFile(hDrop, 0, filename, MAX_PATH);
	if(success) 
	{
		if(!(GetFileAttributes(filename) & FILE_ATTRIBUTE_DIRECTORY))
		{
			OpenFile(filename);
		}
	}

}

void CMainDlg::OpenFile(LPCTSTR pszFileName)
{
	if(!m_logAdapter->Load(pszFileName)) return;
	
	TCHAR szName[MAX_PATH];
	_tsplitpath(pszFileName,NULL,NULL,szName,NULL);
	SStringT strFmt = GETSTRING(R.string.title);
	SStringT strTitle = SStringT().Format(S_CW2T(strFmt),szName);
	FindChildByID(R.id.txt_title)->SetWindowText(strTitle);
	CSimpleWnd::SetWindowText(strTitle);

	ILogParse *pLogParser = m_logAdapter->GetLogParse();
	if(pLogParser)
	{
		m_cbxLevels->ResetContent();
		int nLevels = pLogParser->GetLevels();
		wchar_t (*szLevels)[MAX_LEVEL_LENGTH] = new wchar_t[nLevels][MAX_LEVEL_LENGTH];
		pLogParser->GetLevelText(szLevels);
		for(int i=0;i<nLevels;i++)
		{
			m_cbxLevels->InsertItem(i,S_CW2T(szLevels[i]),0,i);
		}
		delete []szLevels;

	}

	SArray<SStringW> lstTags;
	m_logAdapter->GetTags(lstTags);
	m_pFilterDlg->UpdateTags(lstTags);


	SArray<UINT> lstPid;
	m_logAdapter->GetPids(lstPid);
	m_pFilterDlg->UpdatePids(lstPid);

	SArray<UINT> lstTid;
	m_logAdapter->GetTids(lstTid);
	m_pFilterDlg->UpdateTids(lstTid);

}

bool CMainDlg::OnLvContextMenu(CPoint pt)
{
	CPoint pt2 = pt;
	ClientToScreen(&pt2);

	SItemPanel *pItem = m_lvLogs->HitTest(pt);
	if(!pItem) return false;

	int iItem = pItem->GetItemIndex();
	SLogInfo *pLogInfo = m_logAdapter->GetLogInfo(iItem);

	SMenu menu;
	menu.LoadMenu(UIRES.smenu.menu_lv);
	SStringW str = TR(GETSTRING(R.string.exclude_tag),L"");
	str += pLogInfo->strTag;
	menu.ModifyMenuString(101,MF_BYCOMMAND,S_CW2T(str));
	str = TR(GETSTRING(R.string.only_tag),L"");
	str += pLogInfo->strTag;
	menu.ModifyMenuString(102,MF_BYCOMMAND,S_CW2T(str));

	int cmd = menu.TrackPopupMenu(TPM_RETURNCMD,pt2.x,pt2.y,NULL);
	if(cmd==100)
	{
		HGLOBAL hMen;   

		// 分配全局内存    
		hMen = GlobalAlloc(GMEM_MOVEABLE, pLogInfo->strContent.GetLength()*sizeof(WCHAR));    

		if (!hMen)   
		{   
			return false;         
		}   

		LPWSTR lpStr = (LPWSTR)GlobalLock(hMen);    

		// 内存复制   
		memcpy(lpStr, (LPCWSTR)pLogInfo->strContent, pLogInfo->strContent.GetLength()*sizeof(WCHAR));    
		// 释放锁    
		GlobalUnlock(hMen);   

		::OpenClipboard(m_hWnd);
		::SetClipboardData(CF_UNICODETEXT,hMen);
		::CloseClipboard();
	}else if(cmd == 101)
	{
		m_pFilterDlg->ExcludeTag(pLogInfo->strTag);
	}else if(cmd == 102)
	{
		m_pFilterDlg->OnlyTag(pLogInfo->strTag);
	}

	return true;
}

void CMainDlg::UpdateFilterTags(const SArray<SStringW>& lstTags)
{
	m_logAdapter->SetFilterTags(lstTags);
}

void CMainDlg::UpdateFilterPids(const SArray<UINT> & lstPid)
{
	m_logAdapter->SetFilterPids(lstPid);
}

void CMainDlg::UpdateFilterTids(const SArray<UINT> & lstTid)
{
	m_logAdapter->SetFilterTids(lstTid);
}

void CMainDlg::OnOpenFindDlg()
{
	if(m_pFindDlg==NULL)
	{
		m_pFindDlg = new CFindDlg(this);
		m_pFindDlg->Create(m_hWnd);
		m_pFindDlg->CenterWindow(m_pSciter->m_hWnd);
	}		
	m_pFindDlg->ShowWindow(SW_SHOW);
}


int CMainDlg::FindInTarget(std::string findWhatText, int startPosition, int endPosition)
{
	int findStyle = 0;
	bool findInStyle = false;
	size_t lenFind = findWhatText.length();
	m_pSciter->SendMessage(SCI_SETTARGETSTART, startPosition);
	m_pSciter->SendMessage(SCI_SETTARGETEND, endPosition);
	int posFind = m_pSciter->SendMessage(SCI_SEARCHINTARGET, lenFind, reinterpret_cast<sptr_t>(findWhatText.c_str()));
	while (findInStyle && posFind != -1 && findStyle != m_pSciter->SendMessage(SCI_GETSTYLEAT, posFind))
	{
		if (startPosition < endPosition) {
			m_pSciter->SendMessage(SCI_SETTARGETSTART, posFind + 1);
			m_pSciter->SendMessage(SCI_SETTARGETEND, endPosition);
		}
		else {
			m_pSciter->SendMessage(SCI_SETTARGETSTART, startPosition);
			m_pSciter->SendMessage(SCI_SETTARGETEND, posFind + 1);
		}
		posFind = m_pSciter->SendMessage(SCI_SEARCHINTARGET, lenFind, reinterpret_cast<sptr_t>(findWhatText.c_str()));
	}
	return posFind;
}


std::string EncodeString(const std::string &s) 
{
	return s;
}


static bool IsOctalDigit(char ch) {
	return ch >= '0' && ch <= '7';
}

/**
* Convert C style \0oo into their indicated characters.
* This is used to get control characters into the regular expresion engine.
*/
static unsigned int UnSlashLowOctal(char *s) {
	const char *sStart = s;
	char *o = s;
	while (*s) {
		if ((s[0] == '\\') && (s[1] == '0') && IsOctalDigit(s[2]) && IsOctalDigit(s[3])) {
			*o = static_cast<char>(8 * (s[2] - '0') + (s[3] - '0'));
			s += 3;
		}
		else {
			*o = *s;
		}
		o++;
		if (*s)
			s++;
	}
	*o = '\0';
	return static_cast<unsigned int>(o - sStart);
}

std::string UnSlashLowOctalString(const char *s) {
	std::string sCopy(s, strlen(s) + 1);
	unsigned int len = UnSlashLowOctal(&sCopy[0]);
	return sCopy.substr(0, len);
}


/**
* If the character is an hexa digit, get its value.
*/
static int GetHexaDigit(char ch) {
	if (ch >= '0' && ch <= '9') {
		return ch - '0';
	}
	if (ch >= 'A' && ch <= 'F') {
		return ch - 'A' + 10;
	}
	if (ch >= 'a' && ch <= 'f') {
		return ch - 'a' + 10;
	}
	return -1;
}

/**
* Convert C style \a, \b, \f, \n, \r, \t, \v, \ooo and \xhh into their indicated characters.
*/
unsigned int UnSlash(char *s) {
	const char *sStart = s;
	char *o = s;

	while (*s) {
		if (*s == '\\') {
			s++;
			if (*s == 'a') {
				*o = '\a';
			}
			else if (*s == 'b') {
				*o = '\b';
			}
			else if (*s == 'f') {
				*o = '\f';
			}
			else if (*s == 'n') {
				*o = '\n';
			}
			else if (*s == 'r') {
				*o = '\r';
			}
			else if (*s == 't') {
				*o = '\t';
			}
			else if (*s == 'v') {
				*o = '\v';
			}
			else if (IsOctalDigit(*s)) {
				int val = *s - '0';
				if (IsOctalDigit(*(s + 1))) {
					s++;
					val *= 8;
					val += *s - '0';
					if (IsOctalDigit(*(s + 1))) {
						s++;
						val *= 8;
						val += *s - '0';
					}
				}
				*o = static_cast<char>(val);
			}
			else if (*s == 'x') {
				s++;
				int val = 0;
				int ghd = GetHexaDigit(*s);
				if (ghd >= 0) {
					s++;
					val = ghd;
					ghd = GetHexaDigit(*s);
					if (ghd >= 0) {
						s++;
						val *= 16;
						val += ghd;
					}
				}
				*o = static_cast<char>(val);
			}
			else {
				*o = *s;
			}
		}
		else {
			*o = *s;
		}
		o++;
		if (*s) {
			s++;
		}
	}
	*o = '\0';
	return static_cast<unsigned int>(o - sStart);
}


std::string UnSlashString(const char *s) {
	std::string sCopy(s, strlen(s) + 1);
	unsigned int len = UnSlash(&sCopy[0]);
	return sCopy.substr(0, len);
}


static std::string UnSlashAsNeeded(const std::string &s, bool escapes, bool regularExpression) {
	if (escapes) {
		if (regularExpression) {
			// For regular expressions, the only escape sequences allowed start with \0
			// Other sequences, like \t, are handled by the RE engine.
			return UnSlashLowOctalString(s.c_str());
		}
		else {
			// C style escapes allowed
			return UnSlashString(s.c_str());
		}
	}
	else {
		return s;
	}
}


Sci_CharacterRange CMainDlg::GetSelection()
{
	Sci_CharacterRange crange;
	crange.cpMin = m_pSciter->SendMessage(SCI_GETSELECTIONSTART);
	crange.cpMax = m_pSciter->SendMessage(SCI_GETSELECTIONEND);
	return crange;
} 

int CMainDlg::LengthDocument()
{
	return m_pSciter->SendMessage(SCI_GETLENGTH);
}


inline int Minimum(int a, int b) {
	return (a < b) ? a : b;
}

inline int Maximum(int a, int b) {
	return (a > b) ? a : b;
}

 
void CMainDlg::EnsureRangeVisible(int posStart, int posEnd, bool enforcePolicy)
{
	int lineStart = m_pSciter->SendMessage(SCI_LINEFROMPOSITION, Minimum(posStart, posEnd));
	int lineEnd = m_pSciter->SendMessage(SCI_LINEFROMPOSITION, Maximum(posStart, posEnd));
	for (int line = lineStart; line <= lineEnd; line++) {
		m_pSciter->SendMessage(enforcePolicy ? SCI_ENSUREVISIBLEENFORCEPOLICY : SCI_ENSUREVISIBLE, line);
	}
}


void CMainDlg::SetSelection(int anchor, int currentPos)
{
	m_pSciter->SendMessage(SCI_SETSEL, anchor, currentPos);
}


int CMainDlg::FindNext(const std::string &findWhat, bool bMatchCase, bool bMatchWholeWord,bool reverseDirection, bool showWarnings, bool allowRegExp)
{
	if (findWhat.length() == 0) {
		return -1;
	}

	bool regExp = true;
	bool unSlash = false;

	const std::string findTarget = UnSlashAsNeeded(EncodeString(findWhat), unSlash, regExp);
	if (findTarget.length() == 0)
		return -1;

	Sci_CharacterRange cr = GetSelection();
	int startPosition = static_cast<int>(cr.cpMax);
	int endPosition = LengthDocument();
	if (reverseDirection) {
		startPosition = static_cast<int>(cr.cpMin);
		endPosition = 0;
	}
	 
	  
	bool wrapFind = true;
	bool wholeWord = bMatchWholeWord;
	bool matchCase = bMatchCase;
	bool havefound = false;
	bool failedfind = false; 

	bool regularExpressions = allowRegExp && regExp;
	int nSearchFlags = (wholeWord ? SCFIND_WHOLEWORD : 0) |
		(matchCase ? SCFIND_MATCHCASE : 0) |
		(regularExpressions ? SCFIND_REGEXP : 0) |
		(0) |
		(0);
	 

	m_pSciter->SendMessage(SCI_SETSEARCHFLAGS, nSearchFlags);
	int posFind = FindInTarget(findTarget, startPosition, endPosition);
	if (posFind == -1 && wrapFind) {
		// Failed to find in indicated direction
		// so search from the beginning (forward) or from the end (reverse)
		// unless wrapFind is false
		if (reverseDirection) {
			startPosition = LengthDocument();
			endPosition = 0;
		}
		else {
			startPosition = 0;
			endPosition = LengthDocument();
		}
		posFind = FindInTarget(findTarget, startPosition, endPosition);
		//提示用户继续循环查找？
	}
	if (posFind == -1) {
		havefound = false;
		failedfind = true;
		if (showWarnings) {
			::MessageBoxA(NULL, "找不到找定的字符串", "提示", 0);
		}
	}
	else {
		havefound = true;
		failedfind = false;
		int start = m_pSciter->SendMessage(SCI_GETTARGETSTART);
		int end = m_pSciter->SendMessage(SCI_GETTARGETEND);
		// Ensure found text is styled so that caret will be made visible.
		int endStyled = m_pSciter->SendMessage(SCI_GETENDSTYLED);
		if (endStyled < end)
			m_pSciter->SendMessage(SCI_COLOURISE, endStyled, end);
		EnsureRangeVisible(start, end);
		m_pSciter->SendMessage(SCI_SCROLLRANGE, start, end);
		m_pSciter->SendMessage(SCI_SETTARGETRANGE, start, end);
		SetSelection(start, end);
	}
	return posFind;
}

std::string UTF8FromUTF16(const std::wstring & utf16)
{
	//
	// Special case of empty input string
	//
	if (utf16.empty())
		return std::string();


	//
	// Get length (in chars) of resulting UTF-8 string
	//
	const int utf8Length = ::WideCharToMultiByte(
		CP_UTF8,            // convert to UTF-8
		0,                  // default flags
		utf16.data(),       // source UTF-16 string
		utf16.length(),     // source string length, in wchar_t's,
		NULL,               // unused - no conversion required in this step
		0,                  // request buffer size
		NULL, NULL          // unused
	);
	if (utf8Length == 0)
	{
		return "";
	}


	//
	// Allocate destination buffer for UTF-8 string
	//
	std::string utf8;
	utf8.resize(utf8Length);


	//
	// Do the conversion from UTF-16 to UTF-8
	//
	if (!::WideCharToMultiByte(
		CP_UTF8,                // convert to UTF-8
		0,                      // default flags
		utf16.data(),           // source UTF-16 string
		utf16.length(),         // source string length, in wchar_t's,
		&utf8[0],               // destination buffer
		utf8.length(),          // destination buffer size, in chars
		NULL, NULL              // unused
	))
	{
		// Error
		return "";
	}


	//
	// Return resulting UTF-8 string
	//
	return utf8;
}


bool CMainDlg::OnFind(const SStringT & strText, bool bFindNext, bool bMatchCase, bool bMatchWholeWord)
{
	std::string utf8_str =  UTF8FromUTF16((std::wstring)strText);
	FindNext(utf8_str, bMatchCase,  bMatchWholeWord,false, true, false);
	m_pSciter->SetFocus();
	return true;
	/*
	int flags = (bMatchCase?SCFIND_MATCHCASE:0) | (bMatchWholeWord?SCFIND_WHOLEWORD:0);
	TextToFind ttf;
	ttf.chrg.cpMin = m_pSciter->SendMessage(SCI_GETCURRENTPOS);
	if(bFindNext)
		ttf.chrg.cpMax = m_pSciter->SendMessage(SCI_GETLENGTH, 0, 0);
	else
		ttf.chrg.cpMax = 0;

	SStringA strUtf8 = S_CT2A(strText,CP_UTF8);
	ttf.lpstrText = (char *)(LPCSTR) strUtf8;
	int nPos = m_pSciter->SendMessage(SCI_FINDTEXT,flags,(LPARAM)&ttf);
	if(nPos==-1) return false;
	
	if(bFindNext)
		m_pSciter->SendMessage(SCI_SETSEL,nPos,nPos + strUtf8.GetLength());
	else
		m_pSciter->SendMessage(SCI_SETSEL,nPos+ strUtf8.GetLength(),nPos);

	m_pSciter->SetFocus();

	return true;
	*/
}

void CMainDlg::OnContextMenu(HWND hwnd, CPoint point)
{
	if(hwnd == m_pSciter->m_hWnd)
	{
		pugi::xml_node xmlMenu = SRicheditMenuDef::getSingleton().GetMenuXml();
		if(xmlMenu)
		{
			SMenu menu;
			if(menu.LoadMenu(xmlMenu))
			{
				BOOL canPaste=m_pSciter->SendMessage(SCI_CANPASTE);
				BOOL hasSel=m_pSciter->SendMessage(SCI_GETSELECTIONEMPTY)==0;
				UINT uLen=m_pSciter->SendMessage(SCI_GETTEXTLENGTH ,0,0);
				EnableMenuItem(menu.m_hMenu,MENU_CUT,MF_BYCOMMAND|((hasSel)?0:MF_GRAYED));
				EnableMenuItem(menu.m_hMenu,MENU_COPY,MF_BYCOMMAND|(hasSel?0:MF_GRAYED));
				EnableMenuItem(menu.m_hMenu,MENU_PASTE,MF_BYCOMMAND|((canPaste)?0:MF_GRAYED));
				EnableMenuItem(menu.m_hMenu,MENU_DEL,MF_BYCOMMAND|((hasSel)?0:MF_GRAYED));
				EnableMenuItem(menu.m_hMenu,MENU_SELALL,MF_BYCOMMAND|((uLen>0)?0:MF_GRAYED));

				UINT uCmd=menu.TrackPopupMenu(TPM_RETURNCMD|TPM_LEFTALIGN,point.x,point.y,m_hWnd);
				switch(uCmd)
				{
				case MENU_CUT:
					m_pSciter->SendMessage(SCI_CUT);
					break;
				case MENU_COPY:
					m_pSciter->SendMessage(SCI_COPY);
					break;
				case MENU_PASTE:
					m_pSciter->SendMessage(SCI_PASTE);
					break;
				case MENU_DEL:
					m_pSciter->SendMessage(SCI_REPLACESEL,0,(LPARAM)_T(""));
					break;
				case MENU_SELALL:
					m_pSciter->SendMessage(SCI_SETSEL,0,-1);
					break;
				default:
					break;
				}
			}
		}
	}
}

