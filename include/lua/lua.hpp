#pragma once 

#include <lua.hpp>

class LuaInstance 
{
  lua_State* lua_ = luaL_newstate();
  
  public: 
    auto cref() const noexcept -> const lua_State&;
    auto ref() noexcept -> lua_State&;
};
