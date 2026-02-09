#include "game/projectile.hpp"
#include "lua/lua.hpp"
#include "utils/cast-get.hpp"

#include <array>

Game::Projectile::Projectile(std::pair<float, float> xy, LuaInstance &lua, SDL_Renderer &renderer)
    : bounds_{std::array{xy.first, xy.second, CastGetVar<float>(lua.GetLuaValue(std::array{"Projectile", "bounds_w"})),
                         CastGetVar<float>(lua.GetLuaValue(std::array{"Projectile", "bounds_h"}))}},
      texture_{renderer, CastGetVar<std::string>(lua.GetLuaValue(std::array{"Projectile", "sprite"})).c_str()}
{
}
