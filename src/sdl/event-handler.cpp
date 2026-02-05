#include "sdl/event-handler.hpp"
#include "file-output/logging/logger.hpp"

#include <format>
#include <SDL3/SDL.h>

SDL::EventHandler::EventHandler(File::Logger &logger)
  : logger_{logger} 
{
  logger_.writeAddress("Event Handler", this);
}

auto SDL::EventHandler::PollEvent() noexcept -> void
{
  SDL_Event event;
  
  while(SDL_PollEvent(&event))
  {
    if(event.type == SDL_EVENT_QUIT)
      game_running_ = false;
  }
}

auto SDL::EventHandler::isGameRunning() const noexcept -> bool
{
  return game_running_;
}
