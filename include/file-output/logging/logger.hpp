#pragma once

#include <fstream>
#include <string>
#include <functional>

namespace File
{
class Logger
{
  std::fstream logfile_{"debug.log", std::ios::out | std::ios::trunc};
  bool log_debug_{true};

public:
  Logger(const std::string &file_name, std::function<bool()> use_debug_func);
  Logger() = default;

  enum class LogType
  {
    info,
    debug,
    error,
  };
  auto writeToLog(LogType type, const std::string &message) noexcept -> void;

  auto writeAddress(std::string_view name, auto &object) -> void
  {
    std::println(logfile_, "MEM: Object {} written to address: [{}].", name, static_cast<void *>(&object));
  }
};
} // namespace File
