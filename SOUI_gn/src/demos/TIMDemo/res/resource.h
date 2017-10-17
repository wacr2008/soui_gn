//stamp:1d2da6af2d859c98
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
				xml_init = _T("UIDEF:xml_init");
			}
			const TCHAR * xml_init;
		}UIDEF;
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
		class _layout{
			public:
			_layout(){
				wnd_main = _T("layout:wnd_main");
				layout_asyncmsgbox = _T("layout:layout_asyncmsgbox");
				wnd_msgtooltip = _T("layout:wnd_msgtooltip");
				page_talk = _T("layout:page_talk");
				page_contact = _T("layout:page_contact");
				menu_tray = _T("layout:menu_tray");
				menu_template = _T("layout:menu_template");
				FileOleLayout = _T("layout:FileOleLayout");
				SeperatorOleLayout = _T("layout:SeperatorOleLayout");
				ImageOleLayout = _T("layout:ImageOleLayout");
				FetchMoreOleLayout = _T("layout:FetchMoreOleLayout");
				RemainderOleLayout = _T("layout:RemainderOleLayout");
				MetaFileOleLayout = _T("layout:MetaFileOleLayout");
			}
			const TCHAR * wnd_main;
			const TCHAR * layout_asyncmsgbox;
			const TCHAR * wnd_msgtooltip;
			const TCHAR * page_talk;
			const TCHAR * page_contact;
			const TCHAR * menu_tray;
			const TCHAR * menu_template;
			const TCHAR * FileOleLayout;
			const TCHAR * SeperatorOleLayout;
			const TCHAR * ImageOleLayout;
			const TCHAR * FetchMoreOleLayout;
			const TCHAR * RemainderOleLayout;
			const TCHAR * MetaFileOleLayout;
		}layout;
		class _image{
			public:
			_image(){
				btn_close = _T("image:btn_close");
				btn_menu = _T("image:btn_menu");
				btn_min = _T("image:btn_min");
				btn_reg = _T("image:btn_reg");
				img_busy = _T("image:img_busy");
				shadow = _T("image:shadow");
				bg = _T("image:bg");
				menu_bk = _T("image:menu_bk");
				vscrollbar = _T("image:vscrollbar");
				btn_del = _T("image:btn_del");
				rich_left_bubble = _T("image:rich_left_bubble");
				rich_right_bubble = _T("image:rich_right_bubble");
				rich_center_bk = _T("image:rich_center_bk");
				rich_file_bk = _T("image:rich_file_bk");
				fetch_more = _T("image:fetch_more");
				check_chat_font = _T("image:check_chat_font");
				btn_chat_sendpic = _T("image:btn_chat_sendpic");
				btn_chat_upload = _T("image:btn_chat_upload");
				btn_chat_cut = _T("image:btn_chat_cut");
				tab = _T("image:tab");
				icon_talk = _T("image:icon_talk");
				icon_contact = _T("image:icon_contact");
				icon_count = _T("image:icon_count");
				btn_talk = _T("image:btn_talk");
				warning = _T("image:warning");
				loading16 = _T("image:loading16");
				mask_30 = _T("image:mask_30");
				mask_42 = _T("image:mask_42");
				my = _T("image:my");
				default_cpp = _T("image:default");
			}
			const TCHAR * btn_close;
			const TCHAR * btn_menu;
			const TCHAR * btn_min;
			const TCHAR * btn_reg;
			const TCHAR * img_busy;
			const TCHAR * shadow;
			const TCHAR * bg;
			const TCHAR * menu_bk;
			const TCHAR * vscrollbar;
			const TCHAR * btn_del;
			const TCHAR * rich_left_bubble;
			const TCHAR * rich_right_bubble;
			const TCHAR * rich_center_bk;
			const TCHAR * rich_file_bk;
			const TCHAR * fetch_more;
			const TCHAR * check_chat_font;
			const TCHAR * btn_chat_sendpic;
			const TCHAR * btn_chat_upload;
			const TCHAR * btn_chat_cut;
			const TCHAR * tab;
			const TCHAR * icon_talk;
			const TCHAR * icon_contact;
			const TCHAR * icon_count;
			const TCHAR * btn_talk;
			const TCHAR * warning;
			const TCHAR * loading16;
			const TCHAR * mask_30;
			const TCHAR * mask_42;
			const TCHAR * my;
			const TCHAR * default_cpp;
		}image;
	};
	const SNamedID::NAMEDVALUE namedXmlID[]={
		{L"_name_start",65535},
		{L"btn_chat_sendpic",65566},
		{L"btn_chat_upload",65567},
		{L"btn_close",65540},
		{L"btn_ignore",65554},
		{L"btn_send",65569},
		{L"btn_viewall",65550},
		{L"chat_input",65568},
		{L"chat_record",65564},
		{L"chech_showfont",65565},
		{L"img_myuser",65536},
		{L"img_user",65551},
		{L"lay_loading",65542},
		{L"lay_session",65561},
		{L"lay_userinfo",65575},
		{L"lv_recent",65555},
		{L"ml_btn_del",65560},
		{L"ml_count",65559},
		{L"ml_img_user",65556},
		{L"ml_text_msg",65558},
		{L"ml_text_user",65557},
		{L"msgbox_btn_close",65544},
		{L"msgbox_btn_ok",65547},
		{L"msgbox_icon",65545},
		{L"msgbox_text",65546},
		{L"msgbox_title",65543},
		{L"pagec_img_talk",65577},
		{L"pagec_img_user",65576},
		{L"pagec_text_info",65579},
		{L"pagec_text_user",65578},
		{L"radio_contact",65539},
		{L"radio_talk",65537},
		{L"si_level",65563},
		{L"si_text_title",65562},
		{L"tab_main",65541},
		{L"text_content",65553},
		{L"text_sender",65552},
		{L"text_title",65548},
		{L"tv_contact",65570},
		{L"tv_img_user",65573},
		{L"tv_switch",65571},
		{L"tv_text_content",65574},
		{L"tv_text_user",65572},
		{L"win_count",65538},
		{L"win_totalcount",65549}		};
	class _R{
	public:
		class _name{
		public:
		_name(){
			_name_start = namedXmlID[0].strName;
			btn_chat_sendpic = namedXmlID[1].strName;
			btn_chat_upload = namedXmlID[2].strName;
			btn_close = namedXmlID[3].strName;
			btn_ignore = namedXmlID[4].strName;
			btn_send = namedXmlID[5].strName;
			btn_viewall = namedXmlID[6].strName;
			chat_input = namedXmlID[7].strName;
			chat_record = namedXmlID[8].strName;
			chech_showfont = namedXmlID[9].strName;
			img_myuser = namedXmlID[10].strName;
			img_user = namedXmlID[11].strName;
			lay_loading = namedXmlID[12].strName;
			lay_session = namedXmlID[13].strName;
			lay_userinfo = namedXmlID[14].strName;
			lv_recent = namedXmlID[15].strName;
			ml_btn_del = namedXmlID[16].strName;
			ml_count = namedXmlID[17].strName;
			ml_img_user = namedXmlID[18].strName;
			ml_text_msg = namedXmlID[19].strName;
			ml_text_user = namedXmlID[20].strName;
			msgbox_btn_close = namedXmlID[21].strName;
			msgbox_btn_ok = namedXmlID[22].strName;
			msgbox_icon = namedXmlID[23].strName;
			msgbox_text = namedXmlID[24].strName;
			msgbox_title = namedXmlID[25].strName;
			pagec_img_talk = namedXmlID[26].strName;
			pagec_img_user = namedXmlID[27].strName;
			pagec_text_info = namedXmlID[28].strName;
			pagec_text_user = namedXmlID[29].strName;
			radio_contact = namedXmlID[30].strName;
			radio_talk = namedXmlID[31].strName;
			si_level = namedXmlID[32].strName;
			si_text_title = namedXmlID[33].strName;
			tab_main = namedXmlID[34].strName;
			text_content = namedXmlID[35].strName;
			text_sender = namedXmlID[36].strName;
			text_title = namedXmlID[37].strName;
			tv_contact = namedXmlID[38].strName;
			tv_img_user = namedXmlID[39].strName;
			tv_switch = namedXmlID[40].strName;
			tv_text_content = namedXmlID[41].strName;
			tv_text_user = namedXmlID[42].strName;
			win_count = namedXmlID[43].strName;
			win_totalcount = namedXmlID[44].strName;
		}
		 const wchar_t * _name_start;
		 const wchar_t * btn_chat_sendpic;
		 const wchar_t * btn_chat_upload;
		 const wchar_t * btn_close;
		 const wchar_t * btn_ignore;
		 const wchar_t * btn_send;
		 const wchar_t * btn_viewall;
		 const wchar_t * chat_input;
		 const wchar_t * chat_record;
		 const wchar_t * chech_showfont;
		 const wchar_t * img_myuser;
		 const wchar_t * img_user;
		 const wchar_t * lay_loading;
		 const wchar_t * lay_session;
		 const wchar_t * lay_userinfo;
		 const wchar_t * lv_recent;
		 const wchar_t * ml_btn_del;
		 const wchar_t * ml_count;
		 const wchar_t * ml_img_user;
		 const wchar_t * ml_text_msg;
		 const wchar_t * ml_text_user;
		 const wchar_t * msgbox_btn_close;
		 const wchar_t * msgbox_btn_ok;
		 const wchar_t * msgbox_icon;
		 const wchar_t * msgbox_text;
		 const wchar_t * msgbox_title;
		 const wchar_t * pagec_img_talk;
		 const wchar_t * pagec_img_user;
		 const wchar_t * pagec_text_info;
		 const wchar_t * pagec_text_user;
		 const wchar_t * radio_contact;
		 const wchar_t * radio_talk;
		 const wchar_t * si_level;
		 const wchar_t * si_text_title;
		 const wchar_t * tab_main;
		 const wchar_t * text_content;
		 const wchar_t * text_sender;
		 const wchar_t * text_title;
		 const wchar_t * tv_contact;
		 const wchar_t * tv_img_user;
		 const wchar_t * tv_switch;
		 const wchar_t * tv_text_content;
		 const wchar_t * tv_text_user;
		 const wchar_t * win_count;
		 const wchar_t * win_totalcount;
		}name;

		class _id{
		public:
		const static int _name_start	=	65535;
		const static int btn_chat_sendpic	=	65566;
		const static int btn_chat_upload	=	65567;
		const static int btn_close	=	65540;
		const static int btn_ignore	=	65554;
		const static int btn_send	=	65569;
		const static int btn_viewall	=	65550;
		const static int chat_input	=	65568;
		const static int chat_record	=	65564;
		const static int chech_showfont	=	65565;
		const static int img_myuser	=	65536;
		const static int img_user	=	65551;
		const static int lay_loading	=	65542;
		const static int lay_session	=	65561;
		const static int lay_userinfo	=	65575;
		const static int lv_recent	=	65555;
		const static int ml_btn_del	=	65560;
		const static int ml_count	=	65559;
		const static int ml_img_user	=	65556;
		const static int ml_text_msg	=	65558;
		const static int ml_text_user	=	65557;
		const static int msgbox_btn_close	=	65544;
		const static int msgbox_btn_ok	=	65547;
		const static int msgbox_icon	=	65545;
		const static int msgbox_text	=	65546;
		const static int msgbox_title	=	65543;
		const static int pagec_img_talk	=	65577;
		const static int pagec_img_user	=	65576;
		const static int pagec_text_info	=	65579;
		const static int pagec_text_user	=	65578;
		const static int radio_contact	=	65539;
		const static int radio_talk	=	65537;
		const static int si_level	=	65563;
		const static int si_text_title	=	65562;
		const static int tab_main	=	65541;
		const static int text_content	=	65553;
		const static int text_sender	=	65552;
		const static int text_title	=	65548;
		const static int tv_contact	=	65570;
		const static int tv_img_user	=	65573;
		const static int tv_switch	=	65571;
		const static int tv_text_content	=	65574;
		const static int tv_text_user	=	65572;
		const static int win_count	=	65538;
		const static int win_totalcount	=	65549;
		}id;

		class _string{
		public:
		}string;

		class _color{
		public:
		const static int bg	=	0;
		const static int blue	=	1;
		const static int disable	=	2;
		const static int gray	=	3;
		const static int green	=	4;
		const static int loadbg	=	5;
		const static int nullbg	=	6;
		const static int red	=	7;
		const static int theme	=	8;
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
