#pragma once
#include"Moves.h"
#include"Animation.h"

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
	bool initHostileHazeDemon;

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
	bool initHostileRotBeast;

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

	//Combat Rewards
	bool increase;
	int expGain;

	//Animation Control
	bool comTextRemoved;

	//Music Bools
	bool replayMusic;

public:
	//Constructors & Destructors
	Combat();
	~Combat();

	//Core Stat Functions
	void updateStats();
	void unlockMoves();
	void combatReward();

	//Core Combat Functions
	void combatLoop(sf::RenderWindow& window, Animation& animate);
	void initCombat();
	void reInitCombat();
	void playerDeath();

	//Combat Functions
	void playerTurn(sf::RenderWindow& window, Animation& animate);
	void zinTurn(Animation& animate);
	void thomTurn(Animation& animate);
	void hostileTurn(Animation& animate);

	//Combat Pick Attacks
	void pickMove(sf::RenderWindow& window);
	void pickMoveFunc(sf::RenderWindow& window, sf::RectangleShape& inputRect, int& counter, int& moveChar, int& moveVal);
	void playerSelectMove(Animation& animate);
	void zinSelectMove(Animation& animate);
	void thomSelectMove(Animation& animate);

	//Combat Init Forest Hostiles
	void initWolf();
	void initDecayWalker();
	void initHostileTree();
	void initDecayKnight();
	void initLostNun();
	void initDecapod();
	void initHazeDemon();

	//Combat Init Castle Hostiles
	void initCourtJester();
	void initWallMimic();
	void initLostKnight();
	void initPhantom();
	void initSkinEater();
	void initSiward();

	//Combat Init Decay Hostiles
	void initLimbSplitter();
	void initBurrower();
	void initChatterMouth();
	void initReclus();
	void initTendrilAlpha();
	void initSpade();
	void initRotBeast();

	//Music Functions
	void stopComTrack(sf::Music& comTrack, sf::Music& track) {
		if (this->combatEnd && !this->replayMusic) {
			comTrack.stop();
			track.play();
			this->replayMusic = true;
		}
	}

	//Move Value Getters
	int& getValZero() { return this->valZero; };
	int& getValOne() { return this->valOne; };
	int& getValTwo() { return this->valTwo; };
	int& getValThree() { return this->valThree; };
	int& getValFour() { return this->valFour; };
	int& getValFive() { return this->valFive; };

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

	bool& getInitHostileWolf() { return this->initHostileWolf; };
	bool& getInitHostileWalker() { return this->initHostileWalker; };
	bool& getInitHostileKnight() { return this->initHostileKnight; };
	bool& getInitHostileTreeMimic() { return this->initHostileTreeMimic; };
	bool& getInitHostileLostNun() { return this->initHostileLostNun; };
	bool& getInitHostileDecapod() { return this->initHostileDecapod; };

	bool& getInitHostileJester() { return this->initHostileJester; };
	bool& getInitHostileWallMimic() { return this->initHostileWallMimic; };
	bool& getInitHostileLostKnight() { return this->initHostileLostKnight; };
	bool& getInitHostilePhantom() { return this->initHostilePhantom; };
	bool& getInitHostileEater() { return this->initHostileEater; };
	bool& getInitHostileSiward() { return this->initHostileSiward; };

	bool& getInitHostileLimbSplitter() { return this->initHostileLimbSplitter; };
	bool& getInitHostileBurrower() { return this->initHostileBurrower; };
	bool& getInitHostileChatterMouth() { return this->initHostileChatterMouth; };
	bool& getInitHostileReclus() { return this->initHostileReclus; };
	bool& getInitHostileTendrilAlpha() { return this->initHostileTendrilAlpha; };
	bool& getInitHostileSpade() { return this->initHostileSpade; };

	bool& getPlayerAttack() { return this->playerAttack; };
	bool& getZinAttack() { return this->zinAttack; };
	bool& getThomAttack() { return this->thomAttack; };
	bool& getHostileAttack() { return this->hostileAttack; };
	bool& getHostileAttackZin() { return this->hostileAttackZin; };
	bool& getHostileAttackThom() { return this->hostileAttackThom; };

	bool& getPlayerDead() { return this->playerDead; };
	bool& getZinDead() { return this->zinDead; };
	bool& getThomDead() { return this->thomDead; };

	//Move Selector Getters
	int& getPlayerPickMove() { return this->playerPickMove; };
	int& getZinPickMove() { return this->zinPickMove; };
	int& getThomPickMove() { return this->thomPickMove; };

	//Animation Control Getters
	bool& getComTextRemoved() { return this->comTextRemoved; };

	//Comabt Reward Getters
	bool& getIncease() { return this->increase; };

	//Sound Getters
	bool& getReplayMusic() { return this->replayMusic; };


	sf::Time combatTextElapsed;
	sf::Clock combatTextTime;
};
