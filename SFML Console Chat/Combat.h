#ifndef COMBAT_H
#define COMBAT_H
#include"Assets.h"
#include"Player.h"

class Combat
{
private:
	//Hp
	int playerHp;
	int playerHpMax;
	int zinHp;
	int zinHpMax;

	//Hostile Stats
	int hostileHp;
	int hostileHpMax;

	//Player Moves
	int playerStrike;
	int playerGuard;
	int decayedBlade;

	//Zin Moves
	int zinSmite;
	int zinMend;
	int zinVengeance;

	//Hostile Moves
	int hostileStrike;

	//Attack Counters
	int attackCounter;
	int zinAttackCounter;

	//Move Unlocks
	bool unlockedGuard;

	//Core Bool
	bool initCombatOnce;
	bool reInitCombatOnce;

	//Hostile Bool
	bool initHostileWolf;
	bool initHostileWalker;

	//Combat Control Flow Bool
	bool turnPlayer;
	bool turnZin;
	bool turnHostile;
	bool zinGuarded;

	bool playerAttack;
	bool zinAttack;
	bool hostileAttack;
	bool hostileAttackZin;

	bool playerDead;
	bool zinDead;

	//Move Selectors
	int playerPickMove;
	int zinPickMove;

	//Init Strings
	std::string playerTurnText;
	std::string zinTurnText;

	std::string hostileNameNoSpc;
	std::string hostileName;
	std::string hostileEncounterText;
	std::string hostileAtkPlayerText;
	std::string hostileAtkZinText;
	std::string hostileAtkZinBlkText;

	std::string playerSlashAtkText;
	std::string playerGuardAtkText;
	std::string playerDecayAtkText;

	std::string zinSmiteAtkText;
	std::string zinMendAtkText;
	std::string zinVengeanceAtkText;

public:

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
	void playerDeath(Assets& assets);

	//Combat Functions
	void playerTurn(Assets& assets);
	void zinTurn(Assets& assets);
	void hostileTurn(Assets& assets);

	//Combat Pick Attacks
	void playerSelectMove(Assets& assets);
	void zinSelectMove(Assets& assets);

	//Combat Init Hostile
	void initWolf(Assets& assets);
	void initDecayWalker(Assets& assets);

	//Hp Getters
	int& getPlayerHp() { return this->playerHp; };
	int& getPlayerHpMax() { return this->playerHpMax; };
	int& getZinHp() { return this->zinHp; };
	int& getZinHpMax() { return this->zinHpMax; };

	//Hostile Getters
	int& getHostileHp() { return this->hostileHp; };
	int& getHostileHpMax() { return this->hostileHpMax; };

	//Player Move Getters
	int& getPlayerStrike() { return this->playerStrike; };
	int& getPlayerGuard() { return this->playerGuard; };

	//Zin Move Getters
	int& getZinSmite() { return this->zinSmite; };
	int& getZinMend() { return this->zinMend; };
	int& getZinVengeance() { return this->zinVengeance; };

	//Hostile Move Getters
	int& getHostileSlash() { return this->hostileStrike; };

	//Attack Counter Getters
	int& getAttackCounter() { return this->attackCounter; };
	int& getZinAttackCounter() { return this->zinAttackCounter; };

	void setAttackCounterInc() { this->attackCounter++; };
	void setZinAttackCounterInc() { this->zinAttackCounter++; };

	//Move Unlock Bools
	bool& getUnlockedGuard() { this->unlockedGuard; };

	//Core Bool Getters
	bool& getInitCombatOnce() { return this->initCombatOnce; };
	bool& getReInitCombatOnce() { return this->reInitCombatOnce; };

	//Combat Control Flow Bool Getters
	bool& getTurnPlayer() { return this->turnPlayer; };
	bool& getTurnZin() { return this->turnZin; };
	bool& getTurnHostile() { return this->turnHostile; };
	bool& getZinGuarded() { return this->zinGuarded; };

	bool& getPlayerAttack() { return this->playerAttack; };
	bool& getZinAttack() { return this->zinAttack; };
	bool& getHostileAttack() { return this->hostileAttack; };
	bool& getHostileAttackZin() { return this->hostileAttackZin; };

	//Move Selector Getters
	int& getPlayerPickMove() { return this->playerPickMove; };
	int& getZinPickMove() { return this->zinPickMove; };
};

#endif

