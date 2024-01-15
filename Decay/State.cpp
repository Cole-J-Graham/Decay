#include "State.h"
//Constructors and Destructors
State::State()
{
	this->quit = false;
}

State::~State()
{

}

//Core State Functionality
void State::render(sf::RenderTarget* target)
{

}

void State::update(const float& dt)
{

}

const bool& State::getQuit() const
{
	return this->quit;
}

void State::checkForQuit()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
	{
		this->quit = true;
	}
}

void State::endState()
{
	std::cout << "Ending game state~" << "\n";
}

