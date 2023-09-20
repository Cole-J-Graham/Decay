#include "Combat.h"

//Constructors & Destructors
Combat::Combat()
{
	//Hp
	this->playerHp = 50;
	this->playerHpMax = 50;
	this->zinHp = 35;
	this->zinHpMax = 35;

	//Hostile Stats
	this->hostileHp = 50;
	this->hostileHpMax = 50;

	//Player Moves
	this->playerStrike = 5;
	this->playerGuard = 1;
	this->decayedBlade = 10;

	//Zin Moves
	this->zinSmite = 5;
	this->zinMend = 5;
	this->zinVengeance = 1;

	//Hostile Moves
	this->hostileStrike = 0;

	//Attack Counters
	this->attackCounter = 0;
	this->zinAttackCounter = 0;

	//Move Unlock Bools
	this->unlockedGuard = false;

	//Core Bool
	this->initCombatOnce = false;
	this->reInitCombatOnce = false;

	//Hostile Bool
	this->initHostileWolf = false;
	this->initHostileWalker = false;
	this->initHostileKnight = false;

	//Combat Control Flow Bool
	this->turnPlayer = true;
	this->turnZin = false;
	this->turnHostile = false;
	this->zinGuarded = false;

	this->playerAttack = false;
	this->zinAttack = false;
	this->hostileAttack = false;
	this->hostileAttackZin = false;

	this->playerDead = false;
	this->zinDead = false;

	//Move Selectors
	this->playerPickMove = -1;
	this->zinPickMove = 0;

	//Init Strings
	this->playerTurnText = "You plan your next move...";
	this->zinTurnText = "Zin plans her next move...";

	this->hostileNameNoSpc = "Abomination";
	this->hostileName = "Abomination";
	this->hostileEncounterText = "A combatant ambushes you! Pick your next step carefully...";
	this->hostileAtkPlayerText = "The hostile swings back! Click to continue...";
	this->hostileAtkZinText = "The hostile swings at Zin! Click to continue...";
	this->hostileAtkZinBlkText = "You block Zin from the strike! Click to continue...";

	this->playerSlashAtkText = "You strike the combatant! Click to continue...";
	this->playerGuardAtkText = "You plant yourself in between Zin and the enemy! Click to continue...";
	this->playerDecayAtkText = "You slash yourself open with your sword, using the decay in your blood to strike the enemy!";

	this->zinSmiteAtkText = "Zin smites the combatant! Click to continue...";
	this->zinMendAtkText = "Zin heals the party! Click to continue...";
	this->zinVengeanceAtkText = "Zin takes vengeance, brutally stirking the enemy! Click to continue...";
}

Combat::~Combat()
{

}

//Core Stat Functions
void Combat::updateStats(Assets& assets, Player& player)
{
	this->playerStrike = 5 + player.getStrength() + player.getSwordPower();
	this->playerHp = this->playerHp + player.getVitality();
	player.getDecayMax() = 25 + player.getFortitude();
	this->playerHpMax = this->playerHp;
	this->updateMoves(assets, player);
}

void Combat::updateStatsZin(Player& player)
{
	this->zinSmite = 5 + player.getZinResolve();
	this->zinHp = 35 + player.getZinResilience();
	this->zinHpMax = this->zinHp;
}

void Combat::updateMoves(Assets& assets, Player& player)
{
	if (player.getLevel() >= 15 && unlockedGuard == false) {
		//Unlock Guard
		assets.setCombatPlayerMovesInc();
		assets.text.setString("Move 'Guard' learned!");
		this->unlockedGuard = true;
	}
}

//Core Combat Functions
void Combat::combatLoop(Assets& assets, Player& player, Animation& animate)
{
	animate.animateZin();
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
	if (!this->playerDead) {
		this->playerTurn(assets);
	}
	//Zin's Turn
	if (!this->zinDead) {
		this->zinTurn(assets);
	}
	//Check if hostile is dead. If so, end combat
	if (this->hostileHp <= 0) {
		assets.setCombatAssetsFalse();
		player.combatReward();
		assets.text.setString("You have killed the " + this->hostileNameNoSpc + ". Player Exp increased " + std::to_string(player.getExp()) + " / " + std::to_string(player.getExpNext()));
	}
	//Hostiles turn
	this->hostileTurn(assets);
	//Check if player or Zin has died
	if (this->playerHp <= 0 && !this->playerDead) {
		this->playerDead = true;
		assets.text.setString("You have been left unconscious...");
	} 
	if (this->zinHp <= 0 && !this->zinDead) {
		this->zinDead = true;
		assets.text.setString("Zin has been left unconscious...");
	} 
	//Check if both the player and Zin have died
	if (this->playerHp <= 0 && zinHp <= 0) {
		this->playerDeath(assets);
		assets.text.setString("Your party has died...");
	}
}

void Combat::initCombat(Assets& assets, Player& player)
{
	assets.soundCombatStart.play(); //Play combat Sfx
	this->updateStats(assets, player);
	assets.text.setString(this->hostileEncounterText);
	assets.textElements[6].setString(assets.getPlayerName() + "     " + std::to_string(this->playerHp) + "/" + std::to_string(this->playerHpMax));
	assets.textElements[7].setString("Zin            " + std::to_string(this->zinHp) + "/" + std::to_string(this->zinHpMax));
	assets.textElements[8].setString(this->hostileName + std::to_string(this->hostileHp) + "/" + std::to_string(this->hostileHpMax));

	assets.setPlayerCounterInc(); //Load Player sprite with counter
	assets.setZinCounterInc(); //Load Zins sprite with counter
	assets.setPlayerInitFalse(); //Make usable again
	assets.setZinInitFalse(); //Make usable again
	assets.setHostileInitFalse(); //Make usable again
	assets.setCombatAssetsTrue(); //Utilize all combat assets
	assets.setInitMapFalse(); //Hide the map if its open
	assets.setInitStatsFalse(); //Hide stats if open
	assets.setInitInventoryFalse(); //Hide inventory if open
	assets.setPlayerTurnAssetsTrue(); //Allow player turn
}

void Combat::reInitCombat(Assets& assets)
{
	//If player and zin are still alive
	if (!this->playerDead && !this->zinDead) {
		assets.setCombatCounterZero();
		assets.setPlayerTurnAssetsTrue();
		assets.setZinTurnAssetsFalse();
		this->attackCounter = 0;
		this->zinAttackCounter = 0;
		this->playerAttack = false;
		this->hostileAttack = false;
		this->hostileAttackZin = false;
		this->turnPlayer = true;
		this->turnZin = false;
		this->turnHostile = false;
		this->zinGuarded = false;
		this->zinAttack = false;
	} //If the player is dead and zin is alive
	else if (this->playerDead && !this->zinDead) {
		assets.getCombatCounter() = 1;
		assets.setPlayerTurnAssetsFalse();
		assets.setZinTurnAssetsTrue();
		this->attackCounter = 0;
		this->zinAttackCounter = 0;
		this->hostileAttack = false;
		this->hostileAttackZin = false;
		this->turnZin = true;
		this->turnHostile = false;
		this->zinGuarded = false;
		this->zinAttack = false;
	}
	else if (!this->playerDead && this->zinDead) {
		assets.setCombatCounterZero();
		assets.setPlayerTurnAssetsTrue();
		assets.setZinTurnAssetsFalse();
		this->attackCounter = 0;
		this->playerAttack = false;
		this->hostileAttack = false;
		this->hostileAttackZin = false;
		this->turnPlayer = true;
		this->turnHostile = false;
	}
}

void Combat::playerDeath(Assets& assets)
{
	assets.setCombatAssetsFalse();
	assets.setPlayerDeathTrue();
}

//Combat Functions
void Combat::playerTurn(Assets& assets)
{
	if (this->turnPlayer == true) {
		switch (this->attackCounter) {
		case 0:
			assets.text.setString(this->playerTurnText);
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
			if (!this->zinDead) {
				this->turnZin = true;
			}
			else {
				this->turnHostile = true;
			}
			break;
		}
	}
}

void Combat::zinTurn(Assets& assets)
{
	if (turnZin == true) {
		switch (this->zinAttackCounter) {
		case 0:
			assets.text.setString(this->zinTurnText);
			assets.setZinTurnAssetsTrue();
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
		switch (assets.getCombatCounter()) {
		case 0:
			if (this->hostileAttack == false) {
				this->playerHp -= this->hostileStrike;
				assets.soundCom.play();
				assets.textElements[6].setString(assets.getPlayerName() + "     " + std::to_string(playerHp) + "/" + std::to_string(playerHpMax));
				assets.text.setString(this->hostileAtkPlayerText);
				this->hostileAttack = true;
			}
			break;
		case 1:
			if (this->zinGuarded == false && this->hostileAttackZin == false && !this->zinDead) {
				this->zinHp -= this->hostileStrike;
				assets.soundCom.play();
				assets.textElements[7].setString("Zin            " + std::to_string(zinHp) + "/" + std::to_string(zinHpMax));
				assets.text.setString(this->hostileAtkZinText);
				this->hostileAttackZin = true;
			}
			else if (this->zinGuarded == true && this->hostileAttackZin == false && !this->zinDead) {
				assets.soundGuarded.play();
				assets.text.setString(this->hostileAtkZinBlkText);
				this->hostileAttackZin = true;
			}
			else if (this->zinDead) {
				assets.getCombatCounter() = 2;
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
		//Strike
		assets.soundSlash.play();
		this->hostileHp -= this->playerStrike;
		assets.textElements[8].setString(this->hostileName + std::to_string(hostileHp) + "/" + std::to_string(hostileHpMax));
		assets.setPlayerTurnAssetsFalse();
		assets.text.setString(this->playerSlashAtkText);
		break;
	case 1:
		//Guard Zin
		assets.soundGuard.play();
		assets.setPlayerTurnAssetsFalse();
		this->zinGuarded = true;
		assets.text.setString(this->playerGuardAtkText);
		break;
	case 2:
		//Decayed blade
		assets.soundDecay.play();
		this->hostileHp -= this->decayedBlade;
		assets.textElements[8].setString(this->hostileName + std::to_string(hostileHp) + "/" + std::to_string(hostileHpMax));
		assets.setPlayerTurnAssetsFalse();
		assets.text.setString(this->playerDecayAtkText);
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
		assets.textElements[8].setString(this->hostileName + std::to_string(hostileHp) + "/" + std::to_string(hostileHpMax));
		assets.setZinTurnAssetsFalse();
		assets.text.setString(this->zinSmiteAtkText);
		break;
	case 1:
		//Mend party
		assets.soundMend.play();
		if (this->playerHp < this->playerHpMax) {
			this->playerHp += this->zinMend;
			if (this->playerHp > this->playerHpMax) {
				this->playerHp = this->playerHpMax;
			}
		}
		if (this->zinHp < this->zinHpMax) {
			this->zinHp += this->zinMend;
			if (this->zinHp > this->zinHpMax) {
				this->zinHp = this->zinHpMax;
			}
		}
		assets.textElements[6].setString(assets.getPlayerName() + "     " + std::to_string(playerHp) + "/" + std::to_string(playerHpMax));
		assets.textElements[7].setString("Zin            " + std::to_string(zinHp) + "/" + std::to_string(zinHpMax));
		assets.setZinTurnAssetsFalse();
		assets.text.setString(this->zinMendAtkText);
		break;
	case 2:
		//Use Vengeance the hostile
		assets.soundVengeance.play();
		this->zinVengeance = this->playerHpMax - this->playerHp;
		this->hostileHp -= this->zinVengeance;
		assets.textElements[8].setString(this->hostileName + std::to_string(hostileHp) + "/" + std::to_string(hostileHpMax));
		assets.setZinTurnAssetsFalse();
		assets.text.setString(this->zinVengeanceAtkText);
		break;
	}
	
}

//Combat Init Hostile
void Combat::initWolf(Assets& assets)
{
	if (!this->initHostileWolf) {
		//Set wolf sprite
		assets.getHostileCounter() = 1;
		//Allow new combat to start
		this->initCombatOnce = false;
		this->reInitCombatOnce = false;
		//Set parameters for hostile
		this->hostileHp = 25;
		this->hostileHpMax = 25;
		this->hostileStrike = 5;

		this->hostileNameNoSpc = "Wolf";
		this->hostileName = "Wolf	    ";
		this->hostileEncounterText = "A wolf leaps out of the bushes, ambushing you!";
		this->hostileAtkPlayerText = "The wolf lunges forwards, biting you!";
		this->hostileAtkZinText = "The wolf jumps towards Zin, biting her!";
		this->hostileAtkZinBlkText = "The wolf leaps in the air towards Zin, however you block it just in time!";

		this->playerSlashAtkText = "You slash at the wolf, hitting it!";
		this->playerGuardAtkText = "You watch the wolfs movements and prepare yourself to defend Zin...";
		this->playerDecayAtkText = "You slash yourself open with your sword, using the decay in your blood to strike the wolf!";

		this->zinSmiteAtkText = "Zin places her hands together and creates a bolt of lightning, striking the wolf!";
		this->zinMendAtkText = "Zin slowly moves her arms outwards, casting a green aura around you and herself, restoring health...";
		this->zinVengeanceAtkText = "Zin uses the blood spilled from your body to create blades made of blood, casting them into the wolf!";
		this->initHostileWolf = true;
	}
}

void Combat::initDecayWalker(Assets& assets)
{
	if (!this->initHostileWalker) {
		//Set wolf sprite
		assets.getHostileCounter() = 2;
		//Allow new combat to start
		this->initCombatOnce = false;
		this->reInitCombatOnce = false;
		//Set parameters for hostile
		this->hostileHp = 35;
		this->hostileHpMax = 35;
		this->hostileStrike = 2;

		this->hostileNameNoSpc = "Decay Walker";
		this->hostileName = "Decay Walker ";
		this->hostileEncounterText = "A horrific creature appears before you, threatening your life!";
		this->hostileAtkPlayerText = "The walking pile of decay swings at you, striking you!";
		this->hostileAtkZinText = "The walker jumps towards Zin, hitting her!";
		this->hostileAtkZinBlkText = "The walker leaps towards Zin, however you deflect the attack just in time!";

		this->playerSlashAtkText = "You slash at the vile creature, black ooze";
		this->playerGuardAtkText = "You watch the walkers movements and prepare yourself to defend Zin...";
		this->playerDecayAtkText = "You slash yourself open with your sword, using the decay in your blood to strike the walker!";

		this->zinSmiteAtkText = "Zin places her hands together and creates a bolt of lightning, smiting the unholy creature!";
		this->zinMendAtkText = "Zin slowly moves her arms outwards, casting a green aura around you and herself, restoring health...";
		this->zinVengeanceAtkText = "Zin uses the blood spilled from your body to create blades made of blood, casting them into the walker!";
		this->initHostileWalker = true;
	}
}

void Combat::initDecayKnight(Assets& assets)
{
	if (!this->initHostileKnight) {
		//Set wolf sprite
		assets.getHostileCounter() = 3;
		//Allow new combat to start
		this->initCombatOnce = false;
		this->reInitCombatOnce = false;
		//Set parameters for hostile
		this->hostileHp = 100;
		this->hostileHpMax = 100;
		this->hostileStrike = 15;

		this->hostileNameNoSpc = "Decay Knight";
		this->hostileName = "Decay Knight ";
		this->hostileEncounterText = "You're ambushed by a horrifying knight rotting from decay!";
		this->hostileAtkPlayerText = "The knight lunges forwards with precision, striking you!";
		this->hostileAtkZinText = "The knight swings his sword at Zin, striking her!";
		this->hostileAtkZinBlkText = "The knight lunges his sword towards Zin, however you deflect it just on time!";

		this->playerSlashAtkText = "You slash at the knight, attempting to pierce his armor!";
		this->playerGuardAtkText = "You watch the knights movements and prepare yourself to defend Zin...";
		this->playerDecayAtkText = "You slash yourself open with your sword, using the decay in your blood to strike the knight!";

		this->zinSmiteAtkText = "Zin places her hands together and creates a bolt of lightning, smiting the knight!";
		this->zinMendAtkText = "Zin slowly moves her arms outwards, casting a green aura around you and herself, restoring health...";
		this->zinVengeanceAtkText = "Zin uses the blood spilled from your body to create blades made of blood, casting them into the knight!";
		this->initHostileWalker = true;
	}
}