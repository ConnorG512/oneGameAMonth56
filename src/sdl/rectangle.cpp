#include "sdl/rectangle.hpp"

SDL::Rectangle::Rectangle(float x, float y, float w, float h)
  : rect_ {x, y, w, h} {}

auto SDL::Rectangle::cref() const noexcept -> const SDL_FRect&
{
  return rect_;
}

auto SDL::Rectangle::ref() noexcept -> SDL_FRect&
{
  return rect_;
}
