#include "sdl/image/texture.hpp"
#include "sdl/init.hpp"
#include "sdl/window-renderer/window-renderer.hpp"
#include "game/player.hpp"
#include "game/enemy.hpp"
#include "file-output/logging/logger.hpp"
#include "file-output/binary/binary.hpp"
#include "sdl/input/mouse.hpp"
#include "sdl/event-handler.hpp"
#include "utils/angle.hpp"
#include "lua/lua.hpp"

#include <array>
#include <print>
#include <cmath>
#include <format>
#include <array>

auto main() -> int
{
  File::Logger log{std::getenv("PWD"), "/debug.log", true};
  File::Binary save_file {
    "game.sav",
    {'C','G','E','S','A','V', 'E', 0x00},
    log 
  };
  
  LuaInstance lua_instance {log};
  for(const auto& file : { "config.lua", "gamescript/player.lua" })
  {
    lua_instance.execFile(file);
  }

  SDL::Init init{};
  log.writeAddress("init", static_cast<void*>(&init));
  
  SDL::EventHandler event_handler {log};

  SDL::WindowRenderer display{
    "Game window",
    {
      std::get<double>(lua_instance.GetLuaValue(std::array
            {"AppConfiguration", "Display", "Resolution", "x"})),
      std::get<double>(lua_instance.GetLuaValue(std::array
            {"AppConfiguration", "Display", "Resolution", "y"}))
    }
  };

  const auto window_size {display.game_window.WindowSize()};
  log.writeToLog(File::Logger::LogType::info, std::format("screen size: [{}*{}].", window_size.first, window_size.second));
  
  SDL::Mouse mouse {};

  Gameplay::Player player({
      static_cast<float>(window_size.first / 2 - 16), 
      static_cast<float>(window_size.second / 2 - 16), 32.0, 32.0}, 
      display.game_renderer.ref(), 
      lua_instance,
      "assets/image/player.png"
      );

  Gameplay::Enemy enemy({
      static_cast<float>(window_size.first / 2 - 16), 
      static_cast<float>(window_size.second / 4 - 16), 32.0, 32.0}, 
      display.game_renderer.ref(), 
      lua_instance,
      "assets/image/default.png"
      );

  // Game loop
  while (event_handler.isGameRunning())
  {
    event_handler.PollEvent();

    const auto mouse_xy {mouse.GetCursorPosition()};

    display.game_renderer.clearScreen();
    display.game_renderer.drawColorFloat(0, 0, 0);
    display.game_renderer.renderTextureRotate(player.texture_.ref(), nullptr, &player.bounds_.ref(), 
        Utils::Angle::CaclulateAngleBetweenTwoObjectsDegree(
          mouse_xy, {player.bounds_.cref().x, player.bounds_.cref().y}) + Utils::Angle::texture_offset<double>, nullptr, SDL_FLIP_NONE);
    display.game_renderer.renderTexture(enemy.texture_.ref(), nullptr, &enemy.bounds_.ref());
    display.game_renderer.present();
  }

  return 0;
}
