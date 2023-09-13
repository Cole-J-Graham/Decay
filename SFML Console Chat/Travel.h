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

	//Bonfire Bools
	bool forestBonfireInit;

	//Init Bools
	bool forestEntranceInit;
	bool forestDepthsInit;

	bool castleHallsInit;
	bool castleDepthsInit;

public:

	Assets assets;

	//Constructors & Destructors
	Travel();
	~Travel();

	//Core
	void travelCore(sf::RenderWindow& window, Assets& assets, Event& notevent, Combat& combat, Player& player);

	//Draw Intro
	void intro(sf::RenderWindow& window, Assets& assets, Event& notevent, Combat& combat, Player& player);
	void introBeginning(sf::RenderWindow& window, Assets& assets, Event& notevent, Combat& combat, Player& player);

	//Draw Forest
	void forestMap(sf::RenderWindow& window, Assets& assets, Event& notevent, Combat& combat, Player& player);
	void forestBonfire(sf::RenderWindow& window, Assets& assets, Event& notevent, Combat& combat, Player& player);
	void forestEntrance(Assets& assets, Event& notevent, Combat& combat, Player& player);
	void forestDepths(Assets& assets, Event& notevent, Combat& combat, Player& player);
	void forestAbyssal(Assets& assets, Event& notevent, Combat& combat, Player& player);
	void forestAbyssalDepths(Assets& assets, Event& notevent, Combat& combat, Player& player);

	//Draw Castle
	void castleMap(sf::RenderWindow& window, Assets& assets, Event& notevent, Combat& combat, Player& player);
	void castleBonfire(sf::RenderWindow& window, Assets& assets, Event& notevent, Combat& combat, Player& player);
	void castleHalls(Assets& assets, Event& notevent, Combat& combat, Player& player);
	void castleDepths(Assets& assets, Event& notevent, Combat& combat, Player& player);
	void castleChambers(Assets& assets, Event& notevent, Combat& combat, Player& player);
	void castleLabyrinth(Assets& assets, Event& notevent, Combat& combat, Player& player);

	//Draw Decay
	void decayMap(sf::RenderWindow& window, Assets& assets, Event& notevent, Combat& combat, Player& player);
	void decayBonfire(sf::RenderWindow& window, Assets& assets, Event& notevent, Combat& combat, Player& player);
	void decayChasms(Assets& assets, Event& notevent, Combat& combat, Player& player);
	void decayOcean(Assets& assets, Event& notevent, Combat& combat, Player& player);
	void decayForest(Assets& assets, Event& notevent, Combat& combat, Player& player);
	void decayGiants(Assets& assets, Event& notevent, Combat& combat, Player& player);

	//Core Getters
	int& getFrame() { return this->frame; };
	int& getTravel() { return this->travel; };

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

	//Bonfire Bools
	bool& getForestBonfireInit() { return this->forestBonfireInit; };


};



#endif

