#ifndef COMBAT_H
#define COMBAT_H
#include"Assets.h"
#include"Player.h"

class Combat
{
private:

public:

	//Hp
	int playerHp;
	int playerHpMax;
	int zinHp;
	int zinHpMax;

	//Zin Attributes
	int zinLevel;
	int zinSp;
	int zinExp;
	int zinExpNext;

	int zinResolve;
	int zinPatience;
	int zinResilience;

	//Zin Moves
	int zinSmite;

	//Attack Counters
	int attackCounter;
	int zinAttackCounter;

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
	bool turnPlayer;
	bool turnZin;
	bool turnHostile;

	bool playerAttack;
	bool zinAttack;
	bool hostileAttack;
	bool hostileAttackZin;

	//Constructors & Destructors
	Combat();
	~Combat();

	//Core Stat Functions
	void updateStats(Player& player);
	void updateStatsZin();

	//Core Combat Functions
	void combatLoop(Assets& assets, Player& player);
	void initCombat(Assets& assets, Player& player);
	void reInitCombat(Assets& assets);

	//Combat Functions
	void playerTurn(Assets& assets);
	void zinTurn(Assets& assets);
	void hostileTurn(Assets& assets);
};

#endif

