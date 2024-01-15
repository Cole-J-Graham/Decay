#include "Combat.h"

//Constructors & Destructors
Combat::Combat()
{
	//Move Values
	this->valZero = 0;
	this->valOne = 1;
	this->valTwo = 2;
	this->valThree = 3;
	this->valFour = 4;
	this->valFive = 5;

	//Attack Counters
	this->attackCounter = 0;
	this->zinAttackCounter = 0;
	this->thomAttackCounter = 0;

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
	this->initHostileDecapod = false;
	this->initHostileHazeDemon = false;

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
	this->initHostileSpade = false;
	this->initHostileRotBeast = false;

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

	//Combat Rewards
	this->increase = false;
	this->expGain = 0;

	//Animation Control
	this->comTextRemoved = true;

	//Music Bools
	this->replayMusic = false;
}

Combat::~Combat()
{

}

//Core Stat Functions
void Combat::updateStats()
{
	//Strength Modifiers
	getPlayerStrike() = 5 + getStrength() + getSwordPower();
	getPlayerHeftyBlow() = 25 + getStrength() + getSwordPower();

	//Vitality Modifiers
	getPlayerHpMax() = 50 + getVitality();
	getPlayerHp() = getPlayerHpMax();


	//Fortitude Modifiers
	getDecayMax() = 25 + getFortitude();
	getIronWall() = 10 + getFortitude();

	//Other Modifiers
	getPlayerDecayingSynDmg() = 3 + getDecay();
	getPlayerDecayingSynDef() = 10 + getDecay();
	getPlayerDecayedBlade()  = 10 + getDecay();
	getPlayerHp() = getPlayerHpMax();

	//Resolve Modifiers
	getZinSmite() = 5 + getZinResolve();
	getZinBlaze() = 45 + getZinResolve();
	getCrimsonFlames() = 25 + getZinResolve();

	//Resilience Modifiers
	getZinHp() = 35 + getZinResilience();

	//Patience Modifiers
	getZinMend() = 5 + getZinPatience();
	getZinFocus() = 40 + getZinPatience();

	//Other Modifiers
	getZinHpMax() = getZinHp();
}

void Combat::unlockMoves()
{
	switch (getLevel()) {
	case 5:
		//Unlock Guard
		getCombatPlayerMoves() = 1;
		text.setString("Move 'Guard' learned!");
		break;
	case 15:
		//Unlock Decayed Blade
		getCombatPlayerMoves() = 2;
		text.setString("Move 'Decayed Blade' learned!");
		break;
	case 20:
		//Unlock Hefty blow
		getCombatPlayerMoves() = 3;
		text.setString("Move 'Hefty Blow' learned!");
		break;
	case 30:
		//Unlock Decaying Synergy
		getCombatPlayerMoves() = 4;
		text.setString("Move 'Decaying Synergy' learned!");
		break;
	case 40:
		//Unlock Iron Wall
		getCombatPlayerMoves() = 5;
		text.setString("Move 'Iron Wall' learned!");
		break;
	}

	switch (getZinLevel()) {
	case 5:
		//Unlock Mend
		getCombatZinMoves() = 1;
		text.setString("Move 'Mend' learned!");
		break;
	case 10:
		//Unlock Vengeance
		getCombatZinMoves() = 2;
		text.setString("Move 'Vengeance' learned!");
		break;
	case 15:
		//Unlock Hellish Blaze
		getCombatZinMoves() = 3;
		text.setString("Move 'Hellish Blaze' learned!");
		break;
	case 25:
		//Unlock Focused Healing
		getCombatZinMoves() = 4;
		text.setString("Move 'Focused Healing' learned!");
		break;
	case 35:
		//Unlock Crimson Flames
		getCombatZinMoves() = 5;
		text.setString("Move 'Crimson Flames' learned!");
		break;
	}
}

void Combat::combatReward()
{
	if (!this->increase) {
		getExp() += this->expGain;
		getZinExp() += this->expGain;
		this->increase = true;
	}
}

//Core Combat Functions
void Combat::combatLoop(sf::RenderWindow& window, Animation& animate)
{
	if (!combatEnd) {
		//Combat Animations
		if (!animate.getAnimEnd()) {
			animate.pickAnimation();
		}
		//Begin combat loop initialization
		if (initCombatOnce == false) {
			this->initCombat();
			initCombatOnce = true;
		} //Reinitialize the combat loop for each pass
		else if (reInitCombatOnce == false) {
			this->reInitCombat();
			reInitCombatOnce = true;
		}
		//Players turn
		if (!this->playerDead) {
			this->playerTurn(window, animate);
		}
		//Zin's Turn
		if (!this->zinDead) {
			this->zinTurn(animate);
		}
		if (!this->thomDead) {
			this->thomTurn(animate);
		}
		//Check if hostile is dead. If soend combat
		if (getHostileHp() <= 0) {
			setCombatAssetsFalse();
			this->combatReward();
			text.setString("You have killed the " + getHostileNameNoSpc() + ". " + std::to_string(getExp()) + " Exp gained...");
			combatTextTime.restart();//Start timer to remove text
			this->comTextRemoved = false;//Remove text
			//Make entity viewer blank again
			getEntityViewerCounter() = -1;
			getFatigued() = 0;
			getThomEnraged() = false;
			getZinFatigue() = false;
			getPlayerFatigue() = false;
			getTipBoxCounter() = -1;
			this->replayMusic = false;
			this->combatEnd = true;
		}
		//Hostiles turn
		this->hostileTurn(animate);
		//Check if playerZinor Thom has died
		if (getPlayerHp() <= 0 && !this->playerDead) {
			this->playerDead = true;
			text.setString("You have been left unconscious...");
		}
		if (getZinHp() <= 0 && !this->zinDead) {
			this->zinDead = true;
			text.setString("Zin has been left unconscious...");
		}
		if (getThomHp() <= 0 && !this->thomDead) {
			this->thomDead = true;
			text.setString("Thom has been left unconscious...");
		}
		//Check if both the player and Zin have died
		if (getPlayerHp() <= 0 && getZinHp() <= 0) {
			this->playerDeath();
			text.setString("Your party has died...");
		}
	}
}

void Combat::initCombat()
{
	soundCombatStart.play(); //Play combat Sfx
	//this->updateStats(assetsplayer);
	text.setString(getHostileEncText());
	spriteText[0].setString(getPlayerName() + "     " + std::to_string(getPlayerHp()) + "/" + std::to_string(getPlayerHpMax()));
	spriteText[1].setString("Zin            " + std::to_string(getZinHp()) + "/" + std::to_string(getZinHpMax()));
	spriteText[2].setString(getHostileName() + std::to_string(getHostileHp()) + "/" + std::to_string(getHostileHpMax()));

	getPlayerCounter()++; //Load Player sprite with counter
	getZinCounter()++; //Load Zins sprite with counter
	//Load Thom Sprite with counter if he is unlocked
	if (getThomUnlocked()) {
		getThomCounter()++;
		spriteText[5].setString("Thom          " + std::to_string(getThomHp()) + "/" + std::to_string(getThomHpMax()));
	}

	setCombatAssetsTrue(); //Utilize all combat assets
	setInitMapFalse(); //Hide the map if its open
	setInitStatsFalse(); //Hide stats if open
	setInitInventoryFalse(); //Hide inventory if open

	getFirstAttack() = false;
}

void Combat::reInitCombat()
{
	//Re init Hostile
	this->hostileAttack = false;
	this->hostileAttackZin = false;
	this->hostileAttackThom = false;
	this->turnHostile = false;
	getCombatCounter() = 0;

	//Re init thom if he is unlocked
	if (getThomUnlocked()) {
		this->turnThom = false;
		this->thomAttackCounter = 0;
		this->thomAttack = false;
		getPlayerGuarded() = false;
		getThomTurnAssets() = false;
	}

	//Re init characters if both are alive
	if (!this->playerDead && !this->zinDead) {
		//Player
		setPlayerTurnAssetsTrue();
		this->turnPlayer = true;
		this->attackCounter = 0;
		getZinGuarded() = false;
		this->playerAttack = false;
		//Zin
		setZinTurnAssetsFalse();
		this->turnZin = false;
		this->zinAttackCounter = 0;
		this->zinAttack = false;
	}//Re init zin if she is alive and player is dead
	else if (this->playerDead && !this->zinDead) {
		//Player
		setPlayerTurnAssetsFalse();
		this->turnPlayer = false;
		//Zin
		setZinTurnAssetsTrue();
		this->turnZin = true;
		this->zinAttackCounter = 0;
		this->zinAttack = false;
	}//Re init player if he is alive and zin is dead
	else if (!this->playerDead && this->zinDead) {
		//Player
		this->turnPlayer = true;
		this->attackCounter = 0;
		getZinGuarded() = false;
		this->playerAttack = false;
		//Zin
		setZinTurnAssetsFalse();
		this->turnZin = false;
	}
}

void Combat::playerDeath()
{
	setCombatAssetsFalse();
	setPlayerDeathTrue();
}

//Combat Functions
void Combat::playerTurn(sf::RenderWindow& window, Animation& animate)
{
	if (this->turnPlayer == true) {
		switch (this->attackCounter) {
		case 0:
			if (!getPlayerFatigue()) {
				//Check if the player is fatiguedif not continue turn as normal
				setPlayerTurnAssetsTrue();
				text.setString(getPlayerTurnText());
			}
			else if (getPlayerFatigue()) {
				text.setString("You are forced to take a moment to breathe after your last attack...");
			}
			break;
		case 1:
			if (!this->playerAttack && !getPlayerFatigue()) {
				this->playerSelectMove(animate);
				this->playerAttack = true;
			}
			else if (getPlayerFatigue() && !this->playerAttack) {
				getPlayerFatigue() = false;
				getPlayerTurnAssets() = false;
				this->attackCounter = 2;
				this->playerAttack = true;
			}
			break;
		case 2:
			this->turnPlayer = false;
			if (getThomUnlocked()) {
				//Check who's alive and set it to their turn
				if (!this->zinDead) {
					this->turnZin = true;
				}
				else if (this->zinDead && !this->thomDead) {
					this->turnThom = true;
				}
				else if (this->zinDead && this->thomDead) {
					this->turnHostile = true;
				}
			} else if (!getThomUnlocked()) {
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

void Combat::zinTurn(Animation& animate)
{
	if (this->turnZin == true) {
		switch (this->zinAttackCounter) {
		case 0:
			if (!getZinFatigue()) {
				//Check if Zin is fatiguedif not continue turn as normal
				text.setString(getZinTurnText());
				setZinTurnAssetsTrue();
			}
			else if (getZinFatigue()) {
				text.setString("Zin can hardly stand after her last attack... She takes a moment to rest...");
			}
			break;
		case 1:
			//Zin Attacks Hostile
			if (!getZinFatigue() && !this->zinAttack) {
				this->zinSelectMove(animate);
				this->zinAttack = true;
			}
			else if (getZinFatigue() && !this->zinAttack) {
				getFatigued()--;
				if (getFatigued() == 0) {
					getZinFatigue() = false;
					getZinTurnAssets() = false;
					text.setString("Zin finally catches her breathready to fight once more...");
				}
				this->zinAttackCounter = 2;
				this->zinAttack = true;
			}
			break;
		case 2:
			if (this->thomDead) {
				this->turnHostile = true;
			}
			if (getThomUnlocked() && !this->thomDead) {
				this->turnZin = false;
				this->turnThom = true;
			} else if (!getThomUnlocked()) {
				this->turnZin = false;
				this->turnHostile = true;
			}
			break;
		}
	}
}

void Combat::thomTurn(Animation& animate)
{
	if (this->turnThom == true) {
		switch (this->thomAttackCounter) {
		case 0:
			if (!getThomEnraged()) {
				text.setString("Thom prepares his next move");
				setThomTurnAssetsTrue();
			}
			else if (getThomEnraged()) {
				this->thomAttackCounter = 1;
			}
			break;
		case 1:
			//Thoms turn
			if (!this->thomAttack && !getThomEnraged()) {
				this->thomSelectMove(animate);
				this->thomAttack = true;
			}
			else if (this->thomAttack == false && getThomEnraged()) {
				text.setString("Thom still stands in a state of pure rage...");
				getEnraged()--;
				if (getEnraged() == 0) {
					getThomEnraged() = false;
					getThomCounter() = 0;
					text.setString("Thom snaps out of his rage!");
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

void Combat::hostileTurn(Animation& animate)
{
	if (this->turnHostile == true) {
		switch (getCombatCounter()) {
		case 0:
			//Hostile Attacks Player
			if (this->playerDead && !this->hostileAttack) {
				getCombatCounter() = 1;
			}
			if (!this->hostileAttack && !getPlayerGuarded()) {
				getPlayerHp() -= getHostileStrike();
				soundCom.play();
				spriteText[0].setString(getPlayerName() + "     " + std::to_string(getPlayerHp()) + "/" + std::to_string(getPlayerHpMax()));
				text.setString(getHostileAtkPlayerText());
				animate.getCombatAnimationLocation() = 1;
				animate.getAnimation() = 0;
				animate.getAnimEnd() = false;//Play Attack Animation
				this->hostileAttack = true;
			}
			else if (!this->hostileAttack && getPlayerGuarded()) {
				text.setString(getHostileAtkPlayerBlkText());
				soundPlayerGuarded.play();
				animate.getCombatAnimationLocation() = 1;
				animate.getAnimation() = 3;
				animate.getAnimEnd() = false;//Play Attack Animation
				this->hostileAttack = true;
			}
			break;
		case 1:
			//Hostile Attacks Zin
			if (this->zinDead && !this->hostileAttackZin) {
				getCombatCounter() = 2;
			}
			if (!getZinGuarded() && !this->hostileAttackZin && !this->zinDead) {
				getZinHp() -= getHostileStrike();
				soundCom.play();
				spriteText[1].setString("Zin            " + std::to_string(getZinHp()) + "/" + std::to_string(getZinHpMax()));
				text.setString(getHostileAtkZinText());
				animate.getCombatAnimationLocation() = 2;
				animate.getAnimation() = 0;
				animate.getAnimEnd() = false;//Play Attack Animation
				this->hostileAttackZin = true;
			}
			else if (getZinGuarded() == true && !this->hostileAttackZin && !this->zinDead) {
				soundGuarded.play();
				text.setString(getHostileAtkZinBlkText());
				animate.getCombatAnimationLocation() = 2;
				animate.getAnimation() = 3;
				animate.getAnimEnd() = false;//Play Attack Animation
				this->hostileAttackZin = true;
			}
			break;
		case 2:
			//Check if Thom is unlocked. If notskip entirely.
			if (!getThomUnlocked()) {
				getCombatCounter() = 3;
			}
			if (this->thomDead && !this->hostileAttackThom) {
				getCombatCounter() = 3;
			}
			//Hostile Attacks Thom
			if (!this->thomDead && !this->hostileAttackThom && getThomUnlocked()) {
				getThomHp() -= getHostileStrike();
				soundCom.play();
				spriteText[5].setString("Thom          " + std::to_string(getThomHp()) + "/" + std::to_string(getThomHpMax()));
				text.setString("The hostile strikes Thom!");
				animate.getCombatAnimationLocation() = 3;
				animate.getAnimation() = 0;
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
void Combat::pickMove(sf::RenderWindow& window)
{
	if (this->turnPlayer) {
		this->pickMoveFunc(window, combatRect[0], this->attackCounter, this->playerPickMove, this->valZero);
		this->pickMoveFunc(window, combatRect[1], this->attackCounter, this->playerPickMove, this->valOne);
		this->pickMoveFunc(window, combatRect[2], this->attackCounter, this->playerPickMove, this->valTwo);
		this->pickMoveFunc(window, combatRect[3], this->attackCounter, this->playerPickMove, this->valThree);
		this->pickMoveFunc(window, combatRect[4], this->attackCounter, this->playerPickMove, this->valFour);
		this->pickMoveFunc(window, combatRect[5], this->attackCounter, this->playerPickMove, this->valFive);
	}
	if (this->getTurnZin()) {
		this->pickMoveFunc(window, combatRect[6], this->zinAttackCounter, this->zinPickMove, this->valZero);
		this->pickMoveFunc(window, combatRect[7], this->zinAttackCounter, this->zinPickMove, this->valOne);
		this->pickMoveFunc(window, combatRect[8], this->zinAttackCounter, this->zinPickMove, this->valTwo);
		this->pickMoveFunc(window, combatRect[9], this->zinAttackCounter, this->zinPickMove, this->valThree);
		this->pickMoveFunc(window, combatRect[10], this->zinAttackCounter, this->zinPickMove, this->valFour);
		this->pickMoveFunc(window, combatRect[11], this->zinAttackCounter, this->zinPickMove, this->valFive);
	}
	if (this->getTurnThom()) {
		this->pickMoveFunc(window, combatRect[12], this->thomAttackCounter, this->thomPickMove, this->valZero);
		this->pickMoveFunc(window, combatRect[13], this->thomAttackCounter, this->thomPickMove, this->valOne);
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

void Combat::playerSelectMove(Animation& animate)
{
	switch (this->playerPickMove) {
	case 0:
		slash(animate);
		break;
	case 1:
		guard(animate);
		break;
	case 2:
		decayBlade(animate);
		break;
	case 3:
		heftyBlow(animate);
		break;
	case 4:
		decaySynergy(animate);
		break;
	case 5:
		ironWall(animate);
		break;
	}
}

void Combat::zinSelectMove(Animation& animate)
{
	switch (this->zinPickMove) {
	case 0:
		smite(animate);
		break;
	case 1:
		mend(animate);
		break;
	case 2:
		vengeance(animate);
		break;
	case 3:
		hellBlaze(animate);
		break;
	case 4:
		focusHeal(animate);
		break;
	case 5:
		crimsonFlames(animate);
		break;
	}
	
}

void Combat::thomSelectMove(Animation& animate)
{
	switch (this->thomPickMove) {
	case 0:
		barrier(animate);
		break;
	case 1:
		enrage(animate);
		break;
	}
}

//Combat Init Forest Hostiles
void Combat::initWolf()
{
	if (!this->initHostileWolf) {
		track1.pause();
		track5.play();
		//Make entity viewer visible
		getSpriteViewerCounter() = 0;
		//Make wolf entity visible
		getEntityViewerCounter() = 9;
		//Allow combat to start
		this->combatEnd = false;
		//Set wolf sprite
		getHostileCounter() = 1;
		//Allow new combat to start
		this->initCombatOnce = false;
		this->reInitCombatOnce = false;
		//Set parameters for hostile
		this->increase = false;
		this->expGain = 185;
		getHostileHp() = 25;
		getHostileHpMax() = 25;
		getHostileStrike() = 5;

		getHostileNameNoSpc() = "Wolf";
		getHostileName() = "Wolf	    ";
		getHostileEncText() = "A wolf leaps out of the bushesambushing you!";
		getHostileAtkPlayerText() = "The wolf lunges forwardsbiting you!";
		getHostileAtkZinText() = "The wolf jumps towards Zinbiting her!";
		getHostileAtkZinBlkText() = "The wolf leaps in the air towards Zinhowever you block it just in time!";

		getPlayerSlashAtkText() = "You slash at the wolfhitting it!";
		getPlayerGuardAtkText() = "You watch the wolfs movements and prepare yourself to defend Zin...";
		getPlayerDecayAtkText() = "You slash yourself open with your swordusing the decay in your blood to strike the wolf!";

		getZinSmiteAtkText() = "Zin places her hands together and creates a bolt of lightningstriking the wolf!";
		getZinMendAtkText() = "Zin slowly moves her arms outwardscasting a green aura around you and herselfrestoring health...";
		getZinVengeanceAtkText() = "Zin uses the blood spilled from your body to create blades made of bloodcasting them into the wolf!";
		initHostileWolf = true;
	}
}

void Combat::initDecayWalker()
{
	if (!this->initHostileWalker) {
		track1.pause();
		track5.play();
		//Make entity viewer visible
		getSpriteViewerCounter() = 0;
		//Make decay walker entity visible
		getEntityViewerCounter() = 1;
		//Allow combat to start
		this->combatEnd = false;
		//Set walker sprite
		getHostileCounter() = 2;
		//Allow new combat to start
		this->initCombatOnce = false;
		this->reInitCombatOnce = false;
		//Set parameters for hostile
		this->increase = false;
		this->expGain = 354;
		getHostileHp() = 35;
		getHostileHpMax() = 35;
		getHostileStrike() = 3;

		getHostileNameNoSpc() = "Decay Walker";
		getHostileName() = "Decay Walker ";
		getHostileEncText() = "A horrific creature appears before youthreatening your life!";
		getHostileAtkPlayerText() = "The walking pile of decay swings at youstriking you!";
		getHostileAtkZinText() = "The walker jumps towards Zinhitting her!";
		getHostileAtkZinBlkText() = "The walker leaps towards Zinhowever you deflect the attack just in time!";

		getPlayerSlashAtkText() = "You slash at the vile creatureblack ooze";
		getPlayerGuardAtkText() = "You watch the walkers movements and prepare yourself to defend Zin...";
		getPlayerDecayAtkText() = "You slash yourself open with your swordusing the decay in your blood to strike the walker!";

		getZinSmiteAtkText() = "Zin places her hands together and creates a bolt of lightningsmiting the unholy creature!";
		getZinMendAtkText() = "Zin slowly moves her arms outwardscasting a green aura around you and herselfrestoring health...";
		getZinVengeanceAtkText() = "Zin uses the blood spilled from your body to create blades made of bloodcasting them into the walker!";
		this->initHostileWalker = true;
	}
}

void Combat::initHostileTree()
{
	if (!this->initHostileTreeMimic) {
		track1.pause();
		track5.play();
		//Make entity viewer visible
		getSpriteViewerCounter() = 0;
		//Make tree mimic entity visible
		getEntityViewerCounter() = 5;
		//Allow combat to start
		this->combatEnd = false;
		//Set tree mimic sprite
		getHostileCounter() = 4;
		//Allow new combat to start
		this->initCombatOnce = false;
		this->reInitCombatOnce = false;
		//Set parameters for hostile
		this->increase = false;
		this->expGain = 384;
		getHostileHp() = 65;
		getHostileHpMax() = 65;
		getHostileStrike() = 2;

		getHostileNameNoSpc() = "Tree Mimic";
		getHostileName() = "Tree Mimic ";
		getHostileEncText() = "A tree shifts into a horrifying creaturerevealing itself and lunging at you!";
		getHostileAtkPlayerText() = "The mimic strikes you with a spiked branch!";
		getHostileAtkZinText() = "The mimic launches at Zinstriking her with a branch!";
		getHostileAtkZinBlkText() = "The mimic rushes towards Zinhowever you deflect its strike just in time!";

		getPlayerSlashAtkText() = "You slash at the mimicslowly chipping away at the wood holding its form.";
		getPlayerGuardAtkText() = "You pay close attention to the mimicpreparing to defend Zin.";
		getPlayerDecayAtkText() = "You slash yourself open with your swordusing the decay in your blood to strike the mimic!";

		getZinSmiteAtkText() = "Zin places her hands together and creates a bolt of lightningsmiting the mimic!";
		getZinMendAtkText() = "Zin slowly moves her arms outwardscasting a green aura around you and herselfrestoring health...";
		getZinVengeanceAtkText() = "Zin uses the blood spilled from your body to create blades made of bloodcasting them into the mimic!";
		this->initHostileTreeMimic = true;
	}
}

void Combat::initDecayKnight()
{
	if (!this->initHostileKnight) {
		track1.pause();
		track5.play();
		//Make entity viewer visible
		getSpriteViewerCounter() = 0;
		//Make tree mimic entity visible
		getEntityViewerCounter() = 10;
		//Allow combat to start
		this->combatEnd = false;
		//Set wolf sprite
		getHostileCounter() = 3;
		//Allow new combat to start
		this->initCombatOnce = false;
		this->reInitCombatOnce = false;
		//Set parameters for hostile
		this->increase = false;
		this->expGain = 672;
		getHostileHp() = 100;
		getHostileHpMax() = 100;
		getHostileStrike() = 7;

		getHostileNameNoSpc() = "Decay Knight";
		getHostileName() = "Decay Knight ";
		getHostileEncText() = "You're ambushed by a horrifying knight rotting from decay!";
		getHostileAtkPlayerText() = "The knight lunges forwards with precisionstriking you!";
		getHostileAtkZinText() = "The knight swings his sword at Zinstriking her!";
		getHostileAtkZinBlkText() = "The knight lunges his sword towards Zinhowever you deflect it just on time!";

		getPlayerSlashAtkText() = "You slash at the knightattempting to pierce his armor!";
		getPlayerGuardAtkText() = "You watch the knights movements and prepare yourself to defend Zin...";
		getPlayerDecayAtkText() = "You slash yourself open with your swordusing the decay in your blood to strike the knight!";

		getZinSmiteAtkText() = "Zin places her hands together and creates a bolt of lightningsmiting the knight!";
		getZinMendAtkText() = "Zin slowly moves her arms outwardscasting a green aura around you and herselfrestoring health...";
		getZinVengeanceAtkText() = "Zin uses the blood spilled from your body to create blades made of bloodcasting them into the knight!";
		this->initHostileKnight = true;
	}
}

void Combat::initLostNun()
{
	if (!this->initHostileLostNun) {
		track1.pause();
		track5.play();
		//Allow combat to start
		this->combatEnd = false;
		//Set nun sprite
		getHostileCounter() = 5;
		//Allow new combat to start
		this->initCombatOnce = false;
		this->reInitCombatOnce = false;
		//Set parameters for hostile
		this->increase = false;
		this->expGain = 873;
		getHostileHp() = 200;
		getHostileHpMax() = 200;
		getHostileStrike() = 10;

		getHostileNameNoSpc() = "Lost Nun";
		getHostileName() = "Lost Nun ";
		getHostileEncText() = "The woman steps forwardsrevealing the sheer spread of her decay. She readies to attack you.";
		getHostileAtkPlayerText() = "The nun launches forwards as she spews out rotting decaybrutally striking you!";
		getHostileAtkZinText() = "The nun targets Zinhitting her with horrifying amounts of molten decay!";
		getHostileAtkZinBlkText() = "The nun targets Zin launching more decay at herhowever you deflect it just on time!";

		getPlayerSlashAtkText() = "You slash at the nunthe woman screaming out in pain as you attack.";
		getPlayerGuardAtkText() = "You watch the nuns movements preparing yourself to defend Zin at any cost...";
		getPlayerDecayAtkText() = "You slash yourself open with your swordusing the decay in your blood to strike the nun!";

		getZinSmiteAtkText() = "Zin places her hands together and creates a bolt of lightningsmiting the nun!";
		getZinMendAtkText() = "Zin slowly moves her arms outwardscasting a green aura around you and herselfrestoring health and slowly burning away the decay...";
		getZinVengeanceAtkText() = "Zin uses the blood spilled from your body to create blades made of bloodcasting them into the nun!";
		this->initHostileLostNun = true;
	}
}

void Combat::initDecapod()
{
	if (!this->initHostileDecapod) {
		track1.pause();
		track5.play();
		//Make entity viewer visible
		getSpriteViewerCounter() = 0;
		//Make decapod entity visible
		getEntityViewerCounter() = 8;
		//Allow combat to start
		this->combatEnd = false;
		//Set decapod sprite
		getHostileCounter() = 6;
		//Allow new combat to start
		this->initCombatOnce = false;
		this->reInitCombatOnce = false;
		//Set parameters for hostile
		this->increase = false;
		this->expGain = 250;
		getHostileHp() = 75;
		getHostileHpMax() = 75;
		getHostileStrike() = 12;

		getHostileNameNoSpc() = "Abyssal Decapod";
		getHostileName() = "Abyssal Decapod ";
		getHostileEncText() = "The horrifying abomination stands before you as its face wriggles with tentacles...";
		getHostileAtkPlayerText() = "The horrifying abomination grabs ahold of you and strikes you violently!";
		getHostileAtkZinText() = "The creature spits acid directly at Zinhitting her with it!";
		getHostileAtkZinBlkText() = "The abomination attempts to spit at Zin with acidhowever you block it with your sword just in time!";

		getPlayerSlashAtkText() = "You slash at the decapodthe creature screaming in pain!";
		getPlayerGuardAtkText() = "You watch the decapods movementspreparing yourself to defend Zin from its attacks...";
		getPlayerDecayAtkText() = "You slash yourself open with your swordusing the decay in your blood to strike the decapod!";

		getZinSmiteAtkText() = "Zin places her hands together and creates a bolt of lightningsmiting the decapod!";
		getZinMendAtkText() = "Zin slowly moves her arms outwardscasting a green aura around you and herselfrestoring health and slowly burning away the decay...";
		getZinVengeanceAtkText() = "Zin uses the blood spilled from your body to create blades made of bloodcasting them into the decapod!";
		this->initHostileDecapod = true;
	}
}

void Combat::initHazeDemon()
{
	if (!this->initHostileHazeDemon) {
		track1.pause();
		track5.play();
		//Make entity viewer visible
		getSpriteViewerCounter() = 0;
		//Make decapod entity visible
		getEntityViewerCounter() = 11;
		//Allow combat to start
		this->combatEnd = false;
		//Set decapod sprite
		getHostileCounter() = 7;
		//Allow new combat to start
		this->initCombatOnce = false;
		this->reInitCombatOnce = false;
		//Set parameters for hostile
		this->increase = false;
		this->expGain = 352;
		getHostileHp() = 75;
		getHostileHpMax() = 75;
		getHostileStrike() = 12;

		getHostileNameNoSpc() = "Haze Demon";
		getHostileName() = "Haze Demon ";
		getHostileEncText() = "The horrifying abomination stands before you as it creatres a strange auora...";
		getHostileAtkPlayerText() = "The horrifying abomination grabs ahold of you and strikes you violently!";
		getHostileAtkZinText() = "The creature splices the air in front Zinhitting her with the airwaves!";
		getHostileAtkZinBlkText() = "The abomination attempts to split the air towards Zinhowever you block it just in time!";

		getPlayerSlashAtkText() = "You slash at the demonthe unholy entity screaming in pain!";
		getPlayerGuardAtkText() = "You watch the demons movementspreparing yourself to defend Zin from its attacks...";
		getPlayerDecayAtkText() = "You slash yourself open with your swordusing the decay in your blood to strike the demon!";

		getZinSmiteAtkText() = "Zin places her hands together and creates a bolt of lightningsmiting the demon!";
		getZinMendAtkText() = "Zin slowly moves her arms outwardscasting a green aura around you and herselfrestoring health and slowly burning away the decay...";
		getZinVengeanceAtkText() = "Zin uses the blood spilled from your body to create blades made of bloodcasting them into the demon!";
		this->initHostileDecapod = true;
	}
}

//Combat Init Castle Hostiles
void Combat::initCourtJester()
{
	if (!this->initHostileJester) {
		track6.pause();
		track9.play();
		//Make entity viewer visible
		getSpriteViewerCounter() = 0;
		//Make jester entity visible
		getEntityViewerCounter() = 12;
		//Allow combat to start
		this->combatEnd = false;
		//Set jester sprite
		getHostileCounter() = 8;
		//Allow new combat to start
		this->initCombatOnce = false;
		this->reInitCombatOnce = false;
		//Set parameters for hostile
		this->increase = false;
		this->expGain = 425;
		getHostileHp() = 140;
		getHostileHpMax() = 140;
		getHostileStrike() = 20;

		getHostileNameNoSpc() = "Court Jester";
		getHostileName() = "Court Jester ";
		getHostileEncText() = "The jester stands with a horrifying grin...";
		getHostileAtkPlayerText() = "The jester stabs you with a small daggerbrutally injuring you!";
		getHostileAtkZinText() = "The jester sprints towards Zinstabbing her with his knife!";
		getHostileAtkZinBlkText() = "The jester runs towards Zin with a disgusting smile and a knife in his handhowever you block the knife just in time!";

		getPlayerSlashAtkText() = "You slash at the jesterthe clown smiling in pain!";
		getPlayerGuardAtkText() = "You watch the jesters movementspreparing yourself to defend Zin from its attacks...";
		getPlayerDecayAtkText() = "You slash yourself open with your swordspraying your decayed blood over the jestercausing him to yell in pain!";

		getZinSmiteAtkText() = "Zin places her hands together and creates a bolt of lightningsmiting the jester!";
		getZinMendAtkText() = "Zin slowly moves her arms outwardscasting a green aura around you and herselfrestoring health and slowly burning away the decay...";
		getZinVengeanceAtkText() = "Zin uses the blood spilled from your body to create blades made of bloodcasting them into the jester!";
		this->initHostileJester = true;
	}
}

void Combat::initWallMimic()
{
	if (!this->initHostileWallMimic) {
		track6.pause();
		track9.play();
		//Make entity viewer visible
		getSpriteViewerCounter() = 0;
		//Make wall mimic entity visible
		getEntityViewerCounter() = 13;
		//Allow combat to start
		this->combatEnd = false;
		//Set wall mimic sprite
		getHostileCounter() = 9;
		//Allow new combat to start
		this->initCombatOnce = false;
		this->reInitCombatOnce = false;
		//Set parameters for hostile
		this->increase = false;
		this->expGain = 357;
		getHostileHp() = 160;
		getHostileHpMax() = 160;
		getHostileStrike() = 20;

		getHostileNameNoSpc() = "Wall Mimic";
		getHostileName() = "Wall Mimic ";
		getHostileEncText() = "The walls begin to shift as the face appears before you.";
		getHostileAtkPlayerText() = "The walls shift as the mimic launches towards youstriking you!";
		getHostileAtkZinText() = "The mimic targets Zinstriking her with extreme force!";
		getHostileAtkZinBlkText() = "The mimic attempts to bite Zinhowever you tackle her out of the way just in time!";

		getPlayerSlashAtkText() = "You slash at the mimicthe walls echoing back with screams!";
		getPlayerGuardAtkText() = "You watch the movements of the walls carefullypreparing yourself to defend Zin from its attacks...";
		getPlayerDecayAtkText() = "You slash yourself open with your swordspraying your decayed blood over the walls and ceiling striking the mimic!";

		getZinSmiteAtkText() = "Zin places her hands together and creates a bolt of lightning that obliterates the ceiling and strikes the mimic!";
		getZinMendAtkText() = "Zin slowly moves her arms outwardscasting a green aura around you and herselfrestoring health and slowly burning away the decay...";
		getZinVengeanceAtkText() = "Zin uses the blood spilled from your body to create blades made of bloodcasting them into the walls!";
		this->initHostileWallMimic = true;
	}
}

void Combat::initLostKnight()
{
	if (!this->initHostileLostKnight) {
		track6.pause();
		track9.play();
		//Make entity viewer visible
		getSpriteViewerCounter() = 0;
		//Make Knight entity visible
		getEntityViewerCounter() = 14;
		//Allow combat to start
		this->combatEnd = false;
		//Set Knight sprite
		getHostileCounter() = 10;
		//Allow new combat to start
		this->initCombatOnce = false;
		this->reInitCombatOnce = false;
		//Set parameters for hostile
		this->increase = false;
		this->expGain = 682;
		getHostileHp() = 250;
		getHostileHpMax() = 250;
		getHostileStrike() = 25;

		getHostileNameNoSpc() = "Lost Knight";
		getHostileName() = "Lost Knight ";
		getHostileEncText() = "The knight stands in protestready to fight to the death...";
		getHostileAtkPlayerText() = "The knight stabs you with his sword!";
		getHostileAtkZinText() = "The knight dashes towards Zinslightly hesitanting due to her being a child. Despite thishe still strikes her!";
		getHostileAtkZinBlkText() = "The knight dashes towards Zin slashing at herhowever you block the blade just in time!";

		getPlayerSlashAtkText() = "You slash at the knightthe knight gritting his teeth in pain!";
		getPlayerGuardAtkText() = "You watch the knights movementspreparing yourself to defend Zin from his attacks...";
		getPlayerDecayAtkText() = "You slash yourself open with your swordspraying your decayed blood into the knights helmet! He begins coughing and choking in pain!";

		getZinSmiteAtkText() = "Zin places her hands together and creates a bolt of lightningsmiting the knight!";
		getZinMendAtkText() = "Zin slowly moves her arms outwardscasting a green aura around you and herselfrestoring health and slowly burning away the decay...";
		getZinVengeanceAtkText() = "Zin uses the blood spilled from your body to create blades made of bloodcasting them into the knight!";
		this->initHostileLostKnight = true;
	}
}

void Combat::initPhantom()
{
	if (!this->initHostilePhantom) {
		track6.pause();
		track9.play();
		//Make entity viewer visible
		getSpriteViewerCounter() = 0;
		//Make wall mimic entity visible
		getEntityViewerCounter() = 15;
		//Allow combat to start
		this->combatEnd = false;
		//Set wall mimic sprite
		getHostileCounter() = 11;
		//Allow new combat to start
		this->initCombatOnce = false;
		this->reInitCombatOnce = false;
		//Set parameters for hostile
		this->increase = false;
		this->expGain = 444;
		getHostileHp() = 185;
		getHostileHpMax() = 185;
		getHostileStrike() = 10;

		getHostileNameNoSpc() = "Phantom";
		getHostileName() = "Phantom ";
		getHostileEncText() = "The phantom phases into existence right before youcharging...";
		getHostileAtkPlayerText() = "The phantom appears right before youstriking you before you can react!";
		getHostileAtkZinText() = "The phantom vanishes before reappearing next to Zinusing the opprotunity to strike her!";
		getHostileAtkZinBlkText() = "The phantom runs towards Zin with a disgusting smirkhowever you block the attack just in time!";

		getPlayerSlashAtkText() = "You slash at the phantomits physical form being caught by your blade!";
		getPlayerGuardAtkText() = "You watch the phantoms movementspreparing yourself to defend Zin from its attacks...";
		getPlayerDecayAtkText() = "You slash yourself open with your swordspraying your decayed blood over the phantom!";

		getZinSmiteAtkText() = "Zin places her hands together and creates a bolt of lightningsmiting the phantom!";
		getZinMendAtkText() = "Zin slowly moves her arms outwardscasting a green aura around you and herselfrestoring health and slowly burning away the decay...";
		getZinVengeanceAtkText() = "Zin uses the blood spilled from your body to create blades made of bloodcasting them into the phantom!";
		this->initHostilePhantom = true;
	}
}

void Combat::initSkinEater()
{
	if (!this->initHostileEater) {
		track6.pause();
		track9.play();
		//Make entity viewer visible
		getSpriteViewerCounter() = 0;
		//Make wall mimic entity visible
		getEntityViewerCounter() = 16;
		//Allow combat to start
		this->combatEnd = false;
		//Set wall mimic sprite
		getHostileCounter() = 12;
		//Allow new combat to start
		this->initCombatOnce = false;
		this->reInitCombatOnce = false;
		//Set parameters for hostile
		this->increase = false;
		this->expGain = 274;
		getHostileHp() = 400;
		getHostileHpMax() = 400;
		getHostileStrike() = 8;

		getHostileNameNoSpc() = "Skin Eater";
		getHostileName() = "Skin Eater ";
		getHostileEncText() = "The skin eater stands with a horrifying facelocking eyes with you...";
		getHostileAtkPlayerText() = "The skin eater attempts to bite you but only grazes you!";
		getHostileAtkZinText() = "The skin eater sprints towards Zinlunging at her and striking her!";
		getHostileAtkZinBlkText() = "The skin eater runs towards Zinhowever you pull Zin out of the way just in time!";

		getPlayerSlashAtkText() = "You slash at the skin eaterthe abomination screaming in pain!";
		getPlayerGuardAtkText() = "You watch the skin eaters movementspreparing yourself to defend Zin from its attacks...";
		getPlayerDecayAtkText() = "You slash yourself open with your swordspraying your decayed blood over the skin eatercausing it to yell in pain!";

		getZinSmiteAtkText() = "Zin places her hands together and creates a bolt of lightningsmiting the skin eater!";
		getZinMendAtkText() = "Zin slowly moves her arms outwardscasting a green aura around you and herselfrestoring health and slowly burning away the decay...";
		getZinVengeanceAtkText() = "Zin uses the blood spilled from your body to create blades made of bloodcasting them into the skin eater!";
		this->initHostileEater = true;
	}
}

void Combat::initSiward()
{
	if (!this->initHostileSiward) {
		track6.pause();
		track3.play();
		//Allow combat to start
		this->combatEnd = false;
		//Allow new combat to start
		this->initCombatOnce = false;
		this->reInitCombatOnce = false;
		//Set parameters for hostile
		this->increase = false;
		this->expGain = 1500;
		getHostileHp() = 1000;
		getHostileHpMax() = 1000;
		getHostileStrike() = 25;

		getHostileNameNoSpc() = "Siward";
		getHostileName() = "Siward ";
		getHostileEncText() = "Siward stands with decay dripping from the front of his helmet...";
		getHostileAtkPlayerText() = "Siward slashes his sword at you with the precision of a true knight!";
		getHostileAtkZinText() = "Siward slashes towards Zinbrutally striking her!";
		getHostileAtkZinBlkText() = "Siward sends his sword towards Zin with great mighthowever you deflect it just in time!";

		getPlayerSlashAtkText() = "You slash Siwardthe knight gritting his teeth in pain!";
		getPlayerGuardAtkText() = "You watch Siward's movementspreparing to defend Zin from his brutal strikes...";
		getPlayerDecayAtkText() = "You slash yourself open with your swordspraying your decayed blood over Siwardthough it seems to have little effect...";

		getZinSmiteAtkText() = "Zin places her hands together reluctantly and creates a bolt of lightningsmiting Siward!";
		getZinMendAtkText() = "Zin slowly moves her arms outwardscasting a green aura around you and herselfrestoring health and slowly burning away the decay...";
		getZinVengeanceAtkText() = "Zin uses the blood spilled from your body to create blades made of bloodcasting them into Siward!";
		this->initHostileSiward = true;
	}
}

//Combat Init Decay Hostiles
void Combat::initLimbSplitter()
{
	if (!this->initHostileLimbSplitter) {
		track7.pause();
		track10.play();
		//Make entity viewer visible
		getSpriteViewerCounter() = 0;
		//Make limb splitter entity visible
		getEntityViewerCounter() = 17;
		//Allow combat to start
		this->combatEnd = false;
		//Set wall limb splitter sprite
		getHostileCounter() = 13;
		//Allow new combat to start
		this->initCombatOnce = false;
		this->reInitCombatOnce = false;
		//Set parameters for hostile
		this->increase = false;
		this->expGain = 750;
		getHostileHp() = 500;
		getHostileHpMax() = 500;
		getHostileStrike() = 40;

		getHostileNameNoSpc() = "Limb Splitter";
		getHostileName() = "Limb Splitter ";
		getHostileEncText() = "The limb splitter stares you downwaiting for its meal...";
		getHostileAtkPlayerText() = "The limb splitter strikes you with one of its ligaments!";
		getHostileAtkZinText() = "The limb splitter catches Zin off guardstriking her with one of its arms!";
		getHostileAtkZinBlkText() = "The limb splitter attempts to impale Zin with one of its armshowever you tackle her out of the way just in time!";

		getPlayerSlashAtkText() = "You slash at the limb splitterthe abomination screaming in pain!";
		getPlayerGuardAtkText() = "You watch the limb splitters ligamentspreparing yourself to defend Zin from its attacks...";
		getPlayerDecayAtkText() = "You slash yourself open with your swordspraying your decayed blood over the limb splittercausing it to screech in pain!";

		getZinSmiteAtkText() = "Zin places her hands together and creates a bolt of lightningsmiting the limb splitter!";
		getZinMendAtkText() = "Zin slowly moves her arms outwardscasting a green aura around you and herselfrestoring health and slowly burning away the decay...";
		getZinVengeanceAtkText() = "Zin uses the blood spilled from your body to create blades made of bloodcasting them into the limb splitter!";
		this->initHostileLimbSplitter = true;
	}
}

void Combat::initBurrower()
{
	if (!this->initHostileBurrower) {
		track7.pause();
		track10.play();
		//Make entity viewer visible
		getSpriteViewerCounter() = 0;
		//Make burrower entity visible
		getEntityViewerCounter() = 18;
		//Allow combat to start
		this->combatEnd = false;
		//Set burrower sprite
		getHostileCounter() = 14;
		//Allow new combat to start
		this->initCombatOnce = false;
		this->reInitCombatOnce = false;
		//Set parameters for hostile
		this->increase = false;
		this->expGain = 550;
		getHostileHp() = 400;
		getHostileHpMax() = 400;
		getHostileStrike() = 30;

		getHostileNameNoSpc() = "Burrower";
		getHostileName() = "Burrower ";
		getHostileEncText() = "The burrower quickly rushes towards youready to attack...";
		getHostileAtkPlayerText() = "The burrower crashes up from the groundstriking you with its spiked body!";
		getHostileAtkZinText() = "The burrower catches Zin off guardstriking with one of its spiked quills!";
		getHostileAtkZinBlkText() = "The burrower bursts from the wallattempting to consume Zin wholehowever you tackle her out of the way just in time!";

		getPlayerSlashAtkText() = "You slash at the burrowerthe abomination bleeding across the crimson floor!";
		getPlayerGuardAtkText() = "You listen to the burrowers movements in the wallspreparing yourself to defend Zin from its attacks...";
		getPlayerDecayAtkText() = "You slash yourself open with your swordspraying your decayed blood over the burrowercausing it to scream out in pain!";

		getZinSmiteAtkText() = "Zin places her hands together and creates a bolt of lightningsmiting the burrower!";
		getZinMendAtkText() = "Zin slowly moves her arms outwardscasting a green aura around you and herselfrestoring health and slowly burning away the decay...";
		getZinVengeanceAtkText() = "Zin uses the blood spilled from your body to create blades made of bloodcasting them into the burrower!";
		this->initHostileBurrower = true;
	}
}

void Combat::initChatterMouth()
{
	if (!this->initHostileChatterMouth) {
		track7.pause();
		track10.play();
		//Make entity viewer visible
		getSpriteViewerCounter() = 0;
		//Make chatter mouth entity visible
		getEntityViewerCounter() = 19;
		//Allow combat to start
		this->combatEnd = false;
		//Set chatter mouth sprite
		getHostileCounter() = 15;
		//Allow new combat to start
		this->initCombatOnce = false;
		this->reInitCombatOnce = false;
		//Set parameters for hostile
		this->increase = false;
		this->expGain = 550;
		getHostileHp() = 325;
		getHostileHpMax() = 325;
		getHostileStrike() = 20;

		getHostileNameNoSpc() = "Chatter Mouth";
		getHostileName() = "Chatter Mouth ";
		getHostileEncText() = "The chatter mouth quickly rushes towards youready to attack...";
		getHostileAtkPlayerText() = "The chatter mouth uses its wide body to swing around the limited cave spacesmashing you into the wall!";
		getHostileAtkZinText() = "The chatter mouths body strikes Zin as it swings it violently!";
		getHostileAtkZinBlkText() = "The chatter mouth attempts to drag Zin into its serrated mouthhowever you firmly grab ahold of Zin's arm and pull her out of its grasp!";

		getPlayerSlashAtkText() = "You slash at the chatter mouththe abomination bleeding across the crimson floor!";
		getPlayerGuardAtkText() = "You watch the chatter mouths movementspreparing yourself to defend Zin from its attacks...";
		getPlayerDecayAtkText() = "You slash yourself open with your swordspraying your decayed blood over the chatter mouthcausing it to scream out in pain!";

		getZinSmiteAtkText() = "Zin places her hands together and creates a bolt of lightningsmiting the chatter mouth!";
		getZinMendAtkText() = "Zin slowly moves her arms outwardscasting a green aura around you and herselfrestoring health and slowly burning away the decay...";
		getZinVengeanceAtkText() = "Zin uses the blood spilled from your body to create blades made of bloodcasting them into the chatter mouth!";
		this->initHostileChatterMouth = true;
	}
}

void Combat::initReclus()
{
	if (!this->initHostileReclus) {
		track7.pause();
		track10.play();
		//Make entity viewer visible
		getSpriteViewerCounter() = 0;
		//Make reclus entity visible
		getEntityViewerCounter() = 20;
		//Allow combat to start
		this->combatEnd = false;
		//Set reclus sprite
		getHostileCounter() = 16;
		//Allow new combat to start
		this->initCombatOnce = false;
		this->reInitCombatOnce = false;
		//Set parameters for hostile
		this->increase = false;
		this->expGain = 253;
		getHostileHp() = 265;
		getHostileHpMax() = 265;
		getHostileStrike() = 20;

		getHostileNameNoSpc() = "Reclus";
		getHostileName() = "Reclus ";
		getHostileEncText() = "The reclus moves quickly rushing forwards ready to attack...";
		getHostileAtkPlayerText() = "The reclus smashes you with its hand into the wall!";
		getHostileAtkZinText() = "The reclus drags its hand across the floorstriking Zin!";
		getHostileAtkZinBlkText() = "The reclus mouth attempts to drag Zin into its serrated mouthhowever you firmly grab ahold of Zin's arm and pull her out of its grasp!";

		getPlayerSlashAtkText() = "You slash at the reclusthe abomination bleeding across the crimson floor!";
		getPlayerGuardAtkText() = "You watch the reclus carefullypreparing yourself to defend Zin from its attacks...";
		getPlayerDecayAtkText() = "You slash yourself open with your swordspraying your decayed blood over the recluscausing it to scream out in pain!";

		getZinSmiteAtkText() = "Zin places her hands together and creates a bolt of lightningsmiting the reclus!";
		getZinMendAtkText() = "Zin slowly moves her arms outwardscasting a green aura around you and herselfrestoring health and slowly burning away the decay...";
		getZinVengeanceAtkText() = "Zin uses the blood spilled from your body to create blades made of bloodcasting them into the reclus!";
		this->initHostileReclus = true;
	}
}

void Combat::initTendrilAlpha()
{
	if (!this->initHostileTendrilAlpha) {
		track7.pause();
		track10.play();
		//Make entity viewer visible
		getSpriteViewerCounter() = 0;
		//Make tendril alpha entity visible
		getEntityViewerCounter() = 21;
		//Allow combat to start
		this->combatEnd = false;
		//Set tendril alpha sprite
		getHostileCounter() = 17;
		//Allow new combat to start
		this->initCombatOnce = false;
		this->reInitCombatOnce = false;
		//Set parameters for hostile
		this->increase = false;
		this->expGain = 220;
		getHostileHp() = 400;
		getHostileHpMax() = 400;
		getHostileStrike() = 25;

		getHostileNameNoSpc() = "Tendril Alpha";
		getHostileName() = "Tendril Alpha ";
		getHostileEncText() = "The abomination moves quickly rushing forwards ready to attack...";
		getHostileAtkPlayerText() = "The abomination smashes one of its tendrils into you!";
		getHostileAtkZinText() = "The abomination strikes Zin with one of its tendrils!";
		getHostileAtkZinBlkText() = "The alpha attempts to swarm Zin with its tendrilshowever you jump in between each tendril slicing them away!";

		getPlayerSlashAtkText() = "You slash at the alphaits body squirming in pain!";
		getPlayerGuardAtkText() = "You watch the abominations tendrils carefullypreparing yourself to defend Zin from its attacks...";
		getPlayerDecayAtkText() = "You slash yourself open with your swordspraying your decayed blood over the alphacausing it to quiver!";

		getZinSmiteAtkText() = "Zin places her hands together and creates a bolt of lightningsmiting the alpha!";
		getZinMendAtkText() = "Zin slowly moves her arms outwardscasting a green aura around you and herselfrestoring health and slowly burning away the decay...";
		getZinVengeanceAtkText() = "Zin uses the blood spilled from your body to create blades made of bloodcasting them into the alpha!";
		this->initHostileTendrilAlpha = true;
	}
}

void Combat::initSpade()
{
	if (!this->initHostileSpade) {
		track7.pause();
		track4.play();
		//Allow combat to start
		this->combatEnd = false;
		//Set tendril alpha sprite
		getSpadeCounter() = 6;
		//Allow new combat to start
		this->initCombatOnce = false;
		this->reInitCombatOnce = false;
		//Set parameters for hostile
		this->increase = false;
		this->expGain = 500;
		getHostileHp() = 750;
		getHostileHpMax() = 750;
		getHostileStrike() = 40;

		getHostileNameNoSpc() = "Spade";
		getHostileName() = "Spade ";
		getHostileEncText() = "Spade steps forwardsa horrifying look in her eyes as she's practically inhuman...";
		getHostileAtkPlayerText() = "Spade slams you with a horrifying decaying tentacle!";
		getHostileAtkZinText() = "Spade strikes Zin with one of her decaying tendrils!";
		getHostileAtkZinBlkText() = "Spade attempts to slice Zin in half with a crude sharpened bonehowever you deflect it just in time!";

		getPlayerSlashAtkText() = "You slash at Spadeher cackling back in bliss!";
		getPlayerGuardAtkText() = "You watch Spades movementspreparing yourself to protect Zin at all costs...";
		getPlayerDecayAtkText() = "You slash yourself open with your swordspraying your decayed blood over Spade as she slowly locks eyes with you!";

		getZinSmiteAtkText() = "Zin places her hands together and creates a bolt of lightningsmiting Spade!";
		getZinMendAtkText() = "Zin slowly moves her arms outwardscasting a green aura around you and herselfrestoring health and slowly burning away the decay...";
		getZinVengeanceAtkText() = "Zin uses the blood spilled from your body to create blades made of bloodcasting them into Spade!";
		this->initHostileSpade = true;
	}
}

void Combat::initRotBeast()
{
	if (!this->initHostileRotBeast) {
		track7.pause();
		track4.play();
		//Make entity viewer visible
		getSpriteViewerCounter() = 0;
		//Allow combat to start
		this->combatEnd = false;
		//Allow new combat to start
		this->initCombatOnce = false;
		this->reInitCombatOnce = false;
		//Set parameters for hostile
		this->increase = false;
		this->expGain = 2500;
		getHostileHp() = 1500;
		getHostileHpMax() = 1500;
		getHostileStrike() = 30;

		getHostileNameNoSpc() = "The Rot Beast";
		getHostileName() = "The Rot Beast ";
		getHostileEncText() = "The horrifying beast moves quickly rushing forwards ready to attack...";
		getHostileAtkPlayerText() = "The beast smashes you with one of its oversized arms!";
		getHostileAtkZinText() = "The abomination strikes Zin with a powerful blast of decay!";
		getHostileAtkZinBlkText() = "The rotting beast attempts to smash Zin with its armhowever you tackle Zin out of the way moments before death!";

		getPlayerSlashAtkText() = "You slash at the beasta horrifying bellow coming from it!";
		getPlayerGuardAtkText() = "You watch the beast carefullypreparing yourself to defend Zin from its attacks...";
		getPlayerDecayAtkText() = "You slash yourself open with your swordspraying your decayed blood over the rotting beastcausing it to quiver!";

		getZinSmiteAtkText() = "Zin places her hands together and creates a bolt of lightningsmiting the beast!";
		getZinMendAtkText() = "Zin slowly moves her arms outwardscasting a green aura around you and herselfrestoring health and slowly burning away the decay...";
		getZinVengeanceAtkText() = "Zin uses the blood spilled from your body to create blades made of bloodcasting them into the beast!";
		this->initHostileRotBeast = true;
	}
}