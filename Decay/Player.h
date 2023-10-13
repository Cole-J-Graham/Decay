#pragma once
#include<time.h>
#include<cstdlib>
#include<string>
#include"Assets.h"

class Player
{
private:
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

public:

	//Constructors & Destructors
	Player();
	~Player();

	//Core Functions
	void combatReward();
	void statsText(Assets& assets);
	void printInventory(Assets& assets);

	//Core Modifier Getters
	int& getDecay() { return this->decay; };
	int& getDecayMax() { return this->decayMax; };

	//Leveling Getters
	int& getLevel() { return this->level; };
	int& getExp() { return this->exp; };
	int& getExpNext() { return this->expNext; };
	int& getSp() { return this->sp; };

	//Leveling Setters
	void setLevelInc() { this->level++; };
	void setSpInc() { this->sp++; };
	void setSpDec() { this->sp--; };

	//Attribute Getters
	int& getStrength() { return this->strength; };
	int& getFortitude() { return this->fortitude; };
	int& getVitality() { return this->vitality; };

	//Attribute Setters
	void setStrengthInc() { this->strength++; };
	void setFortitudeInc() { this->fortitude++; };
	void setVitalityInc() { this->vitality++; };

	//Zin Leveling Getters
	int& getZinLevel() { return this->zinLevel; };
	int& getZinSp() { return this->zinSp; };
	int& getZinExp() { return this->zinExp; };
	int& getZinExpNext() { return this->zinExpNext; };

	//Zin Leveling Setters
	void setZinLevelInc() { this->zinLevel++; };
	void setZinSpInc() { this->zinSp++; };
	void setZinSpDec() { this->zinSp--; };

	//Zin Attribute Getters
	int& getZinResolve() { return this->zinResolve; };
	int& getZinPatience() { return this->zinPatience; };
	int& getZinResilience() { return this->zinResilience; };

	//Zin Attribute Setters
	void setZinResolveInc() { this->zinResolve++; };
	void setZinPatienceInc() { this->zinPatience++; };
	void setZinResilienceInc() { this->zinResilience++; };

	//Item Strength Getters
	int& getSwordPower() { return this->swordPower; };

	//Item Strength Setters
	void setSwordPowerInc() { this->swordPower++; };

	//Item Getters
	int& getGold() { return this->gold; };
	int& getSmithingStones() { return this->smithingStones; };

	std::string& getBasicSword() { return this->basicSword; };

	//Item Setters
	void setSmithingStonesDec() { this->smithingStones--; };

	//Control Flow
	bool& getIncease() { return this->increase; };
	
};

