#ifndef WORLD_H
#define WORLD_H

#include<iostream>
#include<SFML/Window.hpp>
#include<SFML/Graphics.hpp>
#include<SFML/Graphics/Text.hpp>
#include<sstream>
#include<string>
#include<SFML/Audio.hpp>

class World
{
private:
	sf::Font font;
	sf::RenderWindow window;
	sf::Texture texture;
	sf::Image image;
	sf::Sprite sprite;
	sf::RectangleShape rectangle;
	sf::RectangleShape outputRect;
	sf::String playerInput;
	sf::SoundBuffer buffer;
	sf::Sound sound;
	sf::Music music;
	sf::Event event;
	sf::Text text;
	sf::Text playerText;

	//Variables
	std::string input;
	bool keyPress;

	//Player Stats
	int level;
	int unicode;

public:
	bool stop = false;
	bool initialized;
	//Constructors & Destructors
	World();
	~World();

	//Functions
	void bootUp();
	void bonFire();
	void userInput();

	//Menu Functions
	void questBoard();

	//Drawing Objects
	void drawTextBox();
	void zinSprite();
	void drawOutputBox();

	//Map Locations
	void questOne();
};

#endif

