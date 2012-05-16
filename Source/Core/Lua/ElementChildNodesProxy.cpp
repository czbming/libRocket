/*
 * This source file is part of libRocket, the HTML/CSS Interface Middleware
 *
 * For the latest information, see http://www.librocket.com
 *
 * Copyright (c) 2008-2010 CodePoint Ltd, Shift Technology Ltd
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 *
 */
 
#include "precompiled.h"
#include "ElementChildNodesProxy.h"
#include "Element.h"

namespace Rocket {
namespace Core {
namespace Lua {

template<> void ExtraInit<ElementChildNodesProxy>(lua_State* L, int metatable_index)
{
    lua_pushcfunction(L,ElementChildNodesProxy__index);
    lua_setfield(L,metatable_index,"__index");
}

int ElementChildNodesProxy__index(lua_State* L)
{
    /*the table obj and the missing key are currently on the stack(index 1 & 2) as defined by the Lua language*/
    int keytype = lua_type(L,2);
    if(keytype == LUA_TNUMBER) //only valid key types
    {
        ElementChildNodesProxy* obj = LuaType<ElementChildNodesProxy>::check(L,1);
        LUACHECKOBJ(obj);
        int key = luaL_checkint(L,2);
        Element* child = obj->owner->GetChild(key);
        LuaType<Element>::push(L,child,false);
        return 1;
    }
    else
        return LuaType<ElementChildNodesProxy>::index(L);
}

//method
int ElementChildNodesProxyGetTable(lua_State* L, ElementChildNodesProxy* obj)
{
    Element* ele = obj->owner;
    if(!ele->HasChildNodes())
        lua_pushnil(L);
    else
    {
        lua_newtable(L);
        int index = 0;
        int num_of_children = ele->GetNumChildren();
        while(index < num_of_children)
        {
            lua_pushinteger(L,index);
            LuaType<Element>::push(L,ele->GetChild(index),false);
            lua_settable(L,-3);
            ++index;
        }
    }
    return 1;
}

RegType<ElementChildNodesProxy> ElementChildNodesProxyMethods[] = 
{
    LUAMETHOD(ElementChildNodesProxy,GetTable)
    { NULL, NULL },
};
luaL_reg ElementChildNodesProxyGetters[] = 
{
    { NULL, NULL },
};
luaL_reg ElementChildNodesProxySetters[] = 
{
    { NULL, NULL },
};

LUATYPEDEFINE(ElementChildNodesProxy,true)
}
}
}