#include "sdl/window-renderer/renderer.hpp"

#include <cassert>

auto SDL::Renderer::CreateRenderer(SDL_Window *window, const char *driver) noexcept
    -> std::unique_ptr<SDL_Renderer, decltype(&SDL_DestroyRenderer)>
{
  SDL_Renderer *renderer{SDL_CreateRenderer(window, driver)};

  assert(renderer != nullptr);
  return std::unique_ptr<SDL_Renderer, decltype(&SDL_DestroyRenderer)>{renderer, &SDL_DestroyRenderer};
}

// Constructor
SDL::Renderer::Renderer(SDL_Window *window) : renderer_{CreateRenderer(window, nullptr)} {}

auto SDL::Renderer::ref() noexcept -> SDL_Renderer &
{
  assert(renderer_.get() != nullptr);
  return *renderer_.get();
}

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
