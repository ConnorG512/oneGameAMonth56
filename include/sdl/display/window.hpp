#pragma once

#include <SDL3/SDL_video.h>
#include <expected>
#include <memory>
#include <utility>

namespace SDL
{
class Window
{
  std::unique_ptr<SDL_Window, decltype(&SDL_DestroyWindow)> window_{
      SDL_CreateWindow("Game Window", 1024, 1024, 0), &SDL_DestroyWindow};

public:
  Window() = default;
  Window(const char *title, const std::pair<int, int> &xy);

  auto ref() noexcept -> SDL_Window &;
  auto WindowSize() const noexcept -> std::expected<std::pair<int, int>, std::string>;
  auto getRefreshRate() const noexcept -> std::expected<float, std::string>;
};
} // namespace SDL
