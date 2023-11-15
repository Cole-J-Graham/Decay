#include "Moves.h"

//Constructors and Destructors
Moves::Moves()
{
	//Hp
	this->playerHp = 50;
	this->playerHpMax = 50;
	this->playerDef = 0;
	this->playerAtk = 0;

	this->zinHp = 35;
	this->zinHpMax = 35;
	this->zinDef = 0;
	this->zinAtk = 0;

	this->thomHp = 30;
	this->thomHpMax = 30;
	this->thomDef = 0;

	this->hostileHp = 50;
	this->hostileHpMax = 50;

	//Player Moves
	this->playerStrike = 5;
	this->playerGuard = 1;
	this->decayedBlade = 10;
	this->heftyBlowDmg = 25;
	this->decaySynergyDmg = 3;
	this->decaySynergyDef = 10;
	this->ironWallDef = 10;

	//Zin Moves
	this->zinSmite = 5;
	this->zinMend = 5;
	this->zinVengeance = 1;
	this->zinBlaze = 45;
	this->zinFocus = 40;
	this->zinCrimson = 25;

	//Thom Moves
	this->enragedAtk = 15;
	this->thomEnraged = false;

	//Hostile Moves
	this->hostileStrike = 0;

	//Move Control Flow Bools
	this->zinGuarded = false;
	this->playerGuarded = false;

	this->playerFatigue = false;
	this->zinFatigue = false;

	//Animation Control
	this->firstAttack = false;

	//Init Strings
	this->playerTurnText = "You plan your next move...";
	this->zinTurnText = "Zin plans her next move...";

	this->hostileNameNoSpc = "Abomination";
	this->hostileName = "Abomination";
	this->hostileEncText = "A combatant ambushes you! Pick your next step carefully...";
	this->hostileAtkPlayerText = "The hostile swings back! Click to continue...";
	this->hostileAtkZinText = "The hostile swings at Zin! Click to continue...";
	this->hostileAtkZinBlkText = "You block Zin from the strike! Click to continue...";
	this->hostileAtkPlayerBlkText = "Thom's barrier casted around you protects you from the enemy!";

	this->playerSlashAtkText = "You strike the combatant! Click to continue...";
	this->playerGuardAtkText = "You plant yourself in between Zin and the enemy! Click to continue...";
	this->playerDecayAtkText = "You slash yourself open with your sword, using the decay in your blood to strike the enemy!";
	this->playerHeftyAtkText = "You slash into them with all of your might, jabbing your dagger deep into their wound and twisting the blade!";
	this->playerSynergyAtkText = "You materialize decay in front of yourself, watching it swirl. You quickly create a small barrier made of pure decay in front of Zin and splice the rest towards the enemy!";
	this->playerIronWallAtkText = "You stand your ground and plant your feet, preparing to defend your entire party to the best of your abilities...";

	this->zinSmiteAtkText = "Zin smites the combatant! Click to continue...";
	this->zinMendAtkText = "Zin heals the party! Click to continue...";
	this->zinVengeanceAtkText = "Zin takes vengeance, brutally striking the enemy! Click to continue...";
	this->zinBlazeAtkText = "Zin braces herself and slowly rises her hands in the air whilst looking at the enemy, summoning a raging fire straight from the pits of hell... All you can hear is the foes screams...";
	this->zinFocusAtkText = "Zin creates a green auroa around you that begins to mend your wounds greatly!";
	this->zinCrimsonAtkText = "Zin clenches her fists together and absorbs every ounce of rage from both herself and you. Suddenly, crimson flames engulf both your and Zin's bodies. You both feel much stronger... ";

	this->thomBarrierAtkText = "Thom uses decay from his body to manipulate a barrier around the player!";
	this->thomEnragedAtkText = "Thom's form slowly melts as he allows the decay to take root in his body. Thom is now enraged!";
}

Moves::~Moves()
{

}

//Player Moves
void Moves::slash(Sprites& sprites, Animation& animate)
{
	sprites.soundSlash.play();
	this->hostileHp -= this->playerStrike + playerAtk;
	sprites.spriteText[2].setString(this->hostileName + std::to_string(hostileHp) + "/" + std::to_string(hostileHpMax));
	sprites.setPlayerTurnAssetsFalse();
	sprites.text.setString(this->playerSlashAtkText);
	if (!this->firstAttack) {
		animate.combatTimer.restart();
		this->firstAttack = true;
	}
	animate.getCombatAnimationLocation() = 0;
	animate.getAnimation() = 0;
	animate.getAnimEnd() = false;//Play Attack Animation
	sprites.getTipBoxCounter() = -1;
}

void Moves::guard(Sprites& sprites, Animation& animate)
{
	sprites.soundGuard.play();
	sprites.setPlayerTurnAssetsFalse();
	this->zinGuarded = true;
	sprites.text.setString(this->playerGuardAtkText);
	sprites.getTipBoxCounter() = -1;
}

void Moves::decayBlade(Sprites& sprites, Animation& animate)
{
	sprites.soundDecay.play();
	this->hostileHp -= this->decayedBlade + playerAtk;
	sprites.spriteText[2].setString(this->hostileName + std::to_string(hostileHp) + "/" + std::to_string(hostileHpMax));
	sprites.setPlayerTurnAssetsFalse();
	sprites.text.setString(this->playerDecayAtkText);
	animate.getCombatAnimationLocation() = 0;
	animate.getAnimation() = 0;
	animate.getAnimEnd() = false;//Play Attack Animation
	sprites.getTipBoxCounter() = -1;
}

void Moves::heftyBlow(Sprites& sprites, Animation& animate)
{
	sprites.soundHefty.play();
	this->hostileHp -= this->heftyBlowDmg + playerAtk;
	sprites.spriteText[2].setString(this->hostileName + std::to_string(hostileHp) + "/" + std::to_string(hostileHpMax));
	sprites.setPlayerTurnAssetsFalse();
	sprites.text.setString(this->playerHeftyAtkText);
	animate.getCombatAnimationLocation() = 0;
	animate.getAnimation() = 0;
	animate.getAnimEnd() = false;//Play Attack Animation
	this->playerFatigue = true;
	sprites.getTipBoxCounter() = -1;
}

void Moves::decaySynergy(Sprites& sprites, Animation& animate)
{
	sprites.soundSynergy.play();
	this->hostileHp -= this->decaySynergyDmg += playerAtk;
	this->zinDef += this->decaySynergyDef;
	sprites.spriteText[2].setString(this->hostileName + std::to_string(hostileHp) + "/" + std::to_string(hostileHpMax));
	sprites.spriteText[1].setString("Zin            " + std::to_string(zinHp + zinDef) + "/" + std::to_string(zinHpMax));
	sprites.text.setString(this->playerSynergyAtkText);
	sprites.setPlayerTurnAssetsFalse();
	animate.getCombatAnimationLocation() = 0;
	animate.getAnimEnd() = false;//Play Attack Animation
	sprites.getTipBoxCounter() = -1;
}

void Moves::ironWall(Sprites& sprites, Animation& animte)
{
	this->playerDef += this->ironWallDef;
	this->zinDef += this->ironWallDef;
	this->thomDef += this->ironWallDef;
	sprites.text.setString(this->playerIronWallAtkText);
	sprites.spriteText[0].setString(sprites.getPlayerName() + "     " + std::to_string(playerHp) + "/" + std::to_string(playerHpMax));
	sprites.spriteText[1].setString("Zin            " + std::to_string(zinHp) + "/" + std::to_string(zinHpMax));
	sprites.spriteText[5].setString("Thom          " + std::to_string(this->thomHp) + "/" + std::to_string(this->thomHpMax));
	sprites.setPlayerTurnAssetsFalse();
	sprites.getTipBoxCounter() = -1;
}

//Zin Moves
void Moves::smite(Sprites& sprites, Animation& animate)
{
	sprites.soundSmite.play();
	this->hostileHp -= this->zinSmite + zinAtk;
	sprites.spriteText[2].setString(this->hostileName + std::to_string(hostileHp) + "/" + std::to_string(hostileHpMax));
	sprites.setZinTurnAssetsFalse();
	sprites.text.setString(this->zinSmiteAtkText);
	animate.getCombatAnimationLocation() = 0;
	animate.getAnimEnd() = false;//Play Attack Animation
	sprites.getTipBoxCounter() = -1;
	animate.getAnimation() = 1;
	animate.getCombatAnimationLocation() = 0;
	animate.getAnimEnd() = false;//Play Attack Animation
}

void Moves::mend(Sprites& sprites, Animation& animate)
{
	sprites.soundMend.play();
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
	if (this->thomHp < this->thomHpMax) {
		this->thomHp += this->zinMend;
		if (this->thomHp > this->thomHpMax) {
			this->thomHp = this->thomHpMax;
		}
	}
	sprites.spriteText[0].setString(sprites.getPlayerName() + "     " + std::to_string(playerHp) + "/" + std::to_string(playerHpMax));
	sprites.spriteText[1].setString("Zin            " + std::to_string(zinHp) + "/" + std::to_string(zinHpMax));
	sprites.spriteText[5].setString("Thom          " + std::to_string(this->thomHp) + "/" + std::to_string(this->thomHpMax));
	sprites.setZinTurnAssetsFalse();
	sprites.text.setString(this->zinMendAtkText);
	sprites.getTipBoxCounter() = -1;
}

void Moves::vengeance(Sprites& sprites, Animation& animate)
{
	sprites.soundVengeance.play();
	this->zinVengeance = this->playerHpMax - this->playerHp + zinAtk;
	this->hostileHp -= this->zinVengeance;
	sprites.spriteText[2].setString(this->hostileName + std::to_string(hostileHp) + "/" + std::to_string(hostileHpMax));
	sprites.setZinTurnAssetsFalse();
	sprites.text.setString(this->zinVengeanceAtkText);
	sprites.getTipBoxCounter() = -1;
}

void Moves::hellBlaze(Sprites& sprites, Animation& animate)
{
	sprites.soundBlaze.play();
	this->hostileHp -= this->zinBlaze + zinAtk;
	sprites.spriteText[2].setString(this->hostileName + std::to_string(hostileHp) + "/" + std::to_string(hostileHpMax));
	sprites.setZinTurnAssetsFalse();
	sprites.text.setString(this->zinBlazeAtkText);
	this->zinFatigue = true;
	sprites.getTipBoxCounter() = -1;
}

void Moves::focusHeal(Sprites& sprites, Animation& animate)
{
	sprites.soundMend.play();
	if (this->playerHp < this->playerHpMax) {
		this->playerHp += this->zinFocus;
		if (this->playerHp > this->playerHpMax) {
			this->playerHp = this->playerHpMax;
		}
	}
	sprites.spriteText[0].setString(sprites.getPlayerName() + "     " + std::to_string(playerHp) + "/" + std::to_string(playerHpMax));
	sprites.setZinTurnAssetsFalse();
	sprites.text.setString(this->zinFocusAtkText);
	sprites.getTipBoxCounter() = -1;
}

void Moves::crimsonFlames(Sprites& sprites, Animation& animate)
{
	sprites.soundFlames.play();
	this->playerAtk += zinCrimson;
	this->zinAtk += zinCrimson;
	sprites.setZinTurnAssetsFalse();
	sprites.text.setString(this->zinCrimsonAtkText);
	sprites.getTipBoxCounter() = -1;
}

//Thom Moves
void Moves::barrier(Sprites& sprites, Animation& animate)
{
	this->playerGuarded = true;
	sprites.soundThomGuard.play();
	sprites.spriteText[2].setString(this->hostileName + std::to_string(hostileHp) + "/" + std::to_string(hostileHpMax));
	sprites.text.setString(this->thomBarrierAtkText);
	sprites.setThomTurnAssetsFalse();
	sprites.getTipBoxCounter() = -1;
}

void Moves::enrage(Sprites& sprites, Animation& animate)
{
	this->thomEnraged = true;
	this->enraged = 3;
	this->playerAtk += enragedAtk;
	this->zinAtk += enragedAtk;
	sprites.getThomCounter() = 1;
	sprites.soundEnraged.play();
	sprites.text.setString(this->thomEnragedAtkText);
	sprites.setThomTurnAssetsFalse();
	sprites.getTipBoxCounter() = -1;
}