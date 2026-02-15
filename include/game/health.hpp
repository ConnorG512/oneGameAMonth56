#pragma once

#include <cassert>

#include "utils/concepts.hpp"

namespace Game
{
template <Concepts::Number T> class HealthComponent
{
  T current_{100};
  T max_{100};

public:
  HealthComponent() = default;

  HealthComponent(T current, T max) : current_{current}, max_{max}
  {
    assert(current_ < max);
    assert(current_ >= 0);
  }

  enum class ModifyType
  {
    reduce,
    increase,
  };
  auto ModifyHealth(ModifyType type, Concepts::Number auto amount) noexcept   
  {
    if (type == ModifyType::reduce)
    {
      current_ -= amount;
      if (current_ < 0)
        current_ = 0;
    }
    else if (type == ModifyType::increase)
    {
      current_ += amount;
      if (current_ > max_)
        current_ = max_;
    }
    return current_;
  }

  [[nodiscard]] auto getCurrentHealth() const noexcept -> const T & { return current_; }

  [[nodiscard]] auto getMaxHealth() const noexcept -> const T & { return max_; }
};
} // namespace Game
