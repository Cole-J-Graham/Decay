#pragma once

#include <SFML/Audio.hpp>

#include <algorithm>
#include <fstream>
#include <iostream>
#include <map>
#include <sstream>
#include <string>
#include <list>

class SfxManager
{
public:
    // Singleton
    static SfxManager& getInstance();

    // Delete copying
    SfxManager(const SfxManager&) = delete;
    SfxManager& operator=(const SfxManager&) = delete;

    // Core
    bool loadFromFile(const std::string& databasePath);
    void update();

    // Playback
    bool play(const std::string& id);
    bool play(const std::string& id, float volume);
    bool play(const std::string& id, float volume, float pitch);

    // Settings
    void setMasterVolume(float volume);
    float getMasterVolume() const;

    // Utility
    bool hasSound(const std::string& id) const;
    void stopAll();

private:
    SfxManager() = default;
    ~SfxManager() = default;

private:
    struct SfxDefinition
    {
        std::string id;
        std::string path;
    };

private:
    bool loadSound(const std::string& id, const std::string& path);
    std::vector<std::string> splitLine(const std::string& line, char delimiter) const;

private:
    float masterVolume = 70.f;

    std::map<std::string, sf::SoundBuffer> buffers;
    std::map<std::string, SfxDefinition> definitions;

    std::list<sf::Sound> activeSounds;
};