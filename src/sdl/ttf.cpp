#include "sdl/ttf.hpp"

#include <stdexcept>

SDL::Ttf::Ttf() 
{
  if(!TTF_Init())
    throw std::runtime_error("Failed to init SDL ttf!");
}

SDL::Ttf::~Ttf() 
{
  TTF_Quit();
}

