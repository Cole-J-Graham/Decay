#pragma once
#include "Rectangle.h"
#include "Button.h"
#include <iostream>
#include <SFML/Audio.hpp>
#include <map>
#include <fstream>
#include <vector>
#include <string>
#include <future>
#include <atomic>

class MusicPlayer
{
public:
    //Constructors and Destructors
    MusicPlayer(const std::string& music_list);
    ~MusicPlayer();

    //Core Functions
    void update(const sf::Vector2f mousePos);
    void render(sf::RenderTarget* target);
    void initMusic();
    bool readFile(const std::string& input);

    //Music Player Functions
    void updateSongFunctions();
    void nextSong();

    //Button Functions
    void initButtons();
    void updateButtons(const sf::Vector2f mousePos);
    void updateOpenButton(const sf::Vector2f mousePos);
    void renderButtons(sf::RenderTarget* target);

    //Setters
    bool& setHidden() { return this->hidden = true; };
    bool& setShown() { return this->hidden = false; };

private:

    int x;
    int y;

    bool hidden;
    bool fileRead;
    int currentBufferId;

    std::map<int, std::string> songNames;

    std::unique_ptr<Rectangle> border;

    std::atomic<int> bufferId;

    std::string musicList;
    std::map<std::string, std::unique_ptr<Button>> buttons;

    sf::Sound song;
    std::map<int, sf::SoundBuffer> buffer;

    std::vector<std::future<void>> futures;

    void loadSoundAsync(int id, const std::string& filename);
};
