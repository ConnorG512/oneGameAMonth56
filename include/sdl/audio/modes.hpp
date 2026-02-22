#pragma once

#include <cmath>
#include <concepts>
#include <numbers>
#include <ranges>
#include <vector>

namespace Audio::Modes
{
template <std::floating_point T>
auto basicSine(T frequency, T sample_rate, std::integral auto count, T amplitude = 0.03f)
{
  std::vector<T> buffer(count);

  for (const auto &[index, sample] : buffer | std::views::enumerate)
  {
    T time = static_cast<T>(index / sample_rate);

    sample = amplitude * std::sin(2.0f * std::numbers::pi_v<T> * frequency * time);
  }

  return buffer;
}
} // namespace Audio::Modes
