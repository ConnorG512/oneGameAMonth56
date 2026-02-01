#include "sdl/window-renderer/window.hpp"

#include <cassert>

auto SDL::Window::ptr() noexcept -> SDL_Window* 
{
  assert(window_.get() != nullptr);
  return window_.get();
}
