#include "MapComponent.h"
//Constructors and Destructors
MapComponent::MapComponent(std::string file_input)
{
    //Variables
    this->file_input = file_input;

    //Initialization
    this->mapView = new MapViewer();
    this->initMapCores();
    //this->loadMap(file_input);
    this->initText();
    
}

MapComponent::~MapComponent()
{
    //Delete Modules
    delete this->mapView;
    //Delete Text
    auto it = this->text.begin();
    for (it = this->text.begin(); it != this->text.end(); ++it) {
        delete it->second;
    }
}

//Core Functions
void MapComponent::update(sf::Vector2f mousePos)
{
    this->mapView->update(mousePos);
}

void MapComponent::render(sf::RenderTarget* target)
{
    this->mapView->render(target);
    this->renderText(target);
}

void MapComponent::initMapCores()
{
    this->mapView->createMapCore(0.390, "Assets/Wallpapers/Forest/forestmap.jpeg",
        sf::Vector2f(150, 150), "Assets/Wallpapers/forest.txt", "Entrance",
        sf::Vector2f(150, 250), "", "Dark Plains",
        sf::Vector2f(200, 200), "", "Depths",
        sf::Vector2f(300, 250), "", "Corruption",
        sf::Vector2f(375, 400), "", "Deep Dark");
    /*this->mapView->createMapCore(0.385, "Assets/Wallpapers/Castle/castleMap.jpeg",
        sf::Vector2f(150, 150), "", "Entrance",
        sf::Vector2f(150, 250), "", "Halls",
        sf::Vector2f(200, 200), "", "Corridors",
        sf::Vector2f(300, 250), "", "Dungeon",
        sf::Vector2f(375, 400), "", "Labs");*/
}
//Asset Functions
void MapComponent::renderText(sf::RenderTarget* target)
{
    for (auto& it : this->text) {
        it.second->render(target);
    }
}

void MapComponent::initText()
{
    /*this->text["MOVETIMER"] = new Text(300, 20, 16, 
        std::to_string(this->move_time), sf::Color::White, false);*/
}