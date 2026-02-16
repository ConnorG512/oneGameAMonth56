#include "sdl/init.hpp"

#include <SDL3/SDL.h>
#include <SDL3/SDL_init.h>
#include <SDL3_ttf/SDL_ttf.h>
#include <format>
#include <stdexcept>

SDL::Init::Init()
{
  if (!SDL_Init(SDL_INIT_VIDEO))
    throw std::runtime_error(std::format("Could not initialise SDL! Error: [].", SDL_GetError()).c_str());
  if (!TTF_Init())
    throw std::runtime_error(std::format("Could not get sdl3 ttf! Error: [].", SDL_GetError()).c_str());
  if(!SDL_Init(SDL_INIT_AUDIO))
    throw std::runtime_error(std::format("Could not initialise SDL Audio! Error: [].", SDL_GetError()).c_str());
}

SDL::Init::~Init()
{
  SDL_Quit();
  TTF_Quit();
}
