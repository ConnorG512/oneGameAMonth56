#include "game/score.hpp"
#include "game/counter.hpp"
#include "sdl/audio/audio.hpp"
#include "sdl/audio/modes.hpp"

#include <cassert>

Game::Score::Score(int max_score) : count_{0, max_score} {}

/*
  For every time the score goes past the 10,000 mark. Play a brighter beep tone.
*/
auto Game::Score::increase(int amount, Audio::Instance &audio) noexcept -> int
{
  constexpr int threshold{10000};

  const auto prev_score{count_.getCurrent()};
  const auto new_score{count_.increase(amount)};

  if ((new_score / threshold) > (prev_score / threshold))
  {
    audio.playAudio<Audio::Modes::BasicSine<float>>(440.0f, 48000.0f, 48000 / 2, 0.05f);
    audio.resumeStream();
  }

  return new_score;
}

auto Game::Score::reset() -> void
{
  count_.reset(Counter<int>::ResetFrom::zero);  
}

auto Game::Score::cref() const noexcept -> const Counter<int> & { return count_; }
