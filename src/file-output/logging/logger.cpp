#include "file-output/logging/logger.hpp"

#include <cassert>
#include <format>
#include <print>

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
} // namespace

File::Logger::Logger(const std::string &file_name, std::function<bool()> use_debug_func)
    : logfile_{file_name, std::ios::out | std::ios::trunc}, log_debug_{use_debug_func()}
{
  writeToLog(File::Logger::LogType::info, std::format("Log file debug mode: {}", use_debug_func()));

  if (logfile_.is_open())
    writeToLog(LogType::info, "Log created.");
  else
    std::println(stderr, "Failed to create log file!");
}

auto File::Logger::writeToLog(LogType type, const std::string &message) noexcept -> void
{
  if (!log_debug_ && type == LogType::debug)
    return;

  std::println(logfile_, "{} {}", GetPrepend(type), message);
}
