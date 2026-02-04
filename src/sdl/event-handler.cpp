#include "sdl/event-handler.hpp"
#include "file-output/logging/logger.hpp"

#include <format>

SDL::EventHandler::EventHandler(File::Logger &logger)
  : logger_{logger} 
{
  logger_.writeAddress("Event Handler", this);
}

auto SDL::EventHandler::PollEvent(uint32_t sdl_event) noexcept -> bool
{
  const bool event_hit {event_.type == sdl_event};
  if (event_hit)
  {
    logger_.writeToLog(File::Logger::LogType::debug, std::format("Event hit {}", sdl_event));
    return true;
  }
  else 
    return false;
}
