#pragma once 

#include "sdl/rectangle.hpp"
#include "sdl/image/texture.hpp"
#include "game/health.hpp"
#include "lua/lua.hpp"

namespace Gameplay 
{
  class GameEntity 
  {
    public:
      SDL::Rectangle bounds_ {0.0, 0.0, 32.0, 32.0};
      SDL::Texture texture_;
      HealthComponent<int> health_ {1000, 1500};

    protected: 
      GameEntity(
        const std::array<float,4>& xywh,
        SDL_Renderer& renderer,
        const LuaInstance& lua_instance,
        const char* image_path
      );
  };
}
