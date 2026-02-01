#include <memory>

#include <SDL3/SDL.h>
#include <SDL3/SDL_video.h>
#include <stdexcept>
#include <format>

auto main() -> int 
{
  if(!SDL_Init(SDL_INIT_VIDEO))
    throw std::runtime_error("Failed to initisalise SDL video!");

  std::unique_ptr<SDL_Window, decltype(&SDL_DestroyWindow)> game_window { 
    SDL_CreateWindow("Game Window", 1600, 900, SDL_WINDOW_RESIZABLE | SDL_WINDOW_OPENGL), &SDL_DestroyWindow};

  if(game_window == nullptr)
    throw std::runtime_error(std::format("Failed to create game window!, {}.", SDL_GetError()).c_str());
  
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
  
  
  SDL_Quit();
  return 0;
}

