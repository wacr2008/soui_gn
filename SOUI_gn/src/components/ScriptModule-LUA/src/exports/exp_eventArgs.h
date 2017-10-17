#pragma once

#ifndef _EXP_EVENTARGS_H
#define _EXP_EVENTARGS_H
#include <windows.h>

extern "C"
{
#include "lua.h"
#include "lstate.h"
}

BOOL ExpLua_EventArgs(lua_State *L);

#endif