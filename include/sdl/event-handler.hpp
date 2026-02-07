#pragma once

#include <SDL3/SDL.h>
#include <cstdint>

namespace File
{
class Logger;
}

namespace SDL
{
class EventHandler
{
  File::Logger &logger_;
  bool game_running_{true};

public:
  EventHandler(File::Logger &logger);

  auto PollEvent() noexcept -> void;
  auto isGameRunning() const noexcept -> bool;
};
} // namespace SDL
