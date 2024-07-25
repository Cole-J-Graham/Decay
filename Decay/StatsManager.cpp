#include "StatsManager.h"
#include "StatsModule.h"

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
            pair.second->getButtons()[pair.second->getButtonId()]->setPosition(1705, height += 30);
        }
    }
    this->buttons["OPENSTATS"]->render(target);
}

// Manager Functions
void StatsManager::createInstance(std::string id) {
    stats[id] = std::make_unique<StatsModule>();
    stats[id]->setId(id);
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

    //Select the button and display stats while hiding all other stats
    this->passCountMax = static_cast<int>(stats.size());
    for (auto& pair : stats) {
        if (pair.second->getButtons()[pair.second->getButtonId()]->isPressed()) {
            this->clicked = true;
        }

        if (this->passCount != this->passCountMax && this->clicked) {
            pair.second->getCurrentInstance() = false;
            this->passCount++;
        }
        else if (this->passCount == this->passCountMax) {
            pair.second->getCurrentInstance() = true;
            this->passCount = 0;
            this->clicked = false;
        }
    }
}