#pragma once
#include <string>

class Settings {
public:
    // 设置音效音量
    static void setSoundVolume(float volume);

    // 获取音效音量
    static float getSoundVolume();

    // 设置歌曲音量
    static void setSongVolume(float volume);

    // 获取歌曲音量
    static float getSongVolume();

private:
    static float soundVolume; // 存储音效音量
    static float songVolume;  // 存储歌曲音量
};
