#include "../include/Settings.h"

// 初始化静态成员变量
float Settings::soundVolume = 100.0f;
float Settings::songVolume = 100.0f;

// 设置音效音量
void Settings::setSoundVolume(float volume)
{
    soundVolume = volume;
}

// 获取音效音量
float Settings::getSoundVolume()
{
    return soundVolume;
}

// 设置歌曲音量
void Settings::setSongVolume(float volume)
{
    songVolume = volume;
}

// 获取歌曲音量
float Settings::getSongVolume()
{
    return songVolume;
}
