#pragma once

#include <SDL3_ttf/SDL_ttf.h>
#include <memory>
#include <utility>

// Forward
class SDL_Renderer;
//

namespace SDL
{
class Text
{
  SDL_Renderer &renderer_;
  std::pair<float, float> xy_{0.0f, 0.0f};

  std::unique_ptr<TTF_TextEngine, decltype(&TTF_DestroyRendererTextEngine)> text_engine_{
      TTF_CreateRendererTextEngine(&renderer_), &TTF_DestroyRendererTextEngine};

  std::unique_ptr<TTF_Font, decltype(&TTF_CloseFont)> font_{
      TTF_OpenFont("assets/fonts/Orbitron/static/Orbitron-Regular.ttf", 32), &TTF_CloseFont};

  std::unique_ptr<TTF_Text, decltype(&TTF_DestroyText)> text_object_{
      TTF_CreateText(text_engine_.get(), font_.get(), "Text", 4), &TTF_DestroyText};

public:
  Text(const std::string &, std::pair<float, float> xy, SDL_Renderer &renderer);

  auto draw() noexcept -> void;
  auto swapText(const std::string &text) noexcept -> void;
};
} // namespace SDL
