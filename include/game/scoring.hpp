#pragma once 

#include <concepts>
#include <limits>

namespace Game 
{
  template <typename T>
  requires std::integral<T> && (!std::same_as<T, bool>)
  class Score 
  {
    T current_score_ {0};
    T high_score_ {0};
    T score_multiplier_ {1};
    T max_score_ {std::numeric_limits<T>::max()};
    
    public:
      Score(T score_multiplier = 1, T max_score = std::numeric_limits<T>::max())
        : score_multiplier_{score_multiplier}
        , max_score_{max_score} {}
      
      auto increaseScore(T amount)
      {
        current_score_ += amount;
        if (current_score_ >= max_score_)
          current_score_ = max_score_;
        if (current_score_ > high_score_)
          high_score_ = current_score_;
      }

      auto setMultiplier(T value) -> T 
      {
        score_multiplier_ += value;
      }

      auto getCurrentScore() noexcept -> T 
      {
        return current_score_;
      }

      auto getHighScore() noexcept -> T 
      {
        return high_score_;
      }
  };
}
