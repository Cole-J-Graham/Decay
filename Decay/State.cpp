#include "State.h"
#include "PauseMenuState.h"

//Constructors and Destructors
State::State(sf::RenderWindow* window, std::stack<State*>* states)
{
	//Core Initializations (window Required to function)
	this->window = window;
	this->states = states;
	this->quit = false;
}

State::~State()
{

}

//Core State Functionality
void State::render(sf::RenderTarget* target)
{

}

void State::update()
{

}

void State::updateMousePositions()
{
	this->mousePosScreen = sf::Mouse::getPosition();
	this->mousePosWindow = sf::Mouse::getPosition(*this->window);
	this->mousePosView = this->window->mapPixelToCoords(sf::Mouse::getPosition(*this->window));
}

const bool& State::getQuit() const
{
	return this->quit;
}

void State::checkForQuit()
{
	const bool escDown = sf::Keyboard::isKeyPressed(sf::Keyboard::Escape);

	if (escDown && !this->escWasDown) {
		this->states->push(new PauseMenuState(this->window, this->states));
	}

	this->escWasDown = escDown;
}

void State::endState()
{
	std::cout << "Ending game state~" << "\n";
}
