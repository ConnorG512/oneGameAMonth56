#include "sdl/init.hpp"

#include <SDL3/SDL.h>
#include <format>
#include <stdexcept>

SDL::Init::Init()
{
  if (!SDL_Init(SDL_INIT_VIDEO))
    throw std::runtime_error(std::format("Could not initialise SDL! Error: [].", SDL_GetError()).c_str());
}

SDL::Init::~Init() { SDL_Quit(); }
