#include "exp_ScriptModule.h"
#include "core-def.h"
#include "interface/SScriptModule-i.h"
#include "lua_tinker/lua_tinker.h"

BOOL ExpLua_ScriptModule(lua_State *L)
{ 
		lua_tinker::class_add<SOUI::IScriptModule>(L,"IScriptModule");
		lua_tinker::class_def<SOUI::IScriptModule>(L,"GetScriptEngine",&SOUI::IScriptModule::GetScriptEngine);
		lua_tinker::class_def<SOUI::IScriptModule>(L,"executeScriptFile",&SOUI::IScriptModule::executeScriptFile);
		lua_tinker::class_def<SOUI::IScriptModule>(L,"executeString",&SOUI::IScriptModule::executeString);
		lua_tinker::class_def<SOUI::IScriptModule>(L,"executeScriptedEventHandler",&SOUI::IScriptModule::executeScriptedEventHandler);
		lua_tinker::class_def<SOUI::IScriptModule>(L,"getIdentifierString",&SOUI::IScriptModule::getIdentifierString);
		lua_tinker::class_def<SOUI::IScriptModule>(L,"subscribeEvent",&SOUI::IScriptModule::subscribeEvent);

		return TRUE; 
} 