#pragma once

#include <fstream>
#include <string>

namespace File
{
class Logger
{
  std::fstream logfile_{"debug.log", std::ios::out | std::ios::trunc};
  bool log_debug_{true};

public:
  Logger(const std::string &file_name = "debug.log", bool active = false);

  enum class LogType
  {
    info,
    debug,
    error,
  };
  auto writeToLog(LogType type, const std::string &message) noexcept -> void;

  template <typename T> auto writeAddress(std::string_view name, T &object) -> void
  {
    std::println(logfile_, "MEM: Object {} written to address: [{}].",  name, static_cast<void *>(&object));
  }
};
} // namespace File
