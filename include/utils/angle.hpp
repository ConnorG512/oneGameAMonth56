#pragma once 

#include <cmath>
#include <utility>
#include <concepts>

namespace Utils::Angle 
{
  template <typename T>
  requires std::floating_point<T>
  auto CaclulateAngleBetweenTwoObjects(const std::pair<T,T>& obj1, const std::pair<T,T>& obj2) -> T
  {
    return std::atan2(obj1.second - obj2.second, obj1.first - obj2.first);
  }
}
