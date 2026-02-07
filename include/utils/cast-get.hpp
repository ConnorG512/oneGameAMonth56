#pragma once 

#include <variant>
#include <type_traits>

template<typename Ret, typename T>
auto CastGetVar(T&& vari) noexcept -> Ret
{
  const auto visit_result {std::visit([](auto&& v) -> Ret {
        if constexpr (std::is_floating_point_v<std::decay_t<decltype(v)>>)
          return static_cast<Ret>(v);
        else 
          return static_cast<Ret>(0);
      }, vari)};

  return visit_result;
}

