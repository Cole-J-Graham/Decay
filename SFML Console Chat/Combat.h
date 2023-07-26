#ifndef COMBAT_H
#define COMBAT_H
#include"Assets.h"
#include"Player.h"

class Combat
{
private:

public:
	Player player;

	//Hp
	int playerHp;
	int playerHpMax;
	int zinHp;
	int zinHpMax;

	//Zin Attributes
	int strengthZin;
	int fortitudeZin;
	int vitalityZin;


	//Player Moves
	int playerStrike;

	//Hostile Stats
	int hostileHp;
	int hostileHpMax;

	//Hostile Moves
	int hostileSlash;

	//Core Bool
	bool initCombatOnce;
	bool reInitCombatOnce;

	//Combat Control Flow Bool
	bool playerAttack;
	bool hostileAttack;
	bool hostileAttackZin;

	//Constructors & Destructors
	Combat();
	~Combat();

	//Core Stat Functions
	void updateStats();

	//Core Combat Functions
	void combatLoop(Assets& assets);
	void initCombat(Assets& assets);
	void reInitCombat(Assets& assets);

	//Combat Functions
	void playerTurn(Assets& assets);
	void hostileTurn(Assets& assets);
};

#endif

