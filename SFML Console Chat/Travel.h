#ifndef TRAVEL_H
#define TRAVEL_H

#include<iostream>
#include<SFML/Window.hpp>
#include<SFML/Graphics.hpp>
#include<SFML/Graphics/Text.hpp>
#include<sstream>
#include<string>
#include<SFML/Audio.hpp>

class Travel
{
private:
	sf::Font font;
	sf::Event eventTravel;
	sf::RenderWindow windowTravel;

	sf::Sound sound;
	sf::Text playerText;
	sf::String playerInput;
	int unicode;
	std::string input;


	//Bool
	bool traveling;

public:
	//Constructors & Destructors
	Travel();
	~Travel();

	//Core
	void userInput();

	//Main Window
	void travelScreen();

	//Getters
	bool& getTraveling() { return this->traveling; };

	//setters
	bool& setTravelingTrue() { return this->traveling = true; };
};



#endif

