#include "MapViewer.h"
//Constructor and Deconstructor
MapViewer::MapViewer()
{
    font.loadFromFile("Assets/Fonts/tickerbit font/Tickerbit-regular.otf");
    this->x = 100;
    this->y = 100;
    this->hidden = true;
    this->map = 0;

    //Initialization
    this->initRects();
    this->initButtons();
    this->initMapCore();
}

MapViewer::~MapViewer()
{
    //Delete Rectangles
    auto ir = this->rectangles.begin();
    for (ir = this->rectangles.begin(); ir != this->rectangles.end(); ++ir) {
        delete ir->second;
    }
    //Delete Maps
    auto im = this->maps.begin();
    for (im = this->maps.begin(); im != this->maps.end(); ++im) {
        delete im->second;
    }
}

//Core Functions
void MapViewer::update(const sf::Vector2f mousePos)
{
    this->updateButtons(mousePos);
    this->updateMaps(mousePos);
}

void MapViewer::render(sf::RenderTarget* target)
{
    if (!this->hidden) {
        this->renderRects(target);
        this->renderMaps(target);
    }

    this->renderButtons(target);
}

//Map Functions
void MapViewer::initMapCore()
{
    this->maps["FOREST"] = new MapCore( 0.395, "Assets/Wallpapers/Forest/forestmap.jpeg",
        sf::Vector2f(10, 10), "Entrance",
        sf::Vector2f(30, 50), "Dark Plains",
        sf::Vector2f(50, 80), "Depths",
        sf::Vector2f(75, 85), "Corruption",
        sf::Vector2f(100, 100), "Deep Dark");
}

void MapViewer::updateMaps(const sf::Vector2f mousePos)
{
    switch (this->map) {
    case 0:
        this->maps["FOREST"]->update(mousePos);
        break;
    case 1:
        break;
    case 2:
        break;
    }
}

void MapViewer::renderMaps(sf::RenderTarget* target)
{
    switch (this->map) {
    case 0:
        this->maps["FOREST"]->render(target);
        break;
    case 1:
        break;
    case 2:
        break;
    }
}

//Rectangle Functions
void MapViewer::initRects()
{
    this->rectangles["MAPVIEWER"] = new Rectangle(this->x, this->y, 400, 400,
        sf::Color::Transparent, sf::Color::White, 1.f, false);
}

void MapViewer::renderRects(sf::RenderTarget* target)
{
    for (auto& it : this->rectangles) {
        it.second->render(target);
    }
}

//Button Functions
void MapViewer::initButtons()
{
    this->buttons["OPENMAP"] = new Button(450, 775, 100, 25, 0.5f, this->font, "Map",
        sf::Color(70, 70, 70, 70), sf::Color(150, 150, 150, 255), sf::Color(20, 20, 20, 70), false);
}

void MapViewer::updateButtons(const sf::Vector2f mousePos)
{
    for (auto& it : this->buttons) {
        it.second->update(mousePos);
    }

    //Open Map Functionality
    if (this->buttons["OPENMAP"]->isPressed() && this->hidden) {
        this->maps["FOREST"]->setShown();
        this->rectangles["MAPVIEWER"]->show();
        this->hidden = false;
    }
    else if (this->buttons["OPENMAP"]->isPressed() && !this->hidden) {
        this->maps["FOREST"]->setHidden();
        this->rectangles["MAPVIEWER"]->show();
        this->hidden = true;
    }
}

void MapViewer::renderButtons(sf::RenderTarget* target)
{
    for (auto& it : this->buttons) {
        it.second->render(target);
    }
}