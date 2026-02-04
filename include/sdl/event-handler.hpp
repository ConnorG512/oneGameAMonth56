#pragma once 

#include <SDL3/SDL.h>
#include <cstdint>

namespace File {class Logger;}

namespace SDL 
{
  class EventHandler 
  {
    SDL_Event event_;
    File::Logger &logger_;

    public:
      EventHandler(File::Logger &logger);
      auto PollEvent(uint32_t sdl_event) noexcept -> bool;
  };
}
