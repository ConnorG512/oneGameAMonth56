#include "sdl/init.hpp"

#include <SDL3/SDL.h>
#include <SDL3/SDL_init.h>
#include <SDL3/SDL_video.h>
#include <SDL3_ttf/SDL_ttf.h>
#include <format>
#include <stdexcept>

SDL::Init::Init()
{
  if (SDL_Init(SDL_INIT_VIDEO) == 0)
    throw std::runtime_error(std::format("Could not initialise SDL! Error: [{}].", SDL_GetError()));
  if (TTF_Init() == 0)
    throw std::runtime_error(std::format("Could not get sdl3 ttf! Error: [{}].", SDL_GetError()));
  if(SDL_Init(SDL_INIT_AUDIO) == 0)
    throw std::runtime_error(std::format("Could not initialise SDL Audio! Error: [{}].", SDL_GetError()));

  // Set OpenGL Attributes:
  if(!SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3))
  {
    throw std::runtime_error(std::format("Failed to set GL Major context", SDL_GetError()));
  }
  if(!SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3))
  {
    throw std::runtime_error(std::format("Failed to set GL Minor context", SDL_GetError()));
  }
  if(!SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE))
  {
    throw std::runtime_error(std::format("Failed to set GL Minor context", SDL_GetError()));
  }
}

SDL::Init::~Init()
{
  SDL_Quit();
  TTF_Quit();
}
