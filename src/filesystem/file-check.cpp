#include "filesystem/file-check.hpp"

#include <filesystem>
#include <format>
#include <ranges>
#include <stdexcept>

auto File::validateFiles(const std::span<const char *const> required_files) -> void
{
  for (const auto &[index, path] : required_files | std::views::enumerate)
  {
    if (!std::filesystem::exists(path))
    {
      throw std::runtime_error(std::format("Failed to find file {}:{}", index, path));
    }
  }
}
