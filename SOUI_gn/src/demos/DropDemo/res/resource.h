//stamp:0cc12bb4916bbdc9
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
		class _LAYOUT{
			public:
			_LAYOUT(){
				wnd_notify = _T("LAYOUT:wnd_notify");
				wnd_main = _T("LAYOUT:wnd_main");
				Menu_FileList = _T("LAYOUT:Menu_FileList");
				Menu_FileListItem = _T("LAYOUT:Menu_FileListItem");
			}
			const TCHAR * wnd_notify;
			const TCHAR * wnd_main;
			const TCHAR * Menu_FileList;
			const TCHAR * Menu_FileListItem;
		}LAYOUT;
		class _image{
			public:
			_image(){
				bg = _T("image:bg");
				btn_close = _T("image:btn_close");
				btn_max = _T("image:btn_max");
				btn_restore = _T("image:btn_restore");
				btn_min = _T("image:btn_min");
				btn_menu = _T("image:btn_menu");
				btn_back = _T("image:btn_back");
				btn_forward = _T("image:btn_forward");
				btn_next = _T("image:btn_next");
				btn_prev = _T("image:btn_prev");
				btn_refresh = _T("image:btn_refresh");
				btn_reg = _T("image:btn_reg");
				img_busy = _T("image:img_busy");
				lcex_header = _T("image:lcex_header");
				lcex_header_arrow = _T("image:lcex_header_arrow");
				lcex_selectrange = _T("image:lcex_selectrange");
				shadow = _T("image:shadow");
				tab_left = _T("image:tab_left");
				tab_main = _T("image:tab_main");
				tool_box = _T("image:tool_box");
				tree_icon = _T("image:tree_icon");
			}
			const TCHAR * bg;
			const TCHAR * btn_close;
			const TCHAR * btn_max;
			const TCHAR * btn_restore;
			const TCHAR * btn_min;
			const TCHAR * btn_menu;
			const TCHAR * btn_back;
			const TCHAR * btn_forward;
			const TCHAR * btn_next;
			const TCHAR * btn_prev;
			const TCHAR * btn_refresh;
			const TCHAR * btn_reg;
			const TCHAR * img_busy;
			const TCHAR * lcex_header;
			const TCHAR * lcex_header_arrow;
			const TCHAR * lcex_selectrange;
			const TCHAR * shadow;
			const TCHAR * tab_left;
			const TCHAR * tab_main;
			const TCHAR * tool_box;
			const TCHAR * tree_icon;
		}image;
	};
	const SNamedID::NAMEDVALUE namedXmlID[]={
		{L"_name_start",65535},
		{L"bar_dir",65546},
		{L"btn_back",65543},
		{L"btn_close",65542},
		{L"btn_forward",65544},
		{L"btn_max",65541},
		{L"btn_menu",65538},
		{L"btn_min",65539},
		{L"btn_refresh",65545},
		{L"btn_restore",65540},
		{L"edit_username",65547},
		{L"lc_file",65548},
		{L"link_more",65537},
		{L"link_url",65536},
		{L"text_status1",65549},
		{L"text_status2",65550},
		{L"text_status3",65551}		};
	class _R{
	public:
		class _name{
		public:
		_name(){
			_name_start = namedXmlID[0].strName;
			bar_dir = namedXmlID[1].strName;
			btn_back = namedXmlID[2].strName;
			btn_close = namedXmlID[3].strName;
			btn_forward = namedXmlID[4].strName;
			btn_max = namedXmlID[5].strName;
			btn_menu = namedXmlID[6].strName;
			btn_min = namedXmlID[7].strName;
			btn_refresh = namedXmlID[8].strName;
			btn_restore = namedXmlID[9].strName;
			edit_username = namedXmlID[10].strName;
			lc_file = namedXmlID[11].strName;
			link_more = namedXmlID[12].strName;
			link_url = namedXmlID[13].strName;
			text_status1 = namedXmlID[14].strName;
			text_status2 = namedXmlID[15].strName;
			text_status3 = namedXmlID[16].strName;
		}
		 const wchar_t * _name_start;
		 const wchar_t * bar_dir;
		 const wchar_t * btn_back;
		 const wchar_t * btn_close;
		 const wchar_t * btn_forward;
		 const wchar_t * btn_max;
		 const wchar_t * btn_menu;
		 const wchar_t * btn_min;
		 const wchar_t * btn_refresh;
		 const wchar_t * btn_restore;
		 const wchar_t * edit_username;
		 const wchar_t * lc_file;
		 const wchar_t * link_more;
		 const wchar_t * link_url;
		 const wchar_t * text_status1;
		 const wchar_t * text_status2;
		 const wchar_t * text_status3;
		}name;

		class _id{
		public:
		const static int _name_start	=	65535;
		const static int bar_dir	=	65546;
		const static int btn_back	=	65543;
		const static int btn_close	=	65542;
		const static int btn_forward	=	65544;
		const static int btn_max	=	65541;
		const static int btn_menu	=	65538;
		const static int btn_min	=	65539;
		const static int btn_refresh	=	65545;
		const static int btn_restore	=	65540;
		const static int edit_username	=	65547;
		const static int lc_file	=	65548;
		const static int link_more	=	65537;
		const static int link_url	=	65536;
		const static int text_status1	=	65549;
		const static int text_status2	=	65550;
		const static int text_status3	=	65551;
		}id;

		class _string{
		public:
		const static int title	=	0;
		}string;

		class _color{
		public:
		const static int bg	=	0;
		const static int blue	=	1;
		const static int disable	=	2;
		const static int gray	=	3;
		const static int green	=	4;
		const static int red	=	5;
		const static int theme	=	6;
		const static int white	=	7;
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
