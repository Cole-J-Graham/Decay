#pragma once
#include "Assets.h"
class Sprites : public Assets
{

private:
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
	void thomSprite(Assets& assets);
	void siwardSprite();
	void spadeSprite();

	//Sprite Textures
	sf::Texture playerTexture;
	sf::Texture playerTextureRage;
	//Zin Textures
	sf::Texture zinTexture;
	sf::Texture zinTextureHappy;
	sf::Texture zinTextureConcerned;
	sf::Texture zinTextureAnnoyed;
	sf::Texture zinTextureSad;
	sf::Texture zinTextureScared;
	//Thom Textures
	sf::Texture thomTexture;
	sf::Texture thomEnragedTexture;
	//Siward Textures
	sf::Texture siwardTexture;
	sf::Texture siwardTextureDecaying;
	sf::Texture siwardTextureDecayed;
	//Spade Textures
	sf::Texture spadeTexture;
	sf::Texture spadeTextureAngry;
	sf::Texture spadeTextureHappy;
	sf::Texture spadeTextureSmug;
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
	sf::Texture thomEntity;
	sf::Texture siwardEntityTexture;
	sf::Texture siwardEntityCastleTexture;
	sf::Texture siwardEntityDuelTexture;
	sf::Texture spadeEntityForest;
	sf::Texture spadeEntityAbyssalForest;
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

