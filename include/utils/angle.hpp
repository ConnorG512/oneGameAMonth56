#pragma once

#include <cmath>
#include <concepts>
#include <numbers>
#include <utility>

namespace Utils::Angle
{
template <typename T>
concept Number = std::integral<T> && !std::same_as<T, bool>;

template <Number T> constexpr T texture_offset{90.0};

template <Number T>
auto CaclulateAngleBetweenTwoObjectsRadians(const std::pair<T, T> &obj1, const std::pair<T, T> &obj2) -> T
{
  return std::atan2(obj1.second - obj2.second, obj1.first - obj2.first);
}

template <Number T>
auto CaclulateAngleBetweenTwoObjectsDegree(const std::pair<T, T> &obj1, const std::pair<T, T> &obj2) -> T
{
  const auto radians{std::atan2(obj1.second - obj2.second, obj1.first - obj2.first)};
  return radians * (180 / std::numbers::pi_v<T>);
}

} // namespace Utils::Angle
