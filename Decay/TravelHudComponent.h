#pragma once

#include "Button.h"

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

    bool partyPanelVisible() const { return this->partyVisible; }
    bool statsPanelVisible() const { return this->statsVisible; }

    void hidePanels();

private:
    void initButtons();

private:
    std::map<std::string, std::unique_ptr<Button>> buttons;

    bool partyVisible = false;
    bool statsVisible = false;
};