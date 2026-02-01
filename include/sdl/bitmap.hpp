#pragma once 

#include <memory>
#include "SDL3/SDL_surface.h"

class SDL_Renderer;

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
};
}
