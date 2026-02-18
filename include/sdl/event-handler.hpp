#pragma once

#include <SDL3/SDL.h>
#include <cstdint>
#include <functional>

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

  auto PollEvent(std::function<void()> on_click_func = nullptr) noexcept -> void;
  auto isGameRunning() const noexcept -> bool;
  auto quit() -> void;
};
} // namespace SDL
