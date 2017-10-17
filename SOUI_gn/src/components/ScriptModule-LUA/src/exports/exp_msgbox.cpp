#include "exp_msgbox.h" 
#include "core-def.h"
#include <control/SMessageBox.h>
#include "lua_tinker/lua_tinker.h"

BOOL ExpLua_MessageBox(lua_State *L)
{ 
	lua_tinker::def(L,"SMessageBox", SOUI::SMessageBox); 
	return TRUE;
}
 