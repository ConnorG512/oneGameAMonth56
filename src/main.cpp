#include "file-out/binary.hpp"
#include "file-out/logger.hpp"
#include "filesystem/file-check.hpp"
#include "game/enemy.hpp"
#include "game/player.hpp"
#include "game/projectile.hpp"
#include "game/rules.hpp"
#include "game/save-object.hpp"
#include "game/spawner.hpp"
#include "game/ui-layout.hpp"
#include "lua/lua.hpp"
#include "sdl/audio/audio.hpp"
#include "sdl/audio/modes.hpp"
#include "sdl/display/display.hpp"
#include "sdl/event-handler.hpp"
#include "sdl/image/texture.hpp"
#include "sdl/init.hpp"
#include "sdl/input/mouse.hpp"
#include "utils/angle.hpp"
#include "utils/cast-get.hpp"
#include "utils/rng.hpp"

#include <SDL3/SDL_error.h>
#include <SDL3/SDL_rect.h>
#include <SDL3/SDL_render.h>
#include <SDL3/SDL_surface.h>
#include <SDL3/SDL_video.h>
#include <SDL3_ttf/SDL_ttf.h>
#include <array>
#include <format>
#include <string>
#include <utility>

auto main() -> int
{
  const auto total_files {File::validateFiles(File::lua_files)};
  
  LuaInstance lua_instance{};
  lua_instance.execFiles(File::lua_files);

  File::Logger log{"debug.log",
                   CastGetVar<bool>(lua_instance.GetLuaValue(std::array{"AppConfiguration", "Logger", "enable"}))};
  log.writeToLog(File::Logger::LogType::debug, std::format("Total files scanned: {0}", total_files));

  File::Binary save_file{"game.sav"};
  Game::Serialize file_data{save_file.readSerialDataFromFile<Game::Serialize>()};

  SDL::Init init{};

  SDL::EventHandler event_handler{log};
  SDL::Display display{
      "Game window",
      {std::get<double>(lua_instance.GetLuaValue(std::array{"AppConfiguration", "Display", "Resolution", "x"})),
       std::get<double>(lua_instance.GetLuaValue(std::array{"AppConfiguration", "Display", "Resolution", "y"}))}};

  if (const auto vsync_result = display.game_renderer.setVsnc(SDL::Renderer::vsync_option::adaptive);
      !vsync_result.has_value())
    log.writeToLog(File::Logger::LogType::error, vsync_result.error());

  Audio::Instance audio{};
  audio.getAudioDevice();

  Game::GUI::Layout game_ui{
      display.game_renderer.ref(),
      {
          CastGetVar<std::string>(lua_instance.GetLuaValue(std::array{"UI", "Name", "label"})).c_str(),
          CastGetVar<int>(lua_instance.GetLuaValue(std::array{"UI", "Name", "x_pos"})),
          CastGetVar<int>(lua_instance.GetLuaValue(std::array{"UI", "Name", "y_pos"})),
      },
      {
          std::format("{:0}", 0).c_str(),
          CastGetVar<int>(lua_instance.GetLuaValue(std::array{"UI", "Score", "x_pos"})),
          CastGetVar<int>(lua_instance.GetLuaValue(std::array{"UI", "Score", "y_pos"})),
      },
      {
          std::format("{:0}", file_data.high_score).c_str(),
          CastGetVar<int>(lua_instance.GetLuaValue(std::array{"UI", "HighScore", "x_pos"})),
          CastGetVar<int>(lua_instance.GetLuaValue(std::array{"UI", "HighScore", "y_pos"})),
      },
      {
          std::format("{:02}", file_data.times_played).c_str(),
          CastGetVar<int>(lua_instance.GetLuaValue(std::array{"UI", "TimesPlayed", "x_pos"})),
          CastGetVar<int>(lua_instance.GetLuaValue(std::array{"UI", "TimesPlayed", "y_pos"})),
      },
  };

  SDL::Mouse mouse{};

  Utils::Rng rng{};
  const auto refresh_rate{static_cast<int>(display.game_window.getRefreshRate().value_or(60))};
  log.writeToLog(File::Logger::LogType::debug, std::format("Refresh rate: {}", refresh_rate));

  Game::Rules game_rules{CastGetVar<int>(lua_instance.GetLuaValue(std::array{"GameRules", "max_time"})) * refresh_rate,
                         CastGetVar<int>(lua_instance.GetLuaValue(std::array{"GameRules", "max_time"})) * refresh_rate,
                         CastGetVar<int>(lua_instance.GetLuaValue(std::array{"GameRules", "max_score"}))};

  Game::Player player{lua_instance, display.game_renderer.ref()};
  Game::Spawner<Game::Projectile> proj_spawner{[&lua_instance]()
                                               {
                                                 return CastGetVar<int>(lua_instance.GetLuaValue(
                                                     std::array{"GameRules", "ProjectileSpawner", "max_spawn_slots"}));
                                               }};
  Game::Spawner<Game::Enemy> enemy_spawner{};

  // Game loop
  while (event_handler.isGameRunning())
  {
    const auto mouse_xy{mouse.GetCursorPosition()};
    const auto mouse_radian{Utils::Angle::CaclulateAngleBetweenTwoObjectsRadians(
        mouse_xy, {player.bounds_.cref().x, player.bounds_.cref().y})};

    event_handler.PollEvent(
        [&]
        {
          const auto window_size_result{display.game_window.WindowSize().value_or({1024, 1024})};
          proj_spawner.spawn(
              window_size_result,
              std::pair<float, float>{window_size_result.first / 2 - 16, window_size_result.second / 2 - 16},
              std::pair<float, float>{
                  Utils::Angle::CalculateXDirection(
                      mouse_radian, CastGetVar<float>(lua_instance.GetLuaValue(std::array{"Projectile", "speed"}))),
                  Utils::Angle::CalculateYDirection(
                      mouse_radian, CastGetVar<float>(lua_instance.GetLuaValue(std::array{"Projectile", "speed"})))},
              lua_instance, display.game_renderer.ref());
        });

    proj_spawner.clearSlot();

    for (auto &projectile : proj_spawner.cref())
      projectile.bounds_.move();

    enemy_spawner.spawn(static_cast<float>(rng.generate(100, 924)), static_cast<float>(rng.generate(100, 924)),
                        lua_instance, display.game_renderer.ref());

    for (const auto &slot : proj_spawner.cref())
    {
      if (enemy_spawner.clearSlot(slot))
      {
        const auto calcNote = [&rng]()
        {
          constexpr std::array<float, 3> notes{220.f, 277.18f, 329.63f};
          const auto rng_result{rng.generate(0, 2)};
          return notes.at(rng_result);
        };
        audio.playAudio<Audio::Modes::BasicSine<float>>(calcNote(), 48000.0f, 48000 / 2, 0.05f);
        const auto [score, type] {game_rules.score.increase(rng.generate(300, 450), rng.generate(1, 5))};
        if(type == Game::Score::ScoreType::bonus)
        {
          audio.playAudio<Audio::Modes::BasicSine<float>>(440.0f, 48000.0f, 48000 / 2, 0.05f);
          audio.resumeStream();
        }

        game_ui.setText(Game::GUI::Layout::Text::score, std::to_string(game_rules.score.cref().getCurrent()));
        audio.resumeStream();
      }
    }

    // Reset player score once it hits end of time.
    game_rules.time.decrease(1);
    game_rules.restartGame(audio, game_ui);
    
    // Rendering
    display.game_renderer.clearScreen();
    display.game_renderer.drawColorFloat(0, 0, 0);

    display.game_renderer.renderTextureRotate(player.texture_.ref(), nullptr, &player.bounds_.ref(),
                                              Utils::Angle::CaclulateAngleBetweenTwoObjectsDegree(
                                                  mouse_xy, {player.bounds_.cref().x, player.bounds_.cref().y}) +
                                                  Utils::Angle::texture_offset<double>,
                                              nullptr, SDL_FLIP_NONE);

    for (auto &projectile : proj_spawner.ref())
      display.game_renderer.renderTexture(projectile.texture_.ref(), nullptr, &projectile.bounds_.ref());

    for (auto &enemy : enemy_spawner.ref())
      display.game_renderer.renderTexture(enemy.texture_.ref(), nullptr, &enemy.bounds_.ref());

    game_ui.drawText();

    display.game_renderer.present();
  }

  file_data.high_score = (game_rules.score.cref().getCurrent() > file_data.high_score)
                             ? game_rules.score.cref().getCurrent()
                             : file_data.high_score;
  file_data.times_played += 1;
  save_file.writeSerialDataToFile(file_data);

  return 0;
}
