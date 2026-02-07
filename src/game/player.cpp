#include "game/player.hpp"
#include "lua/lua.hpp"
#include "file-output/logging/logger.hpp"
#include "utils/cast-get.hpp"
#include "sdl/window-renderer/renderer.hpp"

#include <array>
#include <string>

Game::Player::Player(LuaInstance &lua, SDL_Renderer &renderer)
  : bounds_{std::array{
    CastGetVar<float>(lua.GetLuaValue(std::array{"GameScript", "Player", "pos_x"})),
    CastGetVar<float>(lua.GetLuaValue(std::array{"GameScript", "Player", "pos_y"})),
    CastGetVar<float>(lua.GetLuaValue(std::array{"GameScript", "Player", "bounds_w"})),
    CastGetVar<float>(lua.GetLuaValue(std::array{"GameScript", "Player", "bounds_h"}))}}
  , texture_ {renderer, CastGetVar<std::string>(lua.GetLuaValue(std::array{"GameScript", "Player", "sprite"})).c_str()} {}
