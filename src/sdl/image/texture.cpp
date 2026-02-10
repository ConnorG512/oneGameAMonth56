#include "sdl/image/texture.hpp"

#include <SDL3_image/SDL_image.h>
#include <cassert>
#include <filesystem>
#include <print>

SDL::Texture::Texture(SDL_Renderer &renderer, const char *image_path) : texture_{CreateTexture(renderer, image_path)} {}

auto SDL::Texture::CreateTexture(SDL_Renderer &renderer, const char *image_path) noexcept
    -> std::unique_ptr<SDL_Texture, decltype(&SDL_DestroyTexture)>
{
  if (!std::filesystem::exists(image_path))
    std::println(stderr, "Invalid file path provided!");

  SDL_Texture *texture{IMG_LoadTexture(&renderer, image_path)};
  if (texture == nullptr)
    std::println(stderr, "Failed to create texture! Error: [{}].", SDL_GetError());

  assert(texture != nullptr);
  return std::unique_ptr<SDL_Texture, decltype(&SDL_DestroyTexture)>{texture, &SDL_DestroyTexture};
}

auto SDL::Texture::CreateTextureFromSurface(SDL_Renderer &renderer, SDL_Surface &surface)
    -> std::unique_ptr<SDL_Texture, decltype(&SDL_DestroyTexture)>
{
  auto *texture{SDL_CreateTextureFromSurface(&renderer, &surface)};
  if (texture == nullptr)
    throw std::runtime_error("Failed to create an SDL texture!");

  return {texture, &SDL_DestroyTexture};
}

auto SDL::Texture::ref() -> SDL_Texture &
{
  assert(texture_.get() != nullptr);
  return *texture_.get();
}
