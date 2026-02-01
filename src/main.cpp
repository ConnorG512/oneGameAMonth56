#include <memory>

#include "sdl/init.hpp"
#include "sdl/window-renderer/window-randerer.hpp"

#include <SDL3/SDL.h>
#include <SDL3/SDL_video.h>
#include <stdexcept>
#include <format>

auto main() -> int 
{
  SDL::Init init{};
  SDL::WindowRenderer display{};

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

    display.game_renderer.clearScreen();
    display.game_renderer.drawColorFloat(0.5, 0.5, 0.5);
    display.game_renderer.present();
  }
  
  return 0;
}

