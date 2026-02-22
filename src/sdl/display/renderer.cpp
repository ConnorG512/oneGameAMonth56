#include "sdl/window-renderer/renderer.hpp"

#include <SDL3/SDL_error.h>
#include <SDL3/SDL_render.h>
#include <cassert>
#include <format>
#include <utility>

auto SDL::Renderer::CreateRenderer(SDL_Window &window, const char *driver) noexcept
    -> std::unique_ptr<SDL_Renderer, decltype(&SDL_DestroyRenderer)>
{
  SDL_Renderer *renderer{SDL_CreateRenderer(&window, driver)};

  assert(renderer != nullptr);
  return std::unique_ptr<SDL_Renderer, decltype(&SDL_DestroyRenderer)>{renderer, &SDL_DestroyRenderer};
}

// Constructor
SDL::Renderer::Renderer(SDL_Window &window) : renderer_{CreateRenderer(window, nullptr)} {}

// Getter
auto SDL::Renderer::ref() noexcept -> SDL_Renderer &
{
  assert(renderer_.get() != nullptr);
  return *renderer_.get();
}

// Rendering
auto SDL::Renderer::clearScreen() noexcept -> void { SDL_RenderClear(renderer_.get()); }

auto SDL::Renderer::present() noexcept -> void { SDL_RenderPresent(renderer_.get()); }

auto SDL::Renderer::drawColorFloat(float red, float green, float blue, float alpha) noexcept -> void
{
  assert(red >= 0 && green >= 0 && blue >= 0 && alpha >= 0);
  SDL_SetRenderDrawColorFloat(renderer_.get(), red, green, blue, alpha);
}

auto SDL::Renderer::renderTexture(SDL_Texture &texture, SDL_FRect *source_rect, SDL_FRect *dest_rect) -> void
{
  SDL_RenderTexture(renderer_.get(), &texture, source_rect, dest_rect);
}

auto SDL::Renderer::renderTextureRotate(SDL_Texture &texture, const SDL_FRect *source_rect, const SDL_FRect *dest_rect,
                                        double angle, const SDL_FPoint *center_point, const SDL_FlipMode flipmode)
    -> void
{
  SDL_RenderTextureRotated(renderer_.get(), &texture, source_rect, dest_rect, angle, center_point, flipmode);
}

auto SDL::Renderer::setVsnc(vsync_option vsync) -> std::expected<void, std::string>
{
  if (SDL_SetRenderVSync(renderer_.get(), std::to_underlying(vsync)))
    return std::unexpected(std::format("Failed to set vsync! Error [{}]", SDL_GetError()));
  else
    return {};
}
