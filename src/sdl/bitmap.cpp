#include "sdl/bitmap.hpp"

#include <cassert>
#include <filesystem>
#include <print>

auto SDL::Bitmap::CreateBitmap(const char* image_path) noexcept 
  -> std::unique_ptr<SDL_Surface, decltype(&SDL_DestroySurface)>
{
  assert(image_path != nullptr);
  if(!std::filesystem::exists(image_path))
    std::println(stderr, "ERROR: path [{}] does not exist!", image_path);
  
  SDL_Surface *image {SDL_LoadBMP(image_path)};    
  if(image == nullptr)
    std::println(stderr, "Unable to load bitmap! Error: {}", SDL_GetError());
  
  assert(image != nullptr);
  return std::unique_ptr<SDL_Surface, decltype(&SDL_DestroySurface)> {
    image,
    &SDL_DestroySurface
  };
}

SDL::Bitmap::Bitmap(SDL_Renderer& renderer, std::pair<int, int> wh)
    : texture_{
      renderer, 
        SDL_PixelFormat::SDL_PIXELFORMAT_RGBA32, 
        SDL_TextureAccess::SDL_TEXTUREACCESS_STATIC,
        wh
    }
    , image_{CreateBitmap("assets/image/default.bmp")}
    , renderer_{renderer} {}

auto SDL::Bitmap::render(
    SDL_Renderer& renderer,
    const std::optional<SDL_FRect*> source_rectangle,
    const std::optional<SDL_FRect*> dest_rectangle
) noexcept -> void
{
  SDL_RenderTexture(
      &renderer, 
      texture_.ptr(), 
      source_rectangle.value_or(nullptr), 
      dest_rectangle.value_or(nullptr) 
  );
}
