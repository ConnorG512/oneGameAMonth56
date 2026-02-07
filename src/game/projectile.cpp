#include "game/projectile.hpp"
#include "utils/cast-get.hpp"
#include "lua/lua.hpp"

#include <array>

Game::Projectile::Projectile(LuaInstance &lua, SDL_Renderer &renderer)
    : bounds_{std::array{600.f,
                         600.f,
                         CastGetVar<float>(lua.GetLuaValue(std::array{"Projectile", "bounds_w"})),
                         CastGetVar<float>(lua.GetLuaValue(std::array{"Projectile", "bounds_h"}))}},
      texture_{renderer, CastGetVar<std::string>(lua.GetLuaValue(std::array{"Projectile", "sprite"})).c_str()}
{
}
