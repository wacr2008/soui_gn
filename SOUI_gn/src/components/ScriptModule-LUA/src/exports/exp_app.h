#pragma  once
#ifndef _EXP_APP_H
#define _EXP_APP_H
#include <windows.h>

extern "C"
{
#include "lua.h"
#include "lstate.h"
}

BOOL ExpLua_App(lua_State *L);

#endif