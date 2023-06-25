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
	sf::Text combatText;

	//Core
	std::string input;
	std::string targetHpView;
	int unicode;

	//Bool
	bool stop;
	bool keyPress;
	bool initialized;
	bool questone;
	bool statsmenu;
	bool questboard;
	bool combat;

	//Player Stats
	int level;

	//Enemy Stats
	int targetHp;
	int targetHpMax;

public:
	//Constructors & Destructors
	World();
	~World();

	//CoreFunctions
	void bootUp();
	void userInput();

	//Menu Functions
	void bonFire();
	void statsMenu();
	void questBoard();

	//Combat Functions
	void combatInit();

	//Drawing Objects
	void drawTextBox();
	void zinSprite();
	void drawOutputBox();
	void drawCombatText();

	//Map Locations
	void questOne();

	//Getters and Setters
	bool& getStop() { return this->stop; };
};

#endif

