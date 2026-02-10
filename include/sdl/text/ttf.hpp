#pragma once

#include <SDL3_ttf/SDL_ttf.h>
#include <cassert>
#include <cstddef>
#include <memory>

class SDL_Renderer;
class SDL_Surface;

namespace SDL
{
class Ttf
{
  std::unique_ptr<TTF_Font, decltype(&TTF_CloseFont)> font_{nullptr, &TTF_CloseFont};

  auto OpenFont(const char *font_path, float size) -> std::unique_ptr<TTF_Font, decltype(&TTF_CloseFont)>;
  auto CreateText(const char* text, std::size_t len) -> SDL_Surface*;

public:
  Ttf(const char* font_path, float size);
  ~Ttf() = default;

  auto ref() noexcept -> TTF_Font &
  {
    assert(font_.get() != nullptr);
    return *font_.get();
  }
};
} // namespace SDL
