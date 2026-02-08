#pragma once

#include <array>
#include <cstdint>
#include <functional>
#include <fstream>
#include <span>

namespace File 
{
  class Binary 
  {
    std::fstream file_{"./default.bin", std::ios::out | std::ios::binary};
    std::array<std::uint8_t, 8> magic_ {'C','G','E','B','I','N', 0x00};

    public:
      Binary(const char* file_name);

      auto writeToFile(const std::span<const uint8_t> bytes) noexcept -> void;
      auto isValidBinary() noexcept -> bool;
  };
}
