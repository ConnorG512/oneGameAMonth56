#include "sdl/text/text.hpp"

SDL::Text::Text(const std::string& text, SDL_Renderer &renderer)
    : renderer_{renderer}, text_object_{TTF_CreateText(text_engine_.get(), font_.get(), text.c_str(), text.size()), &TTF_DestroyText}
{
}

auto SDL::Text::draw(std::pair<float, float>xy) noexcept -> void
{
  TTF_DrawRendererText(text_object_.get(), xy.first, xy.second);
}

auto SDL::Text::swapText(const std::string& text) noexcept -> void
{
  TTF_SetTextString(text_object_.get(), text.c_str(), text.size());
}
