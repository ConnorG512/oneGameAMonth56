#include "file-output/binary/binary.hpp"
#include "file-output/logging/logger.hpp"

#include <format>
#include <cstdlib>
#include <filesystem>
#include <optional>

File::Binary::Binary(const char* file_name, std::array<uint8_t, 8> magic, std::optional<std::reference_wrapper<File::Logger>> logger)
  : file_{std::format("{}/{}", std::getenv("PWD"), file_name), std::ios::out} 
{
  if(!std::filesystem::exists(std::format("{}/{}", std::getenv("PWD"), file_name)) && 
      logger.has_value())
    logger.value().get().writeToLog(File::Logger::LogType::error, "Path for binary file does not exist!");

  if(file_.is_open())
    file_.write(reinterpret_cast<const char*>(magic.data()), magic.size());
  else if (logger.has_value())
    logger.value().get().writeToLog(File::Logger::LogType::debug, "Binary file not open!");
}
