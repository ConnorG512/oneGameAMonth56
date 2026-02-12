#pragma once

#include <cassert>
#include <random>
#include <type_traits>

namespace Utils::Rng
{
template <typename T>
concept RandVal = std::is_arithmetic_v<T> && !std::is_same_v<T, bool>;

class Rng
{
  std::random_device device_{};
  std::mt19937 generator_{device_()};

public:
  auto generate(RandVal auto min = 0, RandVal auto max = 100) -> auto
  {
    assert(min < max);

    if constexpr (std::is_floating_point_v<decltype(min)> && std::is_floating_point_v<decltype(max)>)
    {
      assert(min >= 0.0f && max <= 1.0f);
      std::uniform_real_distribution<decltype(min)> dist(min, max);
      return dist(generator_);
    }
    else
    {
      std::uniform_int_distribution<std::mt19937::result_type> dist(min, max);
      return dist(generator_);
    }
  }
};
} // namespace Utils::Rng
