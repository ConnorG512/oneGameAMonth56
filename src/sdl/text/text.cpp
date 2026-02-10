#include "sdl/text/text.hpp"

SDL::Text::Text(const char* font_path, float text_size, std::array<float, 4> bounds_xywh, SDL_Renderer &renderer)
  : ttf{font_path, text_size}
  , rectangle{bounds_xywh}
  , texture{renderer, font_path} {}
