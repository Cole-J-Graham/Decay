#include "MapComponent.h"
//Constructors and Destructors
MapComponent::MapComponent()
{
    //Initialization
    font.loadFromFile("Assets/Fonts/tickerbit font/Tickerbit-regular.otf");
    this->mapView = new MapViewer();
    this->initMapCores();
    this->initButtons();
}

MapComponent::~MapComponent()
{
    //Delete Modules
    delete this->mapView;
    //Delete Buttons
    auto it = this->buttons.begin();
    for (it = this->buttons.begin(); it != this->buttons.end(); ++it) {
        delete it->second;
    }
}

//Core Functions
void MapComponent::update(sf::Vector2f mousePos)
{
    this->mapView->update(mousePos);
    this->updateButtons(mousePos);
}

void MapComponent::render(sf::RenderTarget* target)
{
    this->mapView->render(target);
    if (!this->mapView->getHidden()) { this->renderButtons(target); };
}

//Map Functions
void MapComponent::initMapCores()
{
    this->mapView->createMapCore(0, 0.390, "Assets/Wallpapers/Forest/forestmap.jpeg",
        sf::Vector2f(150, 150), "Assets/Wallpapers/forest.txt", "Entrance",
        sf::Vector2f(150, 250), "", "Dark Plains",
        sf::Vector2f(200, 200), "", "Depths",
        sf::Vector2f(300, 250), "", "Corruption",
        sf::Vector2f(375, 400), "", "Deep Dark");
    this->mapView->createMapCore(1, 0.385, "Assets/Wallpapers/Castle/castleMap.jpeg",
        sf::Vector2f(150, 150), "Assets/Wallpapers/castle.txt", "Entrance",
        sf::Vector2f(150, 250), "", "Halls",
        sf::Vector2f(200, 200), "", "Corridors",
        sf::Vector2f(300, 250), "", "Dungeon",
        sf::Vector2f(375, 400), "", "Labs");
}

//Button Functions
void MapComponent::initButtons()
{
    this->buttons["BUTTON_RIGHT"] = new Button(480, 75, 20, 20, 0.5f, this->font, "->",
        sf::Color(70, 70, 70, 70), sf::Color(150, 150, 150, 255), sf::Color(20, 20, 20, 70), false);
    this->buttons["BUTTON_LEFT"] = new Button(100, 75, 20, 20, 0.5f, this->font, "<-",
        sf::Color(70, 70, 70, 70), sf::Color(150, 150, 150, 255), sf::Color(20, 20, 20, 70), false);
    this->buttons["BUTTON_CENTER_IDLE"] = new Button(125, 75, 350, 20, 0.5f, this->font, "CURRENT MAP",
        sf::Color(70, 70, 70, 70), sf::Color(150, 150, 150, 255), sf::Color(20, 20, 20, 70), false);
}

void MapComponent::updateButtons(const sf::Vector2f mousePos)
{
    for (auto& it : this->buttons) {
        it.second->update(mousePos);
    }

    if (this->buttons["BUTTON_RIGHT"]->isPressed()) {
        this->mapView->getCurrentMapId()++;
        this->mapView->maps[mapView->getCurrentMapId()]->setShown();
    }
    else if (this->buttons["BUTTON_LEFT"]->isPressed()) {
        this->mapView->getCurrentMapId()--;
        this->mapView->maps[mapView->getCurrentMapId()]->setShown();
    }
}

void MapComponent::renderButtons(sf::RenderTarget* target)
{
    for (auto& it : this->buttons) {
        it.second->render(target);
    }
}
