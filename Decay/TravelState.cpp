#include "TravelState.h"
//Constructors and Destructors
TravelState::TravelState(sf::RenderWindow* window, std::stack<State*>* states)
    : State(window, states)
{
    //Initialization
    this->initRects();
    this->map = new MapComponent();
}

TravelState::~TravelState()
{
    delete this->map;
    //Delete Rectangles
    auto ir = this->rectangles.begin();
    for (ir = this->rectangles.begin(); ir != this->rectangles.end(); ++ir) {
        delete ir->second;
    }
}

//State Functions
void TravelState::updateKeybinds()
{

}

void TravelState::update()
{
    this->updateMousePositions();
    this->map->update(this->getMousePosView());
    CharacterManager::getInstance().updateAll(this->getMousePosView());
    CharacterManager::getInstance().updateStats(this->getMousePosView());
    CharacterManager::getInstance().updateInteractions(this->getMousePosView());
}

void TravelState::render(sf::RenderTarget* target)
{
    this->map->render(target);
    this->renderRects(target);
    CharacterManager::getInstance().renderStats(target);
    CharacterManager::getInstance().renderInteractions(target);
}

void TravelState::loadMapData(std::string input)
{

}

//Rectangle Functions
void TravelState::initRects()
{
    this->rectangles["BORDER"] = new Rectangle(560, 5, 800, 800, sf::Color::Transparent,
        sf::Color::White, 1.f, false);
    this->rectangles["LEFTBOX"] = new Rectangle(0, 5, 555, 800, sf::Color::Transparent,
        sf::Color::White, 1.f, false);
    this->rectangles["RIGHTBOX"] = new Rectangle(1365, 5, 555, 800, sf::Color::Transparent,
        sf::Color::White, 1.f, false);
}

void TravelState::renderRects(sf::RenderTarget* target)
{
    for (auto& it : this->rectangles) {
        it.second->render(target);
    }
}