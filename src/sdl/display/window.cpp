#include "sdl/display/window.hpp"

#include <SDL3/SDL_error.h>
#include <cassert>
#include <expected>
#include <format>
#include <stdexcept>

auto SDL::Window::ref() noexcept -> SDL_Window &
{
  assert(window_.get() != nullptr);
  return *window_;
}

auto SDL::Window::WindowSize() const noexcept -> std::expected<std::pair<int, int>, std::string>
{
  int w, h{};
  if(!SDL_GetWindowSize(window_.get(), &w, &h))
    return std::unexpected<std::string>(std::format("Error: Failed to get Window size! {}.", SDL_GetError()));
  else
    return std::pair<int,int>{w, h};
}

SDL::Window::Window(const char *title, const std::pair<int, int> &xy)
    : window_{SDL_CreateWindow(title, xy.first, xy.second), &SDL_DestroyWindow}
{
  if (window_ == nullptr)
    throw std::runtime_error(std::format("Window cannot be null! SDL Error: {}", SDL_GetError()));
}

auto SDL::Window::getRefreshRate() const noexcept -> std::expected<float, std::string>
{
  const auto display_id{SDL_GetDisplayForWindow(window_.get())};
  const auto *display_mode{SDL_GetCurrentDisplayMode(display_id)};
  if (display_mode == nullptr)
    return std::unexpected("Failed to get window display mode!");
  else
    return display_mode->refresh_rate;
}
