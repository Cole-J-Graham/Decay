#include "Player.h"

//Constructors & Destructors
Player::Player()
{
	//Core Modifiers
	this->decay = 0;
	this->decayMax = 25;

	//Leveling
	this->level = 0;
	this->exp = 1000;
	this->expNext = 100;
	this->sp = 5;

	//Attributes
	this->strength = 0;
	this->fortitude = 0;
	this->vitality = 0;

	//Zin Leveling
	this->zinLevel = 0;
	this->zinSp = 0;
	this->zinExp = 1000;
	this->zinExpNext = 50;

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

	//Control Flow
	this->increase = true;
}

Player::~Player()
{

}

//Core Functions
void Player::combatReward()
{
	if (this->increase == true) {
		this->exp += 100 + rand() % 10 + clock() / 95 - 100;
		this->zinExp += 100 + rand() % 15;
		this->increase = false;
	}
}