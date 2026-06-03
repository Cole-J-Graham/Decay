#pragma once

#include <string>

class SettingsManager
{
public:
    static SettingsManager& getInstance()
    {
        static SettingsManager instance;
        return instance;
    }

    void loadFromFile(const std::string& path);
    void saveToFile();

    float getMusicVolume() const { return musicVolume; }
    float getSfxVolume() const { return sfxVolume; }

    void setMusicVolume(float volume);
    void setSfxVolume(float volume);

private:
    SettingsManager() = default;

private:
    std::string settingsPath;

    float musicVolume = 70.f;
    float sfxVolume = 70.f;
};