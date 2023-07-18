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

class Travel
{
private:
	Event event;

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
	void castleEntrance(Assets& assets);
	void castleDepths(Assets& assets);
};



#endif

