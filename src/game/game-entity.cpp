#include "game/game-entity.hpp"

Gameplay::GameEntity::GameEntity(
        const std::array<float,4>& xywh,
        SDL_Renderer& renderer,
        const LuaInstance& lua_instance,
        const char* image_path
        )
  : bounds{xywh.at(0), xywh.at(1), xywh.at(2), xywh.at(3)}
  , texture_{renderer, image_path} {}
