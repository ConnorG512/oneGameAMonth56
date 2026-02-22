#include "sdl/display/display.hpp"

SDL::Display::Display(const char *title, const std::pair<int, int> &xy) : game_window{title, xy} {}

