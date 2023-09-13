#ifndef EVENT_H
#define EVENT_H
#include "Assets.h"
#include "Combat.h"
#include "Player.h"

class Event
{
private:
	bool encounterInit;
	bool encounterInitTwo;

	int dialogue;

public:

	//Constructors & Destructors
	Event();
	~Event();

	//Core Functions
	void reInitialize(Assets& assets);

	//Bonfire Events
	void healCharactersText(sf::RenderWindow& window, Assets& assets);
	void healCharacters(sf::RenderWindow& window, Assets& assets, Combat& combat);
	void smithingText(sf::RenderWindow& window, Assets& assets);
	void smithingSharpenBlade(sf::RenderWindow& window, Assets& assets, Player& player);

	//Castle Events
	void spadeEncounter(Assets& assets);

	//Getters
	bool& getEncounterInit() { return this->encounterInit; };
	bool& getEncounterInitTow() { return this->encounterInitTwo; };

	int& getDialogue() { return this->dialogue; };
};

#endif

