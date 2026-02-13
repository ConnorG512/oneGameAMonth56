#pragma once

#include "game/health.hpp"
#include "sdl/image/texture.hpp"
#include "sdl/rectangle.hpp"
#include "game/counter.hpp"

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
  Game::Counter<int> score_{1000000};

  Player(LuaInstance &lua, SDL_Renderer &renderer);
};
} // namespace Game
