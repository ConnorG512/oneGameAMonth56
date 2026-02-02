#include "sdl/rectangle.hpp"

SDL::Rectangle::Rectangle(float x, float y, float w, float h)
  : rect_ {x, y, w, h} {}
