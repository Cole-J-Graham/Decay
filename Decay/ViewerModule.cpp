#include "ViewerModule.h"
//Constructors and Desctructors
ViewerModule::ViewerModule(std::string imagePath, float scale)
{
    this->imageTexture.loadFromFile(imagePath);
    this->image.setTexture(this->imageTexture);
    this->image.setScale(scale, scale);
    this->x = 1490;
    this->y = 320;
    this->image.setPosition(this->x, this->y);

    //Initialization
    this->initRects();
}

ViewerModule::~ViewerModule()
{
    //Delete Rectangles
    auto ir = this->rectangles.begin();
    for (ir = this->rectangles.begin(); ir != this->rectangles.end(); ++ir) {
        delete ir->second;
    }
}

//Core Functions
void ViewerModule::update(const sf::Vector2f mousePos)
{
    this->updateRects(mousePos);
}

void ViewerModule::render(sf::RenderTarget* target)
{
    target->draw(this->image);
    this->renderRects(target);
}

//Modifier Functions
void ViewerModule::setView(std::string imagePath)
{
    this->imageTexture.loadFromFile(imagePath);
    this->image.setTexture(this->imageTexture);
}

//Rectangle Functions
void ViewerModule::initRects()
{
    this->rectangles["HOSTILEBORDER"] = new Rectangle(this->x, this->y, 200, 200, 
        sf::Color::Transparent, sf::Color::White, 1.f, false);
    this->rectangles["BORDER_TITLE"] = new Rectangle("Close Vision Viewer", sf::Color::White, 16, 
        this->x, this->y,  200, 25, sf::Color::Transparent, sf::Color::White, 1.f, false);
}

void ViewerModule::updateRects(const sf::Vector2f mousePos)
{
    for (auto& it : this->rectangles) {
        it.second->update(mousePos);
    }
}

void ViewerModule::renderRects(sf::RenderTarget* target)
{
    for (auto& it : this->rectangles) {
        it.second->render(target);
    }
}