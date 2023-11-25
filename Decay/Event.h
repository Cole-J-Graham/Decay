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

	bool treeEnced;
	bool obeliskEnced;

	bool nunEnced;

	//Event Control Flow Bools
	bool spadePoison;

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
	void smithingSharpenBlade(sf::RenderWindow& window, Sprites& sprites, Player& player, Combat& combat);

	//Bonfire Text Events
	void zinEvents(sf::RenderWindow& window, Sprites& sprites, Animation& animate);

	//Zin Events
	void zinInitialTalk(Sprites& sprites, Animation& animate);

	//Forest Entrance Events
	void forestSiwardEnc(Sprites& sprites);
	void riEnc(Sprites& sprites);

	//Forest Depths Events
	void forestDepthsSpadeEnc(Sprites& sprites);
	void treeEnc(Sprites& sprites, Player& player);
	void thomEnc(Sprites& sprites);

	//Forest Abyssal Events
	void obeliskEnc(Sprites& sprites, Player& player);
	void lostNunEnc(Sprites& sprites);

	//Forest Abyssal Depths Events
	void forestAbyssalSpadeEnc(Sprites& sprites, Player& player);

	//Castle Hall Events
	void castleSpadeEnc(Sprites& sprites);
	void castleSpadeEncPoison(Sprites& sprites);

	//Castle Depth Events
	void castleSiwardEnc(Sprites& sprites);

	//Castle Chambers Events
	void castleGrifEnc(Sprites& sprites);

	//Castle Labyrinth Events
	void castleSiwardFinalEnc(Sprites& sprites);

	//Decay Forest Events
	void decaySpadeEnc(Sprites& sprites);
	void decaySpadeEncPoison(Sprites& sprites);


	//Control Flow Getters
	bool& getReInitialize() { return this->reInitialize; };

	//Event Availability Bools
	bool& getSiwardEncedFinal() { return this->siwardEncedFinal; };
	bool& getSpadeEnced() { return this->spadeEncedDecayPoison; };
	bool& getNunEnced() { return this->nunEnced; };

	//Counter Getters
	int& getZinTalkCounter() { return this->zinTalkCounter; };
	int& getChoiceCounter() { return this->choiceCounter; };

	int& getDialogue() { return this->dialogue; };

	//Event Control Flow Getters
	bool& getSpadePoison() { return this->spadePoison; };

	//Setters
	void setDialogueInc() { this->dialogue++; };
};

#endif

