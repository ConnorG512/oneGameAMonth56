#pragma once 

#include "utils/concepts.hpp"

template <Concepts::Number T>
class Counter 
{
  T current_ {0};
  T max_ {0};

  public:
    Counter(Concepts::Number auto current, Concepts::Number auto max)
      : current_{current}
      , max_{max} {}

    [[maybe_unused]] auto increase(Concepts::Number auto amount) -> T 
    {
      current_ += amount; 
      if (current_ > max_)
        current_ = max_;
    }
    
    [[maybe_unused]] auto decrease(Concepts::Number auto amount) -> T 
    {
      current_ -= amount; 
      if (current_ < 0)
        current_ = 0;
    }

    [[maybe_unused]] auto setTo(Concepts::Number auto num) -> T
    {
      current_ = num;
      if(current_ > max_)
        current_ = max_;
      else if (current_ < 0)
        current_ = 0;
    }

    auto reset() -> void 
    {
      current_ = 0;
    }
};
