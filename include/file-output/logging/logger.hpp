#pragma once 

#include <fstream>
#include <string>

namespace File 
{
class Logger 
{
  std::fstream logfile_{"./debug.log", std::ios::out | std::ios::trunc};
  bool active_ {true};

  public:
    Logger(const std::string& path, const std::string& file_name = "debug.log", bool active = false);

    enum class LogType 
    {
      info, 
      debug, 
      error,
    };
    auto writeToLog(LogType type, const std::string& message) noexcept -> void;
};
}
