#include "SettingsManager.h"

#include <fstream>
#include <iostream>

void SettingsManager::loadFromFile(const std::string& path)
{
    this->settingsPath = path;

    std::ifstream file(path);

    if (!file.is_open())
    {
        std::cerr << "Failed to open settings file: " << path << std::endl;
        return;
    }

    std::string line;

    while (std::getline(file, line))
    {
        const std::size_t equalsPos = line.find('=');
        if (equalsPos == std::string::npos) continue;

        const std::string key = line.substr(0, equalsPos);
        const std::string value = line.substr(equalsPos + 1);

        try
        {
            if (key == "music")
                this->musicVolume = std::stof(value);
            else if (key == "sfx")
                this->sfxVolume = std::stof(value);
            else if (key == "fullscreen")
                this->fullscreen = (value == "1" || value == "true");
        }
        catch (...)
        {
            std::cerr << "Invalid settings value: " << line << std::endl;
        }
    }
}

void SettingsManager::saveToFile()
{
    if (this->settingsPath.empty())
    {
        std::cerr << "Settings path not initialized.\n";
        return;
    }

    std::ofstream file(this->settingsPath);

    if (!file.is_open())
    {
        std::cerr << "Failed to save settings file: " << this->settingsPath << std::endl;
        return;
    }

    file << "music=" << this->musicVolume << '\n';
    file << "sfx=" << this->sfxVolume << '\n';
    file << "fullscreen=" << (this->fullscreen ? 1 : 0) << '\n';
}

void SettingsManager::setMusicVolume(float volume)
{
    if (volume < 0.f)   volume = 0.f;
    if (volume > 300.f) volume = 300.f;
    this->musicVolume = volume;
}

void SettingsManager::setSfxVolume(float volume)
{
    if (volume < 0.f)   volume = 0.f;
    if (volume > 300.f) volume = 300.f;
    this->sfxVolume = volume;
}