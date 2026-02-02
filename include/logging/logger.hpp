#pragma once 

#include <fstream>
#include <string>

class Logger 
{
  std::fstream logfile_{"debug.log"};
  bool active_ {true}

  public:
    Logger(const std::string& path, const std::string& file_name = "debug.log", bool active = false);

    enum class LogType 
    {
      info, 
      debug, 
      error,
    };
    auto writeToLog(LogType type, std::string& message) noexcept -> void;
};
