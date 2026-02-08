#pragma once 

#include <array>

namespace Game {
template <typename T>
struct Serialize 
{
  std::array<char, 32> player_name {"Player"};
  T high_score{};
  T times_played{};
};
}
