#include "game/enemy.hpp"
#include "lua/lua.hpp"
#include "utils/cast-get.hpp"

#include <array>
#include <string>

Game::Enemy::Enemy(LuaInstance &lua, SDL_Renderer &renderer)
    : bounds_{std::array{CastGetVar<float>(lua.GetLuaValue(std::array{"EnemyValues", "pos_x"})),
                         CastGetVar<float>(lua.GetLuaValue(std::array{"EnemyValues", "pos_y"})),
                         CastGetVar<float>(lua.GetLuaValue(std::array{"EnemyValues", "bounds_w"})),
                         CastGetVar<float>(lua.GetLuaValue(std::array{"EnemyValues", "bounds_h"}))}},
      texture_{renderer, CastGetVar<std::string>(lua.GetLuaValue(std::array{"EnemyValues", "sprite"})).c_str()}
{
}

Game::Enemy::Enemy(float x, float y, LuaInstance &lua, SDL_Renderer &renderer)
    : bounds_{x, y, CastGetVar<float>(lua.GetLuaValue(std::array{"EnemyValues", "bounds_w"})),
              CastGetVar<float>(lua.GetLuaValue(std::array{"EnemyValues", "bounds_h"}))},
      texture_{renderer, CastGetVar<std::string>(lua.GetLuaValue(std::array{"EnemyValues", "sprite"})).c_str()}
{
}
