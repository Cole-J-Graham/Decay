#pragma once
#include"Button.h"
#include<iostream>
#include<SFML/Audio.hpp>
#include<map>
#include<fstream>
#include<vector>
#include<string>
class MusicPlayer
{
public:
	//Constructors and Destructors
	MusicPlayer();
	~MusicPlayer();

	//Core Functions
	void update(const sf::Vector2f mousePos);
	void render(sf::RenderTarget* target);
	void initMusic();
	bool readFile(const std::string& input);

	//Music Player Functions
	void updateSongFunctions();
	void updateCurrentSong();
	void nextSong();

	//Button Functions
	void initButtons();
	void updateButtons(const sf::Vector2f mousePos);
	void renderButtons(sf::RenderTarget* target);

	//Rectangle Functions
	

private:

	bool fileRead;
	int currentSong;
	int songId;

	std::map<int, std::string> music;
	std::map<std::string, std::unique_ptr<Button>> buttons;

	sf::Sound song;
	sf::SoundBuffer buffer;

	class Music {
	public:
		//Constructors and Destructors
		Music() {

		}

		~Music() {

		}

	private:



	};
};

