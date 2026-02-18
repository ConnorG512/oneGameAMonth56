#pragma once

#include "game/counter.hpp"

namespace SDL {class Audio;}

namespace Game
{
class Score
{
  explicit Score(int max_score);
  Counter<int> count_{1000000};
  
  public:
    auto increase(int amount, SDL::Audio &audio) noexcept -> int;
    auto cref() const noexcept -> const Counter<int>&; 
};
} // namespace Game
