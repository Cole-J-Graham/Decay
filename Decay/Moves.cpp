#include "Moves.h"

//Constructors and Destructors
Moves::Moves()
{
	//Hp
	this->playerHp = 50;
	this->playerHpMax = 50;

	this->zinHp = 35;
	this->zinHpMax = 35;

	this->thomHp = 30;
	this->thomHpMax = 30;

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

	//Thom Moves
	this->thomEnraged = false;

	//Hostile Moves
	this->hostileStrike = 0;

	//Control Flow Bools
	this->zinGuarded = false;
	this->playerGuarded = false;

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

	this->zinSmiteAtkText = "Zin smites the combatant! Click to continue...";
	this->zinMendAtkText = "Zin heals the party! Click to continue...";
	this->zinVengeanceAtkText = "Zin takes vengeance, brutally striking the enemy! Click to continue...";

	this->thomBarrierAtkText = "Thom uses decay from his body to manipulate a barrier around the player!";
	this->thomEnragedAtkText = "Thom's form slowly melts as he allows the decay to take root in his body. Thom is now enraged!";
}

Moves::~Moves()
{

}

//Player Moves
void Moves::Slash(Sprites& sprites, Animation& animate)
{
	sprites.soundSlash.play();
	this->hostileHp -= this->playerStrike;
	sprites.spriteText[2].setString(this->hostileName + std::to_string(hostileHp) + "/" + std::to_string(hostileHpMax));
	sprites.setPlayerTurnAssetsFalse();
	sprites.text.setString(this->playerSlashAtkText);
	if (!this->firstAttack) {
		animate.combatTimer.restart();
		this->firstAttack = true;
	}
	animate.getCombatAnimationLocation() = 0;
	animate.getAnimEnd() = false;//Play Attack Animation
}

void Moves::Guard(Sprites& sprites, Animation& animate)
{
	sprites.soundGuard.play();
	sprites.setPlayerTurnAssetsFalse();
	this->zinGuarded = true;
	sprites.text.setString(this->playerGuardAtkText);
}

void Moves::DecayBlade(Sprites& sprites, Animation& animate)
{
	sprites.soundDecay.play();
	this->hostileHp -= this->decayedBlade;
	sprites.spriteText[2].setString(this->hostileName + std::to_string(hostileHp) + "/" + std::to_string(hostileHpMax));
	sprites.setPlayerTurnAssetsFalse();
	sprites.text.setString(this->playerDecayAtkText);
	animate.getCombatAnimationLocation() = 0;
	animate.getAnimEnd() = false;//Play Attack Animation
}

//Zin Moves
void Moves::Smite(Sprites& sprites, Animation& animate)
{
	sprites.soundSmite.play();
	this->hostileHp -= this->zinSmite;
	sprites.spriteText[2].setString(this->hostileName + std::to_string(hostileHp) + "/" + std::to_string(hostileHpMax));
	sprites.setZinTurnAssetsFalse();
	sprites.text.setString(this->zinSmiteAtkText);
	animate.getCombatAnimationLocation() = 0;
	animate.getAnimEnd() = false;//Play Attack Animation
}

void Moves::Mend(Sprites& sprites, Animation& animate)
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
}

void Moves::Vengeance(Sprites& sprites, Animation& animate)
{
	sprites.soundVengeance.play();
	this->zinVengeance = this->playerHpMax - this->playerHp;
	this->hostileHp -= this->zinVengeance;
	sprites.spriteText[2].setString(this->hostileName + std::to_string(hostileHp) + "/" + std::to_string(hostileHpMax));
	sprites.setZinTurnAssetsFalse();
	sprites.text.setString(this->zinVengeanceAtkText);
}

//Thom Moves
void Moves::Barrier(Sprites& sprites, Animation& animate)
{
	this->playerGuarded = true;
	sprites.soundThomGuard.play();
	sprites.spriteText[2].setString(this->hostileName + std::to_string(hostileHp) + "/" + std::to_string(hostileHpMax));
	sprites.text.setString(this->thomBarrierAtkText);
	sprites.setThomTurnAssetsFalse();
}

void Moves::Enrage(Sprites& sprites, Animation& animate)
{
	this->thomEnraged = true;
	this->enraged = 3;
	sprites.getThomCounter() = 1;
	sprites.soundEnraged.play();
	sprites.text.setString(this->thomEnragedAtkText);
	sprites.setThomTurnAssetsFalse();
}