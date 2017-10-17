#pragma once
#ifndef _EXP_STRCPCVT_H
#define _EXP_STRCPCVT_H
#include <windows.h>

extern "C"
{
#include "lua.h"
#include "lstate.h"
}

BOOL ExpLua_StrCpCvt(lua_State *L);

#endif