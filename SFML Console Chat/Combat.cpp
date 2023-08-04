#include "Combat.h"

//Constructors & Destructors
Combat::Combat()
{
	//Hp
	this->playerHp = 50;
	this->playerHpMax = 50;
	this->zinHp = 35;
	this->zinHpMax = 35;

	//Zin Attributes
	this->zinLevel = 0;
	this->zinSp = 0;
	this->zinExp = 1000;
	this->zinExpNext = 50;

	this->zinResolve = 0;
	this->zinPatience = 0;
	this->zinResilience = 0;

	//Zin Moves
	this->zinSmite = 5;

	//Attack Counters
	this->attackCounter = 0;
	this->zinAttackCounter = 0;

	//Player Moves
	this->playerStrike = 5;

	//Hostile Stats
	this->hostileHp = 15;
	this->hostileHpMax = 15;

	//Hostile Moves
	this->hostileSlash = 5;

	//Core Bool
	this->initCombatOnce = false;
	this->reInitCombatOnce = false;

	//Combat Control Flow Bool
	this->turnPlayer = true;
	this->turnZin = false;
	this->turnHostile = false;

	this->playerAttack = false;
	this->zinAttack = false;
	this->hostileAttack = false;
	this->hostileAttackZin = false;
}

Combat::~Combat()
{

}

//Core Stat Functions
void Combat::updateStats(Player& player)
{
	this->playerStrike = 5 + player.strength;
	this->playerHp = 50 + player.vitality;
	this->playerHpMax = this->playerHp;
}

void Combat::updateStatsZin()
{
	this->zinSmite = 5 + this->zinResolve;
	this->zinHp = 35 + this->zinResilience;
	this->zinHpMax = this->zinHp;
}

//Core Combat Functions
void Combat::combatLoop(Assets& assets, Player& player)
{
	//Begin combat loop initialization
	if (initCombatOnce == false) {
		this->initCombat(assets, player);
		initCombatOnce = true;
	} //Reinitialize the combat loop for each pass
	else if (reInitCombatOnce == false) {
		this->reInitCombat(assets);
		reInitCombatOnce = true;
	}
	//Players turn
	this->playerTurn(assets);
	//Zin's Turn
	this->zinTurn(assets);
	//Check if hostile is dead. If so, end combat
	if (this->hostileHp <= 0) {
		assets.combatAssets = false;
		assets.text.setString("You have killed the abomination...");
	}
	//Hostiles turn
	this->hostileTurn(assets);
	//Check if player or Zin has died
	if (this->playerHp <= 0) {
		assets.text.setString("You have been left unconscious...");
	} 
	if (this->zinHp <= 0) {
		assets.text.setString("Zin has been left unconscious...");
	} 
	//Check if both the player and Zin have died
	if (this->playerHp <= 0 && zinHp <= 0) {
		assets.combatAssets = false;
		assets.text.setString("Your party has died...");
	}
}

void Combat::initCombat(Assets& assets, Player& player)
{
	this->updateStats(player);
	assets.text.setString("A combatant ambushes you! Pick your next step carefully...");
	assets.textElements[6].setString(assets.playerName + "     " + std::to_string(this->playerHp) + "/" + std::to_string(this->playerHpMax));
	assets.textElements[7].setString("Zin            " + std::to_string(this->zinHp) + "/" + std::to_string(this->zinHpMax));
	assets.textElements[8].setString("Abomination  " + std::to_string(this->hostileHp) + "/" + std::to_string(this->hostileHpMax));
	assets.zinInit = false; //Make usable again
	assets.zinCounter = 0; //Load Zins sprite with counter
	assets.spadeCounter = -1;//Reset Spade sprite switch case counter
	assets.spriteInit = false; //Uninitialize sprite border
	assets.combatAssets = true; //Utilize all combat assets
	assets.soundCombatStart.play(); //Play combat Sfx
}

void Combat::reInitCombat(Assets& assets)
{
	this->attackCounter = 0;
	this->zinAttackCounter = 0;
	assets.combatCounter = 0;
	assets.playerTurnAssets = true;
	assets.zinTurnAssets = false;
	this->playerAttack = false;
	this->hostileAttack = false;
	this->hostileAttackZin = false;
	this->turnPlayer = true;
	this->turnZin = false;
	this->turnHostile = false;
}

//Combat Functions
void Combat::playerTurn(Assets& assets)
{
	if (this->turnPlayer == true) {
		switch (this->attackCounter) {
		case 0:
			assets.text.setString("You plan your next move...");
			break;
		case 1:
			//Player Attacks Hostile
			if (this->playerAttack == false) {
				assets.soundCom.play();
				this->hostileHp -= this->playerStrike;
				assets.textElements[8].setString("Abomination  " + std::to_string(hostileHp) + "/" + std::to_string(hostileHpMax));
				assets.playerTurnAssets = false;
				this->playerAttack = true;
			}
			assets.text.setString("You strike the combatant! Click to continue...");
			break;
		case 2:
			this->turnPlayer = false;
			this->turnZin = true;
			break;
		}
	}
}

void Combat::zinTurn(Assets& assets)
{
	if (turnZin == true) {
		switch (this->zinAttackCounter) {
		case 0:
			assets.text.setString("Zin plans her next move...");
			assets.zinTurnAssets = true;
			break;
		case 1:
			//Zin Attacks Hostile
			if (this->zinAttack == false) {
				assets.soundCom.play();
				this->hostileHp -= this->zinSmite;
				assets.textElements[8].setString("Abomination  " + std::to_string(hostileHp) + "/" + std::to_string(hostileHpMax));
				assets.zinTurnAssets = false;
				this->zinAttack = true;
			}
			assets.text.setString("Zin smites the combatant! Click to continue...");
			break;
		case 2:
			this->turnZin = false;
			this->turnHostile = true;
			break;
		}
	}
}

void Combat::hostileTurn(Assets& assets)
{
	if (this->turnHostile == true) {
		//Hostile Attacks Player and Zin
		switch (assets.combatCounter) {
		case 0:
			if (this->hostileAttack == false) {
				this->playerHp -= this->hostileSlash;
				assets.soundCom.play();
				assets.textElements[6].setString(assets.playerName + "     " + std::to_string(playerHp) + "/" + std::to_string(playerHpMax));
				this->hostileAttack = true;
			}
			assets.text.setString("The hostile swings back! Click to continue...");
			break;
		case 1:
			if (this->hostileAttackZin == false) {
				this->zinHp -= this->hostileSlash;
				assets.soundCom.play();
				assets.textElements[7].setString("Zin            " + std::to_string(zinHp) + "/" + std::to_string(zinHpMax));
				this->hostileAttackZin = true;
			}
			assets.text.setString("The hostile swings at Zin! Click to continue...");
			break;
		case 2:
			this->reInitCombatOnce = false;
			break;
		}
	}
	
}