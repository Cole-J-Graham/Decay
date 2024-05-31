#include "StatsManager.h"
#include "StatsModule.h"

// Constructors and Destructors
StatsManager::StatsManager() 
{
    font.loadFromFile("Assets/Fonts/tickerbit font/Tickerbit-regular.otf");
    this->buttons["OPENSTATS"] = new Button(1370, 775, 100, 25, 0.5f, this->font, "Stats",
        sf::Color(70, 70, 70, 70), sf::Color(150, 150, 150, 255), sf::Color(20, 20, 20, 70), false);
    this->hidden = true;
}

StatsManager::~StatsManager() {
    // No need to manually delete, unique_ptr handles it
    //Delete Buttons
    auto ib = this->buttons.begin();
    for (ib = this->buttons.begin(); ib != this->buttons.end(); ++ib) {
        delete ib->second;
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
        if (pair.second) { // Check if pointer is valid
            if (!this->hidden) {
               pair.second->render(target);
            }
            pair.second->getButtons()["INSTANCE"]->setPosition(1705, height += 30);
        }
    }
    this->buttons["OPENSTATS"]->render(target);
}

// Manager Functions
void StatsManager::createInstance(std::string id) {
    stats[id] = std::make_unique<StatsModule>();
}

//Button Functions
void StatsManager::updateButtons(const sf::Vector2f mousePos)
{
    for (auto& it : this->buttons) {
        it.second->update(mousePos);
    }

    if (this->buttons["OPENSTATS"]->isPressed() && this->hidden) {
        this->hidden = false;
    }
    else if (this->buttons["OPENSTATS"]->isPressed() && !this->hidden) {
        this->hidden = true;
    }
}