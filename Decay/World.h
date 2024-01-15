#ifndef WORLD_H
#define WORLD_H

#include<iostream>
#include<SFML/Window.hpp>
#include<fstream>
#include<sstream>
#include<string>
#include<SFML/Audio.hpp>
#include"Travel.h"
#include"Player.h"

class World : public Travel
{
private:
	sf::RenderWindow window;
	sf::Image image;
	sf::Clock clock;
	sf::Clock textTime;
	sf::Time textElapsed;

	sf::String playerInput;

	sf::Event event;

	std::string stringtest;

	//Core
	std::string input;
	std::string targetHpView;

	bool mapDefinitionHasLoaded;

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
	void bootUp(Animation& animate);
	void userInput();
	void saveGame(Animation& animate);
	void loadGame(Animation& animate);

	//Draw Functions
	void draw(sf::RenderWindow& window, Animation& animate);
	void drawStatsMenu(sf::RenderWindow& window);
	void drawMap(sf::RenderWindow& window);
	void drawBonfire(sf::RenderWindow& window, Animation& animate);

	//Display Functions
	void drawMapSelectorButtons(sf::RenderWindow& window);
	void printPlayerStats(sf::RenderWindow& window);
	void printZinStats(sf::RenderWindow& window);
	void printToolTipFunc(sf::RenderWindow& window, sf::RectangleShape& inputRect, std::string& toolTip);
	void printToolTip(sf::RenderWindow& window);

	//Display Element Functionality
	void mainMenuButtons(sf::RenderWindow& window, Animation& animate);
	void travelButtons(sf::RenderWindow& window, Animation& animate);
	void menuBar(sf::RenderWindow& window);
	void dialogueCombatBox(sf::RenderWindow& window);
	void movableBox(sf::RenderWindow& window);

	//Stat Functionality
	void statsFunctionality(sf::RenderWindow& window);
	void levelUp(sf::RenderWindow& window, sf::RectangleShape& inputRect, int& lvl, int& sp, int& exp, int& expNext);
	void statUp(sf::RenderWindow& window, sf::RectangleShape& inputRect, int& stat, int& sp, int& exp, int& expNext);

	//Map Button Functionality
	void mapButtons(sf::RenderWindow& window);
	void mapButtonsForest(sf::RenderWindow& window);
	void mapButtonsCastle(sf::RenderWindow& window);
	void mapButtonsDecay(sf::RenderWindow& window);

	//Map Functions
	void resetMapPosition(sf::RenderWindow& window);
	void selectMapView(sf::RenderWindow& window);
	void drawForestMap(sf::RenderWindow& window);
	void drawCastleMap(sf::RenderWindow& window);
	void drawDecayMap(sf::RenderWindow& window);

	//Getters and Setters
	bool& getStop() { return this->stop; };
};

#endif

