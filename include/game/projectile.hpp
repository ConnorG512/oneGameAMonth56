#pragma once 

#include "sdl/image/texture.hpp"
#include "sdl/rectangle.hpp"

class LuaInstance;
class SDL_Renderer;

namespace Game {
class Projectile 
{
  public:
    SDL::Rectangle bounds_{};
    SDL::Texture texture_;

    Projectile(LuaInstance &lua, SDL_Renderer &renderer);
};
}
