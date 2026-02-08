#pragma once 

#include <array>
#include <span>

namespace File
{
  [[maybe_unused]] constexpr auto lua_files = std::to_array<const char*>
  ({
    "config.lua",
    "gamescript/enemy.lua",
    "gamescript/projectile.lua",
    "gamescript/rules.lua"
  });

  auto validateFiles(const std::span<const char* const> required_files) -> void;
}  

