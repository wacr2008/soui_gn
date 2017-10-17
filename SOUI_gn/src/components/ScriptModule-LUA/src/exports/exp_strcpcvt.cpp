#include "exp_strcpcvt.h"
#include "core-def.h"
#include <string/strcpcvt.h>
#include "lua_tinker/lua_tinker.h"
#include "lua_tinker/lua_tinker.h"

BOOL ExpLua_StrCpCvt(lua_State *L)
{ 
        lua_tinker::def(L,"S_W2A",&SOUI::SStrCpCvt::CvtW2A);
        lua_tinker::def(L,"S_A2W",&SOUI::SStrCpCvt::CvtA2W);
        lua_tinker::def(L,"S_A2A",&SOUI::SStrCpCvt::CvtA2A);
        lua_tinker::def(L,"S_W2W",&SOUI::SStrCpCvt::CvtW2W);

        return TRUE; 
}