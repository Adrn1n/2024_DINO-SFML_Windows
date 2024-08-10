#pragma once

#include "stdafx.h"

class IAudioProvider
{
public:
    virtual ~IAudioProvider() {}
    virtual void PlaySound(std::string filename, float volume = 100.f) = 0;
    virtual void PlaySong(std::string filename, bool looping, float volume = 100.f) = 0;
    virtual void ChangeSongVolume(float volume) = 0;
    virtual void ChangeSoundVolume(float volume) = 0;
    virtual void StopAllSounds() = 0;
    virtual void StopSong() = 0;
    virtual void ResumeSong() = 0;
    virtual void PauseSong() = 0;
    virtual bool IsSoundPlaying() = 0;
    virtual bool IsSongPlaying() = 0;
};
