#ifndef TRAVEL_H
#define TRAVEL_H

#include<iostream>
#include<SFML/Window.hpp>
#include<SFML/Graphics.hpp>
#include<SFML/Graphics/Text.hpp>
#include<sstream>
#include<string>
#include<SFML/Audio.hpp>
#include"Assets.h"
#include"Event.h"
#include"Combat.h"
#include"Player.h"

class Travel
{
private:

public:
	//Int
	int frame;
	int introCounterDialogue;
	int introCounter;
	int forestCounter;
	int castleCounter;
	int decayCounter;

	//Core Bools
	bool frameInit;

	//Bonfire
	bool forestBonfireInit;

	//Init Bools
	bool forestEntranceInit;
	bool forestDepthsInit;

	bool castleHallsInit;
	bool castleDepthsInit;

	Assets assets;

	int travel;
	//Constructors & Destructors
	Travel();
	~Travel();

	//Core
	void travelCore(sf::RenderWindow& window, Assets& assets, Event& notevent, Combat& combat, Player& player);

	//Draw Intro
	void intro(sf::RenderWindow& window, Assets& assets, Event& notevent, Combat& combat, Player& player);
	void introBeginning(sf::RenderWindow& window, Assets& assets, Event& notevent, Combat& combat, Player& player);

	//Draw Forest
	void forestMap(sf::RenderWindow& window, Assets& assets, Event& notevent, Combat& combat, Player& player);
	void forestBonfire(sf::RenderWindow& window, Assets& assets, Event& notevent, Combat& combat, Player& player);
	void forestEntrance(Assets& assets, Event& notevent, Combat& combat, Player& player);
	void forestDepths(Assets& assets, Event& notevent, Combat& combat, Player& player);
	void forestAbyssal(Assets& assets, Event& notevent, Combat& combat, Player& player);

	//Draw Castle
	void castleMap(sf::RenderWindow& window, Assets& assets, Event& notevent, Combat& combat, Player& player);
	void castleBonfire(sf::RenderWindow& window, Assets& assets, Event& notevent, Combat& combat, Player& player);
	void castleHalls(Assets& assets, Event& notevent, Combat& combat, Player& player);
	void castleDepths(Assets& assets, Event& notevent, Combat& combat, Player& player);

	//Draw Decay
	void decayMap(sf::RenderWindow& window, Assets& assets, Event& notevent, Combat& combat, Player& player);
	void decayBonfire(sf::RenderWindow& window, Assets& assets, Event& notevent, Combat& combat, Player& player);
	void decayChasms(Assets& assets, Event& notevent, Combat& combat, Player& player);
};



#endif

