#pragma once

#include "sdl/text/text.hpp"

class SDL_Renderer;

namespace Game::UI
{

class Layout
{
  SDL_Renderer &renderer_;

  SDL::Text name_;
  SDL::Text score_;
  SDL::Text high_score_;
  SDL::Text times_played_;
  
public:
  struct Properties
  {
    const char *label{nullptr};
    int x_pos{0};
    int y_pos{0};
  };

  Layout(SDL_Renderer &renderer, const Properties &name, const Properties &score, const Properties &high_score,
         const Properties &times_played);

  auto drawText() -> void;
};
} // namespace Game::UI
