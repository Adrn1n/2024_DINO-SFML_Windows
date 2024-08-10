#pragma once

#include "stdafx.h"
#include "IAudioProvider.h"
#include "SoundFileCache.h"
#include "Settings.h"

class SFMLSoundProvider : public IAudioProvider
{
public:
    SFMLSoundProvider();

    void PlaySound(std::string filename, float volume = 100.f);
    void PlaySong(std::string filename, bool looping = false, float volume = 100.f);
    void ChangeSongVolume(float volume);
    void ChangeSoundVolume(float volume);
    void StopAllSounds();
    void ResumeSong();
    void StopSong();
    void PauseSong();
    bool IsSoundPlaying();
    bool IsSongPlaying();

private:
    static const int MAX_SOUND_CHANNELS = 5;
    static sf::Music *CurrentSong;

    SoundFileCache _soundFileCache;
    sf::Sound _currentSounds[MAX_SOUND_CHANNELS];
    std::string _currentSongName;
};
