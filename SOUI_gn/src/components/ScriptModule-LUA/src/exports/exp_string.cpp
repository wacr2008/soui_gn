#include "exp_string.h"
#include "core-def.h"
#include "string/tstring.h"
#include "lua_tinker/lua_tinker.h"

BOOL ExpLua_String(lua_State *L)
{ 

		lua_tinker::class_add<SOUI::SStringA>(L,"SStringA");
        lua_tinker::class_con<SOUI::SStringA>(L,lua_tinker::constructor<SOUI::SStringA>);
        lua_tinker::class_con<SOUI::SStringA>(L,lua_tinker::constructor<SOUI::SStringA,const SOUI::SStringA &>);
        lua_tinker::class_con<SOUI::SStringA>(L,lua_tinker::constructor<SOUI::SStringA,const char*>);
        
        lua_tinker::class_def<SOUI::SStringA>(L,"GetLength",&SOUI::SStringA::GetLength);
        lua_tinker::class_def<SOUI::SStringA>(L,"IsEmpty",&SOUI::SStringA::IsEmpty);
        lua_tinker::class_def<SOUI::SStringA>(L,"Empty",&SOUI::SStringA::Empty);
        lua_tinker::class_def<SOUI::SStringA>(L,"GetAt",&SOUI::SStringA::GetAt);
        lua_tinker::class_def<SOUI::SStringA>(L,"SetAt",&SOUI::SStringA::SetAt);
        lua_tinker::class_def<SOUI::SStringA>(L,"Mid",(SOUI::SStringA (SOUI::SStringA::*)(int) const)&SOUI::SStringA::Mid);
        lua_tinker::class_def<SOUI::SStringA>(L,"Mid2",(SOUI::SStringA (SOUI::SStringA::*)(int,int) const)&SOUI::SStringA::Mid);
        lua_tinker::class_def<SOUI::SStringA>(L,"Left",&SOUI::SStringA::Left);
        lua_tinker::class_def<SOUI::SStringA>(L,"Right",&SOUI::SStringA::Left);
        lua_tinker::class_def<SOUI::SStringA>(L,"MakeUpper",&SOUI::SStringA::MakeUpper);
        lua_tinker::class_def<SOUI::SStringA>(L,"MakeLower",&SOUI::SStringA::MakeLower);
        lua_tinker::class_def<SOUI::SStringA>(L,"TrimRight",&SOUI::SStringA::TrimRight);
        lua_tinker::class_def<SOUI::SStringA>(L,"TrimLeft",&SOUI::SStringA::TrimLeft);
        lua_tinker::class_def<SOUI::SStringA>(L,"Trim",&SOUI::SStringA::Trim);
        lua_tinker::class_def<SOUI::SStringA>(L,"InsertChar",(int (SOUI::SStringA::*)(int,char))&SOUI::SStringA::Insert);
        lua_tinker::class_def<SOUI::SStringA>(L,"InsertStr",(int (SOUI::SStringA::*)(int,const char*))&SOUI::SStringA::Insert);
        lua_tinker::class_def<SOUI::SStringA>(L,"Delete",&SOUI::SStringA::Delete);
        lua_tinker::class_def<SOUI::SStringA>(L,"ReplaceChar",(int (SOUI::SStringA::*)(char,char))&SOUI::SStringA::Replace);
        lua_tinker::class_def<SOUI::SStringA>(L,"ReplaceStr",(int (SOUI::SStringA::*)(const char*,const char*))&SOUI::SStringA::Replace);
        lua_tinker::class_def<SOUI::SStringA>(L,"Remove",&SOUI::SStringA::Remove);
        lua_tinker::class_def<SOUI::SStringA>(L,"FindChar",(int (SOUI::SStringA::*)(char,int) const)&SOUI::SStringA::Find);
        lua_tinker::class_def<SOUI::SStringA>(L,"FindStr",(int (SOUI::SStringA::*)(const char *,int) const)&SOUI::SStringA::Find);
        lua_tinker::class_def<SOUI::SStringA>(L,"ReverseFind",&SOUI::SStringA::ReverseFind);
        lua_tinker::class_def<SOUI::SStringA>(L,"GetBuffer",&SOUI::SStringA::GetBuffer);
        lua_tinker::class_def<SOUI::SStringA>(L,"ReleaseBuffer",&SOUI::SStringA::ReleaseBuffer);
        lua_tinker::class_def<SOUI::SStringA>(L,"GetBufferSetLength",&SOUI::SStringA::GetBufferSetLength);
        lua_tinker::class_def<SOUI::SStringA>(L,"SetLength",&SOUI::SStringA::SetLength);
        lua_tinker::class_def<SOUI::SStringA>(L,"LockBuffer",&SOUI::SStringA::LockBuffer);
        lua_tinker::class_def<SOUI::SStringA>(L,"UnlockBuffer",&SOUI::SStringA::UnlockBuffer);
        lua_tinker::class_def<SOUI::SStringA>(L,"AppendChar",(const SOUI::SStringA & (SOUI::SStringA::*)(char))&SOUI::SStringA::Append);
        lua_tinker::class_def<SOUI::SStringA>(L,"AppendPsz",(const SOUI::SStringA & (SOUI::SStringA::*)(const char *))&SOUI::SStringA::Append);
        lua_tinker::class_def<SOUI::SStringA>(L,"AppendStr",(const SOUI::SStringA & (SOUI::SStringA::*)(const SOUI::SStringA &))&SOUI::SStringA::Append);


        lua_tinker::class_add<SOUI::SStringW>(L,"SStringW");
        lua_tinker::class_con<SOUI::SStringW>(L,lua_tinker::constructor<SOUI::SStringW>);
        lua_tinker::class_con<SOUI::SStringW>(L,lua_tinker::constructor<SOUI::SStringW,const SOUI::SStringW &>);
        lua_tinker::class_con<SOUI::SStringW>(L,lua_tinker::constructor<SOUI::SStringW,const wchar_t*>);

        lua_tinker::class_def<SOUI::SStringW>(L,"GetLength",&SOUI::SStringW::GetLength);
        lua_tinker::class_def<SOUI::SStringW>(L,"IsEmpty",&SOUI::SStringW::IsEmpty);
        lua_tinker::class_def<SOUI::SStringW>(L,"Empty",&SOUI::SStringW::Empty);
        lua_tinker::class_def<SOUI::SStringW>(L,"GetAt",&SOUI::SStringW::GetAt);
        lua_tinker::class_def<SOUI::SStringW>(L,"SetAt",&SOUI::SStringW::SetAt);
        lua_tinker::class_def<SOUI::SStringW>(L,"Mid",(SOUI::SStringW (SOUI::SStringW::*)(int) const)&SOUI::SStringW::Mid);
        lua_tinker::class_def<SOUI::SStringW>(L,"Mid2",(SOUI::SStringW (SOUI::SStringW::*)(int,int) const)&SOUI::SStringW::Mid);
        lua_tinker::class_def<SOUI::SStringW>(L,"Left",&SOUI::SStringW::Left);
        lua_tinker::class_def<SOUI::SStringW>(L,"Right",&SOUI::SStringW::Left);
        lua_tinker::class_def<SOUI::SStringW>(L,"MakeUpper",&SOUI::SStringW::MakeUpper);
        lua_tinker::class_def<SOUI::SStringW>(L,"MakeLower",&SOUI::SStringW::MakeLower);
        lua_tinker::class_def<SOUI::SStringW>(L,"TrimRight",&SOUI::SStringW::TrimRight);
        lua_tinker::class_def<SOUI::SStringW>(L,"TrimLeft",&SOUI::SStringW::TrimLeft);
        lua_tinker::class_def<SOUI::SStringW>(L,"Trim",&SOUI::SStringW::Trim);
        lua_tinker::class_def<SOUI::SStringW>(L,"InsertChar",(int (SOUI::SStringW::*)(int,wchar_t))&SOUI::SStringW::Insert);
        lua_tinker::class_def<SOUI::SStringW>(L,"InsertStr",(int (SOUI::SStringW::*)(int,const wchar_t*))&SOUI::SStringW::Insert);
        lua_tinker::class_def<SOUI::SStringW>(L,"Delete",&SOUI::SStringW::Delete);
        lua_tinker::class_def<SOUI::SStringW>(L,"ReplaceChar",(int (SOUI::SStringW::*)(wchar_t,wchar_t))&SOUI::SStringW::Replace);
        lua_tinker::class_def<SOUI::SStringW>(L,"ReplaceStr",(int (SOUI::SStringW::*)(const wchar_t*,const wchar_t*))&SOUI::SStringW::Replace);
        lua_tinker::class_def<SOUI::SStringW>(L,"Remove",&SOUI::SStringW::Remove);
        lua_tinker::class_def<SOUI::SStringW>(L,"FindChar",(int (SOUI::SStringW::*)(wchar_t,int) const)&SOUI::SStringW::Find);
        lua_tinker::class_def<SOUI::SStringW>(L,"FindStr",(int (SOUI::SStringW::*)(const wchar_t *,int) const)&SOUI::SStringW::Find);
        lua_tinker::class_def<SOUI::SStringW>(L,"ReverseFind",&SOUI::SStringW::ReverseFind);
        lua_tinker::class_def<SOUI::SStringW>(L,"GetBuffer",&SOUI::SStringW::GetBuffer);
        lua_tinker::class_def<SOUI::SStringW>(L,"ReleaseBuffer",&SOUI::SStringW::ReleaseBuffer);
        lua_tinker::class_def<SOUI::SStringW>(L,"GetBufferSetLength",&SOUI::SStringW::GetBufferSetLength);
        lua_tinker::class_def<SOUI::SStringW>(L,"SetLength",&SOUI::SStringW::SetLength);
        lua_tinker::class_def<SOUI::SStringW>(L,"LockBuffer",&SOUI::SStringW::LockBuffer);
        lua_tinker::class_def<SOUI::SStringW>(L,"UnlockBuffer",&SOUI::SStringW::UnlockBuffer);
        lua_tinker::class_def<SOUI::SStringW>(L,"AppendChar",(const SOUI::SStringW & (SOUI::SStringW::*)(wchar_t))&SOUI::SStringW::Append);
        lua_tinker::class_def<SOUI::SStringW>(L,"AppendPsz",(const SOUI::SStringW & (SOUI::SStringW::*)(const wchar_t *))&SOUI::SStringW::Append);
        lua_tinker::class_def<SOUI::SStringW>(L,"AppendStr",(const SOUI::SStringW & (SOUI::SStringW::*)(const SOUI::SStringW &))&SOUI::SStringW::Append);
		return TRUE; 

}