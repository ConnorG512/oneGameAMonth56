#include "game/enemy.hpp"

Gameplay::Enemy::Enemy(SDL_Renderer &renderer, const char* sprite_path)
  : texture_{renderer, sprite_path} {}
