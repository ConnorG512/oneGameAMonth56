#pragma once

#include <SDL3/SDL_audio.h>
#include <memory>

namespace SDL
{
class Audio
{
  std::unique_ptr<SDL_AudioStream, decltype(&SDL_DestroyAudioStream)> audio_stream_{
      SDL_OpenAudioDeviceStream(SDL_AUDIO_DEVICE_DEFAULT_PLAYBACK, nullptr, nullptr, nullptr), &SDL_DestroyAudioStream};

public:
};
} // namespace SDL
