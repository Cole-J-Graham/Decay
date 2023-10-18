#ifndef TRAVEL_H
#define TRAVEL_H

#include<iostream>
#include<SFML/Window.hpp>
#include<SFML/Graphics.hpp>
#include<SFML/Graphics/Text.hpp>
#include<sstream>
#include<string>
#include<SFML/Audio.hpp>
#include"Assets.h"
#include"Event.h"
#include"Combat.h"
#include"Player.h"

class Travel
{
private:
	//Core
	int frame;
	int travel;

	//Counters
	int introCounterDialogue;
	int introCounter;
	int forestCounter;
	int castleCounter;
	int decayCounter;

	//Core Bools
	bool frameInit;
	bool bonfireInit;

	//Sound Bools
	bool soundPlay;

public:

	Assets assets;

	//Constructors & Destructors
	Travel();
	~Travel();

	//Core
	void travelCore(sf::RenderWindow& window, Sprites& sprites, Event& notevent, 
		Combat& combat, Player& player, Animation& animate);
	void newArea(Sprites& sprites, Animation& animate);

	//Draw Intro
	void intro(sf::RenderWindow& window, Sprites& sprites, Event& notevent, Combat& combat, Player& player);
	void introBeginning(sf::RenderWindow& window, Sprites& sprites, Event& notevent);
	void enterBonfire(sf::RenderWindow& window, Sprites& sprites, Event& notevent);

	//Draw Forest
	void forestMap(sf::RenderWindow& window, Sprites& sprites, Event& notevent, Combat& combat, Player& player, Animation& animate);
	void forestBonfire(sf::RenderWindow& window, Sprites& sprites, Event& notevent, Combat& combat, Player& player, Animation& animate);
	void forestEntrance(Sprites& sprites, Event& notevent, Combat& combat, Player& player, Animation& animate);
	void forestDepths(Sprites& sprites, Event& notevent, Combat& combat, Player& player, Animation& animate);
	void forestAbyssal(Sprites& sprites, Event& notevent, Combat& combat, Player& player, Animation& animate);
	void forestAbyssalDepths(Sprites& sprites, Event& notevent, Combat& combat, Player& player, Animation& animate);

	//Draw Castle
	void castleMap(sf::RenderWindow& window, Sprites& sprites, Event& notevent, Combat& combat, Player& player, Animation& animate);
	void castleBonfire(sf::RenderWindow& window, Sprites& sprites, Event& notevent, Combat& combat, Player& player, Animation& animate);
	void castleHalls(Sprites& sprites, Event& notevent, Combat& combat, Player& player, Animation& animate);
	void castleDepths(Sprites& sprites, Event& notevent, Combat& combat, Player& player, Animation& animate);
	void castleChambers(Sprites& sprites, Event& notevent, Combat& combat, Player& player, Animation& animate);
	void castleLabyrinth(Sprites& sprites, Event& notevent, Combat& combat, Player& player, Animation& animate);

	//Draw Decay
	void decayMap(sf::RenderWindow& window, Sprites& sprites, Event& notevent, Combat& combat, Player& player, Animation& animate);
	void decayBonfire(sf::RenderWindow& window, Sprites& sprites, Event& notevent, Combat& combat, Player& player, Animation& animate);
	void decayChasms(Sprites& sprites, Event& notevent, Combat& combat, Player& player, Animation& animate);
	void decayOcean(Sprites& sprites, Event& notevent, Combat& combat, Player& player, Animation& animate);
	void decayForest(Sprites& sprites, Event& notevent, Combat& combat, Player& player, Animation& animate);
	void decayGiants(Sprites& sprites, Event& notevent, Combat& combat, Player& player, Animation& animate);

	//Core Getters
	int& getFrame() { return this->frame; };
	int& getTravel() { return this->travel; };
	bool& getBonfireInit() { return this->bonfireInit; };

	//Core Setters
	void setFrameInc() { this->frame++; };
	void setFrameDec() { this->frame--; };

	//Counter Getters
	int& getIntroCounterDialogue() { return this->introCounterDialogue; };
	int& getIntroCounter() { return this->introCounter; };
	int& getForestCounter() { return this->forestCounter; };
	int& getCastleCounter() { return this->castleCounter; };
	int& getDecayCounter() { return this->decayCounter; };

	//Counter Setters
	void setIntroCounterDialogueInc() { this->introCounterDialogue++; };

	//Core Bools Getters
	bool& getFrameInit() { return this->frameInit; };

	//Core Bools Setters
	void setFrameInitFalse() { this->frameInit = false; };
};



#endif

