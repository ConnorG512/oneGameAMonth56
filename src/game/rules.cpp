#include "game/rules.hpp"
#include "game/ui-layout.hpp"
#include "sdl/audio/audio.hpp"
#include "sdl/audio/modes.hpp"
#include <string>

Game::Rules::Rules(int time_start, int time_end, int score_max) : score{score_max}, time{time_start, time_end} {}

auto Game::Rules::restartGame(Audio::Instance &audio, Game::GUI::Layout &game_ui) -> void
{
  if (time.isZeroOrLess())
  {
    time.reset(Counter<int>::ResetFrom::max);
    score.reset();
    audio.playAudio<Audio::Modes::BasicSine<float>>(220.f, 48000.0f, 48000 / 2, 0.05f);
    game_ui.setText(Game::GUI::Layout::Text::score, std::to_string(score.cref().getCurrent()));
  }
}
