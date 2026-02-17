#pragma once

#include "game/counter.hpp"

namespace SDL {class Audio;}

namespace Game
{
class Score
{
  Counter<int> count{1000000};
  
  public:
    auto increase(int amount, SDL::Audio &audio) noexcept -> int;
    auto cref() const noexcept -> const Counter<int>&; 
};
} // namespace Game
