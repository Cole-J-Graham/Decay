#ifndef ASSETS_H
#define ASSETS_H

#include<iostream>
#include<vector>
#include<SFML/Graphics.hpp>
#include<SFML/Graphics/Text.hpp>
#include<SFML/Audio.hpp>

class Assets
{
private:

public:
	//Textures
	sf::Texture texture;
	sf::Texture zinTexture;
	sf::Texture combatTexture;
	sf::Texture boxTexture;
	sf::Texture mapTexture;
	sf::Texture buttonTexture;
	sf::Texture buttonBackTexture;
	sf::Texture textureTravel;

	//Map Textures
	sf::Texture textureMapView;

	//Sprites
	sf::Sprite sprite;
	sf::Sprite zin;
	sf::Sprite box;
	sf::Sprite map;
	sf::Sprite button;
	sf::Sprite buttonBack;
	sf::Sprite spriteTravel;

	//Map Sprites
	sf::Sprite spriteMapView;
	sf::Sprite buttonCastleEntrance;
	sf::Sprite buttonCastleDepths;

	//Rectangles
	sf::RectangleShape rect;
	sf::RectangleShape rectMap;
	sf::RectangleShape rectStats;
	sf::RectangleShape rectStatsBox;
	sf::RectangleShape rectSpriteBox;
	sf::RectangleShape rectStatsPointsBox;
	sf::RectangleShape rectStrengthPointsBox;

	//Text
	sf::Font font;
	sf::Text text;
	sf::Text playerText;
	sf::Text combatText;
	sf::Text locationText;
	sf::Text menuText;
	sf::Text rectStatsText;
	sf::Text spriteText;
	sf::Text statsText;
	sf::Text statsPointsText;
	sf::Text statsPointsTextTitle;
	sf::Text statsStrengthTextTitle;
	sf::Text statsStrengthText;

	//Button Text
	sf::Text castleEntranceText;
	sf::Text castleDepthsText;

	//Buttons
	sf::RectangleShape buttonMap;

	//Combat Assets
	sf::RectangleShape rectAttack;
	sf::RectangleShape rectFlee;
	sf::Text attackText;
	sf::Text fleeText;

	//Combat Sprites
	sf::RectangleShape playerSpriteBorder;
	sf::RectangleShape zinSpriteBorder;
	sf::RectangleShape hostileSpriteBorder;

	//Combat Sprites Name Text
	sf::Text playerNameText;
	sf::Text zinText;
	sf::Text hostileNameText;

	//Sounds
	sf::Sound sound;
	sf::Sound blipsound;
	sf::Sound blipmenu;
	sf::Sound soundCom;
	sf::Sound soundWalk;
	sf::Sound soundAngry;
	sf::Sound soundCombatStart;

	sf::SoundBuffer buffer;
	sf::SoundBuffer blipbuffer;
	sf::SoundBuffer blipmenubuffer;
	sf::SoundBuffer bufferCom;
	sf::SoundBuffer bufferWalk;
	sf::SoundBuffer bufferAngry;
	sf::SoundBuffer bufferCombatStart;

	//Music
	sf::Music music;

	//Strings
	std::string playerName;

	//Sprite Bool
	bool initMapTexture;
	bool initMap;
	bool initStats;

	//Sprite Control Flow
	bool spadeInit;
	bool spadeLoadOnce;

	bool zinInit;
	bool zinLoadOnce;

	//Sprite Border Control Flow
	bool spriteInit;

	//Sprite Integer Selection
	int spadeCounter;
	int zinCounter;
	int mapCounter;
	int dialogueCounter;
	int combatCounter;

	//Movable
	bool movable;
	bool movableStatsBox;

	//Rect Coordinates
	float rectMapX;
	float rectMapY;
	float rectStatsBoxX;
	float rectStatsBoxY;

	//Initialize Combat Assets
	bool combatAssets;
	bool playerTurnAssets;
	//Combat Control Flow
	int attackCounter;

	//Constructors & Destructors
	Assets();
	~Assets();

	//Drawing Objects
	void drawObjects();
	void drawMainWindow();
	void drawMap();
	void drawStats();
	void drawText();

	//Sprite Functions
	void drawSpriteBox();
	void spadeSprite();
	void zinSprite();

	//Sound Functions
	void loadSFX();

	//Combat Asset Functions
	void initCombatAssets();

	//Getters and Setters

};

#endif

