#pragma once

#include <SDL3/SDL_render.h>
#include <memory>
#include <utility>

namespace SDL
{
class Texture
{
  std::unique_ptr<SDL_Texture, decltype(&SDL_DestroyTexture)> texture_{nullptr, &SDL_DestroyTexture};

  auto CreateTexture(SDL_Renderer &renderer, const char *image_path) noexcept
      -> std::unique_ptr<SDL_Texture, decltype(&SDL_DestroyTexture)>;

public:
  Texture(SDL_Renderer &renderer, const char *image_path);

  auto ref() -> SDL_Texture &;
};
} // namespace SDL
