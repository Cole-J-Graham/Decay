#pragma once
#include"UserInputComponent.h"
#include<fstream>
class EventModule
{
public:
	//Constructors and Destructors
	EventModule();
	~EventModule();

	//Core Functions
	void initEvent();
	void update(sf::Vector2f mousePos);
	void render(sf::RenderTarget* target);

	UserInputComponent* userInput;

private:

};

