#include "game/enemy.hpp"
#include "lua/lua.hpp"
#include "file-output/logging/logger.hpp"
#include "utils/cast-get.hpp"
#include "sdl/window-renderer/renderer.hpp"

#include <array>
#include <string>

Game::Enemy::Enemy(LuaInstance &lua, SDL_Renderer &renderer)
  : bounds_{std::array{
    CastGetVar<float>(lua.GetLuaValue(std::array{"GameScript", "Enemy", "pos_x"})),
    CastGetVar<float>(lua.GetLuaValue(std::array{"GameScript", "Enemy", "pos_y"})),
    CastGetVar<float>(lua.GetLuaValue(std::array{"GameScript", "Enemy", "bounds_w"})),
    CastGetVar<float>(lua.GetLuaValue(std::array{"GameScript", "Enemy", "bounds_h"}))}}
  , texture_ {renderer, CastGetVar<std::string>(lua.GetLuaValue(std::array{"GameScript", "Enemy", "sprite"})).c_str()} {}
