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

	//Zin Moves
	int zinSmite;
	int zinMend;

	//Attack Counters
	int attackCounter;
	int zinAttackCounter;

	//Player Moves
	int playerStrike;
	int playerGuard;

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
	bool zinGuarded;

	bool playerAttack;
	bool zinAttack;
	bool hostileAttack;
	bool hostileAttackZin;

	//Move Selectors
	int playerPickMove;
	int zinPickMove;

	//Constructors & Destructors
	Combat();
	~Combat();

	//Core Stat Functions
	void updateStats(Assets& assets, Player& player);
	void updateStatsZin(Player& player);
	void updateMoves(Assets& assets, Player& player);

	//Core Combat Functions
	void combatLoop(Assets& assets, Player& player);
	void initCombat(Assets& assets, Player& player);
	void reInitCombat(Assets& assets);

	//Combat Functions
	void playerTurn(Assets& assets);
	void zinTurn(Assets& assets);
	void hostileTurn(Assets& assets);

	//Combat Pick Attacks
	void playerSelectMove(Assets& assets);
	void zinSelectMove(Assets& assets);
};

#endif

