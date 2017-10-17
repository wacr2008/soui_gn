#pragma once

#ifndef _EXP_STRING_H
#define _EXP_STRING_H
#include <windows.h>

extern "C"
{
#include "lua.h"
#include "lstate.h"
}

BOOL ExpLua_String(lua_State *L);

#endif 