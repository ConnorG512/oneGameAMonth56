#pragma once 

#include <variant>
#include <type_traits>
#include <string>

template<typename Ret, typename T>
auto CastGetVar(T&& vari) noexcept -> Ret
{
  return {std::visit([](auto&& v) -> Ret {
        if constexpr (std::is_same_v<std::decay_t<decltype(v)>, bool>)
          return v;
        else if constexpr (std::is_same_v<std::decay_t<decltype(v)>, std::string>)
          return v;
        else if constexpr (std::is_floating_point_v<std::decay_t<decltype(v)>>)
          return static_cast<Ret>(v);
        else 
          return {}; 
      }, vari)};
}

