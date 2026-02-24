#pragma once

#include "game/counter.hpp"

#include <utility>

namespace Audio
{
class Instance;
}

namespace Game
{
class UI;
class Score
{
  Counter<int> count_{0, 1000000};

public:
  explicit Score(int max_score);
  Score() = default;

  enum class ScoreType 
  {
    bonus,
    standard,
  };
  auto increase(int amount, int multiplier = 1) noexcept -> std::pair<int, ScoreType>;
  auto reset() -> void;
  auto cref() const noexcept -> const Counter<int> &;
};
} // namespace Game
