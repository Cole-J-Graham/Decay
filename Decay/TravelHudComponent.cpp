#include "TravelHudComponent.h"

TravelHudComponent::TravelHudComponent()
{
    this->initButtons();

    // Area name — anchored top of the left panel as a header label
    areaNameText = std::make_unique<Text>(
        18.f, 12.f, 13,
        "",
        sf::Color(200, 200, 200, 200), false);
}

void TravelHudComponent::initButtons()
{
    const sf::Color idle(20, 20, 20, 160);
    const sf::Color hover(80, 80, 80, 255);
    const sf::Color active(10, 10, 10, 200);

    // Bottom bar strip spans y=770-805, shared baseline with the travel
    // arrows and bonfire button
    this->buttons["OPENPARTY"] = std::make_unique<Button>(
        1375, 776, 88, 24, 0.5f, "Party",
        idle, hover, active, false);

    this->buttons["OPENSTATS"] = std::make_unique<Button>(
        1468, 776, 88, 24, 0.5f, "Stats",
        idle, hover, active, false);

    this->buttons["OPENINVENTORY"] = std::make_unique<Button>(
        1561, 776, 88, 24, 0.5f, "Inventory",
        idle, hover, active, false);
}

void TravelHudComponent::update(sf::Vector2f mousePos)
{
    for (auto& pair : this->buttons)
        pair.second->update(mousePos);

    if (this->buttons["OPENPARTY"]->isPressed()) {
        this->partyVisible = !this->partyVisible;
        this->statsVisible = false;
        this->inventoryVisible = false;
    }

    if (this->buttons["OPENSTATS"]->isPressed()) {
        this->statsVisible = !this->statsVisible;
        this->partyVisible = false;
        this->inventoryVisible = false;
    }

    if (this->buttons["OPENINVENTORY"]->isPressed()) {
        this->inventoryVisible = !this->inventoryVisible;
        this->partyVisible = false;
        this->statsVisible = false;
    }
}

void TravelHudComponent::render(sf::RenderTarget* target)
{
    if (target == nullptr) return;

    for (auto& pair : this->buttons)
        pair.second->render(target);

    if (areaNameText)
        areaNameText->render(target);
}

void TravelHudComponent::hidePanels()
{
    this->partyVisible = false;
    this->statsVisible = false;
    this->inventoryVisible = false;
}

void TravelHudComponent::setAreaName(const std::string& name)
{
    if (name == currentAreaName) return;
    currentAreaName = name;

    std::string display = name;
    for (char& c : display)
        if (c == '_') c = ' ';
    if (!display.empty())
        display[0] = static_cast<char>(std::toupper(display[0]));

    if (areaNameText)
        areaNameText->setString(display);
}