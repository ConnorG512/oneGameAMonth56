#pragma once 

#include "sdl/rectangle.hpp"
#include "sdl/image/texture.hpp"
#include "game/health.hpp"

class LuaInstance;
namespace File{class Logger;}
class SDL_Renderer;


namespace Game
{
  class Enemy
  {
    public:
      SDL::Rectangle bounds_{};
      SDL::Texture texture_;
      Game::HealthComponent<int> health_{};
      
      Enemy(LuaInstance& lua, SDL_Renderer &renderer);
  };
}
