#ifndef COMBAT_H
#define COMBAT_H
#include"Sprites.h"
#include"Player.h"
#include"Animation.h"
#include"Moves.h"

class Combat : public Moves
{
private:
	//Move Values
	int valZero;
	int valOne;
	int valTwo;
	int valThree;
	int valFour;
	int valFive;

	//Attack Counters
	int attackCounter;
	int zinAttackCounter;
	int thomAttackCounter;

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
	bool initHostileSiward;

	//Hostile Decay Bools
	bool initHostileLimbSplitter;
	bool initHostileBurrower;
	bool initHostileChatterMouth;
	bool initHostileReclus;
	bool initHostileTendrilAlpha;
	bool initHostileSpade;

	//Combat Control Flow Bool
	bool turnPlayer;
	bool turnZin;
	bool turnThom;
	bool turnHostile;

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

	//Animation Control
	bool comTextRemoved;

public:
	//Constructors & Destructors
	Combat();
	~Combat();

	//Core Stat Functions
	void updateStats(Sprites& sprites, Player& player);
	void updateStatsZin(Player& player);
	void unlockMoves(Sprites& sprites, Player& player);

	//Core Combat Functions
	void combatLoop(sf::RenderWindow& window, Sprites& sprites, Player& player, Animation& animate);
	void initCombat(Sprites& sprites, Player& player, Animation& animate);
	void reInitCombat(Sprites& sprites);
	void playerDeath(Sprites& sprites);

	//Combat Functions
	void playerTurn(sf::RenderWindow& window, Sprites& sprites, Animation& animate);
	void zinTurn(Sprites& sprites, Animation& animate);
	void thomTurn(Sprites& sprites, Animation& animate);
	void hostileTurn(Sprites& sprites, Animation& animate);

	//Combat Pick Attacks
	void pickMove(sf::RenderWindow& window, Sprites& sprites);
	void pickMoveFunc(sf::RenderWindow& window, sf::RectangleShape& inputRect, int& counter, int& moveChar, int& moveVal);
	void playerSelectMove(Sprites& sprites, Animation& animate);
	void zinSelectMove(Sprites& sprites, Animation& animate);
	void thomSelectMove(Sprites& sprites, Animation& animate);

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
	void initSiward(Sprites& sprites);

	//Combat Init Decay Hostiles
	void initLimbSplitter(Sprites& sprites);
	void initBurrower(Sprites& sprites);
	void initChatterMouth(Sprites& sprites);
	void initReclus(Sprites& sprites);
	void initTendrilAlpha(Sprites& sprites);
	void initSpade(Sprites& sprites);
	void initRotBeast(Sprites& sprites);

	//Move Value Getters
	int& getValZero() { return this->valZero; };
	int& getValOne() { return this->valOne; };
	int& getValTwo() { return this->valTwo; };

	//Attack Counter Getters
	int& getAttackCounter() { return this->attackCounter; };
	int& getZinAttackCounter() { return this->zinAttackCounter; };
	int& getThomAttackCounter() { return this->thomAttackCounter; };

	void setAttackCounterInc() { this->attackCounter++; };
	void setZinAttackCounterInc() { this->zinAttackCounter++; };

	//Core Bool Getters
	bool& getInitCombatOnce() { return this->initCombatOnce; };
	bool& getReInitCombatOnce() { return this->reInitCombatOnce; };
	bool& getCombatEnd() { return this->combatEnd; };

	//Combat Control Flow Bool Getters
	bool& getTurnPlayer() { return this->turnPlayer; };
	bool& getTurnZin() { return this->turnZin; };
	bool& getTurnThom() { return this->turnThom; };
	bool& getTurnHostile() { return this->turnHostile; };

	bool& getPlayerAttack() { return this->playerAttack; };
	bool& getZinAttack() { return this->zinAttack; };
	bool& getHostileAttack() { return this->hostileAttack; };
	bool& getHostileAttackZin() { return this->hostileAttackZin; };

	//Move Selector Getters
	int& getPlayerPickMove() { return this->playerPickMove; };
	int& getZinPickMove() { return this->zinPickMove; };
	int& getThomPickMove() { return this->thomPickMove; };

	//Animation Control Getters
	bool& getComTextRemoved() { return this->comTextRemoved; };

	sf::Time combatTextElapsed;
	sf::Clock combatTextTime;
};

#endif

