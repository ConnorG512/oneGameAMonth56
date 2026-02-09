#pragma once 

#include <SDL3_ttf/SDL_ttf.h>
#include <cassert>
#include <memory>

class SDL_Renderer; 

namespace SDL 
{
  class Ttf 
  {
    std::unique_ptr<TTF_Font, decltype(&TTF_CloseFont)> font_ {nullptr, &TTF_CloseFont}; 

    public:
      Ttf();
      ~Ttf();

      auto ref() noexcept -> TTF_Font& 
      {
        assert(font_.get() != nullptr);
        return *font_.get();
      }
  };
}
