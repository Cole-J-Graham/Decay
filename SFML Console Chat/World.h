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

class World
{
private:
	sf::RenderWindow window;
	sf::Image image;
	sf::Clock clock;
	sf::Clock clickTime;

	sf::String playerInput;

	sf::Event event;

	Assets assets;
	Travel travel;

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

	//Menu Bool
	bool statsmenu;

	//Quest Bool
	bool questboard;
	bool buttonClick;

	//Combat Bool
	bool combat;
	bool combatPlayer;
	bool combatTarget;
	bool hostile1;
	bool combatvictory;
	bool playerturn;
	bool targetturn;

	//Player Stats
	int level;
	int strike;
	int hp;
	int hpMax;

	//Coordinate Plane
	float xCord;
	float yCord;

	//Enemy Stats
	int targetHp;
	int targetHpMax;
	int targetStrike;

public:
	//Constructors & Destructors
	World();
	~World();

	//Core Functions
	void bootUp();
	void mainLoop();

	//User Input
	void userInput();
	void clearInput();

	//Display Functions
	void Draw(sf::RenderWindow& window);
	void greyOnHover(sf::RenderWindow& window);
	void travelButtons(sf::RenderWindow& window);
	void mapButtons(sf::RenderWindow& window);
	void menuBar(sf::RenderWindow& window);

	//Menu Functions
	void bonFire();
	void statsMenu();
	void questBoard();

	//Combat Functions
	void combatInit();
	void playerTurn();
	void targetTurn();
	void combatVictory();

	//Getters and Setters
	bool& getStop() { return this->stop; };
};

#endif

