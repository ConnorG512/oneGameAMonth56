#include "sdl/text/text.hpp"

SDL::Text::Text(const std::string &text, std::pair<float, float> xy, SDL_Renderer &renderer)
    : renderer_{renderer}, xy_{xy},
      text_object_{TTF_CreateText(text_engine_.get(), font_.get(), text.c_str(), text.size()), &TTF_DestroyText}
{
}

auto SDL::Text::draw() noexcept -> void { TTF_DrawRendererText(text_object_.get(), xy_.first, xy_.second); }

auto SDL::Text::swapText(const std::string &text) noexcept -> void
{
  TTF_SetTextString(text_object_.get(), text.c_str(), text.size());
}
