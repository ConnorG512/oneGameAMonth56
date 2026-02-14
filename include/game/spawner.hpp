#pragma once

#include "sdl/rectangle.hpp"
#include <concepts>
#include <cstdint>
#include <functional>
#include <memory>
#include <ranges>
#include <utility>
#include <vector>

class LuaInstance;
class SDL_Renderer;

namespace Game
{

// Concpets
template <typename T>
concept HasCollisionObject = requires(T &t) {
  { t.bounds_ } -> std::same_as<SDL::Rectangle &>;
};

template <typename T>
concept Destroyable = requires(T &t) {
  { t.isReadyToBeDestroyed() } -> std::convertible_to<bool>;
};

template <typename T>
concept Spawnable = HasCollisionObject<T> || Destroyable<T>;
//

template <Spawnable T> class Spawner
{
  std::vector<std::unique_ptr<T>> spawn_slots_{};

  auto CreateSpawner(std::function<std::uint32_t()> slot_func) -> std::vector<std::unique_ptr<T>>
  {
    const auto slot_size = (slot_func) ? slot_func() : 5;
    std::vector<std::unique_ptr<T>> spawn_slots(slot_size);

    return spawn_slots;
  }

public:
  Spawner(std::function<std::uint32_t()> slot_func) : spawn_slots_{CreateSpawner(slot_func)} {}

  auto spawnProjectile(const std::pair<int, int> &screen_bounds, const std::pair<float, float> &xy, LuaInstance &lua,
                       SDL_Renderer &renderer) -> void
  {
    for (auto &slot : spawn_slots_)
    {
      if (slot == nullptr)
      {
        slot = std::make_unique<T>(screen_bounds, xy, lua, renderer);
        break;
      }
    }
  }
  
  auto clearSlot(const auto& collider) -> void
    requires HasCollisionObject<T>
  {
    for (auto &slot : spawn_slots_ | std::views::filter([](auto &slot) { return slot != nullptr; }))
    {
      if (slot->bounds_.checkCollision(collider.cref()))
        slot.reset();
    }
  }
  
  auto clearSlot() -> void
    requires Destroyable<T>
  {
    for (auto &slot : spawn_slots_ | std::views::filter([](auto &slot) { return slot != nullptr; }))
    {
      if(slot->isReadyToBeDestroyed())
        slot.reset();
    }
  }

  auto ref() noexcept -> auto
  {
    return spawn_slots_ | std::views::filter([](const auto &slot) { return slot != nullptr; }) |
           std::views::transform([](auto &slot) -> T & { return *slot; });
  }

  auto cref() const noexcept -> auto
  {
    return spawn_slots_ | std::views::filter([](const auto &slot) { return slot != nullptr; }) |
           std::views::transform([](auto &slot) -> T & { return *slot; });
  }
};
} // namespace Game
