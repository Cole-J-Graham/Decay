#ifndef EVENT_H
#define EVENT_H
#include "Assets.h"
#include "Combat.h"
#include "Player.h"
#include "Animation.h"

class Event
{
private:
	//Control Flow Bools
	bool reInitialize;
	bool sfxUsed;
	bool itemGained;
	bool endMusic;

	//Event Availability Bools
	bool thomEnced;
	bool siwardEncedForest;
	bool siwardEncedCastle;
	bool siwardEncedFinal;

	bool spadeEncedForest;
	bool spadeEncedAbyssalForest;
	bool spadeEncedCastle;
	bool spadeEncedCastlePoison;
	bool spadeEncedDecay;
	bool spadeEncedDecayPoison;

	bool riEncedForest;

	bool grifEncounteredCastle;
	bool grifEncounteredOcean;

	bool treeEnced;
	bool obeliskEnced;

	bool nunEnced;

	bool playerDeathEnced;
	bool rotBeastDeathEnced;
	bool rotBeastEnced;

	//Event Control Flow Bools
	bool spadePoison;

	//Counters
	int choiceCounter;

	int dialogue;

public:
	//Constructors & Destructors
	Event();
	~Event();

	//Core Functions
	void reInit(Sprites& sprites);
	void hideOpenAssets(Sprites& sprites);

	//Bonfire Events
	void healCharactersText(sf::RenderWindow& window, Sprites& sprites);
	void healCharacters(sf::RenderWindow& window, Sprites& sprites, Combat& combat);
	void smithingText(sf::RenderWindow& window, Sprites& sprites);
	void smithingSharpenBlade(sf::RenderWindow& window, Sprites& sprites, Player& player, Combat& combat);

	//Forest Entrance Events
	void forestSiwardEnc(Sprites& sprites);
	void riEnc(Sprites& sprites);

	//Forest Depths Events
	void forestDepthsSpadeEnc(Sprites& sprites);
	void treeEnc(Sprites& sprites, Player& player);
	void thomEnc(Sprites& sprites);

	//Forest Abyssal Events
	void obeliskEnc(Sprites& sprites, Player& player);
	void lostNunEnc(Sprites& sprites);

	//Forest Abyssal Depths Events
	void forestAbyssalSpadeEnc(Sprites& sprites, Player& player);

	//Castle Hall Events
	void castleSpadeEnc(Sprites& sprites);
	void castleSpadeEncPoison(Sprites& sprites);

	//Castle Depth Events
	void castleSiwardEnc(Sprites& sprites);

	//Castle Chambers Events
	void castleGrifEnc(Sprites& sprites);

	//Castle Labyrinth Events
	void castleSiwardFinalEnc(Sprites& sprites);

	//Decay Forest Events
	void decaySpadeEnc(Sprites& sprites);
	void decaySpadeEncPoison(Sprites& sprites);
	void rotBeastDeathEnding(Sprites& sprites);

	//Decay Ocean Events
	void decayGrifEnc(Sprites& sprites);

	//Final Events
	void rotBeastEnc(Sprites& sprites);
	void playerDeathEnding(Sprites& sprites);

	//Control Flow Getters
	bool& getReInitialize() { return this->reInitialize; };
	bool& getSfxUsed() { return this->sfxUsed; };
	bool& getItemGained() { return this->itemGained; };

	//Event Availability Bools
	bool& getThomEnced() { return this->thomEnced; };

	bool& getSiwardEncedForest() { return this->siwardEncedForest; };
	bool& getSiwardEncedCastle() { return this->siwardEncedCastle; };
	bool& getSiwardEncedFinal() { return this->siwardEncedFinal; };

	bool& getSpadeEncedForest() { return this->spadeEncedForest; };
	bool& getSpadeEncedAbyssalForest() { return this->spadeEncedAbyssalForest; };
	bool& getSpadeEncedCastle() { return this->spadeEncedCastle; };
	bool& getSpadeEncedCastlePoison() { return this->spadeEncedCastlePoison; };
	bool& getSpadeEncedDecay() { return this->spadeEncedDecay; };
	bool& getSpadeEncedDecayPoison() { return this->spadeEncedDecayPoison; };
	bool& getSpadeEnced() { return this->spadeEncedDecayPoison; };

	bool& getRiEncedForest() { return this->riEncedForest; };

	bool& getGrifEncounteredCastle() { return this->grifEncounteredCastle; };
	bool& getGrifEncounteredOcean() { return this->grifEncounteredOcean; };

	bool& getTreeEnced() { return this->treeEnced; };
	bool& getObeliskEnced() { return this->obeliskEnced; };
	bool& getNunEnced() { return this->nunEnced; };

	bool& getPlayerDeathEnced() { return this->playerDeathEnced; };
	bool& getRotBeastDeathEnced() { return this->rotBeastDeathEnced; };
	bool& getRotBeastEnced() { return this->rotBeastEnced; };

	//Counter Getters
	int& getChoiceCounter() { return this->choiceCounter; };

	int& getDialogue() { return this->dialogue; };

	//Event Control Flow Getters
	bool& getSpadePoison() { return this->spadePoison; };

	//Setters
	void setDialogueInc() { this->dialogue++; };
};

#endif

