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
	sf::Texture playerTexture;
	sf::Texture spadeTexture;
	sf::Texture zinTexture;
	sf::Texture combatTexture;
	sf::Texture boxTexture;
	sf::Texture mapTexture;
	sf::Texture buttonTexture;
	sf::Texture arrowTextureRight;
	sf::Texture arrowTextureLeft;
	sf::Texture buttonBackTexture;
	sf::Texture textureTravel;
	sf::Texture multiArrowTexture;

	//Map Textures
	sf::Texture textureMapView;

	//Sprites
	sf::Sprite player;
	sf::Sprite spade;
	sf::Sprite zin;
	sf::Sprite box;
	sf::Sprite map;
	sf::Sprite button;
	sf::Sprite buttonBack;
	sf::Sprite spriteTravel;
	sf::Sprite spriteMapView;
	sf::Sprite multiArrow;

	//Rectangles
	sf::RectangleShape rect;
	sf::RectangleShape rectMap;
	sf::RectangleShape rectStats;
	sf::RectangleShape rectInventory;
	sf::RectangleShape rectStatsBox;
	sf::RectangleShape rectSpadeSpriteBox;
	sf::RectangleShape rectStatsPointsBox;
	sf::RectangleShape rectStrengthPointsBox;
	sf::RectangleShape rectFortitudePointsBox;
	sf::RectangleShape rectVitalityPointsBox;
	sf::RectangleShape rectStatsSideMenu;
	sf::RectangleShape playerStatsBoxButton;
	sf::RectangleShape rectInventoryBox;
	sf::RectangleShape rectAttackSmite;
	sf::RectangleShape buttonMap;

	//Main Menu
	sf::RectangleShape menuScreen;
	sf::RectangleShape menuStartButton;
	sf::RectangleShape menuLoadButton;
	sf::RectangleShape menuQuitButton;

	sf::RectangleShape menuIntroButton;
	sf::RectangleShape menuSkipIntroButton;

	sf::Text menuStartButtonText;
	sf::Text menuLoadButtonText;
	sf::Text menuQuitButtonText;

	std::vector<sf::RectangleShape> menuScreenElements {menuStartButton, menuLoadButton,
		menuQuitButton, menuIntroButton, menuSkipIntroButton};
	std::vector<sf::Text> menuScreenElementsText {menuStartButtonText, menuLoadButtonText,
		menuQuitButtonText, menuLoadButtonText, menuQuitButtonText};

	//Zin Stats Assets
	sf::RectangleShape zinStatsBoxButton;
	sf::RectangleShape rectStatsPointsBoxZin;
	sf::RectangleShape rectResolvePointsBox;
	sf::RectangleShape rectPatiencePointsBox;
	sf::RectangleShape rectResiliencePointsBox;

	//Combat Assets
	sf::RectangleShape rectAttack;
	sf::RectangleShape rectGuard;
	sf::RectangleShape rectMend;
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
	sf::Text spadeText;
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
	sf::Text textGuard;
	sf::Text textMend;

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
		rectAttack, rectAttackSmite, rectSpadeSpriteBox, playerSpriteBorder, zinSpriteBorder,
		hostileSpriteBorder, rectGuard, rectMend};

	std::vector<sf::Text> textElements {rectStatsText, rectInventoryText, menuText, 
		attackText, smiteText, spadeText, playerNameText, zinText,
		hostileNameText, textGuard, textMend};

	std::vector<sf::Sprite> spriteElements {button, buttonBack, spade, 
		zin, player};

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

	//Forest Map Sprites
	sf::Sprite forestMapView;
	sf::Texture forestMapTexture;
	sf::Sprite forestBonfire;
	sf::Sprite forestMapEntrance;
	sf::Sprite forestMapDepths;
	sf::Sprite forestMapAbyssal;
	sf::Sprite forestMapAbyssalDepths;
	sf::Text forestBonfireText;
	sf::Text forestEntranceText;
	sf::Text forestDepthsText;
	sf::Text forestAbyssalText;
	sf::Text forestMapAbyssalDepthsText;

	//Map Button Selectors
	sf::RectangleShape buttonViewForestMap;
	sf::RectangleShape buttonViewCastleMap;
	sf::RectangleShape buttonViewDecayPlaneMap;
	sf::Text buttonViewForestMapText;
	sf::Text buttonViewCastleMapText;
	sf::Text buttonViewDecayPlaneMapText;

	//Decay Map Sprites
	sf::Texture decayTexture;
	sf::Sprite decayMapView;
	sf::Sprite decayBonfire;
	sf::Sprite decayMapChasms;
	sf::Sprite decayMapOcean;
	sf::Sprite decayMapForest;
	sf::Sprite decayMapGiants;

	//Decay Map Text
	sf::Text decayBonfireText;
	sf::Text decayMapChasmsText;
	sf::Text decayMapOceanText;
	sf::Text decayMapForestText;
	sf::Text decayMapGiantsText;

	//Button Map Vectors
	std::vector<sf::RectangleShape> buttonViewMap{buttonViewForestMap,
	buttonViewCastleMap, buttonViewDecayPlaneMap};

	std::vector<sf::Text> buttonViewMapText{buttonViewForestMapText,
	buttonViewCastleMapText, buttonViewDecayPlaneMapText};

	//Castle Map Sprites
	sf::Sprite castleBonfire;
	sf::Sprite buttoncastleHalls;
	sf::Sprite buttonCastleDepths;
	sf::Sprite buttonCastleChambers;
	sf::Sprite buttonCastleLabyrinth;

	//Castle Button Text
	sf::Text castleBonfireText;
	sf::Text castleHallsText;
	sf::Text castleDepthsText;
	sf::Text castleChambersText;
	sf::Text buttonCastleLabyrinthText;

	//Map Vectors
	std::vector<sf::Sprite> mapForestElements {forestBonfire, forestMapEntrance, 
		forestMapDepths, forestMapAbyssal, forestMapAbyssalDepths};
	std::vector<sf::Text> mapForestElementsText {forestBonfireText, forestEntranceText, 
		forestDepthsText, forestAbyssalText, forestMapAbyssalDepthsText};

	std::vector<sf::Sprite> mapCastleElements { castleBonfire, buttoncastleHalls,
		buttonCastleDepths, buttonCastleChambers, buttonCastleLabyrinth };
	std::vector<sf::Text> mapCastleElementsText { castleBonfireText, castleHallsText,
		castleDepthsText, castleChambersText, buttonCastleLabyrinthText };

	std::vector<sf::Sprite> mapDecayElements{ decayBonfire, decayMapChasms,
	decayMapOcean, decayMapForest, decayMapGiants };
	std::vector<sf::Text> mapDecayElementsText{ decayBonfireText, decayMapChasmsText,
	decayMapOceanText, decayMapForestText, decayMapGiantsText };

	//Detection
	sf::RectangleShape bonfireHealDetectionRect;
	sf::Text bonfireHealDetectionText;

	sf::RectangleShape bonfireSmithDetectionRect;
	sf::Text bonfireSmithDetectionText;

	//Sounds
	sf::Sound sound;
	sf::Sound blipsound;
	sf::Sound blipmenu;
	sf::Sound soundCom;
	sf::Sound soundWalk;
	sf::Sound soundAngry;
	sf::Sound soundCombatStart;
	sf::Sound soundHover;
	sf::Sound soundGuard;
	sf::Sound soundGuarded;
	sf::Sound soundMend;
	sf::Sound soundSmite;
	sf::Sound soundSlash;

	sf::SoundBuffer buffer;
	sf::SoundBuffer blipbuffer;
	sf::SoundBuffer blipmenubuffer;
	sf::SoundBuffer bufferCom;
	sf::SoundBuffer bufferWalk;
	sf::SoundBuffer bufferAngry;
	sf::SoundBuffer bufferCombatStart;
	sf::SoundBuffer bufferSoundHover;
	sf::SoundBuffer bufferGuard;
	sf::SoundBuffer bufferGuarded;
	sf::SoundBuffer bufferMend;
	sf::SoundBuffer bufferSmite;
	sf::SoundBuffer bufferSlash;

	//Music
	sf::Music music;

	//Strings
	std::string playerName;

	//Sprite Bool
	bool initialDrawIn;
	bool initMapTexture;
	bool initForestMapTexture;
	bool initDecayMapTexture;
	bool initMap;
	bool initStats;
	bool initInventory;
	bool plusboxes;

	//Menu Control Flow
	bool playerStatsInit;
	bool zinStatsInit;
	bool bootClicked;

	//Map Button Control Flow
	int areaUnlocked;
	int forestAreaUnlocked;
	int castleAreaUnlocked;
	int decayAreaUnlocked;

	//Sprite Control Flow
	bool playerLoadOnce;
	bool spadeInit;
	bool spadeLoadOnce;

	bool zinInit;
	bool zinLoadOnce;

	//Sprite Border Control Flow
	bool spriteInit;
	bool playerInit;

	//Sprite Integer Selection
	int playerCounter;
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
	bool introAssets;
	bool combatAssets;
	bool bonfireAssets;
	bool playerTurnAssets;
	bool zinTurnAssets;

	//Combat Move Unlocks
	int combatPlayerMoves;
	int combatZinMoves;

	//Constructors & Destructors
	Assets();
	~Assets();

	//Drawing Objects
	void drawObjects();
	void drawMainWindow();
	void drawStats();
	void drawInventory();
	void drawZinStats();
	void drawText();
	void drawMainMenu();

	//Draw Map Segments
	void drawMap();
	void drawForestMapButtons();
	void drawCastleMapButtons();
	void drawDecayMapButtons();

	//Detection Functions
	void bonfireHealDetection();
	void bonfireSmithDetection();

	//Draw Sprite Boxes
	void drawSpadeSpriteBox();
	void drawPlayerSpriteBox();
	void drawZinSpriteBox();

	//Sprite Functions
	void playerSprite();
	void spadeSprite();
	void zinSprite();

	//Sound Functions
	void loadSFX();

	//Combat Asset Functions
	void initCombatAssets();
	void playerCombatAssets();
	void zinCombatAssets();

	//Getters and Setters

};

#endif

