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
#include"Animation.h"

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

	//Core
	std::string input;
	std::string targetHpView;

	int unicode;
	int random;
	int test;

	//Core Bool
	bool stop;
	bool keyPress;
	bool initialized;
	bool comInitialized;
	bool bonfire;
	bool mainMenu;

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
	void bootUp(Sprites& sprites, Event& notevent, Combat& combat, Player& player, Travel& travel, Animation& animate);

	//User Input
	void userInput(Sprites& sprites);
	void clearInput();

	//Display Functions
	void Draw(sf::RenderWindow& window, Sprites& sprites, Event& notevent, Combat& combat, Player& player, Travel& travel, Animation& animate);
	void DrawMapSelectorButtons(sf::RenderWindow& window, Sprites& sprites);
	void greyOnHover(sf::RenderWindow& window, Sprites& sprites);
	void printPlayerStats(sf::RenderWindow& window, Sprites& sprites, Event& notevent, Combat& combat, Player& player);
	void printZinStats(sf::RenderWindow& window, Sprites& sprites, Event& notevent, Combat& combat, Player& player);

	//Display Element Functionality
	void mainMenuButtons(sf::RenderWindow& window, Sprites& sprites, Travel& travel, Animation& animate);
	void travelButtons(sf::RenderWindow& window, Sprites& sprites, Travel& travel, Animation& animate, Player& player);
	void menuBar(sf::RenderWindow& window, Sprites& sprites);
	void statsFunctionality(sf::RenderWindow& window, Combat& combat, Player& player, Sprites& sprites);
	void dialogueCombatBox(sf::RenderWindow& window, Combat& combat, Sprites& sprites, Travel& travel, Event& notevent);
	void movableBox(sf::RenderWindow& window, Sprites& sprites);
	void printToolTip(sf::RenderWindow& window, Sprites& sprites, Event& notevent, Combat& combat, Player& player);

	//Map Button Functionality
	void mapButtons(sf::RenderWindow& window, Sprites& sprites, Travel& travel);
	void mapButtonsForest(sf::RenderWindow& window, Sprites& sprites, Travel& travel);
	void mapButtonsCastle(sf::RenderWindow& window, Sprites& sprites, Travel& travel);
	void mapButtonsDecay(sf::RenderWindow& window, Sprites& sprites, Travel& travel);

	//Map Functions
	void resetMapPosition(sf::RenderWindow& window, Sprites& sprites);
	void selectMapView(sf::RenderWindow& window, Sprites& sprites, Travel& travel);
	void drawForestMap(sf::RenderWindow& window, Sprites& sprites);
	void drawCastleMap(sf::RenderWindow& window, Sprites& sprites);
	void drawDecayMap(sf::RenderWindow& window, Sprites& sprites);

	//Getters and Setters
	bool& getStop() { return this->stop; };
};

#endif

