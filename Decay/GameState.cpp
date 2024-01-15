#include "GameState.h"

//Constructors and Destructors
GameState::GameState()
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
	this->updateKeybinds(dt);
}

void GameState::render(sf::RenderTarget* target)
{

}
