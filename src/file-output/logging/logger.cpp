#include "file-output/logging/logger.hpp"

#include <cassert>
#include <format>
#include <print>
#include <filesystem>

namespace 
{
  auto GetPrepend(File::Logger::LogType type) -> std::string_view
  {
    switch (type) 
    {
      case File::Logger::LogType::info:
          return "INFO:";
        break;
        case File::Logger::LogType::debug:
          return "DEBUG:";
        break;
        case File::Logger::LogType::error:
          return "ERROR:";
        break;
    }
    return "N/A:";
  }
}

File::Logger::Logger(const std::string& path, const std::string& file_name, bool active)
  : logfile_{std::format("{}/{}", path, file_name), std::ios::out | std::ios::trunc} 
  , active_{active}
{
  if(logfile_.is_open())
    writeToLog(LogType::info, "Log created.");
  else 
    std::println(stderr, "Failed to create log file!");
}

auto File::Logger::writeToLog(LogType type, const std::string& message) noexcept -> void
{
  if (!active_)
    return;

  std::println(logfile_, "{} {}", GetPrepend(type), message);
}
