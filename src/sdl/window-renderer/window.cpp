#include "sdl/window-renderer/window.hpp"

#include <SDL3/SDL_error.h>
#include <cassert>
#include <format>
#include <stdexcept>

auto SDL::Window::ptr() noexcept -> SDL_Window *
{
  assert(window_.get() != nullptr);
  return window_.get();
}

auto SDL::Window::WindowSize() noexcept -> std::pair<int, int>
{
  int w, h{};
  SDL_GetWindowSize(window_.get(), &w, &h);
  return {w, h};
}

SDL::Window::Window(const char *title, const std::pair<int, int> &xy)
    : window_{SDL_CreateWindow(title, xy.first, xy.second, SDL_WINDOW_OPENGL), &SDL_DestroyWindow}
{
  if(window_ == nullptr)
    throw std::runtime_error(std::format("Window cannot be null! SDL Error: {}", SDL_GetError()));
}
