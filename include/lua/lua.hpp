#pragma once

#include <lua.hpp>
#include <memory>
#include <span>
#include <variant>

namespace File
{
class Logger;
}

class LuaInstance
{
  std::unique_ptr<lua_State, decltype(&lua_close)> lua_{luaL_newstate(), &lua_close};

  auto popStack(int num = 1) noexcept -> void;

public:
  LuaInstance();

  auto execFiles(const std::span<const char *const> file_list) -> void;

  auto cref() const noexcept -> const lua_State &;
  auto ref() noexcept -> lua_State &;

  auto GetLuaValue(const std::span<const char *const> key_path) noexcept
      -> std::variant<double, std::string, bool, std::monostate>;
};
