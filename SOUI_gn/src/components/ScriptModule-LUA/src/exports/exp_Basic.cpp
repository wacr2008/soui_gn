#include "exp_Basic.h"
#include "core-def.h"
#include "helper/color.h"
#include "lua_tinker/lua_tinker.h"

UINT rgb(int r, int g, int b)
{
    return RGBA(r, g, b, 255);
}

UINT rgba(int r, int g, int b, int a)
{
    return RGBA(r, g, b, a);
}


BOOL ExpLua_Basic(lua_State *L)
{ 
        lua_tinker::def(L,"RGB",rgb);
        lua_tinker::def(L,"RGBA",rgba);

        //POINT
        lua_tinker::class_add<POINT>(L,"POINT");
        lua_tinker::class_mem<POINT>(L, "x", &POINT::x);
        lua_tinker::class_mem<POINT>(L, "y", &POINT::y);
        //RECT
        lua_tinker::class_add<RECT>(L,"RECT");
        lua_tinker::class_mem<RECT>(L, "left", &RECT::left);
        lua_tinker::class_mem<RECT>(L, "top", &RECT::top);
        lua_tinker::class_mem<RECT>(L, "right", &RECT::right);
        lua_tinker::class_mem<RECT>(L, "bottom", &RECT::bottom);
        //SIZE
        lua_tinker::class_add<SIZE>(L,"SIZE");
        lua_tinker::class_mem<SIZE>(L, "cx", &SIZE::cx);
        lua_tinker::class_mem<SIZE>(L, "cy", &SIZE::cy);

        //CPoint
        lua_tinker::class_add<SOUI::CPoint>(L,"CPoint");
        lua_tinker::class_inh<SOUI::CPoint,POINT>(L);
        lua_tinker::class_con<SOUI::CPoint>(L,lua_tinker::constructor<SOUI::CPoint,LONG,LONG>);
        //SOUI::CRect
        lua_tinker::class_add<SOUI::CRect>(L,"CRect");
        lua_tinker::class_inh<SOUI::CRect,RECT>(L);
        lua_tinker::class_con<SOUI::CRect>(L,lua_tinker::constructor<SOUI::CRect,LONG,LONG,LONG,LONG>);
        lua_tinker::class_def<SOUI::CRect>(L,"Width",&SOUI::CRect::Width);
        lua_tinker::class_def<SOUI::CRect>(L,"Height",&SOUI::CRect::Height);
        lua_tinker::class_def<SOUI::CRect>(L,"Size",&SOUI::CRect::Size);
        lua_tinker::class_def<SOUI::CRect>(L,"IsRectEmpty",&SOUI::CRect::IsRectEmpty);
        lua_tinker::class_def<SOUI::CRect>(L,"IsRectNull",&SOUI::CRect::IsRectNull);
        lua_tinker::class_def<SOUI::CRect>(L,"PtInRect",&SOUI::CRect::PtInRect);
        lua_tinker::class_def<SOUI::CRect>(L,"SetRectEmpty",&SOUI::CRect::SetRectEmpty);
        lua_tinker::class_def<SOUI::CRect>(L,"OffsetRect",(void (SOUI::CRect::*)(int,int))&SOUI::CRect::OffsetRect);


        //CSize
        lua_tinker::class_add<SOUI::CSize>(L,"CSize");
        lua_tinker::class_inh<SOUI::CSize,SIZE>(L);
        lua_tinker::class_con<SOUI::CSize>(L,lua_tinker::constructor<SOUI::CSize,LONG,LONG>);

        return TRUE; 

}
