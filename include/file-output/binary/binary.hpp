#pragma once 

#include <fstream>
#include <array>
#include <cstdint>

namespace File 
{
  class Logger;

  class Binary 
  {
    const char* file_name_ {nullptr};
    std::fstream file_;
    
    public:
      constexpr Binary(const char* file_name, std::array<uint8_t, 8> magic, std::optional<File::Logger> &logger);
  };
}
