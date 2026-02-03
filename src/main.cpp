#include "sdl/image/texture.hpp"
#include "sdl/init.hpp"
#include "sdl/window-renderer/window-randerer.hpp"
#include "game/player.hpp"
#include "file-output/logging/logger.hpp"
#include "file-output/binary/binary.hpp"
#include "sdl/input/mouse.hpp"
#include "utils/angle.hpp"

#include <array>
#include <print>
#include <cmath>
#include <format>

auto main() -> int
{
  File::Logger log{std::getenv("PWD"), "/debug.log", true};
  File::Binary save_file {
    "game.sav",
    {'C','G','E','S','A','V', 'E', 0x00},
    log 
  };

  SDL::Init init{};
  log.writeToLog(File::Logger::LogType::debug, std::format("SDLInit Address: [{}].", reinterpret_cast<void*>(&init)));
  
  SDL::WindowRenderer display{};
  const auto window_size {display.game_window.WindowSize()};
  log.writeToLog(File::Logger::LogType::debug, std::format("display Address: [{}].", reinterpret_cast<void*>(&display)));
  log.writeToLog(File::Logger::LogType::info, std::format("screen size: [{}*{}].", window_size.first, window_size.second));
  
  

  SDL::Mouse mouse {};

  Gameplay::Player player({
      static_cast<float>(window_size.first / 2 - 16), 
      static_cast<float>(window_size.second / 2 - 16), 32.0, 32.0}, 
      display.game_renderer.ref(), 
      "assets/image/player.png"
      );

  // Game loop
  bool finished{false};
  while (!finished)
  {
    SDL_Event event;

    while (SDL_PollEvent(&event))
    {
      if (event.type == SDL_EVENT_QUIT)
      {
        finished = true;
      }
    }
    
    const auto mouse_xy {mouse.GetCursorPosition()};
    
    std::println("Atan result: {}", 
        Utils::Angle::CaclulateAngleBetweenTwoObjectsDegree(mouse_xy, {player.collision_.cref().x, player.collision_.cref().y}));

    display.game_renderer.clearScreen();
    display.game_renderer.drawColorFloat(0, 0, 0);
    display.game_renderer.renderTextureRotate(player.texture_.ref(), nullptr, &player.collision_.ref(), 
        Utils::Angle::CaclulateAngleBetweenTwoObjectsDegree(mouse_xy, {player.collision_.cref().x, player.collision_.cref().y}) + Utils::Angle::texture_offset<double>, nullptr, SDL_FLIP_NONE);
    display.game_renderer.present();
  }

  return 0;
}
