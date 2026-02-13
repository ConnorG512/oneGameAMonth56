#pragma once 

#include <type_traits>

namespace Concepts 
{
  template <typename T>
  concept Number = std::is_arithmetic_v<T> && !std::is_same_v<T, bool>;
}
