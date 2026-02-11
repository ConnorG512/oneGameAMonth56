#include "file-output/binary/binary.hpp"
#include "file-output/logging/logger.hpp"
#include "filesystem/file-check.hpp"
#include "game/enemy.hpp"
#include "game/player.hpp"
#include "game/projectile.hpp"
#include "game/save-object.hpp"
#include "game/scoring.hpp"
#include "game/spawner.hpp"
#include "lua/lua.hpp"
#include "sdl/event-handler.hpp"
#include "sdl/image/texture.hpp"
#include "sdl/init.hpp"
#include "sdl/input/mouse.hpp"
#include "sdl/text/text.hpp"
#include "sdl/window-renderer/window-renderer.hpp"
#include "utils/angle.hpp"
#include "utils/cast-get.hpp"

#include <SDL3/SDL_error.h>
#include <SDL3/SDL_rect.h>
#include <SDL3/SDL_render.h>
#include <SDL3/SDL_surface.h>
#include <SDL3_ttf/SDL_ttf.h>
#include <array>
#include <complex>

auto main() -> int
{
  File::validateFiles(File::lua_files);
  LuaInstance lua_instance{};
  lua_instance.execFiles(File::lua_files);

  File::Logger log{
      "debug.log", [&lua_instance]
      { return CastGetVar<bool>(lua_instance.GetLuaValue(std::array{"AppConfiguration", "Logger", "enable"})); }};

  File::Binary save_file{"game.sav"};
  Game::Serialize file_data{save_file.readSerialDataFromFile<Game::Serialize>()};

  SDL::Init init{};

  SDL::EventHandler event_handler{log};
  SDL::WindowRenderer display{
      "Game window",
      {std::get<double>(lua_instance.GetLuaValue(std::array{"AppConfiguration", "Display", "Resolution", "x"})),
       std::get<double>(lua_instance.GetLuaValue(std::array{"AppConfiguration", "Display", "Resolution", "y"}))}};

  SDL::Text score_text{32, {20, 20, 100, 20}, "Player", 6, display.game_renderer.ref()};

  SDL::Mouse mouse{};

  Game::Score<int> current_score{};
  Game::Player player{lua_instance, display.game_renderer.ref()};
  Game::Enemy enemy{lua_instance, display.game_renderer.ref()};
  Game::Spawner<Game::Projectile> proj_spawner{[&lua_instance]()
                                               {
                                                 return CastGetVar<int>(lua_instance.GetLuaValue(
                                                     std::array{"GameRules", "ProjectileSpawner", "max_spawn_slots"}));
                                               }};

  // Game loop
  while (event_handler.isGameRunning())
  {
    const auto mouse_xy{mouse.GetCursorPosition()};
    const auto mouse_radian{Utils::Angle::CaclulateAngleBetweenTwoObjectsRadians(
        mouse_xy, {player.bounds_.cref().x, player.bounds_.cref().y})};

    event_handler.PollEvent([&] { proj_spawner.spawnProjectile(mouse_xy, lua_instance, display.game_renderer.ref()); });

    // Rendering
    display.game_renderer.clearScreen();
    display.game_renderer.drawColorFloat(0, 0, 0);

    display.game_renderer.renderTextureRotate(player.texture_.ref(), nullptr, &player.bounds_.ref(),
                                              Utils::Angle::CaclulateAngleBetweenTwoObjectsDegree(
                                                  mouse_xy, {player.bounds_.cref().x, player.bounds_.cref().y}) +
                                                  Utils::Angle::texture_offset<double>,
                                              nullptr, SDL_FLIP_NONE);
    display.game_renderer.renderTexture(enemy.texture_.ref(), nullptr, &enemy.bounds_.ref());

    // Spawned Projectile Render:
    for (auto &projectile : proj_spawner.ref())
    {
      projectile.destroy(display.game_window.WindowSize());
      projectile.bounds_.move(Utils::Angle::CalculateXDirection(mouse_radian, 0.04f),
                              Utils::Angle::CalculateYDirection(mouse_radian, 0.04f));
      display.game_renderer.renderTexture(projectile.texture_.ref(), nullptr, &projectile.bounds_.ref());
    }

    display.game_renderer.renderTexture(score_text.texture.ref(), nullptr, &score_text.rectangle.ref());
    display.game_renderer.present();
  }

  file_data.high_score = current_score.getHighScore();
  file_data.times_played += 1;
  save_file.writeSerialDataToFile(file_data);

  return 0;
}
