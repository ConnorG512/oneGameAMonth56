#include "sdl/window-renderer/window.hpp"

#include <cassert>

auto SDL::Window::ptr() noexcept -> SDL_Window *
{
  assert(window_.get() != nullptr);
  return window_.get();
}

auto SDL::Window::WindowSize() noexcept -> std::pair<int, int> 
{
  int w, h {};
  SDL_GetWindowSize(window_.get(), &w, &h);
  return {w,h};
}
