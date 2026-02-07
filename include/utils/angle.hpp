#pragma once

#include <cmath>
#include <concepts>
#include <numbers>
#include <utility>

namespace Utils::Angle
{
template <typename T>
  requires std::floating_point<T>
constexpr T texture_offset{90.0};

template <typename T>
  requires std::floating_point<T>
auto CaclulateAngleBetweenTwoObjects(const std::pair<T, T> &obj1, const std::pair<T, T> &obj2) -> T
{
  return std::atan2(obj1.second - obj2.second, obj1.first - obj2.first);
}

template <typename T>
  requires std::floating_point<T>
auto CaclulateAngleBetweenTwoObjectsDegree(const std::pair<T, T> &obj1, const std::pair<T, T> &obj2) -> T
{
  const auto radians{std::atan2(obj1.second - obj2.second, obj1.first - obj2.first)};
  return radians * (180 / std::numbers::pi_v<T>);
}
} // namespace Utils::Angle
