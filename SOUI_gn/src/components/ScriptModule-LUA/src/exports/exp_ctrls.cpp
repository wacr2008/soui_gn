#include "exp_ctrls.h"
#include "core-def.h"
#include "souistd.h"
#include "control/souictrls.h"
#include "lua_tinker/lua_tinker.h"

SOUI::SComboBase * toSComboboxBase(SOUI::IObject *pObj)
{
    return SOUI::sobj_cast<SOUI::SComboBase>(pObj);
}

SOUI::SComboBox * toSCombobox(SOUI::IObject *pObj)
{
    return SOUI::sobj_cast<SOUI::SComboBox>(pObj);
}


BOOL ExpLua_Ctrls(lua_State *L)
{ 
		lua_tinker::class_add<SOUI::SComboBase>(L,"SComboBoxBase");
		lua_tinker::class_inh<SOUI::SComboBase,SOUI::SWindow>(L);
//         lua_tinker::class_def<SOUI::SComboBoxBase>(L,"toSWindow",&SOUI::SComboBoxBase::toSWindow);
		lua_tinker::class_def<SOUI::SComboBase>(L,"GetCurSel",&SOUI::SComboBase::GetCurSel);
		lua_tinker::class_def<SOUI::SComboBase>(L,"GetCount",&SOUI::SComboBase::GetCount);
		lua_tinker::class_def<SOUI::SComboBase>(L,"SetCurSel",&SOUI::SComboBase::SetCurSel);
		lua_tinker::class_def<SOUI::SComboBase>(L,"GetLBText",&SOUI::SComboBase::GetLBText);
		lua_tinker::class_def<SOUI::SComboBase>(L,"FindString",&SOUI::SComboBase::FindString);
		lua_tinker::class_def<SOUI::SComboBase>(L,"DropDown",&SOUI::SComboBase::DropDown);
		lua_tinker::class_def<SOUI::SComboBase>(L,"CloseUp",&SOUI::SComboBase::CloseUp);
		lua_tinker::def(L,"toComboboxBase",toSComboboxBase);
		
        lua_tinker::class_add<SOUI::SComboBox>(L,"SComboBox");
        lua_tinker::class_inh<SOUI::SComboBox,SOUI::SComboBase>(L);
        lua_tinker::class_def<SOUI::SComboBox>(L,"InsertItem",&SOUI::SComboBox::InsertItem);
        lua_tinker::class_def<SOUI::SComboBox>(L,"DeleteString",&SOUI::SComboBox::DeleteString);
        lua_tinker::class_def<SOUI::SComboBox>(L,"ResetContent",&SOUI::SComboBox::ResetContent);
        lua_tinker::class_def<SOUI::SComboBox>(L,"GetLBText",&SOUI::SComboBox::GetLBText);
        lua_tinker::class_def<SOUI::SComboBox>(L,"GetListBox",&SOUI::SComboBox::GetListBox);
        lua_tinker::class_def<SOUI::SComboBox>(L,"GetItemData",&SOUI::SComboBox::GetItemData);
        lua_tinker::class_def<SOUI::SComboBox>(L,"SetItemData",&SOUI::SComboBox::SetItemData);
        lua_tinker::def(L,"toCombobox",toSCombobox);

        
		return TRUE; 
}
 