#include "TravelInputComponent.h"

TravelInputComponent::TravelInputComponent()
{
    this->initButtons();
}

void TravelInputComponent::initButtons()
{
    const sf::Color idle(20, 20, 20, 160);
    const sf::Color hover(80, 80, 80, 255);
    const sf::Color active(10, 10, 10, 200);

    const sf::Color dangerIdle(35, 15, 15, 180);
    const sf::Color dangerHover(100, 40, 40, 255);
    const sf::Color dangerActive(15, 5, 5, 200);

    // Bottom bar strip spans y=770-805 — all buttons share this baseline
    // Left travel arrow — sits just left of the map panel
    this->buttons["BUTTON_LEFT"] = std::make_unique<Button>(
        568, 776, 80, 24, 0.5f, "< Prev",
        idle, hover, active, false);

    // Right travel arrow — sits just right of the map panel
    this->buttons["BUTTON_RIGHT"] = std::make_unique<Button>(
        1272, 776, 80, 24, 0.5f, "Next >",
        idle, hover, active, false);

    // Bonfire button — far left of the bottom bar, danger-toned so it reads
    // as a meaningful action rather than a navigation control
    this->buttons["RETURN_BONFIRE"] = std::make_unique<Button>(
        8, 776, 140, 24, 0.5f, "Rest at Bonfire",
        dangerIdle, dangerHover, dangerActive, false);
}

void TravelInputComponent::update(sf::Vector2f mousePos)
{
    for (auto& pair : this->buttons)
        pair.second->update(mousePos);

    this->rightActive = this->buttons["BUTTON_RIGHT"]->isPressed();
    this->leftActive = this->buttons["BUTTON_LEFT"]->isPressed();
    this->returnBonfireActive = this->buttons["RETURN_BONFIRE"]->isPressed();
}

void TravelInputComponent::render(sf::RenderTarget* target)
{
    if (target == nullptr) return;

    for (auto& pair : this->buttons)
        pair.second->render(target);
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