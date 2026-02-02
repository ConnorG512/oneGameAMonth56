#include "logging/logger.hpp"

#include <cassert>
#include <format>
#include <print>

Logger::Logger(const std::string& path, const std::string& file_name, bool active)
  : logfile_{std::format("{}{}", path, file_name)} 
  , active_{active}
{
  std::println(stdout, "logfile active: {}.", active_);
  std::println(stdout, "Logfile created at location: [{}{}].", path, file_name);
}

auto Logger::writeToLog(LogType type, std::string& message) noexcept -> void
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
