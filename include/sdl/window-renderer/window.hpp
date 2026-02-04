#pragma once

#include <SDL3/SDL_video.h>
#include <memory>
#include <utility>

namespace SDL
{
class Window
{
  std::unique_ptr<SDL_Window, decltype(&SDL_DestroyWindow)> window_{
      SDL_CreateWindow("Game Window", 1024, 1024, SDL_WINDOW_OPENGL), &SDL_DestroyWindow};

public:
  Window() = default;
  Window(const char* title, const std::pair<int,int>& xy);

  auto ptr() noexcept -> SDL_Window *;
  auto WindowSize() noexcept -> std::pair<int, int>; 
};
} // namespace SDL
