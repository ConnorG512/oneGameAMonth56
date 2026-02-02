#pragma once 

#include <SDL3/SDL_render.h>
#include <utility>
#include <memory>

namespace SDL 
{
class Texture 
{
  std::unique_ptr<SDL_Texture, decltype(&SDL_DestroyTexture)> texture_ 
    {nullptr, &SDL_DestroyTexture}; 
  
  auto CreateTexture(
      SDL_Renderer& renderer, 
      SDL_PixelFormat format, 
      SDL_TextureAccess access, 
      std::pair<int, int> wh) 
    noexcept -> std::unique_ptr<SDL_Texture, decltype(&SDL_DestroyTexture)>;
  
  public:
    Texture(
      SDL_Renderer& renderer, 
      SDL_PixelFormat format, 
      SDL_TextureAccess access, 
      std::pair<int, int> wh)
    : texture_{CreateTexture(renderer, format, access, wh)} {}

    auto ptr() -> SDL_Texture*;
};
}
