#include "ForestState.h"
//Constructors and Destructors
ForestState::ForestState(sf::RenderWindow* window, std::stack<State*>* states)
    : State(window, states)
{
    //Initialization
    this->map = new MapComponent();
}

ForestState::~ForestState()
{
    delete this->map;
}

//State Functions
void ForestState::updateKeybinds()
{

}

void ForestState::update()
{
    this->updateMousePositions();
    this->map->update(this->getMousePosView());
    CharacterManager::getInstance().updateAll(this->getMousePosView());
    CharacterManager::getInstance().updateStats(this->getMousePosView());
}

void ForestState::render(sf::RenderTarget* target)
{
    this->map->render(target);
    CharacterManager::getInstance().renderStats(target);
}

void ForestState::loadMapData(std::string input)
{

}