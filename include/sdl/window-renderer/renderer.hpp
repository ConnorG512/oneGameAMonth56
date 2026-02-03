#pragma once

#include <SDL3/SDL_render.h>
#include <memory>

class SDL_Window;

namespace SDL
{
class Renderer
{
  std::unique_ptr<SDL_Renderer, decltype(&SDL_DestroyRenderer)> renderer_{nullptr, &SDL_DestroyRenderer};

  auto CreateRenderer(SDL_Window *window, const char *driver = nullptr) noexcept
      -> std::unique_ptr<SDL_Renderer, decltype(&SDL_DestroyRenderer)>;

public:
  Renderer(SDL_Window *window);

  auto ref() noexcept -> SDL_Renderer &;
  auto clearScreen() noexcept -> void;
  auto drawColorFloat(float red = 0, float green = 0, float blue = 0, float alpha = SDL_ALPHA_OPAQUE_FLOAT) noexcept
      -> void;
  auto present() noexcept -> void;
  auto renderTexture(SDL_Texture &texture, SDL_FRect *source_rect, SDL_FRect *dest_rect) -> void;
  auto renderTextureRotate(SDL_Texture &texture, const SDL_FRect* source_rect, const SDL_FRect* dest_rect, double angle, const SDL_FPoint* center_point, SDL_FlipMode flipmode) -> void
};
} // namespace SDL
