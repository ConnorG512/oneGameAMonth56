#include "sdl/event-handler.hpp"
#include "file-output/logging/logger.hpp"

#include <format>
#include <SDL3/SDL.h>
#include <SDL3/SDL_mouse.h>

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

    if(event.type == SDL_EVENT_MOUSE_BUTTON_DOWN)
    {
      logger_.writeToLog(File::Logger::LogType::info, "Mouse pressed!");
    }
  }
}

auto SDL::EventHandler::isGameRunning() const noexcept -> bool
{
  return game_running_;
}
