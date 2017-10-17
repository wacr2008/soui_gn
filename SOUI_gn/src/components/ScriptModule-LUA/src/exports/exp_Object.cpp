#include "exp_Object.h"
#include "core-def.h"
#include "sobject/sobject.hpp"
#include "lua_tinker/lua_tinker.h"

void SetObjAttr(SOUI::IObject *pObj,LPCSTR pszAttr,LPCSTR pszValue)
{
    pObj->SetAttribute(pszAttr,pszValue,FALSE);
}

BOOL ExpLua_SObject(lua_State *L)
{ 
		lua_tinker::class_add<SOUI::IObject>(L,"IObject");
		lua_tinker::class_def<SOUI::IObject>(L,"IsClass",&SOUI::IObject::IsClass);
        lua_tinker::class_def<SOUI::IObject>(L,"GetObjectClass",&SOUI::IObject::GetObjectClass);
        lua_tinker::class_def<SOUI::IObject>(L,"InitFromXml",&SOUI::IObject::InitFromXml);
        lua_tinker::class_def<SOUI::IObject>(L,"SetAttribute",(HRESULT (SOUI::IObject::*)(const char *, const char *, BOOL))&SOUI::IObject::SetAttribute);
        lua_tinker::class_def<SOUI::IObject>(L,"SetAttributeA",(HRESULT (SOUI::IObject::*)(const SOUI::SStringA &, const SOUI::SStringA &, BOOL))&SOUI::IObject::SetAttribute);
        lua_tinker::class_def<SOUI::IObject>(L,"SetAttributeW",(HRESULT (SOUI::IObject::*)(const SOUI::SStringW &, const SOUI::SStringW &, BOOL))&SOUI::IObject::SetAttribute);
        lua_tinker::class_def<SOUI::IObject>(L,"GetID",&SOUI::IObject::GetID);
        lua_tinker::class_def<SOUI::IObject>(L,"GetName",&SOUI::IObject::GetName);
        lua_tinker::def(L,"SetObjAttr",SetObjAttr);
		return TRUE; 
}