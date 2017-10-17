#include "SkinMgr.h"

using namespace SOUI;

EVENT_MAP_BEGIN(CSkinMgr)
	EVENT_NAME_COMMAND(L"btn_skin_close", OnClose)
	EVENT_NAME_COMMAND(L"btn_skinmgr_maxspeed", OnBtnMaxspeed)
	EVENT_NAME_COMMAND(L"btn_skinmgr_deepblue", OnBtnDeepblue)
	EVENT_NAME_COMMAND(L"btn_skinmgr_selfdefine", OnBtnSelfdefine)
	EVENT_NAME_COMMAND(L"btn_skinmgr_bigbang", OnBtnBigbang)
	EVENT_NAME_COMMAND(L"btn_skinmgr_prev", OnBtnPrev)
	EVENT_NAME_COMMAND(L"btn_skinmgr_choosing1", OnBtnChoosing1)
	EVENT_NAME_COMMAND(L"btn_skinmgr_choosing2", OnBtnChoosing2)
	EVENT_NAME_COMMAND(L"btn_skinmgr_next", OnBtnNext)
	EVENT_NAME_COMMAND(L"btn_skinmgr_color1", OnBtnColor1)
	EVENT_NAME_COMMAND(L"btn_skinmgr_color2", OnBtnColor2)
	EVENT_NAME_COMMAND(L"btn_skinmgr_color3", OnBtnColor3)
	EVENT_NAME_COMMAND(L"btn_skinmgr_color4", OnBtnColor4)
	EVENT_NAME_COMMAND(L"btn_skinmgr_color5", OnBtnColor5)
	EVENT_NAME_COMMAND(L"btn_skinmgr_color6", OnBtnColor6)
	EVENT_NAME_COMMAND(L"btn_skinmgr_color7", OnBtnColor7)
	EVENT_NAME_COMMAND(L"btn_skinmgr_color8", OnBtnColor8)
	EVENT_NAME_COMMAND(L"btn_skinmgr_color9", OnBtnColor9)
	EVENT_NAME_COMMAND(L"btn_skinmgr_color10", OnBtnColor10)
	EVENT_NAME_COMMAND(L"btn_skinmgr_color11", OnBtnColor11)
	EVENT_NAME_COMMAND(L"btn_skinmgr_color12", OnBtnColor12)
EVENT_MAP_END()

//窗口消息处理映射表
BEGIN_MSG_MAP_EX(CSkinMgr)
	MSG_WM_INITDIALOG(OnInitDialog)
	MSG_WM_CLOSE(OnClose)
	CHAIN_MSG_MAP(SHostWnd)//注意将没有处理的消息交给基类处理
	REFLECT_NOTIFICATIONS_EX()
END_MSG_MAP()

CSkinMgr::CSkinMgr(void) : SHostWnd(_T("LAYOUT:XML_WINSKINS"))
{
	m_bLayoutInited=FALSE;
}

CSkinMgr::~CSkinMgr(void)
{
}

BOOL CSkinMgr::OnInitDialog( HWND hWnd, LPARAM lParam )
{
	m_bLayoutInited=TRUE;

	return 0;
}

void CSkinMgr::OnBtnMaxspeed()		//极速
{
	SMessageBox(NULL,_T("极速"),_T("haha"),MB_OK|MB_ICONEXCLAMATION);
}

void CSkinMgr::OnBtnDeepblue()		//深湖蓝
{
	SMessageBox(NULL,_T("深湖蓝"),_T("haha"),MB_OK|MB_ICONEXCLAMATION);
}

void CSkinMgr::OnBtnSelfdefine()	//自定义
{
	SMessageBox(NULL,_T("自定义"),_T("haha"),MB_OK|MB_ICONEXCLAMATION);
}

void CSkinMgr::OnBtnBigbang()		//大片风暴
{
	SMessageBox(NULL,_T("大片风暴"),_T("haha"),MB_OK|MB_ICONEXCLAMATION);
}

void CSkinMgr::OnBtnPrev()			//上一个皮肤
{
	SMessageBox(NULL,_T("上一个皮肤"),_T("haha"),MB_OK|MB_ICONEXCLAMATION);
}

void CSkinMgr::OnBtnChoosing1()			//已有的皮肤1
{
	SMessageBox(NULL,_T("已有的皮肤1"),_T("haha"),MB_OK|MB_ICONEXCLAMATION);
}

void CSkinMgr::OnBtnChoosing2()			//已有的皮肤2
{
	SMessageBox(NULL,_T("已有的皮肤2"),_T("haha"),MB_OK|MB_ICONEXCLAMATION);
}

void CSkinMgr::OnBtnNext()				//下一个皮肤
{
	SMessageBox(NULL,_T("下一个皮肤"),_T("haha"),MB_OK|MB_ICONEXCLAMATION);
}

void CSkinMgr::OnBtnColor1()				//配色1
{
	SMessageBox(NULL,_T("配色1"),_T("haha"),MB_OK|MB_ICONEXCLAMATION);
}

void CSkinMgr::OnBtnColor2()				//配色2
{
	SMessageBox(NULL,_T("配色2"),_T("haha"),MB_OK|MB_ICONEXCLAMATION);
}

void CSkinMgr::OnBtnColor3()				//配色3
{
	SMessageBox(NULL,_T("配色3"),_T("haha"),MB_OK|MB_ICONEXCLAMATION);
}

void CSkinMgr::OnBtnColor4()				//配色4
{
	SMessageBox(NULL,_T("配色4"),_T("haha"),MB_OK|MB_ICONEXCLAMATION);
}

void CSkinMgr::OnBtnColor5()				//配色5
{
	SMessageBox(NULL,_T("配色5"),_T("haha"),MB_OK|MB_ICONEXCLAMATION);
}

void CSkinMgr::OnBtnColor6()				//配色6
{
	SMessageBox(NULL,_T("配色6"),_T("haha"),MB_OK|MB_ICONEXCLAMATION);
}

void CSkinMgr::OnBtnColor7()				//配色7
{
	SMessageBox(NULL,_T("配色7"),_T("haha"),MB_OK|MB_ICONEXCLAMATION);
}

void CSkinMgr::OnBtnColor8()				//配色8
{
	SMessageBox(NULL,_T("配色8"),_T("haha"),MB_OK|MB_ICONEXCLAMATION);
}

void CSkinMgr::OnBtnColor9()				//配色9
{
	SMessageBox(NULL,_T("配色9"),_T("haha"),MB_OK|MB_ICONEXCLAMATION);
}

void CSkinMgr::OnBtnColor10()				//配色10
{
	SMessageBox(NULL,_T("配色10"),_T("haha"),MB_OK|MB_ICONEXCLAMATION);
}

void CSkinMgr::OnBtnColor11()				//配色11
{
	SMessageBox(NULL,_T("配色11"),_T("haha"),MB_OK|MB_ICONEXCLAMATION);
}

void CSkinMgr::OnBtnColor12()				//配色12
{
	SMessageBox(NULL,_T("配色12"),_T("haha"),MB_OK|MB_ICONEXCLAMATION);
}