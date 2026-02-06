#pragma once

#include "game/game-entity.hpp"

class LuaInstance;
namespace SDL {class Renderer;}

namespace Gameplay 
{
  class Enemy : public GameEntity
  {
    public:
      Enemy(
        const std::array<float,4>& xywh,
        SDL_Renderer& renderer,
        LuaInstance& lua_instance,
        const char* image_path
      );
  };
}
