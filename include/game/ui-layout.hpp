#pragma once

#include "utils/concepts.hpp"
#include <utility>

namespace UI
{

template <Concepts::Number T> struct Layout
{
  consteval Layout() = default;

  std::pair<T, T> name_xy{20, 20};
  std::pair<T, T> score_xy{20, 60};
  std::pair<T, T> high_score_xy{20, 100};
  std::pair<T, T> times_played_xy{20, 140};
};
} // namespace UI
