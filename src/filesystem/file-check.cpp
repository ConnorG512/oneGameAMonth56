#include "filesystem/file-check.hpp"

#include <ranges>
#include <filesystem>
#include <stdexcept>
#include <format>

auto File::validateFiles(const std::span<const char* const> required_files) -> void
{
  for(const auto& [index, path] : required_files | std::views::enumerate)
  {
    if(!std::filesystem::exists(path))
    {
      throw std::runtime_error(std::format("Failed to find file {}:{}", index, path));
    }
  }
}
