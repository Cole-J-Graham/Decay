#ifndef MOVES_H
#define MOVES_H
#include"Sprites.h"
#include"Animation.h"

class Moves
{
private:	
	//Hp
	int playerHp;
	int playerHpMax;
	int playerDef;
	int playerAtk;

	int zinHp;
	int zinHpMax;
	int zinDef;
	int zinAtk;

	int thomHp;
	int thomHpMax;
	int thomDef;

	int hostileHp;
	int hostileHpMax;

	//Player Moves
	int playerStrike;
	int playerGuard;
	int decayedBlade;
	int heftyBlowDmg;
	int decaySynergyDmg;
	int decaySynergyDef;
	int ironWallDef;

	//Zin Moves
	int zinSmite;
	int zinMend;
	int zinVengeance;
	int zinBlaze;
	int zinFocus;
	int zinCrimson;

	//Thom Moves
	int enragedAtk;
	int enraged;
	bool thomEnraged;

	//Hostile Moves
	int hostileStrike;

	//Move Control Flow Bools
	bool zinGuarded;
	bool playerGuarded;

	bool playerFatigue;
	int fatigued;
	bool zinFatigue;

	//Animation Control
	bool firstAttack;

	//Init Strings
	std::string playerTurnText;
	std::string zinTurnText;

	std::string hostileNameNoSpc;
	std::string hostileName;
	std::string hostileEncText;
	std::string hostileAtkPlayerText;
	std::string hostileAtkZinText;
	std::string hostileAtkZinBlkText;
	std::string hostileAtkPlayerBlkText;

	std::string playerSlashAtkText;
	std::string playerGuardAtkText;
	std::string playerDecayAtkText;
	std::string playerHeftyAtkText;
	std::string playerSynergyAtkText;
	std::string playerIronWallAtkText;

	std::string zinSmiteAtkText;
	std::string zinMendAtkText;
	std::string zinVengeanceAtkText;
	std::string zinBlazeAtkText;
	std::string zinFocusAtkText;
	std::string zinCrimsonAtkText;

	std::string thomBarrierAtkText;
	std::string thomEnragedAtkText;

public:
	//Constructors and Destructors
	Moves();
	~Moves();

	//Player Moves
	void slash(Sprites& sprites, Animation& animate);
	void guard(Sprites& sprites, Animation& animate);
	void decayBlade(Sprites& sprites, Animation& animate);
	void heftyBlow(Sprites& sprites, Animation& animate);
	void decaySynergy(Sprites& sprites, Animation& animate);
	void ironWall(Sprites& sprites, Animation& animte);

	//Zin Moves
	void smite(Sprites& sprites, Animation& animate);
	void mend(Sprites& sprites, Animation& animate);
	void vengeance(Sprites& sprites, Animation& animate);
	void hellBlaze(Sprites& sprites, Animation& animate);
	void focusHeal(Sprites& sprites, Animation& animate);
	void crimsonFlames(Sprites& sprites, Animation& animate);

	//Thom Moves
	void barrier(Sprites& sprites, Animation& animate);
	void enrage(Sprites& sprites, Animation& animate);

	//Hostile Moves


	//Hp Getters
	int& getPlayerHp() { return this->playerHp; };
	int& getPlayerHpMax() { return this->playerHpMax; };
	int& getZinHp() { return this->zinHp; };
	int& getZinHpMax() { return this->zinHpMax; };
	int& getZinDef() { return this->zinDef; };
	int& getThomHp() { return this->thomHp; };
	int& getThomHpMax() { return this->thomHpMax; };

	//Hostile Getters
	int& getHostileHp() { return this->hostileHp; };
	int& getHostileHpMax() { return this->hostileHpMax; };
	int& getHostileStrike() { return this->hostileStrike; };

	//Player Move Getters
	int& getPlayerStrike() { return this->playerStrike; };
	int& getPlayerGuard() { return this->playerGuard; };
	int& getPlayerDecayedBlade() { return this->decayedBlade; };
	int& getPlayerHeftyBlow() { return this->heftyBlowDmg; };
	int& getPlayerDecayingSynDmg() { return this->decaySynergyDmg; };
	int& getPlayerDecayingSynDef() { return this->decaySynergyDef; };

	//Zin Move Getters
	int& getZinSmite() { return this->zinSmite; };
	int& getZinMend() { return this->zinMend; };
	int& getZinVengeance() { return this->zinVengeance; };
	int& getZinBlaze() { return this->zinBlaze; };
	int& getZinFocus() { return this->zinFocus; };
	int& getCrimsonFlames() { return this->zinCrimson; };
	int& getIronWall() { return this->ironWallDef; };
	
	//Thom Move Getters
	bool& getThomEnraged() { return this->thomEnraged; };
	int& getEnraged() { return this->enraged; };

	//Hostile Move Getters
	int& getHostileSlash() { return this->hostileStrike; };

	//Move Control Flow Bool Getters
	bool& getZinGuarded() { return this->zinGuarded; };
	bool& getPlayerGuarded() { return this->playerGuarded; };

	bool& getPlayerFatigue() { return this->playerFatigue; };
	bool& getZinFatigue() { return this->zinFatigue; };
	int& getFatigued() { return this->fatigued; };

	//Animation Flow Getters
	bool& getFirstAttack() { return this->firstAttack; };

	//Init String Getters
	std::string& getPlayerTurnText() { return this->playerTurnText; };
	std::string& getZinTurnText() { return this->zinTurnText; };

	std::string& getHostileNameNoSpc() { return this->hostileNameNoSpc; };
	std::string& getHostileName() { return this->hostileName; };
	std::string& getHostileEncText() { return this->hostileEncText; };
	std::string& getHostileAtkPlayerText() { return this->hostileAtkPlayerText; };
	std::string& getHostileAtkZinText() { return this->hostileAtkZinText; };
	std::string& getHostileAtkZinBlkText() { return this->hostileAtkZinBlkText; };
	std::string& getHostileAtkPlayerBlkText() { return this->hostileAtkPlayerBlkText; };

	std::string& getPlayerSlashAtkText() { return this->playerSlashAtkText; };
	std::string& getPlayerGuardAtkText() { return this->playerGuardAtkText; };
	std::string& getPlayerDecayAtkText() { return this->playerDecayAtkText; };

	std::string& getZinSmiteAtkText() { return this->zinSmiteAtkText; };
	std::string& getZinMendAtkText() { return this->zinMendAtkText; };
	std::string& getZinVengeanceAtkText() { return this->zinVengeanceAtkText; };

	std::string& getThomBarrierAtkText() { return this->thomBarrierAtkText; };
	std::string& getThomEnragedAtkText() { return this->thomEnragedAtkText; };

#endif
};

