#include "game/score.hpp"
#include "sdl/audio.hpp"
#include "utils/sine.hpp"

#include <cassert>

/*
  For every time the score goes past the 10,000 mark. Play a brighter beep tone. 
*/
auto Game::Score::increase(int amount, SDL::Audio &audio) noexcept -> int
{
  constexpr int threshold {10000};
  
  const auto prev_score{count.getCurrent()};
  const auto new_score {count.increase(amount)};
  
  if((new_score / threshold) > (prev_score / threshold))
  {
    audio.pushStream(Utils::generateSine(440.0f, 48000.0f, 48000 / 2, 0.30f));
    audio.resumeStream();
  }

  return new_score;
}

auto Game::Score::cref() const noexcept -> const Counter<int>& 
{
  return count;
}
