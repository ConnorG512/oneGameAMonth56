#pragma once 

#include "sdl/texture.hpp"

#include <SDL3/SDL_surface.h>
#include <SDL3/SDL_render.h>
#include <memory>
#include <optional>

class SDL_Renderer;
class SDL_Texture;

namespace SDL 
{
class Bitmap 
{
  SDL::Texture texture_;
  std::unique_ptr<SDL_Surface, decltype(&SDL_DestroySurface)> image_ {
    CreateBitmap("assets/image/default.bmp")}; 
  SDL_Renderer& renderer_;

  auto CreateBitmap(const char* image_path) noexcept -> 
    std::unique_ptr<SDL_Surface, decltype(&SDL_DestroySurface)>;
  
  public:
    Bitmap(SDL_Renderer& renderer, std::pair<int,int>wh = {32,32});
    auto render(
        SDL_Renderer& renderer,
        const std::optional<SDL_FRect*> source_rectangle,
        const std::optional<SDL_FRect*> dest_rectangle
    ) noexcept -> void;
};
}
