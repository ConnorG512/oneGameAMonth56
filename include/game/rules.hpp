#pragma once

#include "game/counter.hpp"
#include "game/score.hpp"

namespace Game
{
class Rules
{
public:
  Rules(int time_max);
  Rules() = default;

  Score score{};
  Counter<int> time{180};
};
} // namespace Game
