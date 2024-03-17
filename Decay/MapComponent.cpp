#include "MapComponent.h"
//Constructors and Destructors
MapComponent::MapComponent(std::string file_input)
{
    //Variables
    this->file_input = file_input;
    this->map.setPosition(580, 5);
    this->map.setScale(0.75, 0.75);
    this->mapMaxSize = 60;
    this->move_time = 1.0f;

    //Initialization
    this->event = new EventModule();
    this->loadMap(file_input);
    this->initText();
    
}

MapComponent::~MapComponent()
{
    //Delete Modules
    delete this->event;
    //Delete Text
    auto it = this->text.begin();
    for (it = this->text.begin(); it != this->text.end(); ++it) {
        delete it->second;
    }
}

//Core Functions
void MapComponent::update(sf::Vector2f mousePos)
{
    this->move();
    this->event->update(mousePos);
}

void MapComponent::render(sf::RenderTarget* target)
{
    target->draw(this->map);
    this->event->render(target);
    this->renderText(target);
}

void MapComponent::move()
{
    this->time = this->clock.getElapsedTime();
    if (this->time.asSeconds() >= this->move_time) {
        if (this->mapFrame != this->getMapMaxSize() + 1) {
            if (this->event->userInput->rightArrowClicked()) {
                this->mapFrame++;
                this->setMapFrame(mapFrame);
                this->clock.restart();
            }
            if (this->event->userInput->leftArrowClicked()) {
                this->mapFrame--;
                this->setMapFrame(mapFrame);
                this->clock.restart();
            }
        }
    }
}

//Asset Functions
void MapComponent::loadMap(std::string file_input)
{
    ifs.open(file_input);
    if (ifs.is_open()) {
        while (getline(ifs, line)) {
            this->texture.loadFromFile(line);
            this->mapContainer.push_back(texture);
        }
        ifs.close();
    }
}

void MapComponent::renderText(sf::RenderTarget* target)
{
    for (auto& it : this->text) {
        it.second->render(target);
    }
}

void MapComponent::initText()
{
    this->text["MOVETIMER"] = new Text(300, 20, 16, 
        std::to_string(this->move_time), sf::Color::White, false);
}