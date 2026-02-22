#pragma once

#include "sdl/window-renderer/renderer.hpp"
#include "sdl/window-renderer/window.hpp"

namespace SDL
{
class Display
{
public:
  Window game_window{};
  Renderer game_renderer{game_window.ref()};

  Display() = default;
  Display(const char *title, const std::pair<int, int> &xy);
};
} // namespace SDL
