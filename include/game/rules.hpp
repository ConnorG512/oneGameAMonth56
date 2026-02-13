#pragma once

#include "game/counter.hpp"

namespace Game
{
class Rules
{
public:
  Rules(int score_max, int time_max);
  Rules() = default;

  Counter<int> score{1000000};
  Counter<int> time{180};
};
} // namespace Game
