#include "StatsModule.h"
//Constructors and Deconstructors
StatsModule::StatsModule()
{

}

StatsModule::~StatsModule()
{

}

//Core Functions
void StatsModule::update(const sf::Vector2f mousePos)
{
	
}

void StatsModule::render(sf::RenderTarget* target)
{

}

//Stat Functions
void StatsModule::createStat(std::string key, int posX, int posY, std::string stat)
{
	this->stats[key] = new Stat(100, 100, stat);
}