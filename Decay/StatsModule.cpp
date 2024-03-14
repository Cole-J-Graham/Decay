#include "StatsModule.h"
//Constructors and Deconstructors
StatsModule::StatsModule()
{
    //Variables
    this->hidden = true;

    //Initialization
    this->initRects();
}

StatsModule::~StatsModule()
{
    //Delete Stats
    auto is = this->stats.begin();
    for (is = this->stats.begin(); is != this->stats.end(); ++is) {
        delete is->second;
    }
    //Delete Rectangles
    auto ir = this->rectangles.begin();
    for (ir = this->rectangles.begin(); ir != this->rectangles.end(); ++ir) {
        delete ir->second;
    }
}

//Core Functions
void StatsModule::update(const sf::Vector2f mousePos)
{
    this->updateStats(mousePos);
}

void StatsModule::render(sf::RenderTarget* target)
{
    if (!this->hidden) {
        this->renderRects(target);
        this->renderStats(target);
    }
}

//Stat Functions
void StatsModule::updateStats(const sf::Vector2f mousePos)
{
    for (auto& it : this->stats) {
        it.second->update(mousePos);
    }
}

void StatsModule::createStat(std::string key, std::string stat_name)
{
	this->stats[key] = new Stat(stat_name);
}

void StatsModule::renderStats(sf::RenderTarget* target)
{
    int y = 100;
    for (auto& it : this->stats) {
        it.second->setPosition(1402, y += 25);
        it.second->render(target);
    }
}

//Rectangle Functions
void StatsModule::initRects()
{
    this->rectangles["STATSMENU"] = new Rectangle(1400, 100, 300, 800, sf::Color::Transparent,
        sf::Color::White, 1.f);
}

void StatsModule::renderRects(sf::RenderTarget* target)
{
    for (auto& it : this->rectangles) {
        it.second->render(target);
    }
}