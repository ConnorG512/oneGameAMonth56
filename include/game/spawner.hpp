#pragma once

#include "game/player.hpp"
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
  Spawner(std::function<std::uint32_t()> slot_func = nullptr) : spawn_slots_{CreateSpawner(slot_func)} {}

  // Different objects that utilise the spawner may have difference constructors so a variadic template
  // will allow for more generic construction.
  template <typename... Args> auto spawn(Args &&...args) -> void
  {
    for (auto &slot : spawn_slots_)
    {
      if (slot == nullptr)
      {
        slot = std::make_unique<T>(std::forward<Args>(args)...);
        break;
      }
    }
  }

  auto clearSlot(const auto &collider) -> bool
    requires HasCollisionObject<T>
  {
    for (auto &slot : spawn_slots_ | std::views::filter([](auto &slot) { return slot != nullptr; }))
    {
      if (slot->bounds_.checkCollision(collider.bounds_.cref()))
      {
        slot.reset();
        return true;
      }
    }
    return false;
  }

  auto clearSlot() -> void
    requires Destroyable<T>
  {
    for (auto &slot : spawn_slots_ | std::views::filter([](auto &slot) { return slot != nullptr; }))
    {
      if (slot->isReadyToBeDestroyed())
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
