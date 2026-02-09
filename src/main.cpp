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
#include "sdl/window-renderer/window-renderer.hpp"
#include "utils/angle.hpp"
#include "utils/cast-get.hpp"

#include <SDL3/SDL_error.h>
#include <SDL3/SDL_rect.h>
#include <SDL3/SDL_render.h>
#include <SDL3/SDL_surface.h>
#include <array>
#include <format>
#include <SDL3_ttf/SDL_ttf.h>
#include <print>

auto main() -> int
{
  File::Logger log{std::getenv("PWD"), "/debug.log", true};

  File::validateFiles(File::lua_files);

  File::Binary save_file{"game.sav"};
  if (save_file.isValidBinary())
    log.writeToLog(File::Logger::LogType::debug, "Save file magic validated!");
  else
    log.writeToLog(File::Logger::LogType::error, "Save file magic not mathing, possible corruption!");

  Game::Serialize file_data{save_file.readSerialDataFromFile<Game::Serialize>()};

  log.writeToLog(File::Logger::LogType::debug, std::format("Read Save data, High Score: {}", file_data.high_score));
  log.writeToLog(File::Logger::LogType::debug, std::format("Read Save data, Times Played: {}", file_data.times_played));

  LuaInstance lua_instance{log};
  lua_instance.execFiles(File::lua_files);

  SDL::Init init{};
  log.writeAddress("init", static_cast<void *>(&init));
  
  // Ttf
  auto font {TTF_OpenFont("assets/fonts/Orbitron/static/Orbitron-Regular.ttf", 32)};
  if (font == nullptr)
  {
    std::println("Failed to get font! {}", SDL_GetError());
    return -1;
  }

  SDL::EventHandler event_handler{log};
  SDL::WindowRenderer display{
      "Game window",
      {std::get<double>(lua_instance.GetLuaValue(std::array{"AppConfiguration", "Display", "Resolution", "x"})),
       std::get<double>(lua_instance.GetLuaValue(std::array{"AppConfiguration", "Display", "Resolution", "y"}))}};

  const auto window_size{display.game_window.WindowSize()};
  log.writeToLog(File::Logger::LogType::info,
                 std::format("screen size: [{}*{}].", window_size.first, window_size.second));

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

    event_handler.PollEvent([&] { proj_spawner.spawnProjectile(mouse_xy, lua_instance, display.game_renderer.ref()); });

    display.game_renderer.clearScreen();
    
    //ttf 
    auto surface {TTF_RenderText_Blended(font, "Player", 0, {255, 255, 255, 255})};
    auto texture {SDL_CreateTextureFromSurface(&display.game_renderer.ref(), surface)};
    auto texture_ref {*texture};
    SDL_DestroySurface(surface);
    SDL_FRect dstRect {100, 100, 200, 80};
    SDL_DestroyTexture(texture);


    display.game_renderer.drawColorFloat(0, 0, 0);
    display.game_renderer.renderTextureRotate(player.texture_.ref(), nullptr, &player.bounds_.ref(),
                                              Utils::Angle::CaclulateAngleBetweenTwoObjectsDegree(
                                                  mouse_xy, {player.bounds_.cref().x, player.bounds_.cref().y}) +
                                                  Utils::Angle::texture_offset<double>,
                                              nullptr, SDL_FLIP_NONE);
    display.game_renderer.renderTexture(enemy.texture_.ref(), nullptr, &enemy.bounds_.ref());
    
    //ttf
    display.game_renderer.renderTexture(texture_ref, nullptr, &dstRect);

    // Spawned Projectile Render:
    for (auto &projectile : proj_spawner.ref())
    {
      display.game_renderer.renderTexture(projectile.texture_.ref(), nullptr, &projectile.bounds_.ref());
    }

    display.game_renderer.present();
  }

  file_data.high_score = current_score.getHighScore();
  file_data.times_played += 1;
  save_file.writeSerialDataToFile(file_data);

  return 0;
}
