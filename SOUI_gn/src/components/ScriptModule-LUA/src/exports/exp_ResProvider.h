#pragma once

#ifndef _EXP_RESPROVIDER_H
#define _EXP_RESPROVIDER_H

#include <windows.h>

extern "C"
{
#include "lua.h"
#include "lstate.h"
}

BOOL ExpLua_ResProvider(lua_State *L);

#endif