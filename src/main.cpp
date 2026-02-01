#include <memory>

#include "sdl/init.hpp"

#include <SDL3/SDL.h>
#include <SDL3/SDL_video.h>
#include <stdexcept>
#include <format>

auto main() -> int 
{
  SDL::Init init{};

  // Game loop
  bool finished {false};
  while (!finished) 
  {
    SDL_Event event;

    while (SDL_PollEvent(&event)) 
    {
      if(event.type == SDL_EVENT_QUIT)
      {
        finished = true;
      }
    }

  }
  
  return 0;
}

