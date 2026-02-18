#pragma once

#include "game/counter.hpp"

namespace SDL {class Audio;}

namespace Game
{
class Score
{
  Counter<int> count_{1000000};
  
  public:
    explicit Score(int max_score);
    Score() = default;
    
    auto increase(int amount, SDL::Audio &audio) noexcept -> int;
    auto cref() const noexcept -> const Counter<int>&; 
};
} // namespace Game
