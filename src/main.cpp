#include "sdl/image/texture.hpp"
#include "sdl/init.hpp"
#include "sdl/window-renderer/window-randerer.hpp"
#include "game/player.hpp"
#include "logging/logger.hpp"
#include "sdl/input/mouse.hpp"

#include <array>
#include <print>

auto main() -> int
{
  Logger log{std::getenv("PWD"), "/debug.log", true};
  SDL::Init init{};
  SDL::WindowRenderer display{};
  const auto window_size {display.game_window.WindowSize()};
  
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
    std::println(stdout, "mouse pos {}:{}", mouse_xy.first, mouse_xy.second);

    display.game_renderer.clearScreen();
    display.game_renderer.drawColorFloat(0, 0, 0);
    display.game_renderer.renderTexture(
        player.texture_.ref(), 
        nullptr, 
        &player.collision_.ref()
    );
    display.game_renderer.present();
  }

  return 0;
}
