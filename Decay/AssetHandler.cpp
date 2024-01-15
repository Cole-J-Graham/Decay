#include "AssetHandler.h"

//Constructors & Destructors
AssetHandler::AssetHandler()
{
	//Core Modifiers
	this->decay = 0;
	this->decayMax = 50;

	//Leveling
	this->level = 1;
	this->exp = 0;
	this->expNext = 100;
	this->sp = 0;

	//Attributes
	this->strength = 0;
	this->fortitude = 0;
	this->vitality = 0;

	//Zin Leveling
	this->zinLevel = 1;
	this->zinSp = 0;
	this->zinExp = 0;
	this->zinExpNext = 75;

	//Zin Attributes
	this->zinResolve = 0;
	this->zinPatience = 0;
	this->zinResilience = 0;

	//Item Strength
	this->swordPower = 0;

	//Items
	this->gold = 0;
	this->smithingStones = 0;

	this->basicSword = "Basic Longsword";

	//Movement
	this->playerMovable = true;
}

AssetHandler::~AssetHandler()
{

}

//Core Functions

//Control Flow Functions
void AssetHandler::mainMenu()
{

}

//Misc Functions
void AssetHandler::statsText()
{
	playerTextElements[0].setString("LEVEL " + std::to_string(this->level));
	playerTextElements[1].setString("STRENGTH " + std::to_string(this->strength));
	playerTextElements[2].setString("FORTITUDE " + std::to_string(this->fortitude));
	playerTextElements[3].setString("VITALITY " + std::to_string(this->vitality));

	zinTextElements[0].setString("LEVEL " + std::to_string(this->zinLevel));
	zinTextElements[1].setString("RESOLVE " + std::to_string(this->zinResolve));
	zinTextElements[2].setString("PATIENCE " + std::to_string(this->zinPatience));
	zinTextElements[3].setString("RESILIENCE " + std::to_string(this->zinResilience));
}

void AssetHandler::printInventory()
{
	inventoryText.setString("[GENERAL ITEMS]\nGold: x" + std::to_string(this->gold) + "\nSmithing Stones: x"
		+ std::to_string(this->smithingStones) + "\n\n[EQUIPPED ITEMS]\n" + this->basicSword);
}