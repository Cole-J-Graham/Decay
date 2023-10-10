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
	bool siwardEncounteredForest;
	bool spadeEncounteredForest;

	bool treeEncountered;
	bool obeliskEncountered;

	bool nunEncountered;

	//Counters
	int zinTalkCounter;

	int dialogue;

public:

	//Constructors & Destructors
	Event();
	~Event();

	//Core Functions
	void reInit(Assets& assets);
	void hideOpenAssets(Assets& assets);

	//Bonfire Events
	void healCharactersText(sf::RenderWindow& window, Assets& assets);
	void healCharacters(sf::RenderWindow& window, Assets& assets, Combat& combat);
	void smithingText(sf::RenderWindow& window, Assets& assets);
	void smithingSharpenBlade(sf::RenderWindow& window, Assets& assets, Player& player);

	//Bonfire Text Events
	void zinEvents(sf::RenderWindow& window, Assets& assets, Animation& animate);

	//Zin Events
	void zinInitialTalk(Assets& assets, Animation& animate);

	//Forest Entrance Events
	void forestSiwardEncounter(Assets& assets);

	//Forest Depths Events
	void forestDepthsSpadeEncounter(Assets& assets);
	void treeEncounter(Assets& assets, Player& player);

	//Forest Abyssal Events
	void obeliskEncounter(Assets& assets, Player& player);
	void lostNunEncounter(Assets& assets);

	//Castle Events
	void spadeEncounter(Assets& assets);

	//Control Flow Getters
	bool& getEncounterInit() { return this->encounterInit; };
	bool& getEncounterInitTow() { return this->encounterInitTwo; };
	bool& getReInitialize() { return this->reInitialize; };

	//Event Availability Bools
	bool& getNunEncountered() { return this->nunEncountered; };

	//Counter Getters
	int& getZinTalkCounter() { return this->zinTalkCounter; };

	int& getDialogue() { return this->dialogue; };

	//Setters
	void setDialogueInc() { this->dialogue++; };
};

#endif

