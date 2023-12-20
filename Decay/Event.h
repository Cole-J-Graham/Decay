#pragma once
#include"Combat.h"

class Event: public Combat
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
	void reInit();
	void hideOpenAssets();

	//Bonfire Events
	void healCharactersText(sf::RenderWindow& window);
	void healCharacters(sf::RenderWindow& window);
	void smithingText(sf::RenderWindow& window);
	void smithingSharpenBlade(sf::RenderWindow& window);

	//Forest Entrance Events
	void forestSiwardEnc();
	void riEnc();

	//Forest Depths Events
	void forestDepthsSpadeEnc();
	void treeEnc();
	void thomEnc();

	//Forest Abyssal Events
	void obeliskEnc();
	void lostNunEnc();

	//Forest Abyssal Depths Events
	void forestAbyssalSpadeEnc();

	//Castle Hall Events
	void castleSpadeEnc();
	void castleSpadeEncPoison();

	//Castle Depth Events
	void castleSiwardEnc();

	//Castle Chambers Events
	void castleGrifEnc();

	//Castle Labyrinth Events
	void castleSiwardFinalEnc();

	//Decay Forest Events
	void decaySpadeEnc();
	void decaySpadeEncPoison();
	void rotBeastDeathEnding();

	//Decay Ocean Events
	void decayGrifEnc();

	//Final Events
	void rotBeastEnc();
	void playerDeathEnding();

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

