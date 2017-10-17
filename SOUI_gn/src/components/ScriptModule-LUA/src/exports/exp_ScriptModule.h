#pragma once

#ifndef _EXP_SCRIPT_MODULE_H
#define _EXP_SCRIPT_MODULE_H

#include <windows.h>

extern "C"
{
#include "lua.h"
#include "lstate.h"
}

BOOL ExpLua_ScriptModule(lua_State *L);

#endif 