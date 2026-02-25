#include "file-out/binary.hpp"

#include <cstdint>
#include <cstring>
#include <print>

File::Binary::Binary()
{
  if(!file_.is_open())
    std::println(stderr, "Failed to open game save!");
  file_.write(reinterpret_cast<const char*>(magic_.data()), magic_.size());
}

auto File::Binary::isValidBinary() noexcept -> bool
{
  file_.seekg(0, std::ios::beg);

  std::array<std::uint8_t, 8> magic_from_file{};
  file_.read(reinterpret_cast<char *>(magic_from_file.data()), 8);

  if (std::memcmp(magic_from_file.data(), magic_.data(), magic_from_file.size()) == 0)
    return true;
  else
    return false;
}
