#include "game/score.hpp"
#include "game/counter.hpp"

#include <cassert>

Game::Score::Score(int max_score) : count_{0, max_score} {}

/*
  For every time the score goes past the 10,000 mark. Play a brighter beep tone.
*/
auto Game::Score::increase(int amount, int multiplier) noexcept -> std::pair<int, ScoreType>
{
  constexpr int threshold{10000};

  const auto prev_score{count_.getCurrent()};
  const auto new_score{count_.increase(amount) * multiplier};

  if ((new_score / threshold) > (prev_score / threshold))
  {
    return {new_score, Game::Score::ScoreType::bonus};
  }

  return {new_score, Game::Score::ScoreType::standard};
}

auto Game::Score::reset() -> void
{
  count_.reset(Counter<int>::ResetFrom::zero);  
}

auto Game::Score::cref() const noexcept -> const Counter<int> & { return count_; }
