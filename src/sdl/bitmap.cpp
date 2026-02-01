#include "sdl/bitmap.hpp"

#include <cassert>
#include <filesystem>
#include <print>
#include <SDL3/SDL_render.h>

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

SDL::Bitmap::Bitmap(const char* image_path, SDL_Renderer* renderer)
    : image_{CreateBitmap(image_path)}
    , renderer_{renderer} 
{
  assert(renderer_ != nullptr);
}

auto SDL::Bitmap::render(
    SDL_Renderer& renderer,
    SDL_Texture& texture,
    const std::optional<SDL_FRect*> source_rectangle,
    const std::optional<SDL_FRect*> dest_rectangle
) noexcept -> void
{
  SDL_RenderTexture(
      &renderer, 
      &texture, 
      source_rectangle.value_or(nullptr), 
      dest_rectangle.value_or(nullptr) 
  );
}
