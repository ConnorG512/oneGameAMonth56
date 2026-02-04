#pragma once 

#include "file-output/logging/logger.hpp"

#include <lua.hpp>
#include <memory>
#include <optional>
#include <cstddef>
#include <span>
#include <format>
#include <variant>

namespace File {class Logger;}

class LuaInstance 
{
  std::unique_ptr<lua_State, decltype(&lua_close)> lua_ {luaL_newstate(), &lua_close}; 
  std::optional<std::reference_wrapper<File::Logger>> logger_ {std::nullopt};

  auto popStack(int num = 1) noexcept -> void;
  
  public: 
    LuaInstance(std::optional<std::reference_wrapper<File::Logger>> logger = std::nullopt);

    auto execFile(const char* file_name) noexcept -> void;
    
    auto cref() const noexcept -> const lua_State&;
    auto ref() noexcept -> lua_State&;
    
    auto GetLuaValue(const std::span<const char*> key_path) noexcept 
      -> std::variant<double, std::string, bool, std::monostate>;
};
