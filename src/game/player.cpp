#include "game/player.hpp"

Gameplay::Player::Player(
      const std::array<float,4>& xywh,
      SDL_Renderer& renderer,
      const char* image_path
    )
  : collision_{xywh.at(0), xywh.at(1),xywh.at(2),xywh.at(3)}
  , texture_{renderer, image_path} {}
