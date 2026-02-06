#pragma once 

#include <concepts>

namespace Gameplay
{
  template <typename T>
  requires std::floating_point<T> || std::integral<T>
  class HealthComponent 
  {
    T current_ {100};
    T max_ {100};

    public:
      
      HealthComponent() = default;

      HealthComponent(T current, T max)
        : current_{current}
        , max_{max} 
        {
          assert(current_ < max);
          assert(current_ >= 0);
        }

      
      enum class ModifyType
      {
        reduce,
        increase,
      };
      auto ModifyHealth(ModifyType type, T amount) noexcept -> T 
      {
        if(type == ModifyType::reduce)
        {
          current_ -= amount;
          if (current_ < 0)
            current_ = 0;
        }
        else if (type == ModifyType::increase)
        {
          current_ += amount;
          if (current_ > max_)
            current_ = max_;
        }
        return current_;
      }


      [[nodiscard]] auto getCurrentHealth() const noexcept -> const T& 
      {
        return current_;
      }
      
      [[nodiscard]] auto getMaxHealth() const noexcept -> const T& 
      {
        return max_;
      }
  };
}
