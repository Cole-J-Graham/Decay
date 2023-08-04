#ifndef WORLD_H
#define WORLD_H

#include<iostream>
#include<SFML/Window.hpp>
#include<SFML/Graphics.hpp>
#include<SFML/Graphics/Text.hpp>
#include<sstream>
#include<string>
#include<SFML/Audio.hpp>
#include"Travel.h"
#include"Assets.h"
#include"Event.h"
#include"Combat.h"

class World
{
private:
	sf::RenderWindow window;
	sf::Image image;
	sf::Clock clock;
	sf::Clock clickTime;

	sf::String playerInput;

	sf::Event event;

	std::string stringtest;

	Travel travel;

	//Core
	std::string input;
	std::string targetHpView;

	int unicode;
	int random;
	int map;
	int test;

	//Core Bool
	bool stop;
	bool keyPress;
	bool initialized;
	bool comInitialized;
	bool bonfire;

	//Menu Bool
	bool statsmenu;

	//Quest Bool
	bool buttonClick;

	//Coordinate Plane
	float xCord;
	float yCord;

public:
	//Constructors & Destructors
	World();
	~World();

	//Core Functions
	void bootUp(Assets& assets, Event& notevent, Combat& combat, Player& player);
	void mainLoop(Assets& assets, Event& notevent, Combat& combat, Player& player);

	//User Input
	void userInput(Assets& assets);
	void clearInput();

	//Display Functions
	void Draw(sf::RenderWindow& window, Assets& assets, Event& notevent, Combat& combat, Player& player);
	void greyOnHover(sf::RenderWindow& window, Assets& assets);
	void printPlayerStats(sf::RenderWindow& window, Assets& assets, Event& notevent, Combat& combat, Player& player);
	void printZinStats(sf::RenderWindow& window, Assets& assets, Event& notevent, Combat& combat, Player& player);
	void printInventory(sf::RenderWindow& window, Assets& assets, Event& notevent, Combat& combat, Player& player);

	//Display Element Functionality
	void travelButtons(sf::RenderWindow& window, Assets& assets);
	void mapButtons(sf::RenderWindow& window, Assets& assets);
	void menuBar(sf::RenderWindow& window, Assets& assets);
	void menuBarStats(sf::RenderWindow& window, Combat& combat, Player& player, Assets& assets);
	void dialogueBox(sf::RenderWindow& window, Combat& combat, Assets& assets);

	//Map Functions
	void drawCastleMap(sf::RenderWindow& window, Assets& assets);

	//Getters and Setters
	bool& getStop() { return this->stop; };
};

#endif

