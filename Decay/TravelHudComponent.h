#pragma once

#include "Button.h"
#include "Text.h"

#include <SFML/Graphics.hpp>

#include <map>
#include <memory>
#include <string>

class TravelHudComponent
{
public:
    TravelHudComponent();

    void update(sf::Vector2f mousePos);
    void render(sf::RenderTarget* target);

    bool partyPanelVisible()     const { return this->partyVisible; }
    bool statsPanelVisible()     const { return this->statsVisible; }
    bool inventoryPanelVisible() const { return this->inventoryVisible; }

    void hidePanels();
    void setAreaName(const std::string& name);

private:
    void initButtons();

private:
    std::map<std::string, std::unique_ptr<Button>> buttons;

    // Area name display
    std::unique_ptr<Text> areaNameText;
    std::string           currentAreaName;

    bool partyVisible = false;
    bool statsVisible = false;
    bool inventoryVisible = false;
};