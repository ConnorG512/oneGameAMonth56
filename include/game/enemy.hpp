#pragma once

#include "game/health.hpp"
#include "sdl/image/texture.hpp"
#include "sdl/rectangle.hpp"
#include <utility>

class LuaInstance;
namespace File
{
class Logger;
}
class SDL_Renderer;

namespace Game
{
class Enemy
{
public:
  SDL::Rectangle bounds_{};
  SDL::Texture texture_;
  Game::HealthComponent<int> health_{};

  Enemy(LuaInstance &lua, SDL_Renderer &renderer);
  Enemy(std::pair<float, float>xy, LuaInstance &lua, SDL_Renderer &renderer);
};
} // namespace Game
