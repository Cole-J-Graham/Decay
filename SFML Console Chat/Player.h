#pragma once
class Player
{
private:

public:
	//Core modifiers
	int sanity;
	int sanityMax;

	//Leveling
	int level;
	float exp;
	float expNext;
	int sp;

	//Attributes
	int strength;
	int fortitude;
	int vitality;

	//Constructors & Destructors
	Player();
	~Player();
};

