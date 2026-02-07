#pragma once

#include <print>
#include <string>
#include <type_traits>
#include <variant>

template <typename Ret, typename T> auto CastGetVar(T &&vari) noexcept -> Ret
{
  return std::visit(
      [](auto &&v) -> Ret
      {
        if constexpr (std::is_same_v<std::decay_t<decltype(v)>, Ret>)
          return v;
        else if constexpr (std::is_arithmetic_v<std::decay_t<decltype(v)>> && std::is_arithmetic_v<Ret>)
          return static_cast<Ret>(v);
        else
        {
          std::println(stderr, "Error in passing value.");
          return {};
        }
      },
      std::forward<T>(vari));
}
