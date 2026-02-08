#include "file-output/binary/binary.hpp"
#include "file-output/logging/logger.hpp"
#include "game/enemy.hpp"
#include "game/player.hpp"
#include "game/projectile.hpp"
#include "lua/lua.hpp"
#include "sdl/event-handler.hpp"
#include "sdl/image/texture.hpp"
#include "sdl/init.hpp"
#include "sdl/input/mouse.hpp"
#include "sdl/window-renderer/window-renderer.hpp"
#include "utils/angle.hpp"

#include <array>
#include <cmath>
#include <format>
#include <print>

auto main() -> int
{
  File::Logger log{std::getenv("PWD"), "/debug.log", true};
  File::Binary save_file{"game.sav", {'C', 'G', 'E', 'S', 'A', 'V', 'E', 0x00}, log};

  LuaInstance lua_instance{log};
  lua_instance.execFiles(std::array{"config.lua", "gamescript/player.lua", "gamescript/enemy.lua", "gamescript/projectile.lua", "gamescript/rules.lua"});

  SDL::Init init{};
  log.writeAddress("init", static_cast<void *>(&init));

  SDL::EventHandler event_handler{log};

  SDL::WindowRenderer display{
      "Game window",
      {std::get<double>(lua_instance.GetLuaValue(std::array{"AppConfiguration", "Display", "Resolution", "x"})),
       std::get<double>(lua_instance.GetLuaValue(std::array{"AppConfiguration", "Display", "Resolution", "y"}))}};

  const auto window_size{display.game_window.WindowSize()};
  log.writeToLog(File::Logger::LogType::info,
                 std::format("screen size: [{}*{}].", window_size.first, window_size.second));

  SDL::Mouse mouse{};

  Game::Player player{lua_instance, display.game_renderer.ref()};
  Game::Enemy enemy{lua_instance, display.game_renderer.ref()};
  Game::Projectile projectile{{600.f,600.f}, lua_instance, display.game_renderer.ref()};

  // Game loop
  while (event_handler.isGameRunning())
  {
    event_handler.PollEvent();

    const auto mouse_xy{mouse.GetCursorPosition()};

    display.game_renderer.clearScreen();
    display.game_renderer.drawColorFloat(0, 0, 0);
    display.game_renderer.renderTextureRotate(player.texture_.ref(), nullptr, &player.bounds_.ref(),
                                              Utils::Angle::CaclulateAngleBetweenTwoObjectsDegree(
                                                  mouse_xy, {player.bounds_.cref().x, player.bounds_.cref().y}) +
                                                  Utils::Angle::texture_offset<double>,
                                              nullptr, SDL_FLIP_NONE);
    display.game_renderer.renderTexture(enemy.texture_.ref(), nullptr, &enemy.bounds_.ref());
    display.game_renderer.renderTexture(projectile.texture_.ref(), nullptr, &projectile.bounds_.ref());
    display.game_renderer.present();
  }

  return 0;
}
