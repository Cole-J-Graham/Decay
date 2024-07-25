#include "InteractionManager.h"
//Constructors and Deconstructors
InteractionManager::InteractionManager()
{
    this->buttons["OPENINTERACTIONS"] = new Button(1370, 775, 100, 25, 0.5f, "Interact",
        sf::Color(70, 70, 70, 70), sf::Color(150, 150, 150, 255), sf::Color(20, 20, 20, 70), false);

    this->hidden = false;
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

}

void InteractionManager::render(sf::RenderTarget* target)
{
    int height = 20;
    for (auto& pair : stats) {
        if (pair.second) { // Check if pointer is valid
            if (!this->hidden) {
                pair.second->render(target);
            }
            pair.second->getButtons()[pair.second->getButtonId()]->setPosition(1705, height += 30);
        }
    }
    this->buttons["OPENINTERACTIONS"]->render(target);
}

//Manager Functions
void InteractionManager::createInstance(std::string id) 
{
    stats[id] = std::make_unique<Interaction>();
    stats[id]->setId(id);
}