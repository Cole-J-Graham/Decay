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

	bool encounterInit;
	bool encounterInitTwo;

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

	//Castle Events
	void spadeEncounter(Assets& assets);

	//Control Flow Getters
	bool& getEncounterInit() { return this->encounterInit; };
	bool& getEncounterInitTow() { return this->encounterInitTwo; };

	//Counter Getters
	int& getZinTalkCounter() { return this->zinTalkCounter; };

	int& getDialogue() { return this->dialogue; };

	//Setters
	void setDialogueInc() { this->dialogue++; };
};

#endif

