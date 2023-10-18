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
	this->combatEnd = false;

	//Hostile Forest Bools
	this->initHostileWolf = false;
	this->initHostileWalker = false;
	this->initHostileKnight = false;
	this->initHostileTreeMimic = false;
	this->initHostileLostNun = false;

	//Hostile Castle Bools
	this->initHostileJester = false;
	this->initHostileWallMimic = false;
	this->initHostileLostKnight = false;
	this->initHostilePhantom = false;
	this->initHostileEater = false;

	//Hostile Decay Bools
	this->initHostileLimbSplitter = false;
	this->initHostileBurrower = false;
	this->initHostileChatterMouth = false;
	this->initHostileReclus = false;
	this->initHostileTendrilAlpha = false;

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
void Combat::combatLoop(Sprites& sprites, Player& player, Animation& animate)
{
	if (!combatEnd) {
		//Begin combat loop initialization
		if (initCombatOnce == false) {
			this->initCombat(sprites, player);
			initCombatOnce = true;
		} //Reinitialize the combat loop for each pass
		else if (reInitCombatOnce == false) {
			this->reInitCombat(sprites);
			reInitCombatOnce = true;
		}
		//Players turn
		if (!this->playerDead) {
			this->playerTurn(sprites);
		}
		//Zin's Turn
		if (!this->zinDead) {
			this->zinTurn(sprites);
		}
		//Check if hostile is dead. If so, end combat
		if (this->hostileHp <= 0) {
			sprites.setCombatAssetsFalse();
			player.combatReward();
			sprites.text.setString("You have killed the " + this->hostileNameNoSpc + ". " + std::to_string(player.getExp()) + " Exp gained...");
			sprites.getTipBoxCounter() = -1;
			//Make entity viewer blank again
			sprites.getEntityViewerCounter() = -1;
			this->combatEnd = true;
		}
		//Hostiles turn
		this->hostileTurn(sprites);
		//Check if player or Zin has died
		if (this->playerHp <= 0 && !this->playerDead) {
			this->playerDead = true;
			sprites.text.setString("You have been left unconscious...");
		}
		if (this->zinHp <= 0 && !this->zinDead) {
			this->zinDead = true;
			sprites.text.setString("Zin has been left unconscious...");
		}
		//Check if both the player and Zin have died
		if (this->playerHp <= 0 && zinHp <= 0) {
			this->playerDeath(sprites);
			sprites.text.setString("Your party has died...");
		}
	}
}

void Combat::initCombat(Sprites& sprites, Player& player)
{
	sprites.soundCombatStart.play(); //Play combat Sfx
	//this->updateStats(assets, player);
	sprites.text.setString(this->hostileEncounterText);
	sprites.spriteText[0].setString(sprites.getPlayerName() + "     " + std::to_string(this->playerHp) + "/" + std::to_string(this->playerHpMax));
	sprites.spriteText[1].setString("Zin            " + std::to_string(this->zinHp) + "/" + std::to_string(this->zinHpMax));
	sprites.spriteText[2].setString(this->hostileName + std::to_string(this->hostileHp) + "/" + std::to_string(this->hostileHpMax));

	this->combatEnd = false;
	sprites.getPlayerCounter()++; //Load Player sprite with counter
	sprites.getZinCounter()++; //Load Zins sprite with counter
	sprites.setPlayerInitFalse(); //Make usable again
	sprites.setZinInitFalse(); //Make usable again
	sprites.setHostileInitFalse(); //Make usable again
	sprites.setCombatAssetsTrue(); //Utilize all combat assets
	sprites.setInitMapFalse(); //Hide the map if its open
	sprites.setInitStatsFalse(); //Hide stats if open
	sprites.setInitInventoryFalse(); //Hide inventory if open
	sprites.setPlayerTurnAssetsTrue(); //Allow player turn
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
				assets.spriteText[0].setString(assets.getPlayerName() + "     " + std::to_string(playerHp) + "/" + std::to_string(playerHpMax));
				assets.text.setString(this->hostileAtkPlayerText);
				this->hostileAttack = true;
			}
			break;
		case 1:
			if (this->zinGuarded == false && this->hostileAttackZin == false && !this->zinDead) {
				this->zinHp -= this->hostileStrike;
				assets.soundCom.play();
				assets.spriteText[1].setString("Zin            " + std::to_string(zinHp) + "/" + std::to_string(zinHpMax));
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
		assets.spriteText[2].setString(this->hostileName + std::to_string(hostileHp) + "/" + std::to_string(hostileHpMax));
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
		assets.spriteText[2].setString(this->hostileName + std::to_string(hostileHp) + "/" + std::to_string(hostileHpMax));
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
		assets.spriteText[2].setString(this->hostileName + std::to_string(hostileHp) + "/" + std::to_string(hostileHpMax));
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
		assets.spriteText[0].setString(assets.getPlayerName() + "     " + std::to_string(playerHp) + "/" + std::to_string(playerHpMax));
		assets.spriteText[1].setString("Zin            " + std::to_string(zinHp) + "/" + std::to_string(zinHpMax));
		assets.setZinTurnAssetsFalse();
		assets.text.setString(this->zinMendAtkText);
		break;
	case 2:
		//Use Vengeance the hostile
		assets.soundVengeance.play();
		this->zinVengeance = this->playerHpMax - this->playerHp;
		this->hostileHp -= this->zinVengeance;
		assets.spriteText[2].setString(this->hostileName + std::to_string(hostileHp) + "/" + std::to_string(hostileHpMax));
		assets.setZinTurnAssetsFalse();
		assets.text.setString(this->zinVengeanceAtkText);
		break;
	}
	
}

//Combat Init Forest Hostiles
void Combat::initWolf(Sprites& sprites)
{
	if (!this->initHostileWolf) {
		//Make entity viewer visible
		sprites.getSpriteViewerCounter() = 0;
		//Make wolf entity visible
		sprites.getEntityViewerCounter() = 9;
		//Allow combat to start
		this->combatEnd = false;
		//Set wolf sprite
		sprites.getHostileCounter() = 1;
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

void Combat::initDecayWalker(Sprites& sprites)
{
	if (!this->initHostileWalker) {
		//Make entity viewer visible
		sprites.getSpriteViewerCounter() = 0;
		//Make decay walker entity visible
		sprites.getEntityViewerCounter() = 1;
		//Allow combat to start
		this->combatEnd = false;
		//Set walker sprite
		sprites.getHostileCounter() = 2;
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

void Combat::initHostileTree(Sprites& sprites)
{
	if (!this->initHostileTreeMimic) {
		//Make entity viewer visible
		sprites.getSpriteViewerCounter() = 0;
		//Make tree mimic entity visible
		sprites.getEntityViewerCounter() = 5;
		//Allow combat to start
		this->combatEnd = false;
		//Set tree mimic sprite
		sprites.getHostileCounter() = 4;
		//Allow new combat to start
		this->initCombatOnce = false;
		this->reInitCombatOnce = false;
		//Set parameters for hostile
		this->hostileHp = 65;
		this->hostileHpMax = 65;
		this->hostileStrike = 2;

		this->hostileNameNoSpc = "Tree Mimic";
		this->hostileName = "Tree Mimic ";
		this->hostileEncounterText = "A tree shifts into a horrifying creature, revealing itself and lunging at you!";
		this->hostileAtkPlayerText = "The mimic strikes you with a spiked branch!";
		this->hostileAtkZinText = "The mimic launches at Zin, striking her with a branch!";
		this->hostileAtkZinBlkText = "The mimic rushes towards Zin, however you deflect its strike just in time!";

		this->playerSlashAtkText = "You slash at the mimic, slowly chipping away at the wood holding its form.";
		this->playerGuardAtkText = "You pay close attention to the mimic, preparing to defend Zin.";
		this->playerDecayAtkText = "You slash yourself open with your sword, using the decay in your blood to strike the mimic!";

		this->zinSmiteAtkText = "Zin places her hands together and creates a bolt of lightning, smiting the mimic!";
		this->zinMendAtkText = "Zin slowly moves her arms outwards, casting a green aura around you and herself, restoring health...";
		this->zinVengeanceAtkText = "Zin uses the blood spilled from your body to create blades made of blood, casting them into the mimic!";
		this->initHostileTreeMimic = true;
	}
}

void Combat::initDecayKnight(Sprites& sprites)
{
	if (!this->initHostileKnight) {
		//Make entity viewer visible
		sprites.getSpriteViewerCounter() = 0;
		//Make tree mimic entity visible
		sprites.getEntityViewerCounter() = 10;
		//Allow combat to start
		this->combatEnd = false;
		//Set wolf sprite
		sprites.getHostileCounter() = 3;
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

void Combat::initLostNun(Sprites& sprites)
{
	if (!this->initHostileLostNun) {
		//Allow combat to start
		this->combatEnd = false;
		//Set nun sprite
		sprites.getHostileCounter() = 5;
		//Allow new combat to start
		this->initCombatOnce = false;
		this->reInitCombatOnce = false;
		//Set parameters for hostile
		this->hostileHp = 200;
		this->hostileHpMax = 200;
		this->hostileStrike = 20;

		this->hostileNameNoSpc = "Lost Nun";
		this->hostileName = "Lost Nun ";
		this->hostileEncounterText = "The woman steps forwards, revealing the sheer spread of her decay. She readies to attack you.";
		this->hostileAtkPlayerText = "The nun launches forwards as she spews out rotting decay, brutally striking you!";
		this->hostileAtkZinText = "The nun targets Zin, hitting her with horrifying amounts of molten decay!";
		this->hostileAtkZinBlkText = "The nun targets Zin launching more decay at her, however you deflect it just on time!";

		this->playerSlashAtkText = "You slash at the nun, the woman screaming out in pain as you attack.";
		this->playerGuardAtkText = "You watch the nuns movements preparing yourself to defend Zin at any cost...";
		this->playerDecayAtkText = "You slash yourself open with your sword, using the decay in your blood to strike the nun!";

		this->zinSmiteAtkText = "Zin places her hands together and creates a bolt of lightning, smiting the nun!";
		this->zinMendAtkText = "Zin slowly moves her arms outwards, casting a green aura around you and herself, restoring health and slowly burning away the decay...";
		this->zinVengeanceAtkText = "Zin uses the blood spilled from your body to create blades made of blood, casting them into the nun!";
		this->initHostileLostNun = true;
	}
}

void Combat::initDecapod(Sprites& sprites)
{
	if (!this->initHostileDecapod) {
		//Make entity viewer visible
		sprites.getSpriteViewerCounter() = 0;
		//Make decapod entity visible
		sprites.getEntityViewerCounter() = 8;
		//Allow combat to start
		this->combatEnd = false;
		//Set decapod sprite
		sprites.getHostileCounter() = 6;
		//Allow new combat to start
		this->initCombatOnce = false;
		this->reInitCombatOnce = false;
		//Set parameters for hostile
		this->hostileHp = 75;
		this->hostileHpMax = 75;
		this->hostileStrike = 12;

		this->hostileNameNoSpc = "Abyssal Decapod";
		this->hostileName = "Abyssal Decapod ";
		this->hostileEncounterText = "The horrifying abomination stands before you as its face wriggles with tentacles...";
		this->hostileAtkPlayerText = "The horrifying abomination grabs ahold of you and strikes you violently!";
		this->hostileAtkZinText = "The creature spits acid directly at Zin, hitting her with it!";
		this->hostileAtkZinBlkText = "The abomination attempts to spit at Zin with acid, however you block it with your sword just in time!";

		this->playerSlashAtkText = "You slash at the decapod, the creature screaming in pain!";
		this->playerGuardAtkText = "You watch the decapods movements, preparing yourself to defend Zin from its attacks...";
		this->playerDecayAtkText = "You slash yourself open with your sword, using the decay in your blood to strike the decapod!";

		this->zinSmiteAtkText = "Zin places her hands together and creates a bolt of lightning, smiting the decapod!";
		this->zinMendAtkText = "Zin slowly moves her arms outwards, casting a green aura around you and herself, restoring health and slowly burning away the decay...";
		this->zinVengeanceAtkText = "Zin uses the blood spilled from your body to create blades made of blood, casting them into the decapod!";
		this->initHostileDecapod = true;
	}
}

void Combat::initHazeDemon(Sprites& sprites)
{
	if (!this->initHostileDecapod) {
		//Make entity viewer visible
		sprites.getSpriteViewerCounter() = 0;
		//Make decapod entity visible
		sprites.getEntityViewerCounter() = 11;
		//Allow combat to start
		this->combatEnd = false;
		//Set decapod sprite
		sprites.getHostileCounter() = 7;
		//Allow new combat to start
		this->initCombatOnce = false;
		this->reInitCombatOnce = false;
		//Set parameters for hostile
		this->hostileHp = 75;
		this->hostileHpMax = 75;
		this->hostileStrike = 12;

		this->hostileNameNoSpc = "Haze Demon";
		this->hostileName = "Haze Demon ";
		this->hostileEncounterText = "The horrifying abomination stands before you as it creatres a strange auora...";
		this->hostileAtkPlayerText = "The horrifying abomination grabs ahold of you and strikes you violently!";
		this->hostileAtkZinText = "The creature splices the air in front Zin, hitting her with the airwaves!";
		this->hostileAtkZinBlkText = "The abomination attempts to split the air towards Zin, however you block it just in time!";

		this->playerSlashAtkText = "You slash at the demon, the unholy entity screaming in pain!";
		this->playerGuardAtkText = "You watch the demons movements, preparing yourself to defend Zin from its attacks...";
		this->playerDecayAtkText = "You slash yourself open with your sword, using the decay in your blood to strike the demon!";

		this->zinSmiteAtkText = "Zin places her hands together and creates a bolt of lightning, smiting the demon!";
		this->zinMendAtkText = "Zin slowly moves her arms outwards, casting a green aura around you and herself, restoring health and slowly burning away the decay...";
		this->zinVengeanceAtkText = "Zin uses the blood spilled from your body to create blades made of blood, casting them into the demon!";
		this->initHostileDecapod = true;
	}
}

//Combat Init Castle Hostiles
void Combat::initCourtJester(Sprites& sprites)
{
	if (!this->initHostileJester) {
		//Make entity viewer visible
		sprites.getSpriteViewerCounter() = 0;
		//Make jester entity visible
		sprites.getEntityViewerCounter() = 12;
		//Allow combat to start
		this->combatEnd = false;
		//Set jester sprite
		sprites.getHostileCounter() = 8;
		//Allow new combat to start
		this->initCombatOnce = false;
		this->reInitCombatOnce = false;
		//Set parameters for hostile
		this->hostileHp = 80;
		this->hostileHpMax = 80;
		this->hostileStrike = 20;

		this->hostileNameNoSpc = "Court Jester";
		this->hostileName = "Court Jester ";
		this->hostileEncounterText = "The jester stands with a horrifying grin...";
		this->hostileAtkPlayerText = "The jester stabs you with a small dagger, brutally injuring you!";
		this->hostileAtkZinText = "The jester sprints towards Zin, stabbing her with his knife!";
		this->hostileAtkZinBlkText = "The jester runs towards Zin with a disgusting smile and a knife in his hand, however you block the knife just in time!";

		this->playerSlashAtkText = "You slash at the jester, the clown smiling in pain!";
		this->playerGuardAtkText = "You watch the jesters movements, preparing yourself to defend Zin from its attacks...";
		this->playerDecayAtkText = "You slash yourself open with your sword, spraying your decayed blood over the jester, causing him to yell in pain!";

		this->zinSmiteAtkText = "Zin places her hands together and creates a bolt of lightning, smiting the jester!";
		this->zinMendAtkText = "Zin slowly moves her arms outwards, casting a green aura around you and herself, restoring health and slowly burning away the decay...";
		this->zinVengeanceAtkText = "Zin uses the blood spilled from your body to create blades made of blood, casting them into the jester!";
		this->initHostileJester = true;
	}
}

void Combat::initWallMimic(Sprites& sprites)
{
	if (!this->initHostileWallMimic) {
		//Make entity viewer visible
		sprites.getSpriteViewerCounter() = 0;
		//Make wall mimic entity visible
		sprites.getEntityViewerCounter() = 13;
		//Allow combat to start
		this->combatEnd = false;
		//Set wall mimic sprite
		sprites.getHostileCounter() = 9;
		//Allow new combat to start
		this->initCombatOnce = false;
		this->reInitCombatOnce = false;
		//Set parameters for hostile
		this->hostileHp = 80;
		this->hostileHpMax = 80;
		this->hostileStrike = 20;

		this->hostileNameNoSpc = "Wall Mimic";
		this->hostileName = "Wall Mimic ";
		this->hostileEncounterText = "The walls begin to shift as the face appears before you.";
		this->hostileAtkPlayerText = "The walls shift as the mimic launches towards you, striking you!";
		this->hostileAtkZinText = "The mimic targets Zin, striking her with extreme force!";
		this->hostileAtkZinBlkText = "The mimic attempts to bite Zin, however you tackle her out of the way just in time!";

		this->playerSlashAtkText = "You slash at the mimic, the walls echoing back with screams!";
		this->playerGuardAtkText = "You watch the movements of the walls carefully, preparing yourself to defend Zin from its attacks...";
		this->playerDecayAtkText = "You slash yourself open with your sword, spraying your decayed blood over the walls and ceiling striking the mimic!";

		this->zinSmiteAtkText = "Zin places her hands together and creates a bolt of lightning that obliterates the ceiling and strikes the mimic!";
		this->zinMendAtkText = "Zin slowly moves her arms outwards, casting a green aura around you and herself, restoring health and slowly burning away the decay...";
		this->zinVengeanceAtkText = "Zin uses the blood spilled from your body to create blades made of blood, casting them into the walls!";
		this->initHostileWallMimic = true;
	}
}

void Combat::initLostKnight(Sprites& sprites)
{
	if (!this->initHostileLostKnight) {
		//Make entity viewer visible
		sprites.getSpriteViewerCounter() = 0;
		//Make wall mimic entity visible
		sprites.getEntityViewerCounter() = 14;
		//Allow combat to start
		this->combatEnd = false;
		//Set wall mimic sprite
		sprites.getHostileCounter() = 10;
		//Allow new combat to start
		this->initCombatOnce = false;
		this->reInitCombatOnce = false;
		//Set parameters for hostile
		this->hostileHp = 100;
		this->hostileHpMax = 100;
		this->hostileStrike = 25;

		this->hostileNameNoSpc = "Lost Knight";
		this->hostileName = "Lost Knight ";
		this->hostileEncounterText = "The knight stands in protest, ready to fight to the death...";
		this->hostileAtkPlayerText = "The knight stabs you with his sword!";
		this->hostileAtkZinText = "The knight dashes towards Zin, slightly hesitanting due to her being a child. Despite this, he still strikes her!";
		this->hostileAtkZinBlkText = "The knight dashes towards Zin slashing at her, however you block the blade just in time!";

		this->playerSlashAtkText = "You slash at the knight, the knight gritting his teeth in pain!";
		this->playerGuardAtkText = "You watch the knights movements, preparing yourself to defend Zin from his attacks...";
		this->playerDecayAtkText = "You slash yourself open with your sword, spraying your decayed blood into the knights helmet! He begins coughing and choking in pain!";

		this->zinSmiteAtkText = "Zin places her hands together and creates a bolt of lightning, smiting the knight!";
		this->zinMendAtkText = "Zin slowly moves her arms outwards, casting a green aura around you and herself, restoring health and slowly burning away the decay...";
		this->zinVengeanceAtkText = "Zin uses the blood spilled from your body to create blades made of blood, casting them into the knight!";
		this->initHostileLostKnight = true;
	}
}

void Combat::initPhantom(Sprites& sprites)
{
	if (!this->initHostilePhantom) {
		//Make entity viewer visible
		sprites.getSpriteViewerCounter() = 0;
		//Make wall mimic entity visible
		sprites.getEntityViewerCounter() = 15;
		//Allow combat to start
		this->combatEnd = false;
		//Set wall mimic sprite
		sprites.getHostileCounter() = 11;
		//Allow new combat to start
		this->initCombatOnce = false;
		this->reInitCombatOnce = false;
		//Set parameters for hostile
		this->hostileHp = 120;
		this->hostileHpMax = 120;
		this->hostileStrike = 10;

		this->hostileNameNoSpc = "Phantom";
		this->hostileName = "Phantom ";
		this->hostileEncounterText = "The phantom phases into existence right before you, charging...";
		this->hostileAtkPlayerText = "The phantom appears right before you, striking you before you can react!";
		this->hostileAtkZinText = "The phantom vanishes before reappearing next to Zin, using the opprotunity to strike her!";
		this->hostileAtkZinBlkText = "The phantom runs towards Zin with a disgusting smirk, however you block the attack just in time!";

		this->playerSlashAtkText = "You slash at the phantom, its physical form being caught by your blade!";
		this->playerGuardAtkText = "You watch the phantoms movements, preparing yourself to defend Zin from its attacks...";
		this->playerDecayAtkText = "You slash yourself open with your sword, spraying your decayed blood over the phantom!";

		this->zinSmiteAtkText = "Zin places her hands together and creates a bolt of lightning, smiting the phantom!";
		this->zinMendAtkText = "Zin slowly moves her arms outwards, casting a green aura around you and herself, restoring health and slowly burning away the decay...";
		this->zinVengeanceAtkText = "Zin uses the blood spilled from your body to create blades made of blood, casting them into the phantom!";
		this->initHostilePhantom = true;
	}
}

void Combat::initSkinEater(Sprites& sprites)
{
	if (!this->initHostileEater) {
		//Make entity viewer visible
		sprites.getSpriteViewerCounter() = 0;
		//Make wall mimic entity visible
		sprites.getEntityViewerCounter() = 16;
		//Allow combat to start
		this->combatEnd = false;
		//Set wall mimic sprite
		sprites.getHostileCounter() = 12;
		//Allow new combat to start
		this->initCombatOnce = false;
		this->reInitCombatOnce = false;
		//Set parameters for hostile
		this->hostileHp = 65;
		this->hostileHpMax = 65;
		this->hostileStrike = 8;

		this->hostileNameNoSpc = "Skin Eater";
		this->hostileName = "Skin Eater ";
		this->hostileEncounterText = "The skin eater stands with a horrifying face, locking eyes with you...";
		this->hostileAtkPlayerText = "The skin eater attempts to bite you but only grazes you!";
		this->hostileAtkZinText = "The skin eater sprints towards Zin, lunging at her and striking her!";
		this->hostileAtkZinBlkText = "The skin eater runs towards Zin, however you pull Zin out of the way just in time!";

		this->playerSlashAtkText = "You slash at the skin eater, the abomination screaming in pain!";
		this->playerGuardAtkText = "You watch the skin eaters movements, preparing yourself to defend Zin from its attacks...";
		this->playerDecayAtkText = "You slash yourself open with your sword, spraying your decayed blood over the skin eater, causing it to yell in pain!";

		this->zinSmiteAtkText = "Zin places her hands together and creates a bolt of lightning, smiting the skin eater!";
		this->zinMendAtkText = "Zin slowly moves her arms outwards, casting a green aura around you and herself, restoring health and slowly burning away the decay...";
		this->zinVengeanceAtkText = "Zin uses the blood spilled from your body to create blades made of blood, casting them into the skin eater!";
		this->initHostileEater = true;
	}
}

//Combat Init Decay Hostiles
void Combat::initLimbSplitter(Sprites& sprites)
{
	if (!this->initHostileLimbSplitter) {
		//Make entity viewer visible
		sprites.getSpriteViewerCounter() = 0;
		//Make limb splitter entity visible
		sprites.getEntityViewerCounter() = 17;
		//Allow combat to start
		this->combatEnd = false;
		//Set wall limb splitter sprite
		sprites.getHostileCounter() = 13;
		//Allow new combat to start
		this->initCombatOnce = false;
		this->reInitCombatOnce = false;
		//Set parameters for hostile
		this->hostileHp = 250;
		this->hostileHpMax = 250;
		this->hostileStrike = 40;

		this->hostileNameNoSpc = "Limb Splitter";
		this->hostileName = "Limb Splitter ";
		this->hostileEncounterText = "The limb splitter stares you down, waiting for its meal...";
		this->hostileAtkPlayerText = "The limb splitter strikes you with one of its ligaments!";
		this->hostileAtkZinText = "The limb splitter catches Zin off guard, striking her with one of its arms!";
		this->hostileAtkZinBlkText = "The limb splitter attempts to impale Zin with one of its arms, however you tackle her out of the way just in time!";

		this->playerSlashAtkText = "You slash at the limb splitter, the abomination screaming in pain!";
		this->playerGuardAtkText = "You watch the limb splitters ligaments, preparing yourself to defend Zin from its attacks...";
		this->playerDecayAtkText = "You slash yourself open with your sword, spraying your decayed blood over the limb splitter, causing it to screech in pain!";

		this->zinSmiteAtkText = "Zin places her hands together and creates a bolt of lightning, smiting the limb splitter!";
		this->zinMendAtkText = "Zin slowly moves her arms outwards, casting a green aura around you and herself, restoring health and slowly burning away the decay...";
		this->zinVengeanceAtkText = "Zin uses the blood spilled from your body to create blades made of blood, casting them into the limb splitter!";
		this->initHostileLimbSplitter = true;
	}
}

void Combat::initBurrower(Sprites& sprites)
{
	if (!this->initHostileBurrower) {
		//Make entity viewer visible
		sprites.getSpriteViewerCounter() = 0;
		//Make burrower entity visible
		sprites.getEntityViewerCounter() = 18;
		//Allow combat to start
		this->combatEnd = false;
		//Set burrower sprite
		sprites.getHostileCounter() = 14;
		//Allow new combat to start
		this->initCombatOnce = false;
		this->reInitCombatOnce = false;
		//Set parameters for hostile
		this->hostileHp = 250;
		this->hostileHpMax = 250;
		this->hostileStrike = 40;

		this->hostileNameNoSpc = "Burrower";
		this->hostileName = "Burrower ";
		this->hostileEncounterText = "The burrower quickly rushes towards you, ready to attack...";
		this->hostileAtkPlayerText = "The burrower crashes up from the ground, striking you with its spiked body!";
		this->hostileAtkZinText = "The burrower catches Zin off guard, striking with one of its spiked quills!";
		this->hostileAtkZinBlkText = "The burrower bursts from the wall, attempting to consume Zin whole, however you tackle her out of the way just in time!";

		this->playerSlashAtkText = "You slash at the burrower, the abomination bleeding across the crimson floor!";
		this->playerGuardAtkText = "You listen to the burrowers movements in the walls, preparing yourself to defend Zin from its attacks...";
		this->playerDecayAtkText = "You slash yourself open with your sword, spraying your decayed blood over the burrower, causing it to scream out in pain!";

		this->zinSmiteAtkText = "Zin places her hands together and creates a bolt of lightning, smiting the burrower!";
		this->zinMendAtkText = "Zin slowly moves her arms outwards, casting a green aura around you and herself, restoring health and slowly burning away the decay...";
		this->zinVengeanceAtkText = "Zin uses the blood spilled from your body to create blades made of blood, casting them into the burrower!";
		this->initHostileBurrower = true;
	}
}

void Combat::initChatterMouth(Sprites& sprites)
{
	if (!this->initHostileChatterMouth) {
		//Make entity viewer visible
		sprites.getSpriteViewerCounter() = 0;
		//Make chatter mouth entity visible
		sprites.getEntityViewerCounter() = 19;
		//Allow combat to start
		this->combatEnd = false;
		//Set chatter mouth sprite
		sprites.getHostileCounter() = 15;
		//Allow new combat to start
		this->initCombatOnce = false;
		this->reInitCombatOnce = false;
		//Set parameters for hostile
		this->hostileHp = 265;
		this->hostileHpMax = 265;
		this->hostileStrike = 20;

		this->hostileNameNoSpc = "Chatter Mouth";
		this->hostileName = "Chatter Mouth ";
		this->hostileEncounterText = "The chatter mouth quickly rushes towards you, ready to attack...";
		this->hostileAtkPlayerText = "The chatter mouth uses its wide body to swing around the limited cave space, smashing you into the wall!";
		this->hostileAtkZinText = "The chatter mouths body strikes Zin as it swings it violently!";
		this->hostileAtkZinBlkText = "The chatter mouth attempts to drag Zin into its serrated mouth, however you firmly grab ahold of Zin's arm and pull her out of its grasp!";

		this->playerSlashAtkText = "You slash at the chatter mouth, the abomination bleeding across the crimson floor!";
		this->playerGuardAtkText = "You watch the chatter mouths movements, preparing yourself to defend Zin from its attacks...";
		this->playerDecayAtkText = "You slash yourself open with your sword, spraying your decayed blood over the chatter mouth, causing it to scream out in pain!";

		this->zinSmiteAtkText = "Zin places her hands together and creates a bolt of lightning, smiting the chatter mouth!";
		this->zinMendAtkText = "Zin slowly moves her arms outwards, casting a green aura around you and herself, restoring health and slowly burning away the decay...";
		this->zinVengeanceAtkText = "Zin uses the blood spilled from your body to create blades made of blood, casting them into the chatter mouth!";
		this->initHostileChatterMouth = true;
	}
}

void Combat::initReclus(Sprites& sprites)
{
	if (!this->initHostileReclus) {
		//Make entity viewer visible
		sprites.getSpriteViewerCounter() = 0;
		//Make reclus entity visible
		sprites.getEntityViewerCounter() = 20;
		//Allow combat to start
		this->combatEnd = false;
		//Set reclus sprite
		sprites.getHostileCounter() = 16;
		//Allow new combat to start
		this->initCombatOnce = false;
		this->reInitCombatOnce = false;
		//Set parameters for hostile
		this->hostileHp = 265;
		this->hostileHpMax = 265;
		this->hostileStrike = 20;

		this->hostileNameNoSpc = "Reclus";
		this->hostileName = "Reclus ";
		this->hostileEncounterText = "The reclus moves quickly rushing forwards ready to attack...";
		this->hostileAtkPlayerText = "The reclus smashes you with its hand into the wall!";
		this->hostileAtkZinText = "The reclus drags its hand across the floor, striking Zin!";
		this->hostileAtkZinBlkText = "The reclus mouth attempts to drag Zin into its serrated mouth, however you firmly grab ahold of Zin's arm and pull her out of its grasp!";

		this->playerSlashAtkText = "You slash at the reclus, the abomination bleeding across the crimson floor!";
		this->playerGuardAtkText = "You watch the reclus carefully, preparing yourself to defend Zin from its attacks...";
		this->playerDecayAtkText = "You slash yourself open with your sword, spraying your decayed blood over the reclus, causing it to scream out in pain!";

		this->zinSmiteAtkText = "Zin places her hands together and creates a bolt of lightning, smiting the reclus!";
		this->zinMendAtkText = "Zin slowly moves her arms outwards, casting a green aura around you and herself, restoring health and slowly burning away the decay...";
		this->zinVengeanceAtkText = "Zin uses the blood spilled from your body to create blades made of blood, casting them into the reclus!";
		this->initHostileReclus = true;
	}
}

void Combat::initTendrilAlpha(Sprites& sprites)
{
	if (!this->initHostileTendrilAlpha) {
		//Make entity viewer visible
		sprites.getSpriteViewerCounter() = 0;
		//Make tendril alpha entity visible
		sprites.getEntityViewerCounter() = 21;
		//Allow combat to start
		this->combatEnd = false;
		//Set tendril alpha sprite
		sprites.getHostileCounter() = 17;
		//Allow new combat to start
		this->initCombatOnce = false;
		this->reInitCombatOnce = false;
		//Set parameters for hostile
		this->hostileHp = 400;
		this->hostileHpMax = 400;
		this->hostileStrike = 25;

		this->hostileNameNoSpc = "Tendril Alpha";
		this->hostileName = "Tendril Alpha ";
		this->hostileEncounterText = "The abomination moves quickly rushing forwards ready to attack...";
		this->hostileAtkPlayerText = "The abomination smashes one of its tendrils into you!";
		this->hostileAtkZinText = "The abomination strikes Zin with one of its tendrils!";
		this->hostileAtkZinBlkText = "The alpha attempts to swarm Zin with its tendrils, however you jump in between each tendril slicing them away!";

		this->playerSlashAtkText = "You slash at the alpha, its body squirming in pain!";
		this->playerGuardAtkText = "You watch the abominations tendrils carefully, preparing yourself to defend Zin from its attacks...";
		this->playerDecayAtkText = "You slash yourself open with your sword, spraying your decayed blood over the alpha, causing it to quiver!";

		this->zinSmiteAtkText = "Zin places her hands together and creates a bolt of lightning, smiting the alpha!";
		this->zinMendAtkText = "Zin slowly moves her arms outwards, casting a green aura around you and herself, restoring health and slowly burning away the decay...";
		this->zinVengeanceAtkText = "Zin uses the blood spilled from your body to create blades made of blood, casting them into the alpha!";
		this->initHostileTendrilAlpha = true;
	}
}