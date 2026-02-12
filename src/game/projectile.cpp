#include "game/projectile.hpp"
#include "lua/lua.hpp"
#include "utils/cast-get.hpp"

#include <array>
#include <utility>

Game::Projectile::Projectile(std::pair<int, int> screen_max_xy, std::pair<float, float> xy, LuaInstance &lua,
                             SDL_Renderer &renderer)
    : screen_max_xy_{screen_max_xy},
      bounds_{std::array{xy.first, xy.second, CastGetVar<float>(lua.GetLuaValue(std::array{"Projectile", "bounds_w"})),
                         CastGetVar<float>(lua.GetLuaValue(std::array{"Projectile", "bounds_h"}))}},
      texture_{renderer, CastGetVar<std::string>(lua.GetLuaValue(std::array{"Projectile", "sprite"})).c_str()}
{
}

auto Game::Projectile::isReadyToBeDestroyed() -> bool
{
  auto [screen_width, screen_height] = screen_max_xy_;
  if (bounds_.cref().y > screen_height || bounds_.ref().x > screen_width)
  {
    return true;
  }
  else if (bounds_.cref().y < 0 || bounds_.ref().x < 0)
  {
    return true;
  }

  return false;
}
