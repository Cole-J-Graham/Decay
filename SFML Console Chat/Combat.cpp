#include "Combat.h"

//Constructors & Destructors
Combat::Combat()
{
	//Hp
	this->playerHp = 50;
	this->playerHpMax = 50;
	this->zinHp = 35;
	this->zinHpMax = 35;

	//Zin Moves
	this->zinSmite = 5;
	this->zinMend = 5;

	//Attack Counters
	this->attackCounter = 0;
	this->zinAttackCounter = 0;

	//Player Moves
	this->playerStrike = 5;
	this->playerGuard = 1;

	//Hostile Stats
	this->hostileHp = 50;
	this->hostileHpMax = 50;

	//Hostile Moves
	this->hostileSlash = 5;

	//Core Bool
	this->initCombatOnce = false;
	this->reInitCombatOnce = false;

	//Combat Control Flow Bool
	this->turnPlayer = true;
	this->turnZin = false;
	this->turnHostile = false;
	this->zinGuarded = false;

	this->playerAttack = false;
	this->zinAttack = false;
	this->hostileAttack = false;
	this->hostileAttackZin = false;

	//Move Selectors
	this->playerPickMove = -1;
	this->zinPickMove = 0;
}

Combat::~Combat()
{

}

//Core Stat Functions
void Combat::updateStats(Assets& assets, Player& player)
{
	this->playerStrike = 5 + player.strength + player.swordPower;
	this->playerHp = 50 + player.vitality;
	player.decayMax = 25 + player.fortitude;
	this->playerHpMax = this->playerHp;
	this->updateMoves(assets, player);
}

void Combat::updateStatsZin(Player& player)
{
	this->zinSmite = 5 + player.zinResolve;
	this->zinHp = 35 + player.zinResilience;
	this->zinHpMax = this->zinHp;
}

void Combat::updateMoves(Assets& assets, Player& player)
{
	if (player.level >= 15) {
		//Unlock Guard
		assets.combatPlayerMoves = 1;
		assets.text.setString("Move 'Guard' learned!");
	}
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
		player.combatReward();
		assets.text.setString("You have killed the abomination... Player Exp increased " + std::to_string(player.exp) + "/" + std::to_string(player.expNext));
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
	this->updateStats(assets, player);
	assets.text.setString("A combatant ambushes you! Pick your next step carefully...");
	assets.textElements[6].setString(assets.playerName + "     " + std::to_string(this->playerHp) + "/" + std::to_string(this->playerHpMax));
	assets.textElements[7].setString("Zin            " + std::to_string(this->zinHp) + "/" + std::to_string(this->zinHpMax));
	assets.textElements[8].setString("Abomination  " + std::to_string(this->hostileHp) + "/" + std::to_string(this->hostileHpMax));
	assets.playerCounter = 0; //Load Player sprite with counter
	assets.zinCounter = 0; //Load Zins sprite with counter
	assets.playerInit = false; //Make usable again
	assets.zinInit = false; //Make usable again           
	assets.spadeCounter = -1;//Reset Spade sprite switch case counter
	assets.combatAssets = true; //Utilize all combat assets
	assets.soundCombatStart.play(); //Play combat Sfx
	assets.initMap = false; //Hide the map if its open
	assets.initStats = false; //Hide stats if open
	assets.initInventory = false; //Hide inventory if open
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
	this->zinGuarded = false;
	this->zinAttack = false;
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
				this->playerSelectMove(assets);
				this->playerAttack = true;
			}
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
				this->zinSelectMove(assets);
				this->zinAttack = true;
			}
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
			if (this->zinGuarded == false && this->hostileAttackZin == false) {
				this->zinHp -= this->hostileSlash;
				assets.soundCom.play();
				assets.textElements[7].setString("Zin            " + std::to_string(zinHp) + "/" + std::to_string(zinHpMax));
				assets.text.setString("The hostile swings at Zin! Click to continue...");
				this->hostileAttackZin = true;
			}
			else if (this->zinGuarded == true && this->hostileAttackZin == false) {
				assets.soundGuarded.play();
				assets.text.setString("You block Zin from the strike! Click to continue...");
				this->hostileAttackZin = true;
			}
			break;
		case 2:
			this->reInitCombatOnce = false;
			break;
		}
	}
	
}

//Combat Pick Attacks
void Combat::playerSelectMove(Assets& assets)
{
	switch (this->playerPickMove) {
	case 0:
		//Strike the hostile
		assets.soundSlash.play();
		this->hostileHp -= this->playerStrike;
		assets.textElements[8].setString("Abomination  " + std::to_string(hostileHp) + "/" + std::to_string(hostileHpMax));
		assets.playerTurnAssets = false;
		assets.text.setString("You strike the combatant! Click to continue...");
		break;
	case 1:
		//Guard Zin
		assets.soundGuard.play();
		assets.playerTurnAssets = false;
		this->zinGuarded = true;
		assets.text.setString("You plant yourself in between Zin and the enemy! Click to continue...");
		break;
	}
}

void Combat::zinSelectMove(Assets& assets)
{
	switch (this->zinPickMove) {
	case 0:
		//Smite the hostile
		assets.soundSmite.play();
		this->hostileHp -= this->zinSmite;
		assets.textElements[8].setString("Abomination  " + std::to_string(hostileHp) + "/" + std::to_string(hostileHpMax));
		assets.zinTurnAssets = false;
		assets.text.setString("Zin smites the combatant! Click to continue...");
		break;
	case 1:
		//Mend party
		assets.soundMend.play();
		if (this->playerHp < this->playerHpMax) {
			this->playerHp += this->zinMend;
		}
		if (this->zinHp < this->zinHpMax) {
			this->zinHp += this->zinMend;
		}
		assets.textElements[6].setString(assets.playerName + "     " + std::to_string(playerHp) + "/" + std::to_string(playerHpMax));
		assets.textElements[7].setString("Zin            " + std::to_string(zinHp) + "/" + std::to_string(zinHpMax));
		assets.zinTurnAssets = false;
		assets.text.setString("Zin heals the party! Click to continue...");
		break;
	}
	
}