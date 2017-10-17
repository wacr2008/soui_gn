#include "exp_hostwnd.h"
#include "core-def.h"
#include <core/SHostWnd.h>
#include "lua_tinker/lua_tinker.h"

SOUI::SHostWnd * toHostWnd(SOUI::IObject *pObj)
{
    return SOUI::sobj_cast<SOUI::SHostWnd>(pObj);
}

BOOL ExpLua_HostWnd(lua_State *L)
{ 
		lua_tinker::class_add<SOUI::SHostWnd>(L,"SHostWnd");
		lua_tinker::class_def<SOUI::SHostWnd>(L,"AnimateHostWindow",&SOUI::SHostWnd::AnimateHostWindow);
		lua_tinker::class_def<SOUI::SHostWnd>(L,"setTimeout",&SOUI::SHostWnd::setTimeout);
		lua_tinker::class_def<SOUI::SHostWnd>(L,"setInterval",&SOUI::SHostWnd::setInterval);
		lua_tinker::class_def<SOUI::SHostWnd>(L,"clearTimer",&SOUI::SHostWnd::clearTimer);
        lua_tinker::class_def<SOUI::SHostWnd>(L,"GetRoot",&SOUI::SHostWnd::GetRoot);
        
        lua_tinker::def(L,"toHostWnd",toHostWnd); 

		return TRUE;
}
 