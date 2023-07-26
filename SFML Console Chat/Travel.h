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

class Travel
{
private:
	Event notevent;
	Combat combat;

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
	void travelCore(Assets& assets);

	//Draw Castle
	void castleEntrance(Assets& assets, Event& notevent);
	void castleDepths(Assets& assets, Event& notevent);
};



#endif

