#pragma once 

#include "game/game-entity.hpp"

#include <array>

namespace Gameplay
{
  class Player : public GameEntity
  {
    Player(
      const std::array<float,4>& xywh,
      SDL_Renderer& renderer,
      const LuaInstance& lua_instance,
      const char* image_path
    );
  };
}
