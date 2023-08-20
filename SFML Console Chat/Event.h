#ifndef EVENT_H
#define EVENT_H
#include "Assets.h"
#include "Combat.h"
#include "Player.h"

class Event
{
private:

public:
	bool encounterInit;
	bool encounterInitTwo;

	int dialogue;

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
};

#endif

