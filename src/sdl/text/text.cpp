#include "sdl/text/text.hpp"

SDL::Text::Text(float text_size, std::array<float, 4> bounds_xywh, const char* text, size_t len, SDL_Renderer &renderer)
    : ttf{"assets/fonts/Orbitron/static/Orbitron-Regular.ttf", text_size}
    , texture{renderer, ttf.ref(), text, len}
    , rectangle{bounds_xywh} {}
