#include "sdl/text/ttf.hpp"

#include <SDL3/SDL_error.h>
#include <SDL3/SDL_surface.h>
#include <SDL3_ttf/SDL_ttf.h>
#include <format>
#include <memory>
#include <stdexcept>

SDL::Ttf::Ttf(const char *font_path, float size) : font_{OpenFont(font_path, size)} {}

auto SDL::Ttf::OpenFont(const char *font_path, float size) -> std::unique_ptr<TTF_Font, decltype(&TTF_CloseFont)>
{
  TTF_Font *created_font{TTF_OpenFont(font_path, size)};
  if (created_font == nullptr)
  {
    throw std::runtime_error(std::format("Failed to create font! {}", SDL_GetError()));
  }

  return {created_font, &TTF_CloseFont};
}
