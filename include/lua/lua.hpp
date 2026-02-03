#pragma once 

#include "file-output/logging/logger.hpp"

#include <lua.hpp>
#include <memory>
#include <optional>

namespace File {class Logger;}

class LuaInstance 
{
  std::unique_ptr<lua_State, decltype(&lua_close)> lua_ {luaL_newstate(), &lua_close}; 
  
  public: 
    LuaInstance(std::optional<std::reference_wrapper<File::Logger>> logger = std::nullopt);

    auto cref() const noexcept -> const lua_State&;
    auto ref() noexcept -> lua_State&;
};
