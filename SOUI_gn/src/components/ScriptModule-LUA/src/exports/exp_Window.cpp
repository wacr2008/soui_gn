#include "exp_Window.h"
#include "core-def.h"
#include <core/swnd.h>
#include "lua_tinker/lua_tinker.h"

//定义一个从SObject转换成SOUI::SWindow的方法
SOUI::SWindow * toSWindow(SOUI::IObject * pObj)
{
    return SOUI::sobj_cast<SOUI::SWindow>(pObj);
}

BOOL ExpLua_Window(lua_State *L)
{ 
        lua_tinker::def(L,"toSWindow",toSWindow);

		lua_tinker::class_add<SOUI::SWindow>(L,"SWindow");
        lua_tinker::class_inh<SOUI::SWindow,SOUI::IObject>(L);
		lua_tinker::class_con<SOUI::SWindow>(L,lua_tinker::constructor<SOUI::SWindow>);
		lua_tinker::class_def<SOUI::SWindow>(L,"GetContainer",(SOUI::ISwndContainer *(SOUI::SWindow::*)(void))&SOUI::SWindow::GetContainer);
        lua_tinker::class_def<SOUI::SWindow>(L,"GetRoot",&SOUI::SWindow::GetRoot);
        lua_tinker::class_def<SOUI::SWindow>(L,"GetTopLevelParent",&SOUI::SWindow::GetTopLevelParent);
		lua_tinker::class_def<SOUI::SWindow>(L,"GetParent",&SOUI::SWindow::GetParent);
		lua_tinker::class_def<SOUI::SWindow>(L,"DestroyChild",&SOUI::SWindow::DestroyChild);
		lua_tinker::class_def<SOUI::SWindow>(L,"GetChildrenCount",&SOUI::SWindow::GetChildrenCount);
		lua_tinker::class_def<SOUI::SWindow>(L,"FindChildByID",&SOUI::SWindow::FindChildByID);
        lua_tinker::class_def<SOUI::SWindow>(L,"FindChildByNameA",(SOUI::SWindow* (SOUI::SWindow::*)(LPCSTR,int))&SOUI::SWindow::FindChildByName);
        lua_tinker::class_def<SOUI::SWindow>(L,"FindChildByNameW",(SOUI::SWindow* (SOUI::SWindow::*)(LPCWSTR,int ))&SOUI::SWindow::FindChildByName);
 		lua_tinker::class_def<SOUI::SWindow>(L,"CreateChildrenFromString",(SOUI::SWindow* (SOUI::SWindow::*)(LPCWSTR))&SOUI::SWindow::CreateChildren);
		lua_tinker::class_def<SOUI::SWindow>(L,"GetTextAlign",&SOUI::SWindow::GetTextAlign);
		lua_tinker::class_def<SOUI::SWindow>(L,"GetWindowRect",(void (SOUI::SWindow::*)(LPRECT))&SOUI::SWindow::GetWindowRect);
        lua_tinker::class_def<SOUI::SWindow>(L,"GetWindowRect2",(SOUI::CRect (SOUI::SWindow::*)())&SOUI::SWindow::GetWindowRect);
		lua_tinker::class_def<SOUI::SWindow>(L,"GetClientRect",(void (SOUI::SWindow::*)(LPRECT)const)&SOUI::SWindow::GetClientRect);
        lua_tinker::class_def<SOUI::SWindow>(L,"GetClientRect2",(SOUI::CRect (SOUI::SWindow::*)()const)&SOUI::SWindow::GetClientRect);
		lua_tinker::class_def<SOUI::SWindow>(L,"GetWindowText",&SOUI::SWindow::GetWindowText);
		lua_tinker::class_def<SOUI::SWindow>(L,"SetWindowText",&SOUI::SWindow::SetWindowText);
		lua_tinker::class_def<SOUI::SWindow>(L,"SendSwndMessage",&SOUI::SWindow::SSendMessage);
		lua_tinker::class_def<SOUI::SWindow>(L,"GetID",&SOUI::SWindow::GetID);
		lua_tinker::class_def<SOUI::SWindow>(L,"SetID",&SOUI::SWindow::SetID);
		lua_tinker::class_def<SOUI::SWindow>(L,"GetUserData",&SOUI::SWindow::GetUserData);
		lua_tinker::class_def<SOUI::SWindow>(L,"SetUserData",&SOUI::SWindow::SetUserData);
		lua_tinker::class_def<SOUI::SWindow>(L,"GetName",&SOUI::SWindow::GetName);
		lua_tinker::class_def<SOUI::SWindow>(L,"GetSwnd",&SOUI::SWindow::GetSwnd);
		lua_tinker::class_def<SOUI::SWindow>(L,"InsertChild",&SOUI::SWindow::InsertChild);
		lua_tinker::class_def<SOUI::SWindow>(L,"RemoveChild",&SOUI::SWindow::RemoveChild);
		lua_tinker::class_def<SOUI::SWindow>(L,"IsChecked",&SOUI::SWindow::IsChecked);
		lua_tinker::class_def<SOUI::SWindow>(L,"IsDisabled",&SOUI::SWindow::IsDisabled);
		lua_tinker::class_def<SOUI::SWindow>(L,"IsVisible",&SOUI::SWindow::IsVisible);
		lua_tinker::class_def<SOUI::SWindow>(L,"SetVisible",&SOUI::SWindow::SetVisible);
		lua_tinker::class_def<SOUI::SWindow>(L,"EnableWindow",&SOUI::SWindow::EnableWindow);
		lua_tinker::class_def<SOUI::SWindow>(L,"SetCheck",&SOUI::SWindow::SetCheck);
		lua_tinker::class_def<SOUI::SWindow>(L,"SetOwner",&SOUI::SWindow::SetOwner);
		lua_tinker::class_def<SOUI::SWindow>(L,"GetOwner",&SOUI::SWindow::GetOwner);
		lua_tinker::class_def<SOUI::SWindow>(L,"Invalidate",&SOUI::SWindow::Invalidate);
        lua_tinker::class_def<SOUI::SWindow>(L,"InvalidateRect",(void (SOUI::SWindow::*)(LPCRECT))&SOUI::SWindow::InvalidateRect);
		lua_tinker::class_def<SOUI::SWindow>(L,"AnimateWindow",&SOUI::SWindow::AnimateWindow);
        lua_tinker::class_def<SOUI::SWindow>(L,"GetScriptModule",&SOUI::SWindow::GetScriptModule);
        lua_tinker::class_def<SOUI::SWindow>(L,"Move2",(void (SOUI::SWindow::*)(int,int,int,int))&SOUI::SWindow::Move);
        lua_tinker::class_def<SOUI::SWindow>(L,"Move",(void (SOUI::SWindow::*)(LPCRECT))&SOUI::SWindow::Move);
        lua_tinker::class_def<SOUI::SWindow>(L,"FireCommand",&SOUI::SWindow::FireCommand);
		lua_tinker::class_def<SOUI::SWindow>(L,"GetDesiredSize",(SOUI::CSize (SOUI::SWindow::*)(int, int))&SOUI::SWindow::GetDesiredSize);
        lua_tinker::class_def<SOUI::SWindow>(L,"GetWindow",&SOUI::SWindow::GetWindow);
        lua_tinker::class_def<SOUI::SWindow>(L,"SetWindowRgn",&SOUI::SWindow::SetWindowRgn);
        lua_tinker::class_def<SOUI::SWindow>(L,"GetWindowRgn",&SOUI::SWindow::GetWindowRgn);

		return TRUE; 
}