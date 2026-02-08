#pragma once 

#include <vector>
#include <cstdint>
#include <memory>
#include <functional>
#include <ranges>
#include <utility>

class LuaInstance;
class SDL_Renderer;

namespace Game {
template <typename T>
class Spawner 
{
  std::vector<std::unique_ptr<T>> spawn_slots_{};
  
  auto CreateSpawner(std::function<std::uint32_t()> slot_func) -> 
    std::vector<std::unique_ptr<T>>
  {
    const auto slot_size = (slot_func) ? slot_func() : 5;
    std::vector<std::unique_ptr<T>> spawn_slots (slot_size);

    return spawn_slots;
  }

  public:    
    Spawner(std::function<std::uint32_t()> slot_func)
      : spawn_slots_{CreateSpawner(slot_func)} {}

    auto spawnProjectile(const std::pair<float, float> &xy, LuaInstance &lua, SDL_Renderer &renderer) -> void 
    {
      for(auto& slot : spawn_slots_)
      {
        if(slot == nullptr)
        {
          slot = std::make_unique<T>(xy, lua, renderer);
          break;
        }
      }
    }
};
}
