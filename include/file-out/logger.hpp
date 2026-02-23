#pragma once

#include <fstream>
#include <string>

namespace File
{
class Logger
{
  std::fstream logfile_{"debug.log", std::ios::out | std::ios::trunc};
  bool is_debug_{true};

public:
  Logger(const std::string &file_name, bool use_debug);
  Logger() = default;

  enum class LogType
  {
    info,
    debug,
    error,
  };
  auto writeToLog(LogType type, const std::string &message) noexcept -> void;

  auto writeAddress(std::string_view name, const auto &object) -> void
  {
    std::println(logfile_, "MEM: Object {} written to address: [{}].", name, static_cast<const void *>(&object));
  }
};
} // namespace File
