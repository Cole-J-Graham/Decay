#include "Player.h"

//Constructors & Destructors
Player::Player()
{
	//Core Modifiers
	this->sanity = 50;
	this->sanityMax = 100;

	//Leveling
	this->level = 1;
	this->exp = 1000;
	this->expNext = 100;
	this->sp = 5;

	//Attributes
	this->strength = 1;
	this->fortitude = 1;
	this->vitality = 1;
}

Player::~Player()
{

}