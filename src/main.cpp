#include "sdl/init.hpp"
#include "sdl/window-renderer/window-randerer.hpp"
#include "sdl/bitmap.hpp"

auto main() -> int 
{
  SDL::Init init{};
  SDL::WindowRenderer display{};
  
  SDL::Bitmap image{"assets/image/default.bmp", display.game_renderer.ptr()};

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

