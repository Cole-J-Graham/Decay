#include "EventModule.h"
//Constructors and Destructors
EventModule::EventModule()
{
	this->userInput = new UserInputComponent();
}

EventModule::~EventModule()
{
	delete this->userInput;
}

//Core Funtions
void EventModule::initEvent()
{
	this->userInput->hideMoveArrows();
}

void EventModule::update(sf::Vector2f mousePos)
{
	this->userInput->update(mousePos);
}

void EventModule::render(sf::RenderTarget* target)
{
	this->userInput->render(target);
}