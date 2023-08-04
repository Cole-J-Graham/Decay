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

	//Core Bools
	bool frameInit;

	//Init Bools
	bool castleEntranceInit;
	bool castleDepthsInit;

	Assets assets;

	int travel;
	//Constructors & Destructors
	Travel();
	~Travel();

	//Core
	void travelCore(Assets& assets, Event& notevent, Combat& combat, Player& player);

	//Draw Castle
	void castleEntrance(Assets& assets, Event& notevent, Combat& combat, Player& player);
	void castleDepths(Assets& assets, Event& notevent, Combat& combat, Player& player);
};



#endif

