#include "ViewerModule.h"
#include "AssetDatabase.h"
#include <iostream>

//Constructors and Desctructors
ViewerModule::ViewerModule(std::string imageAssetId, float scale)
{
    // imageAssetId is an asset id registered in assets.db, not a raw file
    // path — load via AssetDatabase's cache instead of disk.
    try {
        this->image.setTexture(AssetDatabase::getInstance().getTexture(imageAssetId));
    }
    catch (const std::exception& e) {
        std::cerr << "ViewerModule: failed to load image asset \"" << imageAssetId
            << "\": " << e.what() << "\n";
    }
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
void ViewerModule::setView(std::string imageAssetId)
{
    try {
        this->image.setTexture(AssetDatabase::getInstance().getTexture(imageAssetId));
    }
    catch (const std::exception& e) {
        std::cerr << "ViewerModule: failed to load image asset \"" << imageAssetId
            << "\": " << e.what() << "\n";
    }
}

//Rectangle Functions
void ViewerModule::initRects()
{
    this->rectangles["HOSTILEBORDER"] = new Rectangle(this->x, this->y, 200, 200,
        sf::Color::Transparent, sf::Color::White, 1.f, false);
    this->rectangles["BORDER_TITLE"] = new Rectangle("Close Vision Viewer", sf::Color::White, 16,
        this->x, this->y, 200, 25, sf::Color::Transparent, sf::Color::White, 1.f, false);
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