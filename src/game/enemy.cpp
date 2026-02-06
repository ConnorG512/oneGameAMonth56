#include "game/enemy.hpp"

Gameplay::Enemy::Enemy(
        const std::array<float,4>& xywh,
        SDL_Renderer& renderer,
        LuaInstance& lua_instance,
        const char* image_path
    )
  : GameEntity{xywh, renderer, lua_instance, image_path} {}


