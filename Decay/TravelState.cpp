#include "TravelState.h"
//Constructors and Destructors
TravelState::TravelState(sf::RenderWindow* window, std::stack<State*>* states)
    : State(window, states)
{
    //Initialization
    this->map = new MapComponent();
    this->event = new EventManager();
}

TravelState::~TravelState()
{
    delete this->map;
    delete this->event;
}

//State Functions
void TravelState::updateKeybinds()
{

}

void TravelState::update()
{
    this->updateMousePositions();
    this->map->update(this->getMousePosView());
    this->event->update(this->getMousePosView());
    CharacterManager::getInstance().updateAll(this->getMousePosView());
    CharacterManager::getInstance().updateStats(this->getMousePosView());
}

void TravelState::render(sf::RenderTarget* target)
{
    this->map->render(target);
    this->event->render(target);
    CharacterManager::getInstance().renderStats(target);
}

void TravelState::loadMapData(std::string input)
{

}