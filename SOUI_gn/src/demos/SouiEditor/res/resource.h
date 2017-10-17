//stamp:1d2f59075f566ea7
/*<------------------------------------------------------------------------------------------------->*/
/*该文件由uiresbuilder生成，请不要手动修改*/
/*<------------------------------------------------------------------------------------------------->*/
#pragma once
#include <res.mgr/snamedvalue.h>
#define ROBJ_IN_CPP \
namespace SOUI \
{\
    const _R R;\
    const _UIRES UIRES;\
}
namespace SOUI
{
	class _UIRES{
		public:
		class _UIDEF{
			public:
			_UIDEF(){
				XML_INIT = _T("UIDEF:XML_INIT");
			}
			const TCHAR * XML_INIT;
		}UIDEF;
		class _LAYOUT{
			public:
			_LAYOUT(){
				xml_messagebox = _T("LAYOUT:xml_messagebox");
				XML_MAINWND = _T("LAYOUT:XML_MAINWND");
				xml_mainwnd_left = _T("LAYOUT:xml_mainwnd_left");
				xml_mainwnd_right = _T("LAYOUT:xml_mainwnd_right");
				xml_uidesigner_main = _T("LAYOUT:xml_uidesigner_main");
				UIDESIGNER_XML_SKIN_SELECT = _T("LAYOUT:UIDESIGNER_XML_SKIN_SELECT");
				UIDESIGNER_XML_NEW_LAYOUT = _T("LAYOUT:UIDESIGNER_XML_NEW_LAYOUT");
				UIDESIGNER_XML_NEW_SKIN = _T("LAYOUT:UIDESIGNER_XML_NEW_SKIN");
				UIDESIGNER_XML_INPUT = _T("LAYOUT:UIDESIGNER_XML_INPUT");
				UIDESIGNER_XML_ABOUT = _T("LAYOUT:UIDESIGNER_XML_ABOUT");
				UIDESIGNER_XML_SYTLEMGR = _T("LAYOUT:UIDESIGNER_XML_SYTLEMGR");
				UIDESIGNER_XML_FONTSELECT = _T("LAYOUT:UIDESIGNER_XML_FONTSELECT");
			}
			const TCHAR * xml_messagebox;
			const TCHAR * XML_MAINWND;
			const TCHAR * xml_mainwnd_left;
			const TCHAR * xml_mainwnd_right;
			const TCHAR * xml_uidesigner_main;
			const TCHAR * UIDESIGNER_XML_SKIN_SELECT;
			const TCHAR * UIDESIGNER_XML_NEW_LAYOUT;
			const TCHAR * UIDESIGNER_XML_NEW_SKIN;
			const TCHAR * UIDESIGNER_XML_INPUT;
			const TCHAR * UIDESIGNER_XML_ABOUT;
			const TCHAR * UIDESIGNER_XML_SYTLEMGR;
			const TCHAR * UIDESIGNER_XML_FONTSELECT;
		}LAYOUT;
		class _values{
			public:
			_values(){
				string = _T("values:string");
				color = _T("values:color");
				skin = _T("values:skin");
			}
			const TCHAR * string;
			const TCHAR * color;
			const TCHAR * skin;
		}values;
		class _IMG{
			public:
			_IMG(){
				icon_main = _T("IMG:icon_main");
				caption_line = _T("IMG:caption_line");
				png_tool_button = _T("IMG:png_tool_button");
				png_prop_switch = _T("IMG:png_prop_switch");
				png_tab_skin = _T("IMG:png_tab_skin");
				png_btn_blue = _T("IMG:png_btn_blue");
				png_app_button = _T("IMG:png_app_button");
				default_scrollbar = _T("IMG:default.scrollbar");
				open_menu_png = _T("IMG:open_menu_png");
				tree_toggle_png = _T("IMG:tree_toggle_png");
				menu_skin_png = _T("IMG:menu_skin_png");
				menu_sep_png = _T("IMG:menu_sep_png");
			}
			const TCHAR * icon_main;
			const TCHAR * caption_line;
			const TCHAR * png_tool_button;
			const TCHAR * png_prop_switch;
			const TCHAR * png_tab_skin;
			const TCHAR * png_btn_blue;
			const TCHAR * png_app_button;
			const TCHAR * default_scrollbar;
			const TCHAR * open_menu_png;
			const TCHAR * tree_toggle_png;
			const TCHAR * menu_skin_png;
			const TCHAR * menu_sep_png;
		}IMG;
		class _ICON{
			public:
			_ICON(){
				ICON_LOGO = _T("ICON:ICON_LOGO");
			}
			const TCHAR * ICON_LOGO;
		}ICON;
		class _translator{
			public:
			_translator(){
				lang_cn = _T("translator:lang_cn");
				lang_jp = _T("translator:lang_jp");
			}
			const TCHAR * lang_cn;
			const TCHAR * lang_jp;
		}translator;
		class _smenu{
			public:
			_smenu(){
				menu_layoutfile = _T("smenu:menu_layoutfile");
			}
			const TCHAR * menu_layoutfile;
		}smenu;
	};
	const SNamedID::NAMEDVALUE namedXmlID[]={
		{L"NAME_UIDESIGNER_GRID_CONTAINER",65603},
		{L"NAME_UIDESIGNER_IMG_VIEW",65598},
		{L"NAME_UIDESIGNER_LB_SKIN",65602},
		{L"NAME_UIDESIGNER_LB_ZY",65597},
		{L"NAME_UIDESIGNER_LB_ZYLX",65592},
		{L"NAME_UIDESIGNER_NEW_SKIN_LB",65612},
		{L"NAME_UIDESIGNER_Right_MAIN_TAB",65575},
		{L"NAME_UIDESIGNER_btn_OK",65609},
		{L"NAME_UIDESIGNER_btn_SKIN_DEL",65601},
		{L"NAME_UIDESIGNER_btn_SKIN_new",65600},
		{L"NAME_UIDESIGNER_btn_ZYLX_DEL",65591},
		{L"NAME_UIDESIGNER_btn_ZYLX_new",65590},
		{L"NAME_UIDESIGNER_btn_ZY_DEL",65594},
		{L"NAME_UIDESIGNER_btn_ZY_NEW",65593},
		{L"NAME_UIDESIGNER_btn_ZY_NEWALL",65595},
		{L"NAME_UIDESIGNER_btn_close",65605},
		{L"NAME_UIDESIGNER_btn_dlg",65608},
		{L"NAME_UIDESIGNER_edit_SEARCH",65596},
		{L"NAME_UIDESIGNER_main_icon",65589},
		{L"NAME_UIDESIGNER_split_col",65564},
		{L"UI_main_caption",65546},
		{L"_name_start",65535},
		{L"apptitle",65547},
		{L"btnAdd",65615},
		{L"btnCancel",65611},
		{L"btnClose",65614},
		{L"btnDel",65616},
		{L"btnOK",65604},
		{L"btnSave",65619},
		{L"btnSwitch",65542},
		{L"btn_SetSkin",65552},
		{L"btn_close",65548},
		{L"btn_max",65549},
		{L"btn_min",65551},
		{L"btn_restore",65550},
		{L"button1st",65543},
		{L"button2nd",65544},
		{L"button3rd",65545},
		{L"chkBold",65623},
		{L"chkItalic",65624},
		{L"chkStrike",65626},
		{L"chkUnderline",65625},
		{L"cmbCtrl",65621},
		{L"col1",65580},
		{L"dropwindow",65587},
		{L"edtInput",65613},
		{L"edtSearch",65618},
		{L"edtSize",65628},
		{L"img_icon",65582},
		{L"img_icon_exclamation",65540},
		{L"img_icon_information",65538},
		{L"img_icon_question",65539},
		{L"lbFont",65622},
		{L"lbStyle",65617},
		{L"lb_allStyle",65584},
		{L"lv_allString",65585},
		{L"mclv_color",65583},
		{L"mclv_skin",65579},
		{L"msgicon",65537},
		{L"msgtext",65541},
		{L"msgtitle",65536},
		{L"new_layout_path",65607},
		{L"new_layout_resname",65606},
		{L"page_editor",65566},
		{L"sel_image_size",65599},
		{L"toolbar_btn_Close",65554},
		{L"toolbar_btn_NewDialog",65556},
		{L"toolbar_btn_NewInclude",65557},
		{L"toolbar_btn_Open",65553},
		{L"toolbar_btn_SaveAll",65558},
		{L"toolbar_btn_SaveLayout",65559},
		{L"toolbar_btn_YL",65561},
		{L"toolbar_btn_YSGL",65562},
		{L"toolbar_btn_ZYGL",65560},
		{L"toolbar_btn_about",65563},
		{L"toolbar_btn_reload",65555},
		{L"txt_name",65581},
		{L"txt_string",65586},
		{L"txt_title",65610},
		{L"uidesigner_CtrlTypename",65572},
		{L"uidesigner_DescText",65574},
		{L"uidesigner_control_list",65576},
		{L"uidesigner_curfile",65567},
		{L"uidesigner_maintab",65565},
		{L"uidesigner_nodenum",65577},
		{L"uidesigner_propContainer",65573},
		{L"uidesigner_scintilla",100000},
		{L"uidesigner_split_row",65568},
		{L"uidesigner_wnd_layout",65588},
		{L"uidesigner_wnd_xmltree",65578},
		{L"uidesigner_xml_scintilla",100000},
		{L"wndPreview",65627},
		{L"wndReal",0},
		{L"wndView",65620},
		{L"workspace_tab",65569},
		{L"workspace_tree",65570},
		{L"workspace_xmlfile_lb",65571}		};
	class _R{
	public:
		class _name{
		public:
		_name(){
			NAME_UIDESIGNER_GRID_CONTAINER = namedXmlID[0].strName;
			NAME_UIDESIGNER_IMG_VIEW = namedXmlID[1].strName;
			NAME_UIDESIGNER_LB_SKIN = namedXmlID[2].strName;
			NAME_UIDESIGNER_LB_ZY = namedXmlID[3].strName;
			NAME_UIDESIGNER_LB_ZYLX = namedXmlID[4].strName;
			NAME_UIDESIGNER_NEW_SKIN_LB = namedXmlID[5].strName;
			NAME_UIDESIGNER_Right_MAIN_TAB = namedXmlID[6].strName;
			NAME_UIDESIGNER_btn_OK = namedXmlID[7].strName;
			NAME_UIDESIGNER_btn_SKIN_DEL = namedXmlID[8].strName;
			NAME_UIDESIGNER_btn_SKIN_new = namedXmlID[9].strName;
			NAME_UIDESIGNER_btn_ZYLX_DEL = namedXmlID[10].strName;
			NAME_UIDESIGNER_btn_ZYLX_new = namedXmlID[11].strName;
			NAME_UIDESIGNER_btn_ZY_DEL = namedXmlID[12].strName;
			NAME_UIDESIGNER_btn_ZY_NEW = namedXmlID[13].strName;
			NAME_UIDESIGNER_btn_ZY_NEWALL = namedXmlID[14].strName;
			NAME_UIDESIGNER_btn_close = namedXmlID[15].strName;
			NAME_UIDESIGNER_btn_dlg = namedXmlID[16].strName;
			NAME_UIDESIGNER_edit_SEARCH = namedXmlID[17].strName;
			NAME_UIDESIGNER_main_icon = namedXmlID[18].strName;
			NAME_UIDESIGNER_split_col = namedXmlID[19].strName;
			UI_main_caption = namedXmlID[20].strName;
			_name_start = namedXmlID[21].strName;
			apptitle = namedXmlID[22].strName;
			btnAdd = namedXmlID[23].strName;
			btnCancel = namedXmlID[24].strName;
			btnClose = namedXmlID[25].strName;
			btnDel = namedXmlID[26].strName;
			btnOK = namedXmlID[27].strName;
			btnSave = namedXmlID[28].strName;
			btnSwitch = namedXmlID[29].strName;
			btn_SetSkin = namedXmlID[30].strName;
			btn_close = namedXmlID[31].strName;
			btn_max = namedXmlID[32].strName;
			btn_min = namedXmlID[33].strName;
			btn_restore = namedXmlID[34].strName;
			button1st = namedXmlID[35].strName;
			button2nd = namedXmlID[36].strName;
			button3rd = namedXmlID[37].strName;
			chkBold = namedXmlID[38].strName;
			chkItalic = namedXmlID[39].strName;
			chkStrike = namedXmlID[40].strName;
			chkUnderline = namedXmlID[41].strName;
			cmbCtrl = namedXmlID[42].strName;
			col1 = namedXmlID[43].strName;
			dropwindow = namedXmlID[44].strName;
			edtInput = namedXmlID[45].strName;
			edtSearch = namedXmlID[46].strName;
			edtSize = namedXmlID[47].strName;
			img_icon = namedXmlID[48].strName;
			img_icon_exclamation = namedXmlID[49].strName;
			img_icon_information = namedXmlID[50].strName;
			img_icon_question = namedXmlID[51].strName;
			lbFont = namedXmlID[52].strName;
			lbStyle = namedXmlID[53].strName;
			lb_allStyle = namedXmlID[54].strName;
			lv_allString = namedXmlID[55].strName;
			mclv_color = namedXmlID[56].strName;
			mclv_skin = namedXmlID[57].strName;
			msgicon = namedXmlID[58].strName;
			msgtext = namedXmlID[59].strName;
			msgtitle = namedXmlID[60].strName;
			new_layout_path = namedXmlID[61].strName;
			new_layout_resname = namedXmlID[62].strName;
			page_editor = namedXmlID[63].strName;
			sel_image_size = namedXmlID[64].strName;
			toolbar_btn_Close = namedXmlID[65].strName;
			toolbar_btn_NewDialog = namedXmlID[66].strName;
			toolbar_btn_NewInclude = namedXmlID[67].strName;
			toolbar_btn_Open = namedXmlID[68].strName;
			toolbar_btn_SaveAll = namedXmlID[69].strName;
			toolbar_btn_SaveLayout = namedXmlID[70].strName;
			toolbar_btn_YL = namedXmlID[71].strName;
			toolbar_btn_YSGL = namedXmlID[72].strName;
			toolbar_btn_ZYGL = namedXmlID[73].strName;
			toolbar_btn_about = namedXmlID[74].strName;
			toolbar_btn_reload = namedXmlID[75].strName;
			txt_name = namedXmlID[76].strName;
			txt_string = namedXmlID[77].strName;
			txt_title = namedXmlID[78].strName;
			uidesigner_CtrlTypename = namedXmlID[79].strName;
			uidesigner_DescText = namedXmlID[80].strName;
			uidesigner_control_list = namedXmlID[81].strName;
			uidesigner_curfile = namedXmlID[82].strName;
			uidesigner_maintab = namedXmlID[83].strName;
			uidesigner_nodenum = namedXmlID[84].strName;
			uidesigner_propContainer = namedXmlID[85].strName;
			uidesigner_scintilla = namedXmlID[86].strName;
			uidesigner_split_row = namedXmlID[87].strName;
			uidesigner_wnd_layout = namedXmlID[88].strName;
			uidesigner_wnd_xmltree = namedXmlID[89].strName;
			uidesigner_xml_scintilla = namedXmlID[90].strName;
			wndPreview = namedXmlID[91].strName;
			wndReal = namedXmlID[92].strName;
			wndView = namedXmlID[93].strName;
			workspace_tab = namedXmlID[94].strName;
			workspace_tree = namedXmlID[95].strName;
			workspace_xmlfile_lb = namedXmlID[96].strName;
		}
		 const wchar_t * NAME_UIDESIGNER_GRID_CONTAINER;
		 const wchar_t * NAME_UIDESIGNER_IMG_VIEW;
		 const wchar_t * NAME_UIDESIGNER_LB_SKIN;
		 const wchar_t * NAME_UIDESIGNER_LB_ZY;
		 const wchar_t * NAME_UIDESIGNER_LB_ZYLX;
		 const wchar_t * NAME_UIDESIGNER_NEW_SKIN_LB;
		 const wchar_t * NAME_UIDESIGNER_Right_MAIN_TAB;
		 const wchar_t * NAME_UIDESIGNER_btn_OK;
		 const wchar_t * NAME_UIDESIGNER_btn_SKIN_DEL;
		 const wchar_t * NAME_UIDESIGNER_btn_SKIN_new;
		 const wchar_t * NAME_UIDESIGNER_btn_ZYLX_DEL;
		 const wchar_t * NAME_UIDESIGNER_btn_ZYLX_new;
		 const wchar_t * NAME_UIDESIGNER_btn_ZY_DEL;
		 const wchar_t * NAME_UIDESIGNER_btn_ZY_NEW;
		 const wchar_t * NAME_UIDESIGNER_btn_ZY_NEWALL;
		 const wchar_t * NAME_UIDESIGNER_btn_close;
		 const wchar_t * NAME_UIDESIGNER_btn_dlg;
		 const wchar_t * NAME_UIDESIGNER_edit_SEARCH;
		 const wchar_t * NAME_UIDESIGNER_main_icon;
		 const wchar_t * NAME_UIDESIGNER_split_col;
		 const wchar_t * UI_main_caption;
		 const wchar_t * _name_start;
		 const wchar_t * apptitle;
		 const wchar_t * btnAdd;
		 const wchar_t * btnCancel;
		 const wchar_t * btnClose;
		 const wchar_t * btnDel;
		 const wchar_t * btnOK;
		 const wchar_t * btnSave;
		 const wchar_t * btnSwitch;
		 const wchar_t * btn_SetSkin;
		 const wchar_t * btn_close;
		 const wchar_t * btn_max;
		 const wchar_t * btn_min;
		 const wchar_t * btn_restore;
		 const wchar_t * button1st;
		 const wchar_t * button2nd;
		 const wchar_t * button3rd;
		 const wchar_t * chkBold;
		 const wchar_t * chkItalic;
		 const wchar_t * chkStrike;
		 const wchar_t * chkUnderline;
		 const wchar_t * cmbCtrl;
		 const wchar_t * col1;
		 const wchar_t * dropwindow;
		 const wchar_t * edtInput;
		 const wchar_t * edtSearch;
		 const wchar_t * edtSize;
		 const wchar_t * img_icon;
		 const wchar_t * img_icon_exclamation;
		 const wchar_t * img_icon_information;
		 const wchar_t * img_icon_question;
		 const wchar_t * lbFont;
		 const wchar_t * lbStyle;
		 const wchar_t * lb_allStyle;
		 const wchar_t * lv_allString;
		 const wchar_t * mclv_color;
		 const wchar_t * mclv_skin;
		 const wchar_t * msgicon;
		 const wchar_t * msgtext;
		 const wchar_t * msgtitle;
		 const wchar_t * new_layout_path;
		 const wchar_t * new_layout_resname;
		 const wchar_t * page_editor;
		 const wchar_t * sel_image_size;
		 const wchar_t * toolbar_btn_Close;
		 const wchar_t * toolbar_btn_NewDialog;
		 const wchar_t * toolbar_btn_NewInclude;
		 const wchar_t * toolbar_btn_Open;
		 const wchar_t * toolbar_btn_SaveAll;
		 const wchar_t * toolbar_btn_SaveLayout;
		 const wchar_t * toolbar_btn_YL;
		 const wchar_t * toolbar_btn_YSGL;
		 const wchar_t * toolbar_btn_ZYGL;
		 const wchar_t * toolbar_btn_about;
		 const wchar_t * toolbar_btn_reload;
		 const wchar_t * txt_name;
		 const wchar_t * txt_string;
		 const wchar_t * txt_title;
		 const wchar_t * uidesigner_CtrlTypename;
		 const wchar_t * uidesigner_DescText;
		 const wchar_t * uidesigner_control_list;
		 const wchar_t * uidesigner_curfile;
		 const wchar_t * uidesigner_maintab;
		 const wchar_t * uidesigner_nodenum;
		 const wchar_t * uidesigner_propContainer;
		 const wchar_t * uidesigner_scintilla;
		 const wchar_t * uidesigner_split_row;
		 const wchar_t * uidesigner_wnd_layout;
		 const wchar_t * uidesigner_wnd_xmltree;
		 const wchar_t * uidesigner_xml_scintilla;
		 const wchar_t * wndPreview;
		 const wchar_t * wndReal;
		 const wchar_t * wndView;
		 const wchar_t * workspace_tab;
		 const wchar_t * workspace_tree;
		 const wchar_t * workspace_xmlfile_lb;
		}name;

		class _id{
		public:
		const static int NAME_UIDESIGNER_GRID_CONTAINER	=	65603;
		const static int NAME_UIDESIGNER_IMG_VIEW	=	65598;
		const static int NAME_UIDESIGNER_LB_SKIN	=	65602;
		const static int NAME_UIDESIGNER_LB_ZY	=	65597;
		const static int NAME_UIDESIGNER_LB_ZYLX	=	65592;
		const static int NAME_UIDESIGNER_NEW_SKIN_LB	=	65612;
		const static int NAME_UIDESIGNER_Right_MAIN_TAB	=	65575;
		const static int NAME_UIDESIGNER_btn_OK	=	65609;
		const static int NAME_UIDESIGNER_btn_SKIN_DEL	=	65601;
		const static int NAME_UIDESIGNER_btn_SKIN_new	=	65600;
		const static int NAME_UIDESIGNER_btn_ZYLX_DEL	=	65591;
		const static int NAME_UIDESIGNER_btn_ZYLX_new	=	65590;
		const static int NAME_UIDESIGNER_btn_ZY_DEL	=	65594;
		const static int NAME_UIDESIGNER_btn_ZY_NEW	=	65593;
		const static int NAME_UIDESIGNER_btn_ZY_NEWALL	=	65595;
		const static int NAME_UIDESIGNER_btn_close	=	65605;
		const static int NAME_UIDESIGNER_btn_dlg	=	65608;
		const static int NAME_UIDESIGNER_edit_SEARCH	=	65596;
		const static int NAME_UIDESIGNER_main_icon	=	65589;
		const static int NAME_UIDESIGNER_split_col	=	65564;
		const static int UI_main_caption	=	65546;
		const static int _name_start	=	65535;
		const static int apptitle	=	65547;
		const static int btnAdd	=	65615;
		const static int btnCancel	=	65611;
		const static int btnClose	=	65614;
		const static int btnDel	=	65616;
		const static int btnOK	=	65604;
		const static int btnSave	=	65619;
		const static int btnSwitch	=	65542;
		const static int btn_SetSkin	=	65552;
		const static int btn_close	=	65548;
		const static int btn_max	=	65549;
		const static int btn_min	=	65551;
		const static int btn_restore	=	65550;
		const static int button1st	=	65543;
		const static int button2nd	=	65544;
		const static int button3rd	=	65545;
		const static int chkBold	=	65623;
		const static int chkItalic	=	65624;
		const static int chkStrike	=	65626;
		const static int chkUnderline	=	65625;
		const static int cmbCtrl	=	65621;
		const static int col1	=	65580;
		const static int dropwindow	=	65587;
		const static int edtInput	=	65613;
		const static int edtSearch	=	65618;
		const static int edtSize	=	65628;
		const static int img_icon	=	65582;
		const static int img_icon_exclamation	=	65540;
		const static int img_icon_information	=	65538;
		const static int img_icon_question	=	65539;
		const static int lbFont	=	65622;
		const static int lbStyle	=	65617;
		const static int lb_allStyle	=	65584;
		const static int lv_allString	=	65585;
		const static int mclv_color	=	65583;
		const static int mclv_skin	=	65579;
		const static int msgicon	=	65537;
		const static int msgtext	=	65541;
		const static int msgtitle	=	65536;
		const static int new_layout_path	=	65607;
		const static int new_layout_resname	=	65606;
		const static int page_editor	=	65566;
		const static int sel_image_size	=	65599;
		const static int toolbar_btn_Close	=	65554;
		const static int toolbar_btn_NewDialog	=	65556;
		const static int toolbar_btn_NewInclude	=	65557;
		const static int toolbar_btn_Open	=	65553;
		const static int toolbar_btn_SaveAll	=	65558;
		const static int toolbar_btn_SaveLayout	=	65559;
		const static int toolbar_btn_YL	=	65561;
		const static int toolbar_btn_YSGL	=	65562;
		const static int toolbar_btn_ZYGL	=	65560;
		const static int toolbar_btn_about	=	65563;
		const static int toolbar_btn_reload	=	65555;
		const static int txt_name	=	65581;
		const static int txt_string	=	65586;
		const static int txt_title	=	65610;
		const static int uidesigner_CtrlTypename	=	65572;
		const static int uidesigner_DescText	=	65574;
		const static int uidesigner_control_list	=	65576;
		const static int uidesigner_curfile	=	65567;
		const static int uidesigner_maintab	=	65565;
		const static int uidesigner_nodenum	=	65577;
		const static int uidesigner_propContainer	=	65573;
		const static int uidesigner_scintilla	=	100000;
		const static int uidesigner_split_row	=	65568;
		const static int uidesigner_wnd_layout	=	65588;
		const static int uidesigner_wnd_xmltree	=	65578;
		const static int uidesigner_xml_scintilla	=	100000;
		const static int wndPreview	=	65627;
		const static int wndReal	=	0;
		const static int wndView	=	65620;
		const static int workspace_tab	=	65569;
		const static int workspace_tree	=	65570;
		const static int workspace_xmlfile_lb	=	65571;
		}id;

		class _string{
		public:
		const static int openincode	=	0;
		const static int title	=	1;
		const static int ver	=	2;
		}string;

		class _color{
		public:
		const static int bkBlack1	=	0;
		const static int bkBlack2	=	1;
		const static int blue	=	2;
		const static int gray	=	3;
		const static int green	=	4;
		const static int imgprviewbg	=	5;
		const static int itemHover	=	6;
		const static int itemSelected	=	7;
		const static int red	=	8;
		const static int white	=	9;
		}color;

	};

#ifdef R_IN_CPP
	 extern const _R R;
	 extern const _UIRES UIRES;
#else
	 extern const __declspec(selectany) _R & R = _R();
	 extern const __declspec(selectany) _UIRES & UIRES = _UIRES();
#endif//R_IN_CPP
}
