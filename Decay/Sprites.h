#pragma once
#include "Assets.h"
class Sprites : public Assets
{

private:
	bool zinInit;
	bool spadeInit;
	bool hostileInit;
	bool hostileLoadOnce;

	//Sprite Control Flow
	bool zinLoadOnce;
	bool spadeLoadOnce;
	bool siwardLoadOnce;
	bool playerLoadOnce;

	//Sprite Border Control Flow
	bool spriteInit;
	bool playerInit;

	//Sprite Integer Selection
	int spriteViewerCounter;
	int entityViewerCounter;
	int siwardCounter;
	int spadeCounter;

public:
	//Constructors and Destructors
	Sprites();
	~Sprites();

	//Core Functions
	void drawObjects(Assets& assets);

	//Loading Functions
	void loadSprites();
	void loadEntities();

	//Entity Functions
	void drawEntityViewer();

	//Sprite Functions
	void hostileSprite(Assets& assets);
	void playerSprite(Assets& assets);
	void zinSprite(Assets& assets);
	void siwardSprite();
	void spadeSprite();

	//Sprite Textures
	sf::Texture siwardTexture;
	sf::Texture playerTexture;
	sf::Texture spadeTexture;
	//Zin Textures
	sf::Texture zinTexture;
	sf::Texture zinTextureHappy;
	sf::Texture zinTextureConcerned;
	sf::Texture zinTextureAnnoyed;
	//Hostile Sprite Textures
	sf::Texture hostileTextureWolf;
	sf::Texture hostileTextureWalker;
	sf::Texture hostileTextureKnight;
	sf::Texture hostileTextureTree;
	sf::Texture hostileTextureNun;
	sf::Texture hostileTextureDecapod;
	sf::Texture hostileTextureHaze;
	sf::Texture hostileTextureJester;
	sf::Texture hostileTextureWallMimic;
	sf::Texture hostileTextureLostKnight;
	sf::Texture hostileTexturePhantom;
	sf::Texture hostileTextureEater;
	sf::Texture hostileTextureLimbSplitter;
	sf::Texture hostileTextureBurrower;
	sf::Texture hostileTextureChatterMouth;
	sf::Texture hostileTextureReclus;
	sf::Texture hostileTextureAlphaEntity;

	//Entity Viewer Objects
	sf::Text entityBoxText;
	sf::RectangleShape entityBoxHeader;
	sf::RectangleShape entityBox;
	sf::Sprite entitySprite;
	//Viewer Files Main
	sf::Texture blankEntity;
	sf::Texture siwardEntityTexture;
	sf::Texture spadeEntityForest;
	sf::Texture spadeEntityCastle;
	//Viewer Files Random Events
	sf::Texture treeEntity;
	sf::Texture obeliskEntity;
	sf::Texture strangeCreature;
	//Viewer Files Hostile Entities
	sf::Texture decayEntity;
	sf::Texture hostileTreeEntity;
	sf::Texture lostNunEntity;
	sf::Texture decapodEntity;
	sf::Texture wolfEntity;
	sf::Texture knightEntity;
	sf::Texture hazeEntity;
	sf::Texture jesterEntity;
	sf::Texture wallMimicEntity;
	sf::Texture lostKnightEntity;
	sf::Texture phantomEntity;
	sf::Texture eaterEntity;
	sf::Texture limbSplitterEntity;
	sf::Texture burrowerEntity;
	sf::Texture chatterMouthEntity;
	sf::Texture reclusEntity;
	sf::Texture tendrilAlphaEntity;

	//Sprite Control Flow Getters
	bool& getSiwardLoadOnce() { return this->siwardLoadOnce; };
	bool& getPlayerLoadOnce() { return this->playerLoadOnce; };
	bool& getZinLoadOnce() { return this->zinLoadOnce; };
	bool& getSpadeLoadOnce() { return this->spadeLoadOnce; };

	bool& getZinInit() { return this->zinInit; };
	bool& getSpadeInit() { return this->spadeInit; };

	//Sprite Control Flow Setters
	void setPlayerLoadOnceFalse() { this->playerLoadOnce = false; };
	void setZinLoadOnceFalse() { this->zinLoadOnce = false; };
	void setSpadeLoadOnceFalse() { this->spadeLoadOnce = false; };

	void setZinInitTrue() { this->zinInit = true; };
	void setSpadeInitTrue() { this->zinInit = true; };
	void setHostileInitTrue() { this->hostileInit = true; };
	void setZinInitFalse() { this->zinInit = false; };
	void setSpadeInitFalse() { this->zinInit = false; };
	void setHostileInitFalse() { this->hostileInit = false; };

	//Sprite Border Control Flow Getters
	bool& getSpriteInit() { return this->spriteInit; };
	bool& getPlayerInit() { return this->playerInit; };

	//Sprite Border Control Flow Setters
	void setSpriteInitTrue() { this->spriteInit = true; };
	void setPlayerInitTrue() { this->playerInit = true; };
	void setSpriteInitFalse() { this->spriteInit = false; };
	void setPlayerInitFalse() { this->playerInit = false; };

	//Sprite Integer Selection Getters
	int& getSiwardCounter() { return this->siwardCounter; };
	int& getSpadeCounter() { return this->spadeCounter; };
	int& getSpriteViewerCounter() { return this->spriteViewerCounter; };
	int& getEntityViewerCounter() { return this->entityViewerCounter; };

	//Sprite Integer Selection Setters
	void setSpadeCounterInc() { this->spadeCounter++; };

	void setSpadeCounterDec() { this->spadeCounter--; };

	void setSpadeCounterZero() { this->spadeCounter = 0; };
	void setSpadeCounterOne() { this->spadeCounter = 1; };

};

