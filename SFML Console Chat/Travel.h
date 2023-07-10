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

class Travel
{
private:
	Assets assets;


	//Bool
	bool traveling;

public:
	int travel;
	//Constructors & Destructors
	Travel();
	~Travel();

	//Core

	//Main Window
	void travelScreen();

	//Getters
	bool& getTraveling() { return this->traveling; };

	//setters
	bool& setTravelingTrue() { return this->traveling = true; };
};



#endif

