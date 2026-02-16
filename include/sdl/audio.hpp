#pragma once

#include <SDL3/SDL_audio.h>
#include <memory>
#include <span>

namespace SDL
{
class Audio
{
  SDL_AudioSpec spec{
      .format = SDL_AUDIO_F32,
      .channels = 2,
      .freq = 48000,
  };

  std::unique_ptr<SDL_AudioStream, decltype(&SDL_DestroyAudioStream)> audio_stream_{
      SDL_OpenAudioDeviceStream(SDL_AUDIO_DEVICE_DEFAULT_PLAYBACK, &spec, nullptr, nullptr), &SDL_DestroyAudioStream};

public:
  auto pushStream(std::span<const float> buffer) -> void;
  auto resumeStream() -> void;
  auto pauseStream() -> void;
  auto clearStream() -> void;
  auto stopAndClearStream() -> void;
  auto getAudioDevice() -> void;
};
} // namespace SDL
