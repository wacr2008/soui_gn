#pragma once
#ifndef _EXP_CTRLS_H_
#define _EXP_CTRLS_H_
#include <windows.h>


extern "C"
{
#include "lua.h"
#include "lstate.h"
}

BOOL ExpLua_Ctrls(lua_State *L);

#endif