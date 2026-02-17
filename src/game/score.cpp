#include "game/score.hpp"
#include "sdl/audio.hpp"
#include "utils/sine.hpp"

#include <cassert>

auto Game::Score::increase(int amount, SDL::Audio &audio) noexcept -> int
{
  constexpr int threshold {10000};

  const auto new_score {count.increase(amount)};
  
  assert(threshold != 0);
  if(amount % threshold == 0)
  {
    audio.pushStream(Utils::generateSine(440.0f, 48000.0f, 48000 / 2, 0.4f));
    audio.resumeStream();
  }

  return new_score;
}
