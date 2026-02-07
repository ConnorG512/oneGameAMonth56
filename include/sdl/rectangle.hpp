#pragma once 

#include <SDL3/SDL_rect.h>
#include <utility>
#include <array>

namespace SDL
{
class Rectangle 
{
  // https://wiki.libsdl.org/SDL3/SDL_FRect
  SDL_FRect rect_ {0.0, 0.0, 32.0, 32.0};

  public:
  Rectangle(float x = 0.0, float y = 0.0, float w = 32.0, float h = 32.0);
  Rectangle(std::pair<float, float>xy, std::pair<float, float>wh);
  Rectangle(std::array<float, 4>xywh);

  auto cref() const noexcept -> const SDL_FRect&;
  auto ref() noexcept -> SDL_FRect&;
};
}
