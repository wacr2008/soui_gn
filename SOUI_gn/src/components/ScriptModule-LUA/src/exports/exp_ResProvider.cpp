#include "exp_ResProvider.h"
#include "core-def.h"
#include "interface/SResProvider-i.h"
#include "res.mgr/SResProvider.h"
#include "lua_tinker/lua_tinker.h"

BOOL ExpLua_ResProvider(lua_State *L)
{ 
		lua_tinker::class_add<SOUI::IResProvider>(L,"IResProvider");
        lua_tinker::class_def<SOUI::IResProvider>(L,"Init",&SOUI::IResProvider::Init);
		lua_tinker::class_def<SOUI::IResProvider>(L,"HasResource",&SOUI::IResProvider::HasResource);
		lua_tinker::class_def<SOUI::IResProvider>(L,"LoadIcon",&SOUI::IResProvider::LoadIcon);
 		lua_tinker::class_def<SOUI::IResProvider>(L,"LoadBitmap",&SOUI::IResProvider::LoadBitmap);
 		lua_tinker::class_def<SOUI::IResProvider>(L,"LoadImage",&SOUI::IResProvider::LoadImage);
 		lua_tinker::class_def<SOUI::IResProvider>(L,"GetRawBufferSize",&SOUI::IResProvider::GetRawBufferSize);
 		lua_tinker::class_def<SOUI::IResProvider>(L,"GetRawBuffer",&SOUI::IResProvider::GetRawBuffer);
 		
        lua_tinker::def(L,"CreateResProvider",&SOUI::CreateResProvider);
	
		return TRUE; 
}