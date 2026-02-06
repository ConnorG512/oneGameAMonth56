#pragma once

#include "sdl/image/texture.hpp"
#include "game/health.hpp"

class LuaInstance;
namespace SDL {class Renderer;}

namespace Gameplay 
{
  class Enemy 
  {
    public:
      SDL::Texture texture_;

      Enemy(SDL_Renderer &renderer, const char* sprite_path);
  };
}
