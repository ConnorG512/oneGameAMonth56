#pragma once

#include "sdl/image/texture.hpp"
#include "sdl/rectangle.hpp"
#include "sdl/ttf.hpp"

#include <array>

class SDL_Renderer;

namespace SDL
{
struct Text
{
  SDL::Ttf ttf{nullptr, 32};
  SDL::Rectangle rectangle{32, 32, 32, 32};
  SDL::Texture texture;

  Text(const char *font_path, float text_size, std::array<float, 4> bounds_xywh, SDL_Renderer &renderer);
};
} // namespace SDL
