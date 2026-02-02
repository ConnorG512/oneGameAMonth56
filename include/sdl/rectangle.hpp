#pragma once 

#include <SDL3/SDL_rect.h>

namespace SDL
{
class Rectangle 
{
  // https://wiki.libsdl.org/SDL3/SDL_FRect
  SDL_FRect rect_ {0.0, 0.0, 32.0, 32.0};

  public:
  Rectangle(float x = 0.0, float y = 0.0, float w = 32.0, float h = 32.0);

  auto cref() const noexcept -> const SDL_FRect&
  {
    return rect_;
  }
};
}
