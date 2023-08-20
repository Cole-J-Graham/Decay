#pragma once
#include<time.h>
#include<cstdlib>
#include<string>

class Player
{
private:

public:
	//Core modifiers
	int decay;
	int decayMax;

	//Leveling
	int level;
	int exp;
	int expNext;
	int sp;

	//Attributes
	int strength;
	int fortitude;
	int vitality;

	//Zin Leveling
	int zinLevel;
	int zinSp;
	int zinExp;
	int zinExpNext;

	//Zin Attributes
	int zinResolve;
	int zinPatience;
	int zinResilience;

	//Item Strength
	int swordPower;

	//Items
	int gold;
	int smithingStones;
	std::string basicSword;

	//Control Flow
	bool increase;

	//Constructors & Destructors
	Player();
	~Player();

	//Core Functions
	void combatReward();
};

