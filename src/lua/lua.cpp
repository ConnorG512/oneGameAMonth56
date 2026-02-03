#include "lua/lua.hpp"

#include <cassert>

LuaInstance::LuaInstance(std::optional<std::reference_wrapper<File::Logger>> logger)
{
  luaL_openlibs(lua_.get());
  
  if(logger.has_value())
    logger->get().writeToLog(File::Logger::LogType::info, "Lua setup complete.");
}

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
