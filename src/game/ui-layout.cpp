#include "game/ui-layout.hpp"

Game::GUI::Layout::Layout(SDL_Renderer &renderer, const Properties &name, const Properties &score,
                         const Properties &high_score, const Properties &times_played)
    : renderer_{renderer}, name_{name.label, {name.x_pos, name.y_pos}, renderer_},
      score_{score.label, {score.x_pos, score.y_pos}, renderer},
      high_score_{high_score.label, {high_score.x_pos, high_score.y_pos}, renderer_},
      times_played_{times_played.label, {times_played.x_pos, times_played.y_pos}, renderer_}
{
}

auto Game::GUI::Layout::drawText() -> void
{
  for (auto *element : {&name_, &score_, &high_score_, &times_played_})
  {
    element->draw();
  }
}

auto Game::GUI::Layout::setText(Text text, const std::string &message) -> void
{
  switch (text)
  {
    default:
    case Text::name:
      name_.swapText(message);
      break;
    case Text::score:
      score_.swapText(message);
      break;
    case Text::high_score:
      high_score_.swapText(message);
      break;
    case Text::times_played:
      times_played_.swapText(message);
      break;
  }
}
