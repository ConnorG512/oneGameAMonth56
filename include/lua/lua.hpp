#pragma once 

#include <lua.hpp>
#include <memory>

class LuaInstance 
{
  std::unique_ptr<lua_State, decltype(&lua_close)> lua_ {nullptr, &lua_close}; 
  
  public: 
    auto cref() const noexcept -> const lua_State&;
    auto ref() noexcept -> lua_State&;
};
