#pragma once

#include <cstddef>
#include <format>
#include <lua.hpp>
#include <memory>
#include <optional>
#include <span>
#include <variant>

namespace File
{
class Logger;
}

class LuaInstance
{
  std::unique_ptr<lua_State, decltype(&lua_close)> lua_{luaL_newstate(), &lua_close};
  File::Logger &logger_;

  auto popStack(int num = 1) noexcept -> void;

public:
  LuaInstance(File::Logger &logger);

  auto execFiles(const std::span<const char *const> file_list) noexcept -> void;

  auto cref() const noexcept -> const lua_State &;
  auto ref() noexcept -> lua_State &;

  auto GetLuaValue(const std::span<const char *const> key_path) noexcept
      -> std::variant<double, std::string, bool, std::monostate>;
};
