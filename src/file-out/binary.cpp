#include "file-out/binary.hpp"

#include <cstdint>
#include <cstring>

File::Binary::Binary()
{
  
  // file will not be created if it does not already exist.
  file_.open("game.sav", std::ios::in | std::ios::out | std::ios::binary);
  
  // Workaround to create file.
  if(!file_.is_open())
  {
    file_.clear();

    std::ofstream new_file("game.sav");
    new_file.close();
    
    file_.open("game.sav", std::ios::in | std::ios::out | std::ios::binary);
    file_.write(reinterpret_cast<const char*>(magic_.data()), magic_.size());
  }
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
