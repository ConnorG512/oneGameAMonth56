#include "lua/lua.hpp"

#include <cassert>
#include <format>

LuaInstance::LuaInstance(std::optional<std::reference_wrapper<File::Logger>> logger)
  : logger_ {logger}
{
  luaL_openlibs(lua_.get());
  
  if(logger_.has_value())
    logger_->get().writeToLog(File::Logger::LogType::info, "Lua setup complete.");
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

auto LuaInstance::execFile(const char* file_name) noexcept -> void
{
  const auto result {luaL_dofile(lua_.get(), file_name)};
  if(result != LUA_OK && logger_.has_value())
  {
    const auto error {lua_tostring(lua_.get(), -1)};
    logger_->get().writeToLog(
        File::Logger::LogType::error, std::format("(lua.cpp) Failed to find lua file! [{}]", error));
    popStack();
  }
}

auto LuaInstance::popStack(int num) noexcept -> void
{
  lua_pop(lua_.get(), num);
  if(logger_.has_value())
    logger_->get().writeToLog(File::Logger::LogType::debug, std::format("Lua stack popped by {}.", num));
}
