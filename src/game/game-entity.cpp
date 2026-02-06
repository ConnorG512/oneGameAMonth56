#include "game/game-entity.hpp"

#include <array>

Gameplay::GameEntity::GameEntity(
        const std::array<float,4>& xywh,
        SDL_Renderer& renderer,
        LuaInstance& lua_instance,
        const char* image_path
        )
  : bounds_{xywh.at(0), xywh.at(1), xywh.at(2), xywh.at(3)}
  , texture_{renderer, image_path} 
  , health_{
    static_cast<int>(std::get<double>(lua_instance.GetLuaValue(std::array{"GameScript", "Player", "starting_health"}))),
    static_cast<int>(std::get<double>(lua_instance.GetLuaValue(std::array{"GameScript", "Player", "max_health"})))} {}
