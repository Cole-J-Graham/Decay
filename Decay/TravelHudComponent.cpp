#include "TravelHudComponent.h"

TravelHudComponent::TravelHudComponent()
{
    this->initButtons();
}

void TravelHudComponent::initButtons()
{
    const sf::Color idle(70, 70, 70, 70);
    const sf::Color hover(150, 150, 150, 255);
    const sf::Color active(20, 20, 20, 70);

    this->buttons["OPENPARTY"] = std::make_unique<Button>(
        1370, 775, 100, 25, 0.5f, "Party",
        idle,
        hover,
        active,
        false
    );

    this->buttons["OPENSTATS"] = std::make_unique<Button>(
        1475, 775, 100, 25, 0.5f, "Stats",
        idle,
        hover,
        active,
        false
    );

    this->buttons["OPENINVENTORY"] = std::make_unique<Button>(
        1580, 775, 100, 25, 0.5f, "Inventory",
        idle,
        hover,
        active,
        false
    );
}

void TravelHudComponent::update(sf::Vector2f mousePos)
{
    for (auto& pair : this->buttons) {
        pair.second->update(mousePos);
    }

    if (this->buttons["OPENPARTY"]->isPressed()) {
        this->partyVisible = !this->partyVisible;
        this->statsVisible = false;     // close stats when opening party
        this->inventoryVisible = false; // close inventory when opening party
    }

    if (this->buttons["OPENSTATS"]->isPressed()) {
        this->statsVisible = !this->statsVisible;
        this->partyVisible = false;     // close party when opening stats
        this->inventoryVisible = false; // close inventory when opening stats
    }

    if (this->buttons["OPENINVENTORY"]->isPressed()) {
        this->inventoryVisible = !this->inventoryVisible;
        this->partyVisible = false;  // close party when opening inventory
        this->statsVisible = false;  // close stats when opening inventory
    }
}

void TravelHudComponent::render(sf::RenderTarget* target)
{
    if (target == nullptr) {
        return;
    }

    for (auto& pair : this->buttons) {
        pair.second->render(target);
    }
}

void TravelHudComponent::hidePanels()
{
    this->partyVisible = false;
    this->statsVisible = false;
    this->inventoryVisible = false;
}