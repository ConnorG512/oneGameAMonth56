#pragma once

#include "sdl/image/texture.hpp"
#include "sdl/rectangle.hpp"
#include "sdl/text/ttf.hpp"

#include <array>

class SDL_Renderer;

namespace SDL
{
struct Text
{
  Text(float text_size, std::array<float, 4> bounds_xywh, const char* text, size_t len, SDL_Renderer &renderer);

  SDL::Ttf ttf;
  SDL::Texture texture;
  SDL::Rectangle rectangle{32, 32, 32, 32};
};
} // namespace SDL
