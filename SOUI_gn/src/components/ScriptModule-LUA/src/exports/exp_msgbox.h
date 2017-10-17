#pragma once

#ifndef _EXP_MSG_BOX_H_
#define _EXP_MSG_BOX_H_
#include <windows.h>

extern "C"
{
#include "lua.h"
#include "lstate.h"
}
BOOL ExpLua_MessageBox(lua_State *L);

#endif