#pragma once

#include "Button.h"

#include <map>
#include <memory>
#include <string>

class TravelInputComponent
{
public:
    TravelInputComponent();

    void update(sf::Vector2f mousePos);
    void render(sf::RenderTarget* target);

    bool rightArrowClicked() const { return this->rightActive; }
    bool leftArrowClicked() const { return this->leftActive; }
    bool returnBonfireClicked() const { return this->returnBonfireActive; }

    void showMoveArrows();
    void hideMoveArrows();

private:
    void initButtons();

private:
    std::map<std::string, std::unique_ptr<Button>> buttons;

    bool rightActive = false;
    bool leftActive = false;
    bool returnBonfireActive = false;
};