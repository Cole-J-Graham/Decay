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
	this->strengthZin = 1;
	this->fortitudeZin = 1;
	this->vitalityZin = 1;

	//Plasyer Moves
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
	this->playerAttack = false;
	this->hostileAttack = false;
	this->hostileAttackZin = false;

	this->updateStats();
}

Combat::~Combat()
{

}

//Core Stat Functions
void Combat::updateStats()
{
	this->playerStrike += player.strength;
}

//Core Combat Functions
void Combat::combatLoop(Assets& assets)
{
	//Begin combat loop initialization
	if (initCombatOnce == false) {
		this->initCombat(assets);
		initCombatOnce = true;
	} //Reinitialize the combat loop for each pass
	else if (reInitCombatOnce == false) {
		this->reInitCombat(assets);
		reInitCombatOnce = true;
	}
	//Players turn
	this->playerTurn(assets);
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

void Combat::initCombat(Assets& assets)
{
	assets.text.setString("A combatant ambushes you! Pick your next step carefully...");
	assets.playerNameText.setString(assets.playerName + "     " + std::to_string(playerHp) + "/" + std::to_string(playerHpMax));
	assets.zinText.setString("Zin            " + std::to_string(zinHp) + "/" + std::to_string(zinHpMax));
	assets.zinInit = false; //Make usable again
	assets.zinCounter = 0; //Load Zins sprite with counter
	assets.hostileNameText.setString("Abomination  " + std::to_string(hostileHp) + "/" + std::to_string(hostileHpMax));
	assets.spadeCounter = -1;//Reset Spade sprite switch case counter
	assets.spriteInit = false; //Uninitialize sprite border
	assets.combatAssets = true; //Utilize all combat assets
	//assets.soundCombatStart.play(); //Play combat Sfx
}

void Combat::reInitCombat(Assets& assets)
{
	assets.attackCounter = -1;
	assets.combatCounter = -1;
	assets.playerTurnAssets = true;
	this->playerAttack = false;
	this->hostileAttack = false;
	this->hostileAttackZin = false;
}

//Combat Functions
void Combat::playerTurn(Assets& assets)
{
	switch (assets.attackCounter) {
	case -1:
		assets.text.setString("You plan your next move...");
		break;
	case 1:
		//Player Attacks Hostile
		if (this->playerAttack == false) {
			assets.soundCom.play();
			this->hostileHp -= this->playerStrike;
			assets.hostileNameText.setString("Abomination  " + std::to_string(hostileHp) + "/" + std::to_string(hostileHpMax));
			assets.playerTurnAssets = false;
			this->playerAttack = true;
		}
		assets.text.setString("You strike the combatant! Click to continue...");
		break;
	case 2:
		//Player Flees from hostile
		assets.text.setString("You run away like the coward you are...");
		assets.combatAssets = false;
		break;
	}
}

void Combat::hostileTurn(Assets& assets)
{
	//Hostile Attacks Player
	switch (assets.combatCounter) {
	case 0:
		if (this->hostileAttack == false) {
			this->playerHp -= this->hostileSlash;
			assets.soundCom.play();
			assets.playerNameText.setString(assets.playerName + "     " + std::to_string(playerHp) + "/" + std::to_string(playerHpMax));
			this->hostileAttack = true;
		}
		assets.text.setString("The hostile swings back! Click to continue...");
		break;
	case 1:
		if (this->hostileAttackZin == false) {
			this->zinHp -= this->hostileSlash;
			assets.soundCom.play();
			assets.zinText.setString("Zin            " + std::to_string(zinHp) + "/" + std::to_string(zinHpMax));
			this->hostileAttackZin = true;
		}
		assets.text.setString("The hostile swings at Zin! Click to continue...");
		break; 
	case 2:
		this->reInitCombatOnce = false;
		break;
	}
}