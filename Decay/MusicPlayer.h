#pragma once

#include "UiPanel.h"

#include <SFML/Audio.hpp>

#include <fstream>
#include <iostream>
#include <map>
#include <memory>
#include <string>

class MusicPlayer
{
public:
    // Constructors and Destructors
    MusicPlayer(const std::string& music_list);
    ~MusicPlayer();

    // Core Functions
    bool readFile(const std::string& input);

    // Music Player Functions
    bool playSong(int id);

    // Setters
    void playDirect(const std::string& path);
    bool isStopped() const
    {
        return this->trackStarted && this->song.getStatus() == sf::Sound::Stopped;
    }
    void setVolume(float volume);   // 0-100, applied immediately
    float getVolume() const;
    void stopMusic();

private:
    bool loadSound(int id);

private:
    int x;
    int y;

    bool trackStarted = false;
    float volume = 70.f;  // master volume 0-100
    bool hidden;
    bool fileRead;
    int bufferId;
    int currentBufferId;

    std::map<int, std::string> songNames;

    std::string musicList;

    sf::Sound song;
    std::map<int, sf::SoundBuffer> buffer;

    UiPanel ui;
};