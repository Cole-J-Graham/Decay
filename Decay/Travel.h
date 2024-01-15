#pragma once
#include<iostream>
#include<SFML/Window.hpp>
#include<SFML/Graphics.hpp>
#include<SFML/Graphics/Text.hpp>
#include<sstream>
#include<string>
#include<SFML/Audio.hpp>
#include"Event.h"

class Travel : public Event
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
	bool reInMap;

	//Sound Bools
	bool soundPlay;

public:

	//Assets assets;

	void render(sf::RenderTarget* target = nullptr);

	//Constructors & Destructors
	Travel();
	~Travel();

	//Core
	void travelCore(sf::RenderWindow& window, Animation& animate);
	void newArea(Animation& animate);
	void reInitMap(bool& inBool) {
		if (!this->reInMap) {
			inBool = false;
			this->reInMap = true;
		}
	}

	//Draw Intro
	void intro(sf::RenderWindow& window);
	void introBeginning(sf::RenderWindow& window);
	void enterBonfire(sf::RenderWindow& window);
	void nextArea(std::string& inString);

	//Draw Forest
	void forestMap(sf::RenderWindow& window, Animation& animate);
	void forestBonfire(sf::RenderWindow& window);
	void forestEntrance(sf::RenderWindow& window, Animation& animate);
	void forestDepths(sf::RenderWindow& window, Animation& animate);
	void forestAbyssal(sf::RenderWindow& window, Animation& animate);
	void forestAbyssalDepths(sf::RenderWindow& window, Animation& animate);

	//Draw Castle
	void castleMap(sf::RenderWindow& window, Animation& animate);
	void castleBonfire(sf::RenderWindow& window);
	void castleHalls(sf::RenderWindow& window, Animation& animate);
	void castleDepths(sf::RenderWindow& window, Animation& animate);
	void castleChambers(sf::RenderWindow& window, Animation& animate);
	void castleLabyrinth(sf::RenderWindow& window, Animation& animate);

	//Draw Decay
	void decayMap(sf::RenderWindow& window, Animation& animate);
	void decayBonfire(sf::RenderWindow& window);
	void decayChasms(sf::RenderWindow& window, Animation& animate);
	void decayOcean(sf::RenderWindow& window, Animation& animate);
	void decayForest(sf::RenderWindow& window, Animation& animate);
	void decayGiants(sf::RenderWindow& window, Animation& animate);

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
