#include "precompiled.h"
#include "Colourb.h"


namespace Rocket {
namespace Core {
namespace Lua {


template<> void LuaType<Colourb>::extra_init(lua_State* L, int metatable_index)
{
    lua_pushcfunction(L,Colourb__call);
    lua_setfield(L,metatable_index,"__call");

    lua_pushcfunction(L,Colourb__eq);
    lua_setfield(L,metatable_index,"__eq");

    lua_pushcfunction(L,Colourb__add);
    lua_setfield(L,metatable_index,"__add");

    lua_pushcfunction(L,Colourb__mul);
    lua_setfield(L,metatable_index,"__mul");

    return;
}

int Colourb__call(lua_State* L)
{
    byte red = (byte)luaL_checkint(L,1);
    byte green = (byte)luaL_checkint(L,2);
    byte blue = (byte)luaL_checkint(L,3);
    byte alpha = (byte)luaL_checkint(L,4);

    Colourb* col = new Colourb(red,green,blue,alpha);

    LuaType<Colourb>::push(L,col,true);
    return 1;
}

int Colourb__eq(lua_State* L)
{
    Colourb* lhs = LuaType<Colourb>::check(L,1);
    Colourb* rhs = LuaType<Colourb>::check(L,2);

    lua_pushboolean(L, (*lhs) == (*rhs) ? 1 : 0);
    return 1;
}

int Colourb__add(lua_State* L)
{
    Colourb* lhs = LuaType<Colourb>::check(L,1);
    Colourb* rhs = LuaType<Colourb>::check(L,2);

    Colourb* res = new Colourb((*lhs) + (*rhs));

    LuaType<Colourb>::push(L,res,true);
    return 1;
}

int Colourb__mul(lua_State* L)
{
    Colourb* lhs = LuaType<Colourb>::check(L,1);
    float rhs = (float)luaL_checknumber(L,2);

    Colourb* res = new Colourb((*lhs) * rhs);
    
    LuaType<Colourb>::push(L,res,true);
    return 1;
}



//getters
int ColourbGetAttrred(lua_State* L)
{
    Colourb* obj = LuaType<Colourb>::check(L,1);
    lua_pushinteger(L,obj->red);
    return 1;
}

int ColourbGetAttrgreen(lua_State* L)
{
    Colourb* obj = LuaType<Colourb>::check(L,1);
    lua_pushinteger(L,obj->green);
    return 1;
}

int ColourbGetAttrblue(lua_State* L)
{
    Colourb* obj = LuaType<Colourb>::check(L,1);
    lua_pushinteger(L,obj->blue);
    return 1;
}

int ColourbGetAttralpha(lua_State* L)
{
    Colourb* obj = LuaType<Colourb>::check(L,1);
    lua_pushinteger(L,obj->alpha);
    return 1;
}

int ColourbGetAttrrgba(lua_State* L)
{
    Colourb* obj = LuaType<Colourb>::check(L,1);
    lua_pushinteger(L,obj->red);
    lua_pushinteger(L,obj->green);
    lua_pushinteger(L,obj->blue);
    lua_pushinteger(L,obj->alpha);
    return 4;
}


//setters
int ColourbSetAttrred(lua_State* L)
{
    Colourb* obj = LuaType<Colourb>::check(L,1);
    byte red = (byte)luaL_checkinteger(L,2);
    obj->red = red;
    return 0;
}

int ColourbSetAttrgreen(lua_State* L)
{
    Colourb* obj = LuaType<Colourb>::check(L,1);
    byte green = (byte)luaL_checkinteger(L,2);
    obj->green = green;
    return 0;
}

int ColourbSetAttrblue(lua_State* L)
{
    Colourb* obj = LuaType<Colourb>::check(L,1);
    byte blue = (byte)luaL_checkinteger(L,2);
    obj->blue = blue;
    return 0;
}

int ColourbSetAttralpha(lua_State* L)
{
    Colourb* obj = LuaType<Colourb>::check(L,1);
    byte alpha = (byte)luaL_checkinteger(L,2);
    obj->alpha = alpha;
    return 0;
}


RegType<Colourb> ColourbMethods[] =
{
    { NULL, NULL },
};

luaL_reg ColourbGetters[] =
{
    LUAGETTER(Colourb,red)
    LUAGETTER(Colourb,green)
    LUAGETTER(Colourb,blue)
    LUAGETTER(Colourb,alpha)
    LUAGETTER(Colourb,rgba)
    { NULL, NULL },
};

luaL_reg ColourbSetters[] =
{
    LUASETTER(Colourb,red)
    LUASETTER(Colourb,green)
    LUASETTER(Colourb,blue)
    LUASETTER(Colourb,alpha)
    { NULL, NULL },
};


template<> const char* GetTClassName<Colourb>() { return "Colourb"; }
template<> RegType<Colourb>* GetMethodTable<Colourb>() { return ColourbMethods; }
template<> luaL_reg* GetAttrTable<Colourb>() { return ColourbGetters; }
template<> luaL_reg* SetAttrTable<Colourb>() { return ColourbSetters; }


}
}
}