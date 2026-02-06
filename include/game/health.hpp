#pragma once 

namespace Game 
{
  template <typename T>
  class HealthComponent 
  {
    T current_ {100};
    T max_ {100};
    

    public:
      

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
        }
        else if (type == ModifyType::increase)
        {
          current_ += amount;
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
