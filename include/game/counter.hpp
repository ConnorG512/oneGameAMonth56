#pragma once

#include "utils/concepts.hpp"

#include <limits>

namespace Game
{
template <Concepts::Number T> class Counter
{
  T current_{0};
  T max_{std::numeric_limits<T>::max()};

public:
  // Constructors:
  Counter(Concepts::Number auto current, Concepts::Number auto max) : current_{current}, max_{max} {}
  Counter() = default;

  // Methods:
  [[maybe_unused]] auto increase(Concepts::Number auto amount) noexcept
  {
    current_ += amount;
    if (current_ > max_)
      current_ = max_;

    return current_;
  }

  [[maybe_unused]] auto decrease(Concepts::Number auto amount) noexcept
  {
    current_ -= amount;
    if (current_ < 0)
      current_ = 0;

    return current_;
  }

  [[maybe_unused]] auto setTo(Concepts::Number auto num) noexcept
  {
    current_ = num;
    if (current_ > max_)
      current_ = max_;
    else if (current_ < 0)
      current_ = 0;

    return current_;
  }
  
  enum class ResetFrom
  {
    zero,
    max,
  };
  auto reset(ResetFrom position) noexcept -> void 
  {
    if(position == ResetFrom::zero)
      current_ = 0;
    else
      current_ = max_;
  }

  // Getters:
  [[nodiscard]] auto getCurrent() const noexcept -> T { return current_; }

  [[nodiscard]] auto getMax() const noexcept -> T { return max_; }

  [[nodiscard]] auto getBoth() const noexcept -> T { return {current_, max_}; }

  [[nodiscard]] auto isZero() const noexcept -> bool { return current_ <= 0;}
};
} // namespace Game
