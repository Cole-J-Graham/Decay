#include "Player.h"

//Constructors & Destructors
Player::Player()
{
	//Core Modifiers
	this->sanity = 50;
	this->sanityMax = 100;

	//Leveling
	this->level = 0;
	this->exp = 1000;
	this->expNext = 100;
	this->sp = 5;

	//Attributes
	this->strength = 0;
	this->fortitude = 0;
	this->vitality = 0;
}

Player::~Player()
{

}