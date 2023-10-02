#ifndef EVENT_H
#define EVENT_H
#include "Assets.h"
#include "Combat.h"
#include "Player.h"

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
	bool siwardEncounteredForest;

	bool treeEncountered;

	//Counters
	int zinTalkCounter;

	int dialogue;

public:

	//Constructors & Destructors
	Event();
	~Event();

	//Core Functions
	void reInit(Assets& assets);

	//Bonfire Events
	void healCharactersText(sf::RenderWindow& window, Assets& assets);
	void healCharacters(sf::RenderWindow& window, Assets& assets, Combat& combat);
	void smithingText(sf::RenderWindow& window, Assets& assets);
	void smithingSharpenBlade(sf::RenderWindow& window, Assets& assets, Player& player);

	//Bonfire Text Events
	void zinEvents(sf::RenderWindow& window, Assets& assets, Animation& animate);

	//Zin Events
	void zinInitialTalk(Assets& assets, Animation& animate);

	//Forest Events
	void forestSiwardEncounter(Assets& assets);
	void treeEncounter(Assets& assets, Player& player);

	//Castle Events
	void spadeEncounter(Assets& assets);

	//Control Flow Getters
	bool& getEncounterInit() { return this->encounterInit; };
	bool& getEncounterInitTow() { return this->encounterInitTwo; };
	bool& getReInitialize() { return this->reInitialize; };

	//Counter Getters
	int& getZinTalkCounter() { return this->zinTalkCounter; };

	int& getDialogue() { return this->dialogue; };

	//Setters
	void setDialogueInc() { this->dialogue++; };
};

#endif

