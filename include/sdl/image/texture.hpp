#pragma once

#include <SDL3/SDL_render.h>
#include <memory>

class SDL_Renderer;
class SDL_Surface;

namespace SDL
{
class Texture
{
  std::unique_ptr<SDL_Texture, decltype(&SDL_DestroyTexture)> texture_{nullptr, &SDL_DestroyTexture};

  auto CreateTexture(SDL_Renderer &renderer, const char *image_path) noexcept
      -> std::unique_ptr<SDL_Texture, decltype(&SDL_DestroyTexture)>;

  auto CreateTextureFromSurface(SDL_Renderer &renderer, SDL_Surface &surface)
      -> std::unique_ptr<SDL_Texture, decltype(&SDL_DestroyTexture)>;

public:
  Texture(SDL_Renderer &renderer, const char *image_path);
  Texture(SDL_Renderer &renderer, SDL_Surface &surface);

  auto ref() -> SDL_Texture &;
};
} // namespace SDL
