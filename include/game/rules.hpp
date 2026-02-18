#pragma once

#include "game/counter.hpp"
#include "game/score.hpp"

namespace Game
{
class Rules
{
public:
  Rules(int time_max, int score_max);
  Rules() = default;

  Score score{1000000};
  Counter<int> time{180};
};
} // namespace Game
