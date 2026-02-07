#include "sdl/window-renderer/window-renderer.hpp"

SDL::WindowRenderer::WindowRenderer(const char *title, const std::pair<int, int> &xy) : game_window{title, xy} {}
