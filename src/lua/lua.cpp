#include "lua/lua.hpp"

#include <cassert>
#include <format>
#include <ranges>

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
  if(result != LUA_OK)
  {
    const auto error {lua_tostring(lua_.get(), -1)};
    if (logger_.has_value())
      logger_->get().writeToLog(
          File::Logger::LogType::error, std::format("(lua.cpp) Failed to find lua file! [{}]", error));
    
    popStack();
  }
}

auto LuaInstance::GetLuaValue(const std::span<const char* const> key_path) noexcept 
  -> std::variant<double, std::string, bool, std::monostate>
{
  if(key_path.size() == 1)
    lua_getglobal(lua_.get(), key_path[0]);
  
  for(const auto& [index, key] : key_path | std::views::enumerate)
  {
    if(index == 0)
    {
      lua_getglobal(lua_.get(), key);
      continue;
    }
    lua_getfield(lua_.get(), -1, key);
  }
  
  const auto found_type {lua_type(lua_.get(), -1)};
  if(found_type == LUA_TNUMBER)
  {
    auto value {lua_tonumber(lua_.get(), -1)};
    popStack(key_path.size());
    return value;
  }
  if(found_type == LUA_TSTRING)
  {
    std::string value {lua_tostring(lua_.get(), -1)};
    popStack(key_path.size());
    return value;
  }
  if(found_type == LUA_TBOOLEAN)
  {
    bool value {static_cast<bool>(lua_toboolean(lua_.get(), -1))};
    popStack(key_path.size());
    return value;
  }
  logger_->get().writeToLog(File::Logger::LogType::error, "Failed to find a valid lua type. Likely returning nil.");
  
  popStack(key_path.size());
  return std::monostate();
}

auto LuaInstance::popStack(int num) noexcept -> void
{
  lua_pop(lua_.get(), num);
  if(logger_.has_value())
    logger_->get().writeToLog(File::Logger::LogType::debug, std::format("Lua stack popped by {}.", num));
}
