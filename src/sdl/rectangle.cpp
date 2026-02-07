#include "sdl/rectangle.hpp"

SDL::Rectangle::Rectangle(float x, float y, float w, float h) : rect_{x, y, w, h} {}

SDL::Rectangle::Rectangle(std::pair<float, float> xy, std::pair<float, float> wh)
    : rect_{xy.first, xy.second, wh.first, wh.second}
{
}

SDL::Rectangle::Rectangle(std::array<float, 4> xywh) : rect_{xywh.at(0), xywh.at(1), xywh.at(2), xywh.at(3)} {}

auto SDL::Rectangle::cref() const noexcept -> const SDL_FRect & { return rect_; }

auto SDL::Rectangle::ref() noexcept -> SDL_FRect & { return rect_; }
