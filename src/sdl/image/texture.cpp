#include "sdl/image/texture.hpp"

#include <SDL3/SDL_render.h>
#include <cassert>
#include <print>

SDL::Texture::Texture(SDL_Renderer& renderer, const char* image_path)
  : texture_{CreateTexture(renderer, image_path)} {}

auto SDL::Texture::CreateTexture(SDL_Renderer& renderer, const char* image_path) noexcept 
  -> std::unique_ptr<SDL_Texture, decltype(&SDL_DestroyTexture)>
{
  std::unique_ptr<SDL_Surface, decltype(&SDL_DestroySurface)> surface {
    SDL_LoadBMP(image_path), &SDL_DestroySurface}; 
  if(surface == nullptr)
    std::println(stderr, "Failed to create Surface! Error: [{}].", SDL_GetError());

  SDL_Texture *texture {SDL_CreateTextureFromSurface(&renderer, surface.get())};
  if(texture == nullptr)
    std::println(stderr, "Failed to create texture! Error: [{}].", SDL_GetError());
  
  assert(texture != nullptr);
  return std::unique_ptr<SDL_Texture, decltype(&SDL_DestroyTexture)> {
    texture,
    &SDL_DestroyTexture
  };
}

auto SDL::Texture::ref() -> SDL_Texture&
{
  assert(texture_.get() != nullptr);
  return *texture_.get();
}
