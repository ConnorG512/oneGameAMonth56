#pragma once

#include "game/counter.hpp"

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

  auto increase(int amount, Audio::Instance &audio) noexcept -> int;
  auto reset() -> void;
  auto cref() const noexcept -> const Counter<int> &;
};
} // namespace Game
