#include "GameState.h"

//Constructors and Destructors
GameState::GameState(sf::RenderWindow* window, std::stack<State*>* states)
	: State(window, states)
{

}

GameState::~GameState()
{

}

void GameState::endState()
{
	std::cout << "Ending game state~" << "\n";
}

//Functions
void GameState::updateKeybinds(const float& dt)
{
	this->checkForQuit();
}

void GameState::update(const float& dt)
{
	this->updateMousePositions();
	this->updateKeybinds(dt);
}

void GameState::render(sf::RenderTarget* target)
{

}
