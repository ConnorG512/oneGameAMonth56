#pragma once

#include <SDL3/SDL_audio.h>
#include <cassert>
#include <memory>

namespace Audio
{
class Instance
{
  SDL_AudioSpec spec{
      .format = SDL_AUDIO_F32,
      .channels = 2,
      .freq = 48000,
  };

  std::unique_ptr<SDL_AudioStream, decltype(&SDL_DestroyAudioStream)> audio_stream_{
      SDL_OpenAudioDeviceStream(SDL_AUDIO_DEVICE_DEFAULT_PLAYBACK, &spec, nullptr, nullptr), &SDL_DestroyAudioStream};

public:
  //auto pushStream(std::span<const float> buffer) -> void;
  auto resumeStream() -> void;
  auto pauseStream() -> void;
  auto clearStream() -> void;
  auto stopAndClearStream() -> void;
  auto getAudioDevice() -> void;

  template <typename audio_func, typename... Args>
  auto playAudio(Args&&... args) -> void
  {
    const auto buffer {audio_func{}(std::forward<Args>(args)...)};
    SDL_PutAudioStreamData(audio_stream_.get(), buffer.data(), buffer.size());
  }
};
} // namespace Audio
