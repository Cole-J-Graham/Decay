#include "Combat.h"

//Constructors & Destructors
Combat::Combat()
{
	//Move Values
	this->valZero = 0;
	this->valOne = 1;
	this->valTwo = 2;

	//Attack Counters
	this->attackCounter = 0;
	this->zinAttackCounter = 0;
	this->thomAttackCounter = 0;

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
	this->initHostileSiward = false;

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

	this->playerAttack = false;
	this->zinAttack = false;
	this->thomAttack = false;
	this->hostileAttack = false;
	this->hostileAttackZin = false;
	this->hostileAttackThom = false;

	this->playerDead = false;
	this->zinDead = false;
	this->thomDead = false;

	//Move Selectors
	this->playerPickMove = -1;
	this->zinPickMove = 0;
	this->thomPickMove = 0;

	//Animation Control
	this->comTextRemoved = true;
}

Combat::~Combat()
{

}

//Core Stat Functions
void Combat::updateStats(Sprites& sprites, Player& player)
{
	getPlayerStrike() = 5 + player.getStrength() + player.getSwordPower();
	getPlayerHp() = getPlayerHpMax() + player.getVitality();
	player.getDecayMax() = 25 + player.getFortitude();
	getPlayerHpMax() = getPlayerHp();
	this->updateMoves(sprites, player);
}

void Combat::updateStatsZin(Player& player)
{
	getZinSmite() = 5 + player.getZinResolve();
	getZinHp() = 35 + player.getZinResilience();
	getZinHpMax() = getZinHp();
}

void Combat::updateMoves(Sprites& sprites, Player& player)
{
	if (player.getLevel() >= 15 && unlockedGuard == false) {
		//Unlock Guard
		sprites.setCombatPlayerMovesInc();
		sprites.text.setString("Move 'Guard' learned!");
		this->unlockedGuard = true;
	}
}

//Core Combat Functions
void Combat::combatLoop(sf::RenderWindow& window, Sprites& sprites, Player& player, Animation& animate)
{
	if (!combatEnd) {
		//Combat Animations
		if (!animate.getAnimEnd()) {
			animate.animateAttack(sprites);
		}
		//Begin combat loop initialization
		if (initCombatOnce == false) {
			this->initCombat(sprites, player, animate);
			initCombatOnce = true;
		} //Reinitialize the combat loop for each pass
		else if (reInitCombatOnce == false) {
			this->reInitCombat(sprites);
			reInitCombatOnce = true;
		}
		//Players turn
		if (!this->playerDead) {
			this->playerTurn(window, sprites, animate);
		}
		//Zin's Turn
		if (!this->zinDead) {
			this->zinTurn(sprites, animate);
		}
		if (!this->thomDead) {
			this->thomTurn(sprites, animate);
		}
		//Check if hostile is dead. If so, end combat
		if (getHostileHp() <= 0) {
			sprites.setCombatAssetsFalse();
			player.combatReward();
			sprites.text.setString("You have killed the " + getHostileNameNoSpc() + ". " + std::to_string(player.getExp()) + " Exp gained...");
			combatTextTime.restart();//Start timer to remove text
			this->comTextRemoved = false;//Remove text
			sprites.getTipBoxCounter() = -1;
			//Make entity viewer blank again
			sprites.getEntityViewerCounter() = -1;
			animate.getCombatAnimationLocation() = -1;
			getThomEnraged() = false;
			this->combatEnd = true;
		}
		//Hostiles turn
		this->hostileTurn(sprites, animate);
		//Check if player, Zin, or Thom has died
		if (getPlayerHp() <= 0 && !this->playerDead) {
			this->playerDead = true;
			sprites.text.setString("You have been left unconscious...");
		}
		if (getZinHp() <= 0 && !this->zinDead) {
			this->zinDead = true;
			sprites.text.setString("Zin has been left unconscious...");
		}
		if (getThomHp() <= 0 && !this->thomDead) {
			this->thomDead = true;
			sprites.text.setString("Thom has been left unconscious...");
		}
		if (!sprites.getThomUnlocked()) {
			//Check if both the player and Zin have died
			if (getPlayerHp() <= 0 && getZinHp() <= 0) {
				this->playerDeath(sprites);
				sprites.text.setString("Your party has died...");
			}
		}
		else if (sprites.getThomUnlocked()) {
			//Check if both the player, Zin and Thom have died
			if (getPlayerHp() <= 0 && getZinHp() <= 0 && getThomHp() <= 0) {
				this->playerDeath(sprites);
				sprites.text.setString("Your party has died...");
			}
		}
	}
}

void Combat::initCombat(Sprites& sprites, Player& player, Animation& animate)
{
	sprites.soundCombatStart.play(); //Play combat Sfx
	//this->updateStats(assets, player);
	sprites.text.setString(getHostileEncText());
	sprites.spriteText[0].setString(sprites.getPlayerName() + "     " + std::to_string(getPlayerHp()) + "/" + std::to_string(getPlayerHpMax()));
	sprites.spriteText[1].setString("Zin            " + std::to_string(getZinHp()) + "/" + std::to_string(getZinHpMax()));
	sprites.spriteText[2].setString(getHostileName() + std::to_string(getHostileHp()) + "/" + std::to_string(getHostileHpMax()));

	sprites.getPlayerCounter()++; //Load Player sprite with counter
	sprites.getZinCounter()++; //Load Zins sprite with counter
	//Load Thom Sprite with counter if he is unlocked
	if (sprites.getThomUnlocked()) {
		sprites.getThomCounter()++;
		sprites.spriteText[5].setString("Thom          " + std::to_string(getThomHp()) + "/" + std::to_string(getThomHpMax()));
	}

	sprites.setCombatAssetsTrue(); //Utilize all combat assets
	sprites.setInitMapFalse(); //Hide the map if its open
	sprites.setInitStatsFalse(); //Hide stats if open
	sprites.setInitInventoryFalse(); //Hide inventory if open
	sprites.setPlayerTurnAssetsTrue(); //Allow player turn

	animate.getAnimEnd() = true;//Prevent animation attempt from running at start
	getFirstAttack() = false;
}

void Combat::reInitCombat(Sprites& sprites)
{
	//Re init Hostile
	this->hostileAttack = false;
	this->hostileAttackZin = false;
	this->hostileAttackThom = false;
	this->turnHostile = false;
	sprites.getCombatCounter() = 0;

	//Re init thom if he is unlocked
	if (sprites.getThomUnlocked()) {
		this->turnThom = false;
		this->thomAttackCounter = 0;
		this->thomAttack = false;
		getPlayerGuarded() = false;
		sprites.getThomTurnAssets() = false;
	}

	//Re init characters if both are alive
	if (!this->playerDead && !this->zinDead) {
		//Player
		sprites.setPlayerTurnAssetsTrue();
		this->turnPlayer = true;
		this->attackCounter = 0;
		getZinGuarded() = false;
		this->playerAttack = false;
		//Zin
		sprites.setZinTurnAssetsFalse();
		this->turnZin = false;
		this->zinAttackCounter = 0;
		this->zinAttack = false;
	}//Re init zin if she is alive and player is dead
	else if (this->playerDead && !this->zinDead) {
		//Player
		sprites.setPlayerTurnAssetsFalse();
		this->turnPlayer = false;
		//Zin
		sprites.setZinTurnAssetsTrue();
		this->turnZin = true;
		this->zinAttackCounter = 0;
		this->zinAttack = false;
	}//Re init player if he is alive and zin is dead
	else if (!this->playerDead && this->zinDead) {
		//Player
		sprites.setPlayerTurnAssetsTrue();
		this->turnPlayer = true;
		this->attackCounter = 0;
		getZinGuarded() = false;
		this->playerAttack = false;
		//Zin
		sprites.setZinTurnAssetsFalse();
		this->turnZin = false;
	}
}

void Combat::playerDeath(Sprites& sprites)
{
	sprites.setCombatAssetsFalse();
	sprites.setPlayerDeathTrue();
}

//Combat Functions
void Combat::playerTurn(sf::RenderWindow& window, Sprites& sprites, Animation& animate)
{
	if (this->turnPlayer == true) {
		switch (this->attackCounter) {
		case 0:
			sprites.text.setString(getPlayerTurnText());
			break;
		case 1:
			//Player Attacks Hostile
			if (this->playerAttack == false) {
				this->playerSelectMove(sprites, animate);
				this->playerAttack = true;
			}
			break;
		case 2:
			this->turnPlayer = false;
			if (sprites.getThomUnlocked()) {
				if (!this->zinDead) {
					this->turnZin = true;
				}
				else if (this->zinDead && !this->thomDead) {
					this->turnThom = true;
				}
				else if (this->zinDead && this->thomDead) {
					this->turnHostile = true;
				}
			}
			else if (!sprites.getThomUnlocked()) {
				if (!this->zinDead) {
					this->turnZin = true;
				}
				else if (this->zinDead) {
					this->turnHostile = true;
				}
			}
			break;
		}
	}
}

void Combat::zinTurn(Sprites& sprites, Animation& animate)
{
	if (this->turnZin == true) {
		switch (this->zinAttackCounter) {
		case 0:
			sprites.text.setString(getZinTurnText());
			sprites.setZinTurnAssetsTrue();
			break;
		case 1:
			//Zin Attacks Hostile
			if (this->zinAttack == false) {
				this->zinSelectMove(sprites, animate);
				this->zinAttack = true;
			}
			break;
		case 2:
			if (sprites.getThomUnlocked()) {
				this->turnZin = false;
				this->turnThom = true;
			}
			else if (!sprites.getThomUnlocked()) {
				this->turnZin = false;
				this->turnHostile = true;
			}
			break;
		}
	}
}

void Combat::thomTurn(Sprites& sprites, Animation& animate)
{
	if (this->turnThom == true) {
		switch (this->thomAttackCounter) {
		case 0:
			if (!getThomEnraged()) {
				sprites.text.setString("Thom prepares his next move");
				sprites.setThomTurnAssetsTrue();
			}
			else if (getThomEnraged()) {
				this->thomAttackCounter = 1;
			}
			break;
		case 1:
			//Thoms turn
			if (!this->thomAttack && !getThomEnraged()) {
				this->thomSelectMove(sprites, animate);
				this->thomAttack = true;
			}
			else if (this->thomAttack == false && getThomEnraged()) {
				sprites.text.setString("Thom still stands in a state of pure rage...");
				getEnraged()--;
				if (getEnraged() == 0) {
					getThomEnraged() = false;
					sprites.getThomCounter() = 0;
					sprites.text.setString("Thom snaps out of his rage!");
				}
				this->thomAttack = true;
			}
			break;
		case 2:
			this->turnThom = false;
			this->turnHostile = true;
			break;
		}
	}
}

void Combat::hostileTurn(Sprites& sprites, Animation& animate)
{
	if (this->turnHostile == true) {
		switch (sprites.getCombatCounter()) {
		case 0:
			//Hostile Attacks Player
			if (this->playerDead && !this->hostileAttack) {
				sprites.getCombatCounter() = 1;
			}
			if (!this->hostileAttack && !getPlayerGuarded()) {
				getPlayerHp() -= getHostileStrike();
				sprites.soundCom.play();
				sprites.spriteText[0].setString(sprites.getPlayerName() + "     " + std::to_string(getPlayerHp()) + "/" + std::to_string(getPlayerHpMax()));
				sprites.text.setString(getHostileAtkPlayerText());
				animate.getCombatAnimationLocation() = 1;
				animate.getAnimEnd() = false;//Play Attack Animation
				this->hostileAttack = true;
			}
			else if (!this->hostileAttack && getPlayerGuarded()) {
				sprites.text.setString(getHostileAtkPlayerBlkText());
				sprites.soundPlayerGuarded.play();
				this->hostileAttack = true;
			}
			break;
		case 1:
			//Hostile Attacks Zin
			if (this->zinDead && !this->hostileAttackZin) {
				sprites.getCombatCounter() = 2;
			}
			if (!getZinGuarded() && !this->hostileAttackZin && !this->zinDead) {
				getZinHp() -= getHostileStrike();
				sprites.soundCom.play();
				sprites.spriteText[1].setString("Zin            " + std::to_string(getZinHp()) + "/" + std::to_string(getZinHpMax()));
				sprites.text.setString(getHostileAtkZinText());
				animate.getCombatAnimationLocation() = 2;
				animate.getAnimEnd() = false;//Play Attack Animation
				this->hostileAttackZin = true;
			}
			else if (getZinGuarded() == true && !this->hostileAttackZin && !this->zinDead) {
				sprites.soundGuarded.play();
				sprites.text.setString(getHostileAtkZinBlkText());
				this->hostileAttackZin = true;
			}
			break;
		case 2:
			//Check if Thom is unlocked. If not, skip entirely.
			if (!sprites.getThomUnlocked()) {
				sprites.getCombatCounter() = 3;
			}
			if (this->thomDead && !this->hostileAttackThom) {
				sprites.getCombatCounter() = 3;
			}
			//Hostile Attacks Thom
			if (!this->thomDead && !this->hostileAttackThom) {
				getThomHp() -= getHostileStrike();
				sprites.soundCom.play();
				sprites.spriteText[5].setString("Thom          " + std::to_string(getThomHp()) + "/" + std::to_string(getThomHpMax()));
				sprites.text.setString("The hostile strikes Thom!");
				animate.getCombatAnimationLocation() = 3;
				animate.getAnimEnd() = false;//Play Attack Animation
				this->hostileAttackThom = true;
			}
			break;
		case 3:
			this->reInitCombatOnce = false;
			break;
		}
	}
	
}

//Combat Pick Attacks
void Combat::pickMove(sf::RenderWindow& window, Sprites& sprites)
{
	if (this->turnPlayer) {
		this->pickMoveFunc(window, sprites.combatRect[0], this->attackCounter, this->playerPickMove, this->valZero);
		this->pickMoveFunc(window, sprites.combatRect[1], this->attackCounter, this->playerPickMove, this->valOne);
		this->pickMoveFunc(window, sprites.combatRect[2], this->attackCounter, this->playerPickMove, this->valTwo);
	}
	if (this->getTurnZin()) {
		this->pickMoveFunc(window, sprites.combatRect[3], this->zinAttackCounter, this->zinPickMove, this->valZero);
		this->pickMoveFunc(window, sprites.combatRect[4], this->zinAttackCounter, this->zinPickMove, this->valOne);
		this->pickMoveFunc(window, sprites.combatRect[5], this->zinAttackCounter, this->zinPickMove, this->valTwo);
	}
	if (this->getTurnThom()) {
		this->pickMoveFunc(window, sprites.combatRect[6], this->thomAttackCounter, this->thomPickMove, this->valZero);
		this->pickMoveFunc(window, sprites.combatRect[7], this->thomAttackCounter, this->thomPickMove, this->valOne);
	}
}

void Combat::pickMoveFunc(sf::RenderWindow& window, sf::RectangleShape& inputRect, int& counter, int& moveChar, int& moveVal)
{
	sf::Vector2i mousePos = sf::Mouse::getPosition(window);
	sf::Vector2f mousePosF(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y));
	//Player Combat Buttons Functionality
	if (inputRect.getGlobalBounds().contains(mousePosF)) { //If attack button is clicked...
		counter++;
		moveChar = moveVal;
	}
}

void Combat::playerSelectMove(Sprites& sprites, Animation& animate)
{
	switch (this->playerPickMove) {
	case 0:
		Slash(sprites, animate);
		break;
	case 1:
		Guard(sprites, animate);
		break;
	case 2:
		DecayBlade(sprites, animate);
		break;
	}
}

void Combat::zinSelectMove(Sprites& sprites, Animation& animate)
{
	switch (this->zinPickMove) {
	case 0:
		Smite(sprites, animate);
		break;
	case 1:
		Mend(sprites, animate);
		break;
	case 2:
		Vengeance(sprites, animate);
		break;
	}
	
}

void Combat::thomSelectMove(Sprites& sprites, Animation& animate)
{
	switch (this->thomPickMove) {
	case 0:
		Barrier(sprites, animate);
		break;
	case 1:
		Enrage(sprites, animate);
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
		getHostileHp() = 25;
		getHostileHpMax() = 25;
		getHostileStrike() = 5;

		getHostileNameNoSpc() = "Wolf";
		getHostileName() = "Wolf	    ";
		getHostileEncText() = "A wolf leaps out of the bushes, ambushing you!";
		getHostileAtkPlayerText() = "The wolf lunges forwards, biting you!";
		getHostileAtkZinText() = "The wolf jumps towards Zin, biting her!";
		getHostileAtkZinBlkText() = "The wolf leaps in the air towards Zin, however you block it just in time!";

		getPlayerSlashAtkText() = "You slash at the wolf, hitting it!";
		getPlayerGuardAtkText() = "You watch the wolfs movements and prepare yourself to defend Zin...";
		getPlayerDecayAtkText() = "You slash yourself open with your sword, using the decay in your blood to strike the wolf!";

		getZinSmiteAtkText() = "Zin places her hands together and creates a bolt of lightning, striking the wolf!";
		getZinMendAtkText() = "Zin slowly moves her arms outwards, casting a green aura around you and herself, restoring health...";
		getZinVengeanceAtkText() = "Zin uses the blood spilled from your body to create blades made of blood, casting them into the wolf!";
		initHostileWolf = true;
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
		getHostileHp() = 35;
		getHostileHpMax() = 35;
		getHostileStrike() = 2;

		getHostileNameNoSpc() = "Decay Walker";
		getHostileName() = "Decay Walker ";
		getHostileEncText() = "A horrific creature appears before you, threatening your life!";
		getHostileAtkPlayerText() = "The walking pile of decay swings at you, striking you!";
		getHostileAtkZinText() = "The walker jumps towards Zin, hitting her!";
		getHostileAtkZinBlkText() = "The walker leaps towards Zin, however you deflect the attack just in time!";

		getPlayerSlashAtkText() = "You slash at the vile creature, black ooze";
		getPlayerGuardAtkText() = "You watch the walkers movements and prepare yourself to defend Zin...";
		getPlayerDecayAtkText() = "You slash yourself open with your sword, using the decay in your blood to strike the walker!";

		getZinSmiteAtkText() = "Zin places her hands together and creates a bolt of lightning, smiting the unholy creature!";
		getZinMendAtkText() = "Zin slowly moves her arms outwards, casting a green aura around you and herself, restoring health...";
		getZinVengeanceAtkText() = "Zin uses the blood spilled from your body to create blades made of blood, casting them into the walker!";
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
		getHostileHp() = 65;
		getHostileHpMax() = 65;
		getHostileStrike() = 2;

		getHostileNameNoSpc() = "Tree Mimic";
		getHostileName() = "Tree Mimic ";
		getHostileEncText() = "A tree shifts into a horrifying creature, revealing itself and lunging at you!";
		getHostileAtkPlayerText() = "The mimic strikes you with a spiked branch!";
		getHostileAtkZinText() = "The mimic launches at Zin, striking her with a branch!";
		getHostileAtkZinBlkText() = "The mimic rushes towards Zin, however you deflect its strike just in time!";

		getPlayerSlashAtkText() = "You slash at the mimic, slowly chipping away at the wood holding its form.";
		getPlayerGuardAtkText() = "You pay close attention to the mimic, preparing to defend Zin.";
		getPlayerDecayAtkText() = "You slash yourself open with your sword, using the decay in your blood to strike the mimic!";

		getZinSmiteAtkText() = "Zin places her hands together and creates a bolt of lightning, smiting the mimic!";
		getZinMendAtkText() = "Zin slowly moves her arms outwards, casting a green aura around you and herself, restoring health...";
		getZinVengeanceAtkText() = "Zin uses the blood spilled from your body to create blades made of blood, casting them into the mimic!";
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
		getHostileHp() = 100;
		getHostileHpMax() = 100;
		getHostileStrike() = 15;

		getHostileNameNoSpc() = "Decay Knight";
		getHostileName() = "Decay Knight ";
		getHostileEncText() = "You're ambushed by a horrifying knight rotting from decay!";
		getHostileAtkPlayerText() = "The knight lunges forwards with precision, striking you!";
		getHostileAtkZinText() = "The knight swings his sword at Zin, striking her!";
		getHostileAtkZinBlkText() = "The knight lunges his sword towards Zin, however you deflect it just on time!";

		getPlayerSlashAtkText() = "You slash at the knight, attempting to pierce his armor!";
		getPlayerGuardAtkText() = "You watch the knights movements and prepare yourself to defend Zin...";
		getPlayerDecayAtkText() = "You slash yourself open with your sword, using the decay in your blood to strike the knight!";

		getZinSmiteAtkText() = "Zin places her hands together and creates a bolt of lightning, smiting the knight!";
		getZinMendAtkText() = "Zin slowly moves her arms outwards, casting a green aura around you and herself, restoring health...";
		getZinVengeanceAtkText() = "Zin uses the blood spilled from your body to create blades made of blood, casting them into the knight!";
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
		getHostileHp() = 200;
		getHostileHpMax() = 200;
		getHostileStrike() = 1;

		getHostileNameNoSpc() = "Lost Nun";
		getHostileName() = "Lost Nun ";
		getHostileEncText() = "The woman steps forwards, revealing the sheer spread of her decay. She readies to attack you.";
		getHostileAtkPlayerText() = "The nun launches forwards as she spews out rotting decay, brutally striking you!";
		getHostileAtkZinText() = "The nun targets Zin, hitting her with horrifying amounts of molten decay!";
		getHostileAtkZinBlkText() = "The nun targets Zin launching more decay at her, however you deflect it just on time!";

		getPlayerSlashAtkText() = "You slash at the nun, the woman screaming out in pain as you attack.";
		getPlayerGuardAtkText() = "You watch the nuns movements preparing yourself to defend Zin at any cost...";
		getPlayerDecayAtkText() = "You slash yourself open with your sword, using the decay in your blood to strike the nun!";

		getZinSmiteAtkText() = "Zin places her hands together and creates a bolt of lightning, smiting the nun!";
		getZinMendAtkText() = "Zin slowly moves her arms outwards, casting a green aura around you and herself, restoring health and slowly burning away the decay...";
		getZinVengeanceAtkText() = "Zin uses the blood spilled from your body to create blades made of blood, casting them into the nun!";
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
		getHostileHp() = 1;
		getHostileHpMax() = 75;
		getHostileStrike() = 12;

		getHostileNameNoSpc() = "Abyssal Decapod";
		getHostileName() = "Abyssal Decapod ";
		getHostileEncText() = "The horrifying abomination stands before you as its face wriggles with tentacles...";
		getHostileAtkPlayerText() = "The horrifying abomination grabs ahold of you and strikes you violently!";
		getHostileAtkZinText() = "The creature spits acid directly at Zin, hitting her with it!";
		getHostileAtkZinBlkText() = "The abomination attempts to spit at Zin with acid, however you block it with your sword just in time!";

		getPlayerSlashAtkText() = "You slash at the decapod, the creature screaming in pain!";
		getPlayerGuardAtkText() = "You watch the decapods movements, preparing yourself to defend Zin from its attacks...";
		getPlayerDecayAtkText() = "You slash yourself open with your sword, using the decay in your blood to strike the decapod!";

		getZinSmiteAtkText() = "Zin places her hands together and creates a bolt of lightning, smiting the decapod!";
		getZinMendAtkText() = "Zin slowly moves her arms outwards, casting a green aura around you and herself, restoring health and slowly burning away the decay...";
		getZinVengeanceAtkText() = "Zin uses the blood spilled from your body to create blades made of blood, casting them into the decapod!";
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
		getHostileHp() = 75;
		getHostileHpMax() = 75;
		getHostileStrike() = 12;

		getHostileNameNoSpc() = "Haze Demon";
		getHostileName() = "Haze Demon ";
		getHostileEncText() = "The horrifying abomination stands before you as it creatres a strange auora...";
		getHostileAtkPlayerText() = "The horrifying abomination grabs ahold of you and strikes you violently!";
		getHostileAtkZinText() = "The creature splices the air in front Zin, hitting her with the airwaves!";
		getHostileAtkZinBlkText() = "The abomination attempts to split the air towards Zin, however you block it just in time!";

		getPlayerSlashAtkText() = "You slash at the demon, the unholy entity screaming in pain!";
		getPlayerGuardAtkText() = "You watch the demons movements, preparing yourself to defend Zin from its attacks...";
		getPlayerDecayAtkText() = "You slash yourself open with your sword, using the decay in your blood to strike the demon!";

		getZinSmiteAtkText() = "Zin places her hands together and creates a bolt of lightning, smiting the demon!";
		getZinMendAtkText() = "Zin slowly moves her arms outwards, casting a green aura around you and herself, restoring health and slowly burning away the decay...";
		getZinVengeanceAtkText() = "Zin uses the blood spilled from your body to create blades made of blood, casting them into the demon!";
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
		getHostileHp() = 80;
		getHostileHpMax() = 80;
		getHostileStrike() = 20;

		getHostileNameNoSpc() = "Court Jester";
		getHostileName() = "Court Jester ";
		getHostileEncText() = "The jester stands with a horrifying grin...";
		getHostileAtkPlayerText() = "The jester stabs you with a small dagger, brutally injuring you!";
		getHostileAtkZinText() = "The jester sprints towards Zin, stabbing her with his knife!";
		getHostileAtkZinBlkText() = "The jester runs towards Zin with a disgusting smile and a knife in his hand, however you block the knife just in time!";

		getPlayerSlashAtkText() = "You slash at the jester, the clown smiling in pain!";
		getPlayerGuardAtkText() = "You watch the jesters movements, preparing yourself to defend Zin from its attacks...";
		getPlayerDecayAtkText() = "You slash yourself open with your sword, spraying your decayed blood over the jester, causing him to yell in pain!";

		getZinSmiteAtkText() = "Zin places her hands together and creates a bolt of lightning, smiting the jester!";
		getZinMendAtkText() = "Zin slowly moves her arms outwards, casting a green aura around you and herself, restoring health and slowly burning away the decay...";
		getZinVengeanceAtkText() = "Zin uses the blood spilled from your body to create blades made of blood, casting them into the jester!";
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
		getHostileHp() = 80;
		getHostileHpMax() = 80;
		getHostileStrike() = 20;

		getHostileNameNoSpc() = "Wall Mimic";
		getHostileName() = "Wall Mimic ";
		getHostileEncText() = "The walls begin to shift as the face appears before you.";
		getHostileAtkPlayerText() = "The walls shift as the mimic launches towards you, striking you!";
		getHostileAtkZinText() = "The mimic targets Zin, striking her with extreme force!";
		getHostileAtkZinBlkText() = "The mimic attempts to bite Zin, however you tackle her out of the way just in time!";

		getPlayerSlashAtkText() = "You slash at the mimic, the walls echoing back with screams!";
		getPlayerGuardAtkText() = "You watch the movements of the walls carefully, preparing yourself to defend Zin from its attacks...";
		getPlayerDecayAtkText() = "You slash yourself open with your sword, spraying your decayed blood over the walls and ceiling striking the mimic!";

		getZinSmiteAtkText() = "Zin places her hands together and creates a bolt of lightning that obliterates the ceiling and strikes the mimic!";
		getZinMendAtkText() = "Zin slowly moves her arms outwards, casting a green aura around you and herself, restoring health and slowly burning away the decay...";
		getZinVengeanceAtkText() = "Zin uses the blood spilled from your body to create blades made of blood, casting them into the walls!";
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
		getHostileHp() = 100;
		getHostileHpMax() = 100;
		getHostileStrike() = 25;

		getHostileNameNoSpc() = "Lost Knight";
		getHostileName() = "Lost Knight ";
		getHostileEncText() = "The knight stands in protest, ready to fight to the death...";
		getHostileAtkPlayerText() = "The knight stabs you with his sword!";
		getHostileAtkZinText() = "The knight dashes towards Zin, slightly hesitanting due to her being a child. Despite this, he still strikes her!";
		getHostileAtkZinBlkText() = "The knight dashes towards Zin slashing at her, however you block the blade just in time!";

		getPlayerSlashAtkText() = "You slash at the knight, the knight gritting his teeth in pain!";
		getPlayerGuardAtkText() = "You watch the knights movements, preparing yourself to defend Zin from his attacks...";
		getPlayerDecayAtkText() = "You slash yourself open with your sword, spraying your decayed blood into the knights helmet! He begins coughing and choking in pain!";

		getZinSmiteAtkText() = "Zin places her hands together and creates a bolt of lightning, smiting the knight!";
		getZinMendAtkText() = "Zin slowly moves her arms outwards, casting a green aura around you and herself, restoring health and slowly burning away the decay...";
		getZinVengeanceAtkText() = "Zin uses the blood spilled from your body to create blades made of blood, casting them into the knight!";
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
		getHostileHp() = 120;
		getHostileHpMax() = 120;
		getHostileStrike() = 10;

		getHostileNameNoSpc() = "Phantom";
		getHostileName() = "Phantom ";
		getHostileEncText() = "The phantom phases into existence right before you, charging...";
		getHostileAtkPlayerText() = "The phantom appears right before you, striking you before you can react!";
		getHostileAtkZinText() = "The phantom vanishes before reappearing next to Zin, using the opprotunity to strike her!";
		getHostileAtkZinBlkText() = "The phantom runs towards Zin with a disgusting smirk, however you block the attack just in time!";

		getPlayerSlashAtkText() = "You slash at the phantom, its physical form being caught by your blade!";
		getPlayerGuardAtkText() = "You watch the phantoms movements, preparing yourself to defend Zin from its attacks...";
		getPlayerDecayAtkText() = "You slash yourself open with your sword, spraying your decayed blood over the phantom!";

		getZinSmiteAtkText() = "Zin places her hands together and creates a bolt of lightning, smiting the phantom!";
		getZinMendAtkText() = "Zin slowly moves her arms outwards, casting a green aura around you and herself, restoring health and slowly burning away the decay...";
		getZinVengeanceAtkText() = "Zin uses the blood spilled from your body to create blades made of blood, casting them into the phantom!";
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
		getHostileHp() = 65;
		getHostileHpMax() = 65;
		getHostileStrike() = 8;

		getHostileNameNoSpc() = "Skin Eater";
		getHostileName() = "Skin Eater ";
		getHostileEncText() = "The skin eater stands with a horrifying face, locking eyes with you...";
		getHostileAtkPlayerText() = "The skin eater attempts to bite you but only grazes you!";
		getHostileAtkZinText() = "The skin eater sprints towards Zin, lunging at her and striking her!";
		getHostileAtkZinBlkText() = "The skin eater runs towards Zin, however you pull Zin out of the way just in time!";

		getPlayerSlashAtkText() = "You slash at the skin eater, the abomination screaming in pain!";
		getPlayerGuardAtkText() = "You watch the skin eaters movements, preparing yourself to defend Zin from its attacks...";
		getPlayerDecayAtkText() = "You slash yourself open with your sword, spraying your decayed blood over the skin eater, causing it to yell in pain!";

		getZinSmiteAtkText() = "Zin places her hands together and creates a bolt of lightning, smiting the skin eater!";
		getZinMendAtkText() = "Zin slowly moves her arms outwards, casting a green aura around you and herself, restoring health and slowly burning away the decay...";
		getZinVengeanceAtkText() = "Zin uses the blood spilled from your body to create blades made of blood, casting them into the skin eater!";
		this->initHostileEater = true;
	}
}

void Combat::initSiward(Sprites& sprites)
{
	if (!this->initHostileSiward) {
		//Combat Text for Siward (Due to him having a seperate sprite sheet from hostiles)
		sprites.spriteText[2].setPosition(sf::Vector2f(1650.0f, 453.0f));
		//Allow combat to start
		this->combatEnd = false;
		//Allow new combat to start
		this->initCombatOnce = false;
		this->reInitCombatOnce = false;
		//Set parameters for hostile
		getHostileHp() = 500;
		getHostileHpMax() = 1000;
		getHostileStrike() = 40;

		getHostileNameNoSpc() = "Siward";
		getHostileName() = "Siward ";
		getHostileEncText() = "Siward stands with decay dripping from the front of his helmet...";
		getHostileAtkPlayerText() = "Siward slashes his sword at you with the precision of a true knight!";
		getHostileAtkZinText() = "Siward slashes towards Zin, brutally striking her!";
		getHostileAtkZinBlkText() = "Siward sends his sword towards Zin with great might, however you deflect it just in time!";

		getPlayerSlashAtkText() = "You slash Siward, the knight gritting his teeth in pain!";
		getPlayerGuardAtkText() = "You watch Siward's movements, preparing to defend Zin from his brutal strikes...";
		getPlayerDecayAtkText() = "You slash yourself open with your sword, spraying your decayed blood over Siward, though it seems to have little effect...";

		getZinSmiteAtkText() = "Zin places her hands together reluctantly and creates a bolt of lightning, smiting Siward!";
		getZinMendAtkText() = "Zin slowly moves her arms outwards, casting a green aura around you and herself, restoring health and slowly burning away the decay...";
		getZinVengeanceAtkText() = "Zin uses the blood spilled from your body to create blades made of blood, casting them into Siward!";
		this->initHostileSiward = true;
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
		getHostileHp() = 250;
		getHostileHpMax() = 250;
		getHostileStrike() = 40;

		getHostileNameNoSpc() = "Limb Splitter";
		getHostileName() = "Limb Splitter ";
		getHostileEncText() = "The limb splitter stares you down, waiting for its meal...";
		getHostileAtkPlayerText() = "The limb splitter strikes you with one of its ligaments!";
		getHostileAtkZinText() = "The limb splitter catches Zin off guard, striking her with one of its arms!";
		getHostileAtkZinBlkText() = "The limb splitter attempts to impale Zin with one of its arms, however you tackle her out of the way just in time!";

		getPlayerSlashAtkText() = "You slash at the limb splitter, the abomination screaming in pain!";
		getPlayerGuardAtkText() = "You watch the limb splitters ligaments, preparing yourself to defend Zin from its attacks...";
		getPlayerDecayAtkText() = "You slash yourself open with your sword, spraying your decayed blood over the limb splitter, causing it to screech in pain!";

		getZinSmiteAtkText() = "Zin places her hands together and creates a bolt of lightning, smiting the limb splitter!";
		getZinMendAtkText() = "Zin slowly moves her arms outwards, casting a green aura around you and herself, restoring health and slowly burning away the decay...";
		getZinVengeanceAtkText() = "Zin uses the blood spilled from your body to create blades made of blood, casting them into the limb splitter!";
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
		getHostileHp() = 250;
		getHostileHpMax() = 250;
		getHostileStrike() = 40;

		getHostileNameNoSpc() = "Burrower";
		getHostileName() = "Burrower ";
		getHostileEncText() = "The burrower quickly rushes towards you, ready to attack...";
		getHostileAtkPlayerText() = "The burrower crashes up from the ground, striking you with its spiked body!";
		getHostileAtkZinText() = "The burrower catches Zin off guard, striking with one of its spiked quills!";
		getHostileAtkZinBlkText() = "The burrower bursts from the wall, attempting to consume Zin whole, however you tackle her out of the way just in time!";

		getPlayerSlashAtkText() = "You slash at the burrower, the abomination bleeding across the crimson floor!";
		getPlayerGuardAtkText() = "You listen to the burrowers movements in the walls, preparing yourself to defend Zin from its attacks...";
		getPlayerDecayAtkText() = "You slash yourself open with your sword, spraying your decayed blood over the burrower, causing it to scream out in pain!";

		getZinSmiteAtkText() = "Zin places her hands together and creates a bolt of lightning, smiting the burrower!";
		getZinMendAtkText() = "Zin slowly moves her arms outwards, casting a green aura around you and herself, restoring health and slowly burning away the decay...";
		getZinVengeanceAtkText() = "Zin uses the blood spilled from your body to create blades made of blood, casting them into the burrower!";
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
		getHostileHp() = 265;
		getHostileHpMax() = 265;
		getHostileStrike() = 20;

		getHostileNameNoSpc() = "Chatter Mouth";
		getHostileName() = "Chatter Mouth ";
		getHostileEncText() = "The chatter mouth quickly rushes towards you, ready to attack...";
		getHostileAtkPlayerText() = "The chatter mouth uses its wide body to swing around the limited cave space, smashing you into the wall!";
		getHostileAtkZinText() = "The chatter mouths body strikes Zin as it swings it violently!";
		getHostileAtkZinBlkText() = "The chatter mouth attempts to drag Zin into its serrated mouth, however you firmly grab ahold of Zin's arm and pull her out of its grasp!";

		getPlayerSlashAtkText() = "You slash at the chatter mouth, the abomination bleeding across the crimson floor!";
		getPlayerGuardAtkText() = "You watch the chatter mouths movements, preparing yourself to defend Zin from its attacks...";
		getPlayerDecayAtkText() = "You slash yourself open with your sword, spraying your decayed blood over the chatter mouth, causing it to scream out in pain!";

		getZinSmiteAtkText() = "Zin places her hands together and creates a bolt of lightning, smiting the chatter mouth!";
		getZinMendAtkText() = "Zin slowly moves her arms outwards, casting a green aura around you and herself, restoring health and slowly burning away the decay...";
		getZinVengeanceAtkText() = "Zin uses the blood spilled from your body to create blades made of blood, casting them into the chatter mouth!";
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
		getHostileHp() = 265;
		getHostileHpMax() = 265;
		getHostileStrike() = 20;

		getHostileNameNoSpc() = "Reclus";
		getHostileName() = "Reclus ";
		getHostileEncText() = "The reclus moves quickly rushing forwards ready to attack...";
		getHostileAtkPlayerText() = "The reclus smashes you with its hand into the wall!";
		getHostileAtkZinText() = "The reclus drags its hand across the floor, striking Zin!";
		getHostileAtkZinBlkText() = "The reclus mouth attempts to drag Zin into its serrated mouth, however you firmly grab ahold of Zin's arm and pull her out of its grasp!";

		getPlayerSlashAtkText() = "You slash at the reclus, the abomination bleeding across the crimson floor!";
		getPlayerGuardAtkText() = "You watch the reclus carefully, preparing yourself to defend Zin from its attacks...";
		getPlayerDecayAtkText() = "You slash yourself open with your sword, spraying your decayed blood over the reclus, causing it to scream out in pain!";

		getZinSmiteAtkText() = "Zin places her hands together and creates a bolt of lightning, smiting the reclus!";
		getZinMendAtkText() = "Zin slowly moves her arms outwards, casting a green aura around you and herself, restoring health and slowly burning away the decay...";
		getZinVengeanceAtkText() = "Zin uses the blood spilled from your body to create blades made of blood, casting them into the reclus!";
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
		getHostileHp() = 400;
		getHostileHpMax() = 400;
		getHostileStrike() = 25;

		getHostileNameNoSpc() = "Tendril Alpha";
		getHostileName() = "Tendril Alpha ";
		getHostileEncText() = "The abomination moves quickly rushing forwards ready to attack...";
		getHostileAtkPlayerText() = "The abomination smashes one of its tendrils into you!";
		getHostileAtkZinText() = "The abomination strikes Zin with one of its tendrils!";
		getHostileAtkZinBlkText() = "The alpha attempts to swarm Zin with its tendrils, however you jump in between each tendril slicing them away!";

		getPlayerSlashAtkText() = "You slash at the alpha, its body squirming in pain!";
		getPlayerGuardAtkText() = "You watch the abominations tendrils carefully, preparing yourself to defend Zin from its attacks...";
		getPlayerDecayAtkText() = "You slash yourself open with your sword, spraying your decayed blood over the alpha, causing it to quiver!";

		getZinSmiteAtkText() = "Zin places her hands together and creates a bolt of lightning, smiting the alpha!";
		getZinMendAtkText() = "Zin slowly moves her arms outwards, casting a green aura around you and herself, restoring health and slowly burning away the decay...";
		getZinVengeanceAtkText() = "Zin uses the blood spilled from your body to create blades made of blood, casting them into the alpha!";
		this->initHostileTendrilAlpha = true;
	}
}