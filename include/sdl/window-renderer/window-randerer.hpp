#pragma once

#include "sdl/window-renderer/renderer.hpp"
#include "sdl/window-renderer/window.hpp"

namespace SDL
{
class WindowRenderer
{
public:
  Window game_window{};
  Renderer game_renderer{game_window.ptr()};
};
} // namespace SDL
