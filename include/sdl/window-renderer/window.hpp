#pragma once

#include <memory>
#include <SDL3/SDL_video.h>

namespace SDL 
{
  class Window 
  {
    std::unique_ptr<SDL_Window, decltype(&SDL_DestroyWindow)> window_ { 
      SDL_CreateWindow("Game Window", 1600, 900, SDL_WINDOW_RESIZABLE | SDL_WINDOW_OPENGL), &SDL_DestroyWindow};

    public:
      auto ptr() noexcept -> SDL_Window*;
  };
}
