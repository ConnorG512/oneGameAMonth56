#pragma once

#include "game/counter.hpp"
#include "game/score.hpp"

namespace Game
{
class Rules
{
public:
  Rules(int time_start, int time_end, int score_max);
  Rules() = default;

  Score score{1000000};
  Counter<int> time{0, 60};
};
} // namespace Game
