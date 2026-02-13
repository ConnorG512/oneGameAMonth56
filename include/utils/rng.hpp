#pragma once

#include "concepts.hpp"

#include <cassert>
#include <random>

namespace Utils::Rng
{

class Rng
{
  std::random_device device_{};
  std::mt19937 generator_{device_()};

public:
  auto generate(Concepts::Number auto min = 0, Concepts::Number auto max = 100) -> auto
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
