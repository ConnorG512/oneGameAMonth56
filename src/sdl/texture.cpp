#include "sdl/texture.hpp"

#include <SDL3/SDL_render.h>
#include <cassert>
#include <print>

auto SDL::Texture::CreateTexture(
    SDL_Renderer& renderer, 
    SDL_PixelFormat format, 
    SDL_TextureAccess access, 
    std::pair<int, int> wh ) noexcept 
  -> std::unique_ptr<SDL_Texture, decltype(&SDL_DestroyTexture)>
{
  const auto [width, height] = wh;

  SDL_Texture *texture {SDL_CreateTexture(
      &renderer, 
      format, 
      access, 
      width, 
      height)
  };
  if(texture == nullptr)
    std::println(stderr, "Failed to create texture! Error: [{}].", SDL_GetError());
  
  assert(texture != nullptr);
  return std::unique_ptr<SDL_Texture, decltype(&SDL_DestroyTexture)> {
    texture,
    &SDL_DestroyTexture
  };
}

auto SDL::Texture::ptr() -> SDL_Texture*
{
  assert(texture_.get() != nullptr);
  return texture_.get();
}
