#include "TravelInputComponent.h"

TravelInputComponent::TravelInputComponent()
{
    this->initButtons();
}

void TravelInputComponent::initButtons()
{
    const sf::Color idle(70, 70, 70, 70);
    const sf::Color hover(150, 150, 150, 255);
    const sf::Color active(20, 20, 20, 70);

    this->buttons["RETURN_BONFIRE"] = std::make_unique<Button>(415, 10, 135, 25, 0.5f, "Return->Bonfire", idle, hover, active, false);
    this->buttons["BUTTON_RIGHT"] = std::make_unique<Button>(1335, 780, 20, 20, 0.5f, "->", idle, hover, active, false);
    this->buttons["BUTTON_LEFT"] = std::make_unique<Button>(565, 780, 20, 20, 0.5f, "<-", idle, hover, active, false);
}

void TravelInputComponent::update(sf::Vector2f mousePos)
{
    for (auto& pair : this->buttons) {
        pair.second->update(mousePos);
    }

    this->rightActive = this->buttons["BUTTON_RIGHT"]->isPressed();
    this->leftActive = this->buttons["BUTTON_LEFT"]->isPressed();
    this->returnBonfireActive = this->buttons["RETURN_BONFIRE"]->isPressed();
}

void TravelInputComponent::render(sf::RenderTarget* target)
{
    if (target == nullptr) {
        return;
    }

    for (auto& pair : this->buttons) {
        pair.second->render(target);
    }
}

void TravelInputComponent::showMoveArrows()
{
    this->buttons["BUTTON_RIGHT"]->show();
    this->buttons["BUTTON_LEFT"]->show();
}

void TravelInputComponent::hideMoveArrows()
{
    this->buttons["BUTTON_RIGHT"]->hide();
    this->buttons["BUTTON_LEFT"]->hide();
}