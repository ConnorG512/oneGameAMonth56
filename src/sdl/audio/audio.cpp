#include "sdl/audio/audio.hpp"

#include <SDL3/SDL_audio.h>
#include <cassert>
#include <print>

auto Audio::Instance::resumeStream() -> void { SDL_ResumeAudioStreamDevice(audio_stream_.get()); }

auto Audio::Instance::pauseStream() -> void { SDL_PauseAudioStreamDevice(audio_stream_.get()); }

auto Audio::Instance::clearStream() -> void { SDL_ClearAudioStream(audio_stream_.get()); }

auto Audio::Instance::stopAndClearStream() -> void
{
  SDL_PauseAudioStreamDevice(audio_stream_.get());
  SDL_ClearAudioStream(audio_stream_.get());
}

auto Audio::Instance::getAudioDevice() -> void
{
  const auto result{SDL_GetNumAudioDrivers()};
  std::println("Audio Devices: {}", result);
}

