#pragma once
#ifndef _EXP_WINDOW_H
#define _EXP_WINDOW_H
 
#include <windows.h>

extern "C"
{
#include "lua.h"
#include "lstate.h"
}

BOOL ExpLua_Window(lua_State *L);

#endif