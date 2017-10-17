#include "exp_eventArgs.h"
#include "core-def.h"
#include "event/events.h"
#include "lua_tinker/lua_tinker.h"

SOUI::EventTimer * toEventTimer(SOUI::EventArgs *pEvt)
{
    return SOUI::sobj_cast<SOUI::EventTimer>(pEvt);
}

SOUI::EventSwndSize * toEventSize(SOUI::EventArgs *pEvt)
{
    return SOUI::sobj_cast<SOUI::EventSwndSize>(pEvt);
}

BOOL ExpLua_EventArgs(lua_State *L)
{ 
		lua_tinker::class_add<SOUI::EventArgs>(L,"EventArgs");
        lua_tinker::class_inh<SOUI::EventArgs,SOUI::IObject>(L);
		lua_tinker::class_mem<SOUI::EventArgs>(L,"sender",&SOUI::EventArgs::sender);
        lua_tinker::class_mem<SOUI::EventArgs>(L,"idFrom",&SOUI::EventArgs::idFrom);
        lua_tinker::class_mem<SOUI::EventArgs>(L,"nameFrom",&SOUI::EventArgs::nameFrom);
        
        lua_tinker::class_add<SOUI::EventTimer>(L,"EventTimer");
        lua_tinker::class_inh<SOUI::EventTimer,SOUI::EventArgs>(L);
        lua_tinker::class_mem<SOUI::EventTimer>(L,"uID",&SOUI::EventTimer::uID);
        lua_tinker::def(L,"toEventTimer", toEventTimer);//类型转换

        lua_tinker::class_add<SOUI::EventSwndSize>(L,"EventSwndSize");
        lua_tinker::class_inh<SOUI::EventSwndSize,SOUI::EventArgs>(L);
        lua_tinker::class_mem<SOUI::EventSwndSize>(L,"szWnd",&SOUI::EventSwndSize::szWnd);
        lua_tinker::def(L,"toEventSize",toEventSize);//类型转换

		return TRUE; 
} 