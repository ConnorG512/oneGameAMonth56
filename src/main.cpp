#include <memory>

#include "sdl/init.hpp"

#include <SDL3/SDL.h>
#include <SDL3/SDL_video.h>
#include <stdexcept>
#include <format>

auto main() -> int 
{
  SDL::Init init{};


  std::unique_ptr<SDL_Renderer, decltype(&SDL_DestroyRenderer)> game_renderer {
    SDL_CreateRenderer(game_window.get(), nullptr), &SDL_DestroyRenderer}; 

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

    SDL_RenderClear(game_renderer.get());
    SDL_RenderPresent(game_renderer.get());
  }
  
  return 0;
}

