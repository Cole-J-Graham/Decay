#pragma once

#include "UiPanel.h"

#include <SFML/Audio.hpp>

#include <iostream>
#include <map>
#include <string>

class MusicPlayer
{
public:
    MusicPlayer();
    ~MusicPlayer();

    // Preload a track by file path into memory. Called by MusicManager at boot.
    bool preload(const std::string& path);

    // Play a previously preloaded track by path.
    void play(const std::string& path);

    void stop();

    bool isStopped() const;

    void setVolume(float volume);   // 0-100
    float getVolume() const;

private:
    float volume = 70.f;
    bool trackStarted = false;

    sf::Sound song;
    std::map<std::string, sf::SoundBuffer> buffers;

    UiPanel ui;
};