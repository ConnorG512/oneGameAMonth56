#include "sdl/image/texture.hpp"
#include "sdl/init.hpp"
#include "sdl/window-renderer/window-randerer.hpp"
#include "game/player.hpp"

#include <array>

auto main() -> int
{
  SDL::Init init{};
  SDL::WindowRenderer display{};

  SDL::Texture image{display.game_renderer.ref(), "assets/image/default.bmp"};
  Gameplay::Player player({0.0, 0.0, 32.0, 32.0}, display.game_renderer.ref(), "assets/image/default.bmp");

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

    display.game_renderer.clearScreen();
    display.game_renderer.drawColorFloat(0.5, 0.5, 0.5);
    display.game_renderer.renderTexture(image.ref(), nullptr, nullptr);
    display.game_renderer.renderTexture(
        player.texture_.ref(), 
        &player.collision_.ref(), 
        &player.collision_.ref()
    );
    display.game_renderer.present();
  }

  return 0;
}
