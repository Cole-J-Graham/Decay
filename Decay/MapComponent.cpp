#include "MapComponent.h"
#include "MapDatabase.h"

#include <iostream>

MapComponent::MapComponent()
{
    this->mapView = std::make_unique<MapViewer>();

    // Database must already be loaded by the time MapComponent is constructed.
    // If it hasn't been loaded yet, load it here as a fallback.
    MapDatabase::getInstance().loadFromFile("Assets/Data/maps.db");

    this->mapView->buildFromDatabase();
    this->initButtons();
}

// ---------------------------------------------------------------------------
// Core
// ---------------------------------------------------------------------------

void MapComponent::update(const sf::Vector2f& mousePos, bool moveRight, bool moveLeft)
{
    this->mapView->update(mousePos, moveRight, moveLeft);
    this->updateButtons(mousePos);
    this->syncCenterButtonLabel();
}

void MapComponent::render(sf::RenderTarget* target)
{
    this->mapView->render(target);
    if (!this->mapView->isHidden()) {
        this->renderButtons(target);
    }
}

// ---------------------------------------------------------------------------
// State queries
// ---------------------------------------------------------------------------

bool MapComponent::mapIsOpen() const
{
    return !this->mapView->isHidden();
}

bool MapComponent::mapIsSelected() const
{
    return this->mapView->isMapSelected();
}

std::string MapComponent::getCurrentAreaId() const
{
    return this->mapView->getCurrentMapName();
}

std::string MapComponent::getCurrentMapId() const
{
    return this->mapView->getCurrentMapId();
}

// ---------------------------------------------------------------------------
// Button functions
// ---------------------------------------------------------------------------

void MapComponent::initButtons()
{
    this->buttons["BUTTON_RIGHT"] = std::make_unique<Button>(
        480, 75, 20, 20, 0.5f, "->",
        sf::Color(70, 70, 70, 70),
        sf::Color(150, 150, 150, 255),
        sf::Color(20, 20, 20, 70),
        false
    );
    this->buttons["BUTTON_LEFT"] = std::make_unique<Button>(
        100, 75, 20, 20, 0.5f, "<-",
        sf::Color(70, 70, 70, 70),
        sf::Color(150, 150, 150, 255),
        sf::Color(20, 20, 20, 70),
        false
    );
    this->buttons["BUTTON_CENTER_IDLE"] = std::make_unique<Button>(
        125, 75, 350, 20, 0.5f, this->mapView->getCurrentMapName(),
        sf::Color(70, 70, 70, 70),
        sf::Color(150, 150, 150, 255),
        sf::Color(20, 20, 20, 70),
        false
    );
}

void MapComponent::updateButtons(const sf::Vector2f& mousePos)
{
    for (auto& it : this->buttons) {
        it.second->update(mousePos);
    }

    if (this->buttons["BUTTON_RIGHT"]->isPressed()) {
        this->mapView->navigateRight();
    }
    else if (this->buttons["BUTTON_LEFT"]->isPressed()) {
        this->mapView->navigateLeft();
    }
}

void MapComponent::syncCenterButtonLabel()
{
    std::string name = this->mapView->getCurrentMapName();
    this->buttons["BUTTON_CENTER_IDLE"]->setText(name);
}

void MapComponent::renderButtons(sf::RenderTarget* target)
{
    for (auto& it : this->buttons) {
        it.second->render(target);
    }
}