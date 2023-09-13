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
	bool zinLoadOnce;
	bool spadeLoadOnce;

	bool zinInit;
	bool spadeInit;

	//Sprite Border Control Flow
	bool spriteInit;
	bool playerInit;

	//Sprite Integer Selection
	int playerCounter;
	int zinCounter;
	int spadeCounter;
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

	//Strings
	std::string playerName;
	
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
	sf::RectangleShape rectVengeance;
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
	sf::Text textVengeance;

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
		hostileSpriteBorder, rectGuard, rectMend, rectVengeance };

	std::vector<sf::Text> textElements {rectStatsText, rectInventoryText, menuText, 
		attackText, smiteText, spadeText, playerNameText, zinText,
		hostileNameText, textGuard, textMend, textVengeance };

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
	sf::Sound soundVengeance;

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
	sf::SoundBuffer bufferVengeance;

	//Music
	sf::Music music;

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

	//Sprite Bool Getters
	bool& getInitialDrawIn() { return this->initialDrawIn; };
	bool& getInitMapTexture() { return this->initMapTexture; };
	bool& getInitForestMapTexture() { return this->initForestMapTexture; };
	bool& getInitDecayMapTexture() { return this->initDecayMapTexture; };
	bool& getInitMap() { return this->initMap; };
	bool& getInitStats() { return this->initStats; };
	bool& getInitInventory() { return this->initInventory; };
	bool& getPlusboxes() { return this->plusboxes; };

	//Sprite Bool Setters
	void setInitialDrawInTrue()  { this->initialDrawIn = true; };
	void setInitMapTextureTrue() { this->initMapTexture = true; };
	void setInitForestMapTextureTrue() { this->initForestMapTexture = true; };
	void setInitDecayMapTextureTrue() { this->initDecayMapTexture = true; };
	void setInitMapTrue() { this->initMap = true; };
	void setInitMapFalse() { this->initMap = false; };
	void setInitStatsTrue() { this->initStats = true; };
	void setInitStatsFalse() { this->initStats = false; };
	void setInitInventoryTrue() { this->initInventory = true; };
	void setInitInventoryFalse() { this->initInventory = false; };
	void setPlusboxesTrue() { this->plusboxes = true; };

	//Menu Control Flow Getters
	bool& getPlayerStatsInit() { return this->playerStatsInit; };
	bool& getZinStatsInit() { return this->zinStatsInit; };
	bool& getBootClicked() { return this->bootClicked; };

	//Menu Control Flow Setters
	void setPlayerStatsInitTrue() { this->playerStatsInit = true; };
	void setZinStatsInitTrue() { this->zinStatsInit = true; };
	void setBootClickedTrue() { this->bootClicked = true; };

	void setPlayerStatsInitFalse() { this->playerStatsInit = false; };
	void setZinStatsInitFalse() { this->zinStatsInit = false; };
	void setBootClickedFalse() { this->bootClicked = false; };

	//Map Button Control Flow Getters
	int& getAreaUnlocked() { return this->areaUnlocked; };
	int& getForestAreaUnlocked() { return this->forestAreaUnlocked; };
	int& getCastleAreaUnlocked() { return this->castleAreaUnlocked; };
	int& getDecayAreaUnlocked() { return this->decayAreaUnlocked; };

	//Sprite Control Flow Getters
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
	void setZinInitFalse() { this->zinInit = false; };
	void setSpadeInitFalse() { this->zinInit = false; };

	//Sprite Border Control Flow Getters
	bool& getSpriteInit() { return this->spriteInit; };
	bool& getPlayerInit() { return this->playerInit; };

	//Sprite Border Control Flow Setters
	void setSpriteInitTrue() { this->spriteInit = true; };
	void setPlayerInitTrue() { this->playerInit = true; };
	void setSpriteInitFalse() { this->spriteInit = false; };
	void setPlayerInitFalse() { this->playerInit = false; };

	//Sprite Integer Selection Getters
	int& getPlayerCounter() { return this->playerCounter; };
	int& getZinCounter() { return this->zinCounter; };
	int& getSpadeCounter() { return this->spadeCounter; };
	int& getMapCounter() { return this->mapCounter; };
	int& getDialogueCounter() { return this->dialogueCounter; };
	int& getCombatCounter() { return this->combatCounter; };

	//Sprite Integer Selection Setters
	void setPlayerCounterInc() { this->playerCounter++; };
	void setZinCounterInc() { this->zinCounter++; };
	void setSpadeCounterInc() { this->spadeCounter++; };
	void setMapCounterInc() { this->mapCounter++; };
	void setDialogueCounterInc() { this->dialogueCounter++; };
	void setCombatCounterInc() { this->combatCounter++; };

	void setPlayerCounterDec() { this->playerCounter--; };
	void setZinCounterDec() { this->zinCounter--; };
	void setSpadeCounterDec() { this->spadeCounter--; };
	void setMapCounterDec() { this->mapCounter--; };
	void setDialogueCounterDec() { this->dialogueCounter--; };
	void setCombatCounterDec() { this->combatCounter--; };

	void setZinCounterZero() { this->zinCounter = 0; };
	void setSpadeCounterZero() { this->spadeCounter = 0; };
	void setSpadeCounterOne() { this->spadeCounter = 1; };
	void setCombatCounterZero() { this->combatCounter = 0; };
	void setMapCounterZero() { this->mapCounter = 0; };
	void setMapCounterOne() { this->mapCounter = 1; };
	void setMapCounterTwo() { this->mapCounter = 2; };

	//Movable Getters
	bool& getMovable() { return this->movable; };
	bool& getMovableStatsBox() { return this->movableStatsBox; };

	//Movable Setters
	void setMovableTrue() { this->movable = true; };
	void setMovableStatsBoxTrue() { this->movableStatsBox = true; };
	void setMovableFalse() { this->movable = false; };
	void setMovableStatsBoxFalse() { this->movableStatsBox = false; };

	//Rect Coordinate Getters
	float& getRectMapX() { return this->rectMapX; };
	float& getRectMapY() { return this->rectMapY; };
	float& getRectStatsBoxX() { return this->rectStatsBoxX; };
	float& getRectStatsBoxY() { return this->rectStatsBoxY; };
	float& getRectInventoryBoxX() { return this->rectInventoryBoxX; };
	float& getRectInventoryBoxY() { return this->rectInventoryBoxY; };

	//Rect Coordinate Setters
	void setRectMapXVal() { this->rectMapX = 25; };
	void setRectMapYVal() { this->rectMapY = 50; };

	//Initialize Combat Assets Getters
	bool& getIntroAssets() { return this->introAssets; };
	bool& getCombatAssets() { return this->combatAssets; };
	bool& getBonfireAssets() { return this->bonfireAssets; };
	bool& getPlayerTurnAssets() { return this->playerTurnAssets; };
	bool& getZinTurnAssets() { return this->zinTurnAssets; };

	//Initialize Combat Assets Setters
	void setIntroAssetsTrue() { this->introAssets = true; };
	void setCombatAssetsTrue() { this->combatAssets = true; };
	void setBonfireAssetsTrue() { this->bonfireAssets = true; };
	void setPlayerTurnAssetsTrue() { this->playerTurnAssets = true; };
	void setZinTurnAssetsTrue() { this->zinTurnAssets = true; };

	void setIntroAssetsFalse() { this->introAssets = false; };
	void setCombatAssetsFalse() { this->combatAssets = false; };
	void setBonfireAssetsFalse() { this->bonfireAssets = false; };
	void setPlayerTurnAssetsFalse() { this->playerTurnAssets = false; };
	void setZinTurnAssetsFalse() { this->zinTurnAssets = false; };

	//Combat Move Unlock Getters
	int& getCombatPlayerMoves() { return this->combatPlayerMoves; };
	int& getCombatZinMoves() { return this->combatZinMoves; };

	//Combat Move Unlock Setters
	void setCombatPlayerMovesInc() { this->combatPlayerMoves++; };
	void setCombatZinMovesInc() { this->combatZinMoves++; };

	//String Getters
	std::string& getPlayerName() { return this->playerName; };

	//String Setters
	void setPlayerName() { this->playerName; };
};

#endif

