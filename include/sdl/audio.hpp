#pragma once

#include <SDL3/SDL_audio.h>
#include <memory>
#include <span>

namespace SDL
{
class Audio
{
  std::unique_ptr<SDL_AudioStream, decltype(&SDL_DestroyAudioStream)> audio_stream_{
      SDL_OpenAudioDeviceStream(SDL_AUDIO_DEVICE_DEFAULT_PLAYBACK, 0, nullptr, nullptr), &SDL_DestroyAudioStream};

public:
  auto pushStream(std::span<const float> buffer) -> void;
  auto resumeStream() -> void;
  auto pauseStream() -> void;
  auto clearStream() -> void;
  auto stopAndClearStream() -> void;
  auto getAudioDevice() -> void;
};
} // namespace SDL
