#include "../include/stdafx.h"
#include "../include/SFMLSoundProvider.h"
#include "../include/SoundFileCache.h"

SFMLSoundProvider::SFMLSoundProvider() : _currentSongName("")
{
}

sf::Music *SFMLSoundProvider::CurrentSong;

void SFMLSoundProvider::PlaySound(std::string filename, float volume)
{
    int availChannel = -1;
    for (int i = 0; i < MAX_SOUND_CHANNELS; i++)
    {
        if (_currentSounds[i].getStatus() != sf::Sound::Playing)
        {
            availChannel = i;
            break;
        }
    }

    // If all sound channels are in use, do nothing for now
    if (availChannel != -1)
    {
        try
        {
            _currentSounds[availChannel] = _soundFileCache.GetSound(filename);
            _currentSounds[availChannel].setVolume(Settings::getSoundVolume());
            _currentSounds[availChannel].play();
        }
        catch (SoundNotFoundExeception &snfe) // snfe捕获了try块的异常信息，具体来说是来自GetSound
        {
            // ERROR, file wasnt found, should handle error here
            // snfe.what will contain the exception details
            std::cerr << "Failed to paly sound: " << snfe.what() << std::endl;
        }
    }
}

void SFMLSoundProvider::PlaySong(std::string filename, bool looping, float volume)
{
    sf::Music *currentSong;
    try
    {
        currentSong = _soundFileCache.GetSong(filename);
    }
    catch (SoundNotFoundExeception &snfe)
    {
        // This one is dire, means we couldn't find or load the selected song
        // So, lets exit!
        std::cerr << "Failed to play song: " << snfe.what() << std::endl;
        return;
    }
    // See if prior song is playing still, if so, stop it
    if (_currentSongName != "")
    {
        try
        {
            sf::Music *priorSong = _soundFileCache.GetSong(_currentSongName);
            if (priorSong->getStatus() != sf::Sound::Stopped)
            {
                priorSong->stop();
            }
        }
        catch (SoundNotFoundExeception &)
        {
            // Do nothing, this exception isn't dire.  It simply means the previous sound we were
            // trying to stop wasn't located.
        }
    }
    _currentSongName = filename;
    currentSong->setLoop(looping);
    currentSong->setVolume(volume);
    currentSong->play();
    CurrentSong = currentSong;
}
void SFMLSoundProvider::ChangeSongVolume(float volume)
{
    CurrentSong->setVolume(volume);
}

void SFMLSoundProvider::StopAllSounds()
{
    for (int i = 0; i < MAX_SOUND_CHANNELS; i++)
    {
        _currentSounds[i].stop();
    }
}

void SFMLSoundProvider::ChangeSoundVolume(float volume)
{
    for (int i = 0; i < MAX_SOUND_CHANNELS; i++)
    {
        _currentSounds[i].setVolume(volume);
    }
}

void SFMLSoundProvider::StopSong()
{
    if (_currentSongName != "")
    {
        sf::Music *currentSong = _soundFileCache.GetSong(_currentSongName);
        if (currentSong->getStatus() == sf::Sound::Playing)
        {
            currentSong->stop();
        }
    }
}
void SFMLSoundProvider::PauseSong()
{
    if (_currentSongName != "")
    {
        sf::Music *currentSong = _soundFileCache.GetSong(_currentSongName);
        if (currentSong->getStatus() == sf::Sound::Playing)
        {
            currentSong->pause();
        }
    }
}
void SFMLSoundProvider::ResumeSong()
{
    if (_currentSongName != "")
    {
        sf::Music *currentSong = _soundFileCache.GetSong(_currentSongName);
        if (currentSong->getStatus() == sf::Sound::Paused)
        {
            currentSong->play();
        }
    }
}

bool SFMLSoundProvider::IsSoundPlaying()
{
    for (int i = 0; i < MAX_SOUND_CHANNELS; i++)
    {
        if (_currentSounds[i].getStatus() == sf::Sound::Playing)
            return true;
    }
    return false;
}

bool SFMLSoundProvider::IsSongPlaying()
{
    if (_currentSongName != "")
    {
        return _soundFileCache.GetSong(_currentSongName)->getStatus() == sf::Music::Playing;
    }
    return false;
}
