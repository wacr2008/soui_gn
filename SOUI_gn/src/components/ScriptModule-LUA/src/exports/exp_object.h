#pragma once
#ifndef _EXP_MSGBOX_H
#define _EXP_MSGBOX_H

#include <windows.h>

extern "C"
{
#include "lua.h"
#include "lstate.h"
}
BOOL ExpLua_SObject(lua_State *L);

#endif

