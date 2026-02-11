#include "lua/lua.hpp"
#include "file-output/logging/logger.hpp"

#include <cassert>
#include <format>
#include <ranges>

LuaInstance::LuaInstance(File::Logger &logger) : logger_{logger}
{
  luaL_openlibs(lua_.get());

  logger_.writeAddress("Lua Instance", *this);
  logger_.writeToLog(File::Logger::LogType::info, "Lua setup complete.");
}

auto LuaInstance::cref() const noexcept -> const lua_State &
{
  assert(lua_ != nullptr);
  return *lua_;
}

auto LuaInstance::ref() noexcept -> lua_State &
{
  assert(lua_ != nullptr);
  return *lua_;
}

auto LuaInstance::execFiles(const std::span<const char *const> file_list) noexcept -> void
{
  logger_.writeToLog(File::Logger::LogType::debug, "Reading multiple Lua files:");
  for (const auto &path : file_list)
  {
    logger_.writeToLog(File::Logger::LogType::debug, std::format("File: {}", path));
  }

  for (const auto &path : file_list)
  {
    const auto result{luaL_dofile(lua_.get(), path)};
    if (result != LUA_OK)
      logger_.writeToLog(File::Logger::LogType::error,
                         std::format("Could not load Lua file! [{}].", lua_tostring(lua_.get(), -1)));
  }
}

auto LuaInstance::GetLuaValue(const std::span<const char *const> key_path) noexcept
    -> std::variant<double, std::string, bool, std::monostate>
{
  for (const auto &[index, key] : key_path | std::views::enumerate)
  {
    if (index == 0)
    {
      lua_getglobal(lua_.get(), key);
      continue;
    }
    lua_getfield(lua_.get(), -1, key);
  }

  const auto found_type{lua_type(lua_.get(), -1)};
  if (found_type == LUA_TNUMBER)
  {
    auto value{lua_tonumber(lua_.get(), -1)};
    popStack(key_path.size());
    return value;
  }
  if (found_type == LUA_TSTRING)
  {
    std::string value{lua_tostring(lua_.get(), -1)};
    popStack(key_path.size());
    return value;
  }
  if (found_type == LUA_TBOOLEAN)
  {
    bool value{static_cast<bool>(lua_toboolean(lua_.get(), -1))};
    popStack(key_path.size());
    return value;
  }
  logger_.writeToLog(File::Logger::LogType::error, "Failed to find a valid lua type. Likely returning nil.");

  popStack(key_path.size());
  return std::monostate();
}

auto LuaInstance::popStack(int num) noexcept -> void
{
  lua_pop(lua_.get(), num);
  logger_.writeToLog(File::Logger::LogType::debug, std::format("Lua stack popped by {}.", num));
}
