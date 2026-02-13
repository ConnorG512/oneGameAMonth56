#pragma once

#include "game/health.hpp"
#include "sdl/image/texture.hpp"
#include "sdl/rectangle.hpp"

class LuaInstance;
namespace File
{
class Logger;
}
class SDL_Renderer;

namespace Game
{
class Player
{
public:
  SDL::Rectangle bounds_{};
  SDL::Texture texture_;
  Game::HealthComponent<int> health_{};

  Player(LuaInstance &lua, SDL_Renderer &renderer);
};
} // namespace Game
