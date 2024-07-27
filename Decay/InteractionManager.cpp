#include "InteractionManager.h"
//Constructors and Deconstructors
InteractionManager::InteractionManager()
{
    this->buttons["OPENINTERACTIONS"] = new Button(1475, 775, 100, 25, 0.5f, "Interact",
        sf::Color(70, 70, 70, 70), sf::Color(150, 150, 150, 255), sf::Color(20, 20, 20, 70), false);

    this->hidden = true;
}

InteractionManager::~InteractionManager()
{
    auto ib = this->buttons.begin();
    for (ib = this->buttons.begin(); ib != this->buttons.end(); ++ib) {
        delete ib->second;
    }
}

//Core Functions
void InteractionManager::update(const sf::Vector2f mousePos)
{
    for (auto& pair : interactions) {
        pair.second->update(mousePos);
    }
    this->updateButtons(mousePos);
}

void InteractionManager::render(sf::RenderTarget* target)
{
    int height = 200;
    for (auto& pair : interactions) {
        if (pair.second) { // Check if pointer is valid
            if (!this->hidden) {
                pair.second->render(target);
            }
            pair.second->getButtons()[""]->setPosition(1705, height += 30);
        }
    }
    this->buttons["OPENINTERACTIONS"]->render(target);
}

//Button Functions
void InteractionManager::updateButtons(const sf::Vector2f mousePos) 
{
    for (auto& pair : buttons) {
        pair.second->update(mousePos);
    }

    if (this->buttons["OPENINTERACTIONS"]->isPressed() && this->hidden) {
        this->hidden = false;
    }
    else if (this->buttons["OPENINTERACTIONS"]->isPressed() && !this->hidden) {
        this->hidden = true;
    }
}

//Manager Functions
void InteractionManager::createInstance(const std::string& id)
{
    interactions[id] = std::make_unique<Interaction>();
    interactions[id]->setId(id);
}