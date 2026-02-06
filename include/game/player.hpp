#pragma once 

#include "game/game-entity.hpp"

#include <array>

namespace Gameplay
{
  class Player : public GameEntity
  {
    public:
      Player(
        const std::array<float,4>& xywh,
        SDL_Renderer& renderer,
        LuaInstance& lua_instance,
        const char* image_path
      );
  };
}
