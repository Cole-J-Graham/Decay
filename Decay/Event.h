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

	bool encounterInit;
	bool encounterInitTwo;

	//Event Availability Bools
	bool thomEncountered;
	bool siwardEncounteredForest;
	bool spadeEncounteredForest;

	bool treeEncountered;
	bool obeliskEncountered;

	bool nunEncountered;

	//Counters
	int zinTalkCounter;
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
	void smithingSharpenBlade(sf::RenderWindow& window, Sprites& sprites, Player& player);

	//Bonfire Text Events
	void zinEvents(sf::RenderWindow& window, Sprites& sprites, Animation& animate);

	//Zin Events
	void zinInitialTalk(Sprites& sprites, Animation& animate);

	//Forest Entrance Events
	void forestSiwardEncounter(Sprites& sprites);

	//Forest Depths Events
	void forestDepthsSpadeEncounter(Sprites& sprites);
	void treeEncounter(Sprites& sprites, Player& player);
	void thomEncounter(Sprites& sprites);

	//Forest Abyssal Events
	void obeliskEncounter(Sprites& sprites, Player& player);
	void lostNunEncounter(Sprites& sprites);

	//Castle Events
	void spadeEncounter(Sprites& sprites);

	//Control Flow Getters
	bool& getEncounterInit() { return this->encounterInit; };
	bool& getEncounterInitTow() { return this->encounterInitTwo; };
	bool& getReInitialize() { return this->reInitialize; };

	//Event Availability Bools
	bool& getNunEncountered() { return this->nunEncountered; };

	//Counter Getters
	int& getZinTalkCounter() { return this->zinTalkCounter; };
	int& getChoiceCounter() { return this->choiceCounter; };

	int& getDialogue() { return this->dialogue; };

	//Setters
	void setDialogueInc() { this->dialogue++; };
};

#endif

