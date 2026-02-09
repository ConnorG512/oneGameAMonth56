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

      auto isValidBinary() noexcept -> bool;

      template <typename T>
      auto writeSerialDataToFile(const T& serial_struct) noexcept -> void
      {
        file_.seekp(magic_.size(),  std::ios::beg);
        
        file_.write(reinterpret_cast<const char*>(&serial_struct), sizeof(serial_struct));
      }
  };
}
