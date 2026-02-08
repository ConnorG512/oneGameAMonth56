#include "file-output/binary/binary.hpp"

File::Binary::Binary(const char *file_name)
  : file_{file_name} 
{
  if(!file_.is_open())
    return;
  
  writeToFile(magic_);
}

auto File::Binary::writeToFile(const std::span<const uint8_t> bytes) noexcept -> void
{
  file_.write(reinterpret_cast<const char*>(bytes.data()), bytes.size());
}
