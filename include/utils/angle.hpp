#pragma once

#include <cmath>
#include <concepts>
#include <numbers>
#include <utility>

namespace Utils::Angle
{
template <typename T>
concept FloatingPoint = std::floating_point<T>;

template <FloatingPoint T> constexpr T texture_offset{90.0};

template <FloatingPoint T>
auto CaclulateAngleBetweenTwoObjectsRadians(const std::pair<T, T> &obj1, const std::pair<T, T> &obj2) -> T
{
  return std::atan2(obj1.second - obj2.second, obj1.first - obj2.first);
}

template <FloatingPoint T>
auto CaclulateAngleBetweenTwoObjectsDegree(const std::pair<T, T> &obj1, const std::pair<T, T> &obj2) -> T
{
  const auto radians{std::atan2(obj1.second - obj2.second, obj1.first - obj2.first)};
  return radians * (180 / std::numbers::pi_v<T>);
}

template <FloatingPoint T>
auto CalculateYDirection(T radians, T speed) -> T
{
  return std::sin(radians) * speed;
}

template <FloatingPoint T>
auto CalculateXDirection(T radians, T speed) -> T
{
  return std::cos(radians) * speed;
}

} // namespace Utils::Angle
