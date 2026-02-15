#pragma once

#include <SDL3/SDL_rect.h>
#include <array>
#include <span>
#include <utility>

namespace SDL
{
class Rectangle
{
  // https://wiki.libsdl.org/SDL3/SDL_FRect
  SDL_FRect rect_{0.0, 0.0, 32.0, 32.0};

  float x_vel_{0.0f};
  float y_vel_{0.0f};

public:
  Rectangle(float x = 0.0, float y = 0.0, float w = 32.0, float h = 32.0, float vel_x = 0.0f, float vel_y = 0.0f);
  Rectangle(std::pair<float, float> xy, std::pair<float, float> wh);
  Rectangle(std::array<float, 4> xywh);

  enum class Direction
  {
    positive,
    negative,
  };
  auto move(Direction dir, float x, float y) noexcept -> void;
  auto move(float x_vel, float y_vel) noexcept -> void;

  auto checkCollision(const std::span<const SDL_FRect> other_bounds) noexcept -> bool;
  auto checkCollision(const SDL_FRect &other_bound) noexcept -> bool;

  auto cref() const noexcept -> const SDL_FRect &;
  auto ref() noexcept -> SDL_FRect &;
};
} // namespace SDL
