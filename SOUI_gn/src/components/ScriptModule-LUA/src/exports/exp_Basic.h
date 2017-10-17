//导出基本结构体类型
#pragma once
#ifndef _EXP_BASIC_H
#define _EXP_BASIC_H

#include <windows.h>


extern "C"
{
#include "lua.h"
#include "lstate.h"
}

UINT rgb(int r, int g, int b);
UINT rgba(int r, int g, int b, int a);
BOOL ExpLua_Basic(lua_State *L);

#endif