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
    void update(const sf::Vector2f mousePos);
    void render(sf::RenderTarget* target);
    void initMusic();
    bool readFile(const std::string& input);

    // Music Player Functions
    void updateSongFunctions();
    void nextSong();
    bool playSong(int id);

    // UI Functions
    void initUi();
    void updateUi(const sf::Vector2f mousePos);
    void showPanel();
    void hidePanel();

    // Setters
    void setHidden();
    void setShown();

private:
    bool loadSound(int id);
    std::string getDisplayName(const std::string& filename) const;

private:
    int x;
    int y;

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