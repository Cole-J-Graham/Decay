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
    while (!maps.empty()) {
        MapCore* obj = maps.top();
        maps.pop();
        delete obj;
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
    this->maps.push(new MapCore( 0.395, "Assets/Wallpapers/Forest/forestmap.jpeg",
        sf::Vector2f(150, 150), "Entrance",
        sf::Vector2f(150, 250), "Dark Plains",
        sf::Vector2f(200,200), "Depths",
        sf::Vector2f(300, 250), "Corruption",
        sf::Vector2f(375, 400), "Deep Dark"));
}

void MapViewer::updateMaps(const sf::Vector2f mousePos)
{
    this->maps.top()->update(mousePos);
}

void MapViewer::renderMaps(sf::RenderTarget* target)
{
    this->maps.top()->render(target);
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
        this->maps.top()->setShown();
        this->rectangles["MAPVIEWER"]->show();
        this->hidden = false;
    }
    else if (this->buttons["OPENMAP"]->isPressed() && !this->hidden) {
        this->maps.top()->setHidden();
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