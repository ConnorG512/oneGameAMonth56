#include "lua/lua.hpp"

#include <cassert>

auto LuaInstance::cref() const noexcept -> const lua_State&
{
  assert(lua_ != nullptr);
  return *lua_;
}

auto LuaInstance::ref() noexcept -> lua_State&
{
  assert(lua_ != nullptr);
  return *lua_;
}
