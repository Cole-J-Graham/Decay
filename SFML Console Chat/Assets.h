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
	//Window Icon
	sf::Image windowIcon;

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
	sf::RectangleShape rectInventory;
	sf::RectangleShape rectStatsBox;
	sf::RectangleShape rectSpriteBox;
	sf::RectangleShape rectStatsPointsBox;
	sf::RectangleShape rectStrengthPointsBox;
	sf::RectangleShape rectFortitudePointsBox;
	sf::RectangleShape rectVitalityPointsBox;
	sf::RectangleShape rectStatsSideMenu;
	sf::RectangleShape playerStatsBoxButton;
	sf::RectangleShape rectInventoryBox;
	sf::RectangleShape rectAttackSmite;
	sf::RectangleShape buttonMap;

	//Zin Stats Assets
	sf::RectangleShape zinStatsBoxButton;
	sf::RectangleShape rectStatsPointsBoxZin;
	sf::RectangleShape rectResolvePointsBox;
	sf::RectangleShape rectPatiencePointsBox;
	sf::RectangleShape rectResiliencePointsBox;

	//Combat Assets
	sf::RectangleShape rectAttack;
	sf::Text attackText;

	//Text
	sf::Font font;
	sf::Text text;
	sf::Text playerText;
	sf::Text combatText;
	sf::Text locationText;
	sf::Text menuText;
	sf::Text rectStatsText;
	sf::Text rectInventoryText;
	sf::Text spriteText;
	sf::Text statsText;
	sf::Text statsPointsText;
	sf::Text statsPointsTextTitle;
	sf::Text statsStrengthTextTitle;
	sf::Text statsFortitudeTextTitle;
	sf::Text statsVitalityTextTitle;
	sf::Text statsStrengthText;
	sf::Text statsFortitudeText;
	sf::Text statsVitalityText;
	sf::Text playerStatsBoxButtonText;
	sf::Text inventoryText;
	sf::Text smiteText;

	//Zin Stats Assets Text
	sf::Text zinStatsBoxButtonText;
	sf::Text statsPointsTextZin;
	sf::Text statsResolveText;
	sf::Text statsPatienceText;
	sf::Text statsResilienceText;
	sf::Text statsPointsTextTitleZin;
	sf::Text statsResolveTextTitle;
	sf::Text statsPatienceTextTitle;
	sf::Text statsResilienceTextTitle;

	//Button Text
	sf::Text castleEntranceText;
	sf::Text castleDepthsText;

	//Combat Sprites
	sf::RectangleShape playerSpriteBorder;
	sf::RectangleShape zinSpriteBorder;
	sf::RectangleShape hostileSpriteBorder;

	//Combat Sprites Name Text
	sf::Text playerNameText;
	sf::Text zinText;
	sf::Text hostileNameText;

	//Main Vectors
	std::vector<sf::RectangleShape> rectElements {rectStats, rectInventory, buttonMap, 
		rectAttack, rectAttackSmite, rectSpriteBox, playerSpriteBorder, zinSpriteBorder,
		hostileSpriteBorder};

	std::vector<sf::Text> textElements {rectStatsText, rectInventoryText, menuText, 
		attackText, smiteText, spriteText, playerNameText, zinText,
		hostileNameText};

	std::vector<sf::Sprite> spriteElements {button, buttonBack, sprite, zin};

	//Stats Menu Vectors
	std::vector<sf::RectangleShape> playerStatElements {rectStatsPointsBox, rectStrengthPointsBox,
		rectFortitudePointsBox, rectVitalityPointsBox, playerStatsBoxButton, zinStatsBoxButton};

	std::vector<sf::Text> playerTextElements {statsPointsText, statsStrengthText,
		statsFortitudeText, statsVitalityText, statsPointsTextTitle, statsStrengthTextTitle,
		statsFortitudeTextTitle, statsVitalityTextTitle, playerStatsBoxButtonText, zinStatsBoxButtonText, statsText};

	std::vector<sf::RectangleShape> zinStatElements {rectStatsPointsBoxZin, rectResolvePointsBox,
		rectPatiencePointsBox, rectResiliencePointsBox, playerStatsBoxButton, zinStatsBoxButton};

	std::vector<sf::Text> zinTextElements {statsPointsTextZin, statsResolveText,
		statsPatienceText, statsResilienceText, statsPointsTextTitleZin,
		statsResolveTextTitle, statsPatienceTextTitle, statsResilienceTextTitle, 
		playerStatsBoxButtonText, zinStatsBoxButtonText, statsText};

	//Map Vectors
	std::vector<sf::Sprite> mapCastleElements {buttonCastleEntrance, buttonCastleDepths};
	std::vector<sf::Text> mapCastleElementsText {castleEntranceText, castleDepthsText};

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
	bool initialDrawIn;
	bool initMapTexture;
	bool initMap;
	bool initStats;
	bool initInventory;
	bool plusboxes;

	//Menu Control Flow
	bool playerStatsInit;
	bool zinStatsInit;

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
	float rectInventoryBoxX;
	float rectInventoryBoxY;

	//Initialize Combat Assets
	bool combatAssets;
	bool playerTurnAssets;
	bool zinTurnAssets;

	//Constructors & Destructors
	Assets();
	~Assets();

	//Drawing Objects
	void drawObjects();
	void drawMainWindow();
	void drawMap();
	void drawStats();
	void drawInventory();
	void drawZinStats();
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

