#pragma once

#include <utility>

namespace SDL
{
class Mouse
{
  std::pair<float, float> xy_pos{0.0, 0.0};

public:
  auto GetCursorPosition() noexcept -> const std::pair<float, float> &;
};
} // namespace SDL
