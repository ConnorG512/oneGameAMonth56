#include "logging/logger.hpp"

#include <cassert>
#include <format>
#include <print>
#include <filesystem>

Logger::Logger(const std::string& path, const std::string& file_name, bool active)
  : logfile_{std::format("{}/{}", path, file_name), std::ios::out | std::ios::trunc} 
  , active_{active}
{
  if(logfile_.is_open())
    writeToLog(LogType::info, "Log created.");
  else 
    std::println(stderr, "Failed to create log file!");
}

auto Logger::writeToLog(LogType type, const std::string& message) noexcept -> void
{
  if (!active_)
    return;

  const char * prepend {nullptr};
  
  switch (type) 
  {
      case LogType::info:
        prepend = "INFO:";
      break;
      case LogType::debug:
        prepend = "DEBUG:";
      break;
      case LogType::error:
        prepend = "ERROR:";
      break;
  }

  assert(prepend != nullptr);
  std::println(logfile_, "{} {}", prepend, message);
}
