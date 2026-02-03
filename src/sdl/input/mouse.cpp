#include "sdl/input/mouse.hpp"

#include <SDL3/SDL_mouse.h>

auto SDL::Mouse::GetCursorPosition() noexcept -> const std::pair<float, float>&
{
  SDL_GetMouseState(&xy_pos.first, &xy_pos.second);
  return xy_pos;
}
