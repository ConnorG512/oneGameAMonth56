#pragma once 

#include "SDL3/SDL_surface.h"

#include <memory>
#include <optional>

class SDL_Renderer;
class SDL_Texture;

namespace SDL 
{
class Bitmap 
{
  std::unique_ptr<SDL_Surface, decltype(&SDL_DestroySurface)> image_ {
    CreateBitmap("assets/image/default.bmp")}; 
  SDL_Renderer* renderer_ {nullptr};

  auto CreateBitmap(const char* image_path) noexcept -> 
    std::unique_ptr<SDL_Surface, decltype(&SDL_DestroySurface)>;
  
  public:
    Bitmap(const char* image_path = "assets/image/default.bmp", SDL_Renderer* renderer = nullptr);
    auto render(
        SDL_Renderer& renderer,
        SDL_Texture& texture,
        const std::optional<SDL_FRect*> source_rectangle,
        const std::optional<SDL_FRect*> dest_rectangle
    ) noexcept -> void;
};
}
