#include "StatsManager.h"

// Constructors and Destructors
StatsManager::StatsManager() 
{
    this->buttons["OPENSTATS"] = new Button(1370, 775, 100, 25, 0.5f, "Stats",
        sf::Color(70, 70, 70, 70), sf::Color(150, 150, 150, 255), sf::Color(20, 20, 20, 70), false);
    this->hidden = true;
    this->clicked = false;
}

StatsManager::~StatsManager() 
{
    // Delete Buttons
    for (auto& pair : this->buttons) {
        delete pair.second;
    }
}

// Core Functions
void StatsManager::update(const sf::Vector2f mousePos) {
    for (auto& pair : stats) {
        if (pair.second) { // Check if pointer is valid
            pair.second->update(mousePos);
        }
    }
    this->updateButtons(mousePos);
}

void StatsManager::render(sf::RenderTarget* target) {
    int height = 20;
    for (auto& pair : stats) {
        if (pair.second && !this->hidden) { // Check if pointer is valid
            pair.second->render(target);
            auto button = pair.second->getButtons()[pair.second->getButtonId()];
            if (button) {
                button->setPosition(1705, height += 30);
            } else {
                std::cerr << "Button not found for ID: " << pair.second->getButtonId() << std::endl;
            }
        }
    }
    this->buttons["OPENSTATS"]->render(target);
}

// Manager Functions
void StatsManager::createInstance(const std::string& id) 
{
    stats[id] = std::make_unique<StatsModule>(id);
}

// Button Functions
void StatsManager::updateButtons(const sf::Vector2f mousePos)
{
    for (auto& it : this->buttons) {
        if (it.second) { // Ensure button is valid
            it.second->update(mousePos);
        }
    }

    if (this->buttons["OPENSTATS"] && this->buttons["OPENSTATS"]->isPressed()) {
        this->hidden = !this->hidden;
    }

    // Select the button and display stats while hiding all other stats
    this->passCountMax = static_cast<int>(stats.size());
    for (auto& pair : stats) {
        auto button = pair.second->getButtons()[pair.second->getButtonId()];
        if (button && button->isPressed()) {
            this->clicked = true;
        }

        if (this->passCount != this->passCountMax && this->clicked) {
            pair.second->getCurrentInstance() = false;
            this->passCount++;
        } else if (this->passCount == this->passCountMax) {
            pair.second->getCurrentInstance() = true;
            this->passCount = 0;
            this->clicked = false;
        }
    }
}
