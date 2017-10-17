#pragma once

#ifndef _EXP_PUGIXML_H
#define _EXP_PUGIXML_H

#include <windows.h>

extern "C"
{
#include "lua.h"
#include "lstate.h"
}

BOOL ExpLua_pugixml(lua_State *L);

#endif 