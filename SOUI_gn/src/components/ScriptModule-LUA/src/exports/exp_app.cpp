#include "exp_app.h"
#include "lua_tinker/lua_tinker.h"
#include "SApp.h"

BOOL ExpLua_App(lua_State *L)
{ 
	lua_tinker::class_add<SOUI::SApplication>(L,"SApplication");
	lua_tinker::class_def<SOUI::SApplication>(L,"AddResProvider",&SOUI::SApplication::AddResProvider);
	lua_tinker::class_def<SOUI::SApplication>(L,"RemoveResProvider",&SOUI::SApplication::RemoveResProvider);
	lua_tinker::class_def<SOUI::SApplication>(L,"GetInstance",&SOUI::SApplication::GetInstance);
	lua_tinker::class_def<SOUI::SApplication>(L,"CreateScriptModule",&SOUI::SApplication::CreateScriptModule);
	lua_tinker::class_def<SOUI::SApplication>(L,"SetScriptModule",&SOUI::SApplication::SetScriptFactory);
	lua_tinker::class_def<SOUI::SApplication>(L,"GetTranslator",&SOUI::SApplication::GetTranslator);
    lua_tinker::class_def<SOUI::SApplication>(L,"SetTranslator",&SOUI::SApplication::SetTranslator);
	lua_tinker::def(L,"theApp",&SOUI::SApplication::getSingletonPtr);

	return TRUE; 
}
 