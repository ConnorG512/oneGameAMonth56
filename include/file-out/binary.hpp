#pragma once

#include <array>
#include <cstdint>
#include <fstream>

namespace File
{
class Binary
{
  std::fstream file_;
  std::array<std::uint8_t, 8> magic_{'C', 'G', 'E', 'B', 'I', 'N', 0x00, 0x00};

public:
  Binary();
  auto isValidBinary() noexcept -> bool;

  template <typename T> auto writeSerialDataToFile(std::span<const T> data) noexcept -> void
  {
    file_.seekp(magic_.size(), std::ios::beg);

    file_.write(reinterpret_cast<const char *>(data.data()), data.size());
  }

  template <typename T> auto readSerialDataFromFile() -> T
  {
    T loaded_data{};

    file_.seekg(magic_.size(), std::ios::beg);
    file_.read(reinterpret_cast<char *>(&loaded_data), sizeof(T));
    return loaded_data;
  }
};
} // namespace File
