#pragma  once

#include <unknown/obj-ref-i.h>
#include <unknown/obj-ref-impl.hpp> 
#include <windows.h>

namespace SOUI
{
	namespace SCRIPT_LUA
	{
		SOUI_COM_C BOOL SOUI_COM_API SCreateInstance(IObjRef ** ppScript);
	}
}

