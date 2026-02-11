#pragma once

#include "sdl/image/texture.hpp"
#include "sdl/rectangle.hpp"

#include <utility>

class LuaInstance;
class SDL_Renderer;

namespace Game
{
class Projectile
{
  std::pair<int, int> screen_max_xy_{0, 0};

public:
  SDL::Rectangle bounds_{};
  SDL::Texture texture_;

  auto destroy() -> bool;

  Projectile(std::pair<int, int> screen_max_xy, std::pair<float, float> xy, LuaInstance &lua, SDL_Renderer &renderer);
};
} // namespace Game
