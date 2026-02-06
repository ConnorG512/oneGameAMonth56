#pragma once 

#include "sdl/rectangle.hpp"
#include "sdl/image/texture.hpp"
#include "game/health.hpp"

#include <array>

namespace SDL 
{
class Renderer;
}
namespace Gameplay
{
  class Player 
  {
    public:
      SDL::Rectangle collision_ {0.0, 0.0, 32.0, 32.0};
      SDL::Texture texture_;
      HealthComponent<int> health_{1000, 1500};

      Player(
          const std::array<float,4>& xywh,
          SDL_Renderer& renderer,
          const char* image_path
      );
  };
}
