#include "file-output/binary/binary.hpp"

#include <cstring>
#include <filesystem>

File::Binary::Binary(const char *file_name)
  : file_{file_name,  std::ios::in | std::ios::out | std::ios::binary} 
{
  if(!file_.is_open())
  {
    file_.open(file_name, std::ios::out | std::ios::binary);
    writeToFile(magic_);
    
    file_.close();
    file_.open(file_name, std::ios::in | std::ios::out | std::ios::binary);
  }
}
auto File::Binary::writeToFile(const std::span<const uint8_t> bytes) noexcept -> void
{
  file_.write(reinterpret_cast<const char*>(bytes.data()), bytes.size());
}
    
auto File::Binary::isValidBinary() noexcept -> bool
{
  file_.seekg(0, std::ios::beg);
  
  std::array<std::uint8_t, 8> magic_from_file{};
  file_.read(reinterpret_cast<char*>(magic_from_file.data()), 8);
  
  if(std::memcmp(magic_from_file.data(), magic_.data(), magic_from_file.size()) == 0)
    return true;
  else 
    return false;
}
