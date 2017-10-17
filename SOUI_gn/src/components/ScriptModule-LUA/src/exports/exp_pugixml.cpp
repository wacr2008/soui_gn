#include "exp_pugixml.h" 
#include "core-def.h"
#include "pugixml/pugixml.hpp"
#include "lua_tinker/lua_tinker.h"

BOOL ExpLua_pugixml(lua_State *L)
{ 	 
        lua_tinker::class_add<pugi::xml_parse_result>(L,"xml_parse_result");
        lua_tinker::class_def<pugi::xml_parse_result>(L,"isOK",&pugi::xml_parse_result::isOK);
        
        lua_tinker::class_add<pugi::xml_text>(L,"xml_text");
        lua_tinker::class_con<pugi::xml_text>(L,lua_tinker::constructor<pugi::xml_text>);
        lua_tinker::class_def<pugi::xml_text>(L,"get",&pugi::xml_text::get);
        lua_tinker::class_def<pugi::xml_text>(L,"as_int",&pugi::xml_text::as_int);
        lua_tinker::class_def<pugi::xml_text>(L,"as_uint",&pugi::xml_text::as_uint);
        lua_tinker::class_def<pugi::xml_text>(L,"as_double",&pugi::xml_text::as_double);
        lua_tinker::class_def<pugi::xml_text>(L,"as_float",&pugi::xml_text::as_float);
        lua_tinker::class_def<pugi::xml_text>(L,"as_bool",&pugi::xml_text::as_bool);
        
        lua_tinker::class_add<pugi::xml_attribute>(L,"xml_attribute");
        lua_tinker::class_def<pugi::xml_attribute>(L,"name",&pugi::xml_attribute::name);
        lua_tinker::class_def<pugi::xml_attribute>(L,"value",&pugi::xml_attribute::value);
        lua_tinker::class_def<pugi::xml_attribute>(L,"empty",&pugi::xml_attribute::empty);
        lua_tinker::class_def<pugi::xml_attribute>(L,"as_int",&pugi::xml_attribute::as_int);
        lua_tinker::class_def<pugi::xml_attribute>(L,"as_uint",&pugi::xml_attribute::as_uint);
        lua_tinker::class_def<pugi::xml_attribute>(L,"as_double",&pugi::xml_attribute::as_double);
        lua_tinker::class_def<pugi::xml_attribute>(L,"as_float",&pugi::xml_attribute::as_float);
        lua_tinker::class_def<pugi::xml_attribute>(L,"as_bool",&pugi::xml_attribute::as_bool);
        lua_tinker::class_def<pugi::xml_attribute>(L,"next_attribute",&pugi::xml_attribute::next_attribute);
        lua_tinker::class_def<pugi::xml_attribute>(L,"previous_attribute",&pugi::xml_attribute::previous_attribute);

        lua_tinker::class_add<pugi::xml_node>(L,"xml_node");
        lua_tinker::class_con<pugi::xml_node>(L,lua_tinker::constructor<pugi::xml_node>);
        lua_tinker::class_def<pugi::xml_node>(L,"name",&pugi::xml_node::name);
        lua_tinker::class_def<pugi::xml_node>(L,"set_name",&pugi::xml_node::set_name);
        lua_tinker::class_def<pugi::xml_node>(L,"value",&pugi::xml_node::value);
        lua_tinker::class_def<pugi::xml_node>(L,"set_value",&pugi::xml_node::set_value);
        lua_tinker::class_def<pugi::xml_node>(L,"first_attribute",&pugi::xml_node::first_attribute);
        lua_tinker::class_def<pugi::xml_node>(L,"last_attribute",&pugi::xml_node::last_attribute);
        lua_tinker::class_def<pugi::xml_node>(L,"first_child",&pugi::xml_node::first_child);
        lua_tinker::class_def<pugi::xml_node>(L,"last_child",&pugi::xml_node::last_child);
        lua_tinker::class_def<pugi::xml_node>(L,"next_sibling",(pugi::xml_node (pugi::xml_node::*)()const)&pugi::xml_node::next_sibling);
        lua_tinker::class_def<pugi::xml_node>(L,"previous_sibling",(pugi::xml_node (pugi::xml_node::*)()const)&pugi::xml_node::previous_sibling);
        lua_tinker::class_def<pugi::xml_node>(L,"next_siblingByName",(pugi::xml_node (pugi::xml_node::*)(const wchar_t *,bool)const)&pugi::xml_node::next_sibling);
        lua_tinker::class_def<pugi::xml_node>(L,"previous_siblingByName",(pugi::xml_node (pugi::xml_node::*)(const wchar_t *,bool)const)&pugi::xml_node::previous_sibling);
        lua_tinker::class_def<pugi::xml_node>(L,"parent",&pugi::xml_node::parent);
        lua_tinker::class_def<pugi::xml_node>(L,"root",&pugi::xml_node::root);
        lua_tinker::class_def<pugi::xml_node>(L,"text",&pugi::xml_node::text);
        lua_tinker::class_def<pugi::xml_node>(L,"child",&pugi::xml_node::child);
        lua_tinker::class_def<pugi::xml_node>(L,"attribute",&pugi::xml_node::attribute);
        
        lua_tinker::class_add<pugi::xml_document>(L,"xml_document");
        lua_tinker::class_inh<pugi::xml_document, pugi::xml_node>(L);
        lua_tinker::class_con<pugi::xml_document>(L,lua_tinker::constructor<pugi::xml_document>);

        lua_tinker::class_def<pugi::xml_document>(L,"load",&pugi::xml_document::load);
        lua_tinker::class_def<pugi::xml_document>(L,"load_buffer",&pugi::xml_document::load_buffer);
		lua_tinker::class_def<pugi::xml_document>(L, "load_fileA", (pugi::xml_parse_result(pugi::xml_document::*)(const char *, unsigned int, pugi::xml_encoding))&pugi::xml_document::load_file);
        lua_tinker::class_def<pugi::xml_document>(L,"load_fileW",(pugi::xml_parse_result (pugi::xml_document::*)(const wchar_t *,unsigned int, pugi::xml_encoding))&pugi::xml_document::load_file);
        lua_tinker::class_def<pugi::xml_document>(L,"reset",(void (pugi::xml_document::*)())&pugi::xml_document::reset);
        lua_tinker::class_def<pugi::xml_document>(L,"reset2",(void (pugi::xml_document::*)(const pugi::xml_document&))&pugi::xml_document::reset);
        lua_tinker::class_def<pugi::xml_document>(L,"save_fileA",(bool (pugi::xml_document::*)(const char*, const wchar_t*, unsigned int, pugi::xml_encoding)const)&pugi::xml_document::save_file);
        lua_tinker::class_def<pugi::xml_document>(L,"save_fileW",(bool (pugi::xml_document::*)(const wchar_t*, const wchar_t*, unsigned int, pugi::xml_encoding)const)&pugi::xml_document::save_file);
        
        
        return TRUE;
     
}

 