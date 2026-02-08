#pragma once 

#include <array>

namespace Game {
template <typename T>
struct Serialize 
{
  T high_score{};
  T times_played{};
};
}
