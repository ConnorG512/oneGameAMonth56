#include "sdl/audio.hpp"
#include <SDL3/SDL_audio.h>
#include <cassert>
#include <cstdint>

auto SDL::Audio::pushStream(std::span<const float> buffer) -> void
{
  // check for empty buffer.
  if (buffer.empty())
    return;

  assert(buffer.data() != nullptr);
  SDL_PutAudioStreamData(audio_stream_.get(), buffer.data(), buffer.size() * sizeof(uint8_t));
}

auto SDL::Audio::resumeStream() -> void { SDL_ResumeAudioStreamDevice(audio_stream_.get()); }

auto SDL::Audio::pauseStream() -> void { SDL_PauseAudioStreamDevice(audio_stream_.get()); }

auto SDL::Audio::clearStream() -> void { SDL_ClearAudioStream(audio_stream_.get()); }

auto SDL::Audio::stopAndClearStream() -> void
{
  SDL_PauseAudioStreamDevice(audio_stream_.get());
  SDL_ClearAudioStream(audio_stream_.get());
}
