#include "file-out/binary.hpp"

#include <cstring>
#include <string_view>

namespace 
{
  auto createNewFile(std::fstream& file, std::span<uint8_t, 8> magic, std::string_view file_name)
  {
    if (!file.is_open())
    {
      file.open(file_name.data(), std::ios::out | std::ios::binary);

      file.write(reinterpret_cast<const char *>(magic.data()), magic.size());

      file.close();
      file.open(file_name.data(), std::ios::in | std::ios::out | std::ios::binary);
    }
  }
}

File::Binary::Binary(const std::string& file_name) : file_{file_name, std::ios::in | std::ios::out | std::ios::binary}
{
  createNewFile(file_, magic_, file_name);
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
