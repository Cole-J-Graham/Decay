#ifndef COMBAT_H
#define COMBAT_H
#include"Sprites.h"
#include"Player.h"
#include"Animation.h"

class Combat
{
private:
	//Hp
	int playerHp;
	int playerHpMax;
	int zinHp;
	int zinHpMax;
	int thomHp;
	int thomHpMax;

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
	int thomAttackCounter;

	//Move Unlocks
	bool unlockedGuard;

	//Core Bool
	bool initCombatOnce;
	bool reInitCombatOnce;
	bool combatEnd;

	//Hostile Forest Bools
	bool initHostileWolf;
	bool initHostileWalker;
	bool initHostileKnight;
	bool initHostileTreeMimic;
	bool initHostileLostNun;
	bool initHostileDecapod;

	//Hostile Castle Bools
	bool initHostileJester;
	bool initHostileWallMimic;
	bool initHostileLostKnight;
	bool initHostilePhantom;
	bool initHostileEater;

	//Hostile Decay Bools
	bool initHostileLimbSplitter;
	bool initHostileBurrower;
	bool initHostileChatterMouth;
	bool initHostileReclus;
	bool initHostileTendrilAlpha;

	//Combat Control Flow Bool
	bool turnPlayer;
	bool turnZin;
	bool turnThom;
	bool turnHostile;
	bool zinGuarded;

	bool playerAttack;
	bool zinAttack;
	bool thomAttack;
	bool hostileAttack;
	bool hostileAttackZin;
	bool hostileAttackThom;

	bool playerDead;
	bool zinDead;
	bool thomDead;

	//Move Selectors
	int playerPickMove;
	int zinPickMove;
	int thomPickMove;

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
	void updateStats(Sprites& sprites, Player& player);
	void updateStatsZin(Player& player);
	void updateMoves(Sprites& sprites, Player& player);

	//Core Combat Functions
	void combatLoop(Sprites& sprites, Player& player, Animation& animate);
	void initCombat(Sprites& sprites, Player& player);
	void reInitCombat(Sprites& sprites);
	void playerDeath(Sprites& sprites);

	//Combat Functions
	void playerTurn(Sprites& sprites);
	void zinTurn(Sprites& sprites);
	void thomTurn(Sprites& sprites);
	void hostileTurn(Sprites& sprites);

	//Combat Pick Attacks
	void playerSelectMove(Sprites& sprites);
	void zinSelectMove(Sprites& sprites);
	void thomSelectMove(Sprites& sprites);

	//Combat Init Forest Hostiles
	void initWolf(Sprites& sprites);
	void initDecayWalker(Sprites& sprites);
	void initHostileTree(Sprites& sprites);
	void initDecayKnight(Sprites& sprites);
	void initLostNun(Sprites& sprites);
	void initDecapod(Sprites& sprites);
	void initHazeDemon(Sprites& sprites);

	//Combat Init Castle Hostiles
	void initCourtJester(Sprites& sprites);
	void initWallMimic(Sprites& sprites);
	void initLostKnight(Sprites& sprites);
	void initPhantom(Sprites& sprites);
	void initSkinEater(Sprites& sprites);

	//Combat Init Decay Hostiles
	void initLimbSplitter(Sprites& sprites);
	void initBurrower(Sprites& sprites);
	void initChatterMouth(Sprites& sprites);
	void initReclus(Sprites& sprites);
	void initTendrilAlpha(Sprites& sprites);

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
	int& getThomAttackCounter() { return this->thomAttackCounter; };

	void setAttackCounterInc() { this->attackCounter++; };
	void setZinAttackCounterInc() { this->zinAttackCounter++; };

	//Move Unlock Bools
	bool& getUnlockedGuard() { this->unlockedGuard; };

	//Core Bool Getters
	bool& getInitCombatOnce() { return this->initCombatOnce; };
	bool& getReInitCombatOnce() { return this->reInitCombatOnce; };
	bool& getCombatEnd() { return this->combatEnd; };

	//Combat Control Flow Bool Getters
	bool& getTurnPlayer() { return this->turnPlayer; };
	bool& getTurnZin() { return this->turnZin; };
	bool& getTurnThom() { return this->turnThom; };
	bool& getTurnHostile() { return this->turnHostile; };
	bool& getZinGuarded() { return this->zinGuarded; };

	bool& getPlayerAttack() { return this->playerAttack; };
	bool& getZinAttack() { return this->zinAttack; };
	bool& getHostileAttack() { return this->hostileAttack; };
	bool& getHostileAttackZin() { return this->hostileAttackZin; };

	//Move Selector Getters
	int& getPlayerPickMove() { return this->playerPickMove; };
	int& getZinPickMove() { return this->zinPickMove; };
	int& getThomPickMove() { return this->thomPickMove; };
};

#endif

