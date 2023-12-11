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
	bool thomUnlocked;
	int dialogueCounter;
	int combatCounter;
	int playerCounter;
	int zinCounter;
	int thomCounter;
	int hostileCounter;
	int mapCounter;
	int tipBoxCounter;
	int showAnsBoxesCounter;

	//Sprite Bool
	bool initialDrawIn;
	bool initForestMapTexture;
	bool initCastleMapTexture;
	bool initDecayMapTexture;
	bool initMap;
	bool initStats;
	bool initInventory;
	bool plusboxes;

	//Menu Control Flow
	bool playerStatsInit;
	bool zinStatsInit;
	bool bootClicked;
	bool introFinished;
	bool settingsShown;

	//Map Button Control Flow
	int areaUnlocked;
	int forestAreaUnlocked;
	int castleAreaUnlocked;
	int decayAreaUnlocked;

	bool startFrame;
	bool endFrame;

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
	bool eventAssets;
	bool bonfireAssets;
	bool playerTurnAssets;
	bool zinTurnAssets;
	bool thomTurnAssets;
	bool playerDeath;

	//Combat Move Unlocks
	int combatPlayerMoves;
	int combatZinMoves;
	int combatThomMoves;

	//Music
	bool trackPlayed;
	bool ambPlayed;

	//Strings
	std::string playerName;

	//ToolTip Strings
	std::string tipStrength;
	std::string tipFortitude;
	std::string tipVitality;

	std::string tipResolve;
	std::string tipPatience;
	std::string tipResilience;

	std::string tipSlash;
	std::string tipGuard;
	std::string tipDecay;
	std::string tipHefty;
	std::string tipSynergy;
	std::string tipIronWall;

	std::string tipSmite;
	std::string tipMend;
	std::string tipVengeance;
	std::string tipBlaze;
	std::string tipHeal;
	std::string tipFlames;

	std::string tipBarrier;
	std::string tipEnrage;
	
public:
	//Constructors & Destructors
	Assets();
	~Assets();

	//Core Functions
	void loadSprites();
	void loadSounds();
	void loadMapImages();

	//Draw Functions
	void drawObjects();
	void drawMainWindow();
	void drawText();
	void drawMainMenu();
	void drawDeathAssets();
	void drawAnswerBoxes();
	void drawTipBox();

	//Stat && Inventory Functions
	void drawStats();
	void drawZinStats();
	void drawInventory();


	//Draw Map Segments
	void drawMap();
	void drawForestMapButtons();
	void drawCastleMapButtons();
	void drawDecayMapButtons();

	//Detection Functions
	void bonfireHealDetection();
	void bonfireSmithDetection();

	//Draw Sprite Boxes
	void drawSpriteBoxes();

	//Sound Functions
	void loadSFX();
	void playTrack(sf::Music& track);
	void playAmbience(sf::Music& track);

	//Combat Asset Functions
	void initCombatAssets();
	void playerCombatAssets();
	void zinCombatAssets();
	void thomCombatAssets();

	//Window Icon
	sf::Image windowIcon;

	//Textures
	sf::Texture combatTexture;
	sf::Texture boxTexture;
	sf::Texture buttonTexture;
	sf::Texture arrowTextureRight;
	sf::Texture arrowTextureLeft;
	sf::Texture buttonBackTexture;
	sf::Texture textureTravel;
	sf::Texture multiArrowTexture;

	//Map Textures
	sf::Texture textureMapView;

	//Sprites
	sf::Sprite siward;
	sf::Sprite player;
	sf::Sprite spade;
	sf::Sprite zin;
	sf::Sprite thom;
	sf::Sprite ri;
	sf::Sprite grif;

	sf::Sprite box;
	sf::Sprite map;
	sf::Sprite button;
	sf::Sprite buttonBack;
	sf::Sprite spriteTravel;
	sf::Sprite spriteMapView;
	sf::Sprite multiArrow;

	//Rectangles
	sf::RectangleShape rect;
	sf::RectangleShape mapBorder;
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
	sf::RectangleShape buttonMap;
	sf::RectangleShape tipBox;
	sf::RectangleShape rectSettings;

	//Main Menu && Settings
	sf::RectangleShape menuScreen;
	sf::RectangleShape menuStartButton;
	sf::RectangleShape menuLoadButton;
	sf::RectangleShape menuQuitButton;

	sf::RectangleShape menuIntroButton;
	sf::RectangleShape menuSkipIntroButton;
	sf::RectangleShape saveButton;

	sf::Text menuStartButtonText;
	sf::Text menuLoadButtonText;
	sf::Text menuQuitButtonText;
	sf::Text saveButtonText;

	std::vector<sf::RectangleShape> menuScreenElements {menuStartButton, menuLoadButton,
		menuQuitButton, menuIntroButton, menuSkipIntroButton, saveButton };
	std::vector<sf::Text> menuScreenElementsText {menuStartButtonText, menuLoadButtonText,
		menuQuitButtonText, menuLoadButtonText, menuQuitButtonText, saveButtonText };

	//Death Screen Assets
	sf::Text deathText;

	//Zin Stats Assets
	sf::RectangleShape zinStatsBoxButton;
	sf::RectangleShape rectStatsPointsBoxZin;
	sf::RectangleShape rectResolvePointsBox;
	sf::RectangleShape rectPatiencePointsBox;
	sf::RectangleShape rectResiliencePointsBox;

	sf::Sprite hostile;

	//Text
	sf::Font font;
	sf::Text text;
	sf::Text playerText;
	sf::Text locationText;
	sf::Text menuText;
	sf::Text rectStatsText;
	sf::Text rectInventoryText;
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
	sf::Text spadeText;
	sf::Text tipBoxText;
	

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

	//Combat Assets
	sf::RectangleShape rectSlash;
	sf::RectangleShape rectGuard;
	sf::RectangleShape rectDecay;
	sf::RectangleShape rectHefty;
	sf::RectangleShape rectSynergy;
	sf::RectangleShape rectIronWall;

	sf::RectangleShape rectSmite;
	sf::RectangleShape rectMend;
	sf::RectangleShape rectVengeance;
	sf::RectangleShape rectBlaze;
	sf::RectangleShape rectFocus;
	sf::RectangleShape rectFlames;

	sf::RectangleShape rectBarrier;
	sf::RectangleShape rectEnraged;

	std::vector<sf::RectangleShape> combatRect{ rectSlash, rectGuard, 
		rectDecay, rectHefty, rectSynergy, rectIronWall, rectSmite, rectMend, 
		rectVengeance, rectBlaze, rectFocus, rectFlames, rectBarrier, 
		rectEnraged };

	//combatText Vect Objects
	sf::Text textSlash;
	sf::Text textGuard;
	sf::Text textDecay;
	sf::Text textHefty;
	sf::Text textSynergy;
	sf::Text textIronWall;

	sf::Text textSmite;
	sf::Text textMend;
	sf::Text textVengeance;
	sf::Text textBlaze;
	sf::Text textFocus;
	sf::Text textFlames;

	sf::Text textBarrier;
	sf::Text textEnraged;

	std::vector<sf::Text> combatText{ textSlash, textGuard, textDecay,
		textHefty, textSynergy, textIronWall, textSmite, textMend,
		textVengeance, textBlaze, textFocus, textFlames, textBarrier, 
		textEnraged };

	//Main Vectors
	std::vector<sf::RectangleShape> rectElements {rectStats, rectInventory, 
		buttonMap};

	std::vector<sf::Text> textElements {rectStatsText, rectInventoryText, 
		menuText};

	std::vector<sf::Sprite> spriteElements{ button, buttonBack, spade,
		zin, player, hostile, siward, thom, ri, grif };

	//Stats Menu Vectors
	std::vector<sf::RectangleShape> playerStatElements {rectStatsPointsBox, rectStrengthPointsBox,
		rectFortitudePointsBox, rectVitalityPointsBox, playerStatsBoxButton, zinStatsBoxButton };

	std::vector <sf::Text> playerTextPlus{ statsPointsText, statsStrengthText,
	statsFortitudeText, statsVitalityText, playerStatsBoxButtonText, zinStatsBoxButtonText };

	std::vector<sf::Text> playerTextElements { statsPointsTextTitle, statsStrengthTextTitle,
		statsFortitudeTextTitle, statsVitalityTextTitle, statsText};

	std::vector<sf::RectangleShape> zinStatElements {rectStatsPointsBoxZin, rectResolvePointsBox,
		rectPatiencePointsBox, rectResiliencePointsBox, playerStatsBoxButton, zinStatsBoxButton};

	std::vector<sf::Text> zinTextPlus{ statsPointsTextZin, statsResolveText,
	statsPatienceText, statsResilienceText, playerStatsBoxButtonText, zinStatsBoxButtonText };

		std::vector<sf::Text> zinTextElements {statsPointsTextTitleZin,
		statsResolveTextTitle, statsPatienceTextTitle, statsResilienceTextTitle, statsText};

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
	sf::RectangleShape bonfireHealBorder;
	sf::Text bonfireHealDetectionText;

	sf::RectangleShape bonfireSmithDetectionRect;
	sf::RectangleShape bonfireSmithBorder;
	sf::Text bonfireSmithDetectionText;

	//User Input (Answer Boxes Rects)
	sf::RectangleShape ansOne;
	sf::RectangleShape ansTwo;
	sf::Text ansOneText;
	sf::Text ansTwoText;

	//User Input Vector
	std::vector<sf::RectangleShape> answerBox {ansOne, ansTwo};
	std::vector<sf::Text> answerBoxText{ ansOneText, ansTwoText };

	//Sprite Rectangles and Text
	sf::RectangleShape boxPlayer;
	sf::RectangleShape boxZin;
	sf::RectangleShape boxHostile;
	sf::RectangleShape boxSpade;
	sf::RectangleShape boxSiward;
	sf::RectangleShape boxThom;
	sf::RectangleShape boxRi;
	sf::RectangleShape boxGrif;

	std::vector<sf::RectangleShape> spriteRect{ boxPlayer, boxZin, boxHostile,
		 boxSpade, boxSiward, boxThom, boxRi, boxGrif };

	sf::Text textPlayer;
	sf::Text textZin;
	sf::Text textHostile;
	sf::Text textSpade;
	sf::Text textSiward;
	sf::Text textThom;
	sf::Text textRi;
	sf::Text textGrif;

	std::vector<sf::Text> spriteText{ textPlayer, textZin, textHostile,
		textSpade, textSiward, textThom, textRi, textGrif };

	//Sounds
	sf::Sound sound;
	sf::Sound blipsound;
	sf::Sound blipmenu;
	sf::Sound statSound;
	sf::Sound soundWalk;
	sf::Sound soundHover;
	sf::Sound soundCampfire;
	sf::Sound soundClick;
	//Combat Sounds
	sf::Sound soundCom;
	sf::Sound soundDecay;
	sf::Sound soundVengeance;
	sf::Sound soundSlash;
	sf::Sound soundSmite;
	sf::Sound soundMend;
	sf::Sound soundGuarded;
	sf::Sound soundGuard;
	sf::Sound soundAngry;
	sf::Sound soundCombatStart;
	sf::Sound soundPlayerGuarded;
	sf::Sound soundThomGuard;
	sf::Sound soundEnraged;
	sf::Sound soundHefty;
	sf::Sound soundSynergy;
	sf::Sound soundBlaze;
	sf::Sound soundFlames;
	sf::Sound soundIronWall;
	sf::Sound soundBeastDeath;
	sf::Sound soundAltBeastDeath;
	//Sound Buffers
	sf::SoundBuffer buffer;
	sf::SoundBuffer blipbuffer;
	sf::SoundBuffer blipmenubuffer;
	sf::SoundBuffer statBuffer;
	sf::SoundBuffer bufferWalk;
	sf::SoundBuffer bufferSoundHover;
	sf::SoundBuffer bufferCampfire;
	sf::SoundBuffer bufferClick;
	//Combat Buffers
	sf::SoundBuffer bufferCom;
	sf::SoundBuffer bufferAngry;
	sf::SoundBuffer bufferCombatStart;
	sf::SoundBuffer bufferGuard;
	sf::SoundBuffer bufferGuarded;
	sf::SoundBuffer bufferMend;
	sf::SoundBuffer bufferSmite;
	sf::SoundBuffer bufferSlash;
	sf::SoundBuffer bufferVengeance;
	sf::SoundBuffer bufferDecay;
	sf::SoundBuffer bufferPlayerGuarded;
	sf::SoundBuffer bufferThomGuard;
	sf::SoundBuffer bufferEnraged;
	sf::SoundBuffer bufferHefty;
	sf::SoundBuffer bufferSynergy;
	sf::SoundBuffer bufferBlaze;
	sf::SoundBuffer bufferFlames;
	sf::SoundBuffer bufferIronWall;
	sf::SoundBuffer bufferBeastDeath;
	sf::SoundBuffer bufferAltBeastDeath;

	//Music
	sf::Music bonfire;
	sf::Music forestAmbience;
	
	sf::Music track1;
	sf::Music track2;
	sf::Music track3;
	sf::Music track4;
	sf::Music track5;
	sf::Music track6;
	sf::Music track7;
	sf::Music track8;
	sf::Music track9;
	sf::Music track10;
	sf::Music track11;

	//Forest Wallpapers
	sf::Texture mapTexture;
	sf::Texture forestEntrance1;
	sf::Texture forestEntrance2;
	sf::Texture forestEntrance3;
	sf::Texture forestEntrance4;
	sf::Texture forestEntrance5;
	sf::Texture forestEntrance6;
	sf::Texture forestEntrance7;
	sf::Texture forestEntrance8;
	sf::Texture forestEntrance9;
	sf::Texture forestEntrance10;
	sf::Texture forestEntrance11;
	sf::Texture forestEntrance12;
	sf::Texture forestEntrance13;
	sf::Texture forestEntrance14;
	sf::Texture forestEntrance15;

	sf::Texture forestDepths1;
	sf::Texture forestDepths2;
	sf::Texture forestDepths3;
	sf::Texture forestDepths4;
	sf::Texture forestDepths5;
	sf::Texture forestDepths6;
	sf::Texture forestDepths7;
	sf::Texture forestDepths8;
	sf::Texture forestDepths9;
	sf::Texture forestDepths10;
	sf::Texture forestDepths11;
	sf::Texture forestDepths12;
	sf::Texture forestDepths13;
	sf::Texture forestDepths14;
	sf::Texture forestDepths15;

	sf::Texture forestAbyssal1;
	sf::Texture forestAbyssal2;
	sf::Texture forestAbyssal3;
	sf::Texture forestAbyssal4;
	sf::Texture forestAbyssal5;
	sf::Texture forestAbyssal6;
	sf::Texture forestAbyssal7;
	sf::Texture forestAbyssal8;
	sf::Texture forestAbyssal9;
	sf::Texture forestAbyssal10;
	sf::Texture forestAbyssal11;
	sf::Texture forestAbyssal12;
	sf::Texture forestAbyssal13;
	sf::Texture forestAbyssal14;
	sf::Texture forestAbyssal15;

	sf::Texture forestAbyssalDepth1;
	sf::Texture forestAbyssalDepth2;
	sf::Texture forestAbyssalDepth3;
	sf::Texture forestAbyssalDepth4;
	sf::Texture forestAbyssalDepth5;
	sf::Texture forestAbyssalDepth6;
	sf::Texture forestAbyssalDepth7;
	sf::Texture forestAbyssalDepth8;
	sf::Texture forestAbyssalDepth9;
	sf::Texture forestAbyssalDepth10;
	sf::Texture forestAbyssalDepth11;
	sf::Texture forestAbyssalDepth12;
	sf::Texture forestAbyssalDepth13;
	sf::Texture forestAbyssalDepth14;
	sf::Texture forestAbyssalDepth15;

	//Castle Wallpapers
	sf::Texture castleHalls1;
	sf::Texture castleHalls2;
	sf::Texture castleHalls3;
	sf::Texture castleHalls4;
	sf::Texture castleHalls5;
	sf::Texture castleHalls6;
	sf::Texture castleHalls7;
	sf::Texture castleHalls8;
	sf::Texture castleHalls9;
	sf::Texture castleHalls10;
	sf::Texture castleHalls11;
	sf::Texture castleHalls12;
	sf::Texture castleHalls13;
	sf::Texture castleHalls14;
	sf::Texture castleHalls15;

	sf::Texture castleDepths1;
	sf::Texture castleDepths2;
	sf::Texture castleDepths3;
	sf::Texture castleDepths4;
	sf::Texture castleDepths5;
	sf::Texture castleDepths6;
	sf::Texture castleDepths7;
	sf::Texture castleDepths8;
	sf::Texture castleDepths9;
	sf::Texture castleDepths10;
	sf::Texture castleDepths11;
	sf::Texture castleDepths12;
	sf::Texture castleDepths13;
	sf::Texture castleDepths14;
	sf::Texture castleDepths15;

	sf::Texture castleChambers1;
	sf::Texture castleChambers2;
	sf::Texture castleChambers3;
	sf::Texture castleChambers4;
	sf::Texture castleChambers5;
	sf::Texture castleChambers6;
	sf::Texture castleChambers7;
	sf::Texture castleChambers8;
	sf::Texture castleChambers9;
	sf::Texture castleChambers10;
	sf::Texture castleChambers11;
	sf::Texture castleChambers12;
	sf::Texture castleChambers13;
	sf::Texture castleChambers14;
	sf::Texture castleChambers15;

	sf::Texture castleLab1;
	sf::Texture castleLab2;
	sf::Texture castleLab3;
	sf::Texture castleLab4;
	sf::Texture castleLab5;
	sf::Texture castleLab6;
	sf::Texture castleLab7;
	sf::Texture castleLab8;
	sf::Texture castleLab9;
	sf::Texture castleLab10;
	sf::Texture castleLab11;
	sf::Texture castleLab12;
	sf::Texture castleLab13;
	sf::Texture castleLab14;
	sf::Texture castleLab15;

	//Decay Wallpapers
	sf::Texture decayChasms1;
	sf::Texture decayChasms2;
	sf::Texture decayChasms3;
	sf::Texture decayChasms4;
	sf::Texture decayChasms5;
	sf::Texture decayChasms6;
	sf::Texture decayChasms7;
	sf::Texture decayChasms8;
	sf::Texture decayChasms9;
	sf::Texture decayChasms10;
	sf::Texture decayChasms11;
	sf::Texture decayChasms12;
	sf::Texture decayChasms13;
	sf::Texture decayChasms14;
	sf::Texture decayChasms15;

	sf::Texture decayOcean1;
	sf::Texture decayOcean2;
	sf::Texture decayOcean3;
	sf::Texture decayOcean4;
	sf::Texture decayOcean5;
	sf::Texture decayOcean6;
	sf::Texture decayOcean7;
	sf::Texture decayOcean8;
	sf::Texture decayOcean9;
	sf::Texture decayOcean10;
	sf::Texture decayOcean11;
	sf::Texture decayOcean12;
	sf::Texture decayOcean13;
	sf::Texture decayOcean14;
	sf::Texture decayOcean15;

	sf::Texture decayForest1;
	sf::Texture decayForest2;
	sf::Texture decayForest3;
	sf::Texture decayForest4;
	sf::Texture decayForest5;
	sf::Texture decayForest6;
	sf::Texture decayForest7;
	sf::Texture decayForest8;
	sf::Texture decayForest9;
	sf::Texture decayForest10;
	sf::Texture decayForest11;
	sf::Texture decayForest12;
	sf::Texture decayForest13;
	sf::Texture decayForest14;
	sf::Texture decayForest15;

	sf::Texture decayGiants1;
	sf::Texture decayGiants2;
	sf::Texture decayGiants3;
	sf::Texture decayGiants4;
	sf::Texture decayGiants5;
	sf::Texture decayGiants6;
	sf::Texture decayGiants7;
	sf::Texture decayGiants8;
	sf::Texture decayGiants9;
	sf::Texture decayGiants10;
	sf::Texture decayGiants11;
	sf::Texture decayGiants12;
	sf::Texture decayGiants13;
	sf::Texture decayGiants14;
	sf::Texture decayGiants15;

	//Sprite Int Getters
	int& getPlayerCounter() { return this->playerCounter; };
	int& getZinCounter() { return this->zinCounter; };
	int& getThomCounter() { return this->thomCounter; };
	int& getHostileCounter() { return this->hostileCounter; };
	int& getCombatCounter() { return this->combatCounter; };
	int& getDialogueCounter() { return this->dialogueCounter; };

	//Sprite Int Setters
	void setCombatCounterZero() { this->combatCounter = 0; };
	void setCombatCounterInc() { this->combatCounter++; };
	void setCombatCounterDec() { this->combatCounter--; };
	void setDialogueCounterInc() { this->dialogueCounter++; };
	void setDialogueCounterDec() { this->dialogueCounter--; };

	//Sprite Bool Getters
	bool& getInitialDrawIn() { return this->initialDrawIn; };
	bool& getInitForestMapTexture() { return this->initForestMapTexture; };
	bool& getInitCastleMapTexture() { return this->initCastleMapTexture; };
	bool& getInitDecayMapTexture() { return this->initDecayMapTexture; };
	bool& getInitMap() { return this->initMap; };
	bool& getInitStats() { return this->initStats; };
	bool& getInitInventory() { return this->initInventory; };
	bool& getPlusboxes() { return this->plusboxes; };
	bool& getEndFrame() { return this->endFrame; };
	bool& getStartFrame() { return this->startFrame; };
	bool& getThomUnlocked() { return this->thomUnlocked; };

	//Sprite Bool Setters
	void setInitialDrawInTrue()  { this->initialDrawIn = true; };
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
	bool& getIntroFinished() { return this->introFinished; };
	bool& getSettingsShown() { return this->settingsShown; };

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

	int& getMapCounter() { return this->mapCounter; };
	int& getShowAnsBoxesCounter() { return this->showAnsBoxesCounter; };
	int& getTipBoxCounter() { return this->tipBoxCounter; };

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
	bool& getCombatAssets() { return this->combatAssets; };
	bool& getEventAssets() { return this->eventAssets; };
	bool& getBonfireAssets() { return this->bonfireAssets; };
	bool& getPlayerTurnAssets() { return this->playerTurnAssets; };
	bool& getZinTurnAssets() { return this->zinTurnAssets; };
	bool& getThomTurnAssets() { return this->thomTurnAssets; };
	bool& getPlayerDeath() { return this->playerDeath; };

	//Initialize Combat Assets Setters
	void setCombatAssetsTrue() { this->combatAssets = true; };
	void setBonfireAssetsTrue() { this->bonfireAssets = true; };
	void setPlayerTurnAssetsTrue() { this->playerTurnAssets = true; };
	void setZinTurnAssetsTrue() { this->zinTurnAssets = true; };
	void setThomTurnAssetsTrue() { this->thomTurnAssets = true; };
	void setPlayerDeathTrue() { this->playerDeath = true; };

	void setCombatAssetsFalse() { this->combatAssets = false; };
	void setBonfireAssetsFalse() { this->bonfireAssets = false; };
	void setPlayerTurnAssetsFalse() { this->playerTurnAssets = false; };
	void setZinTurnAssetsFalse() { this->zinTurnAssets = false; };
	void setThomTurnAssetsFalse() { this->thomTurnAssets = false; };
	void setPlayerDeathFalse() { this->playerDeath = false; };

	//Combat Move Unlock Getters
	int& getCombatPlayerMoves() { return this->combatPlayerMoves; };
	int& getCombatZinMoves() { return this->combatZinMoves; };
	int& getCombatThomMoves() { return this->combatThomMoves; };

	//Combat Move Unlock Setters
	void setCombatPlayerMovesInc() { this->combatPlayerMoves++; };
	void setCombatZinMovesInc() { this->combatZinMoves++; };

	//Music
	bool& getTrackPlayed() { return this->trackPlayed; };
	bool& getAmbTrackPlayed() { return this->ambPlayed; };

	//String Getters
	std::string& getPlayerName() { return this->playerName; };

	//ToolTip Getters
	std::string& getTipStrength() { return this->tipStrength; };
	std::string& getTipFortitude() { return this->tipFortitude; };
	std::string& getTipVitality() { return this->tipVitality; };

	std::string& getTipResolve() { return this->tipResolve; };
	std::string& getTipPatience() { return this->tipPatience; };
	std::string& getTipResilience() { return this->tipResilience; };

	std::string& getTipSlash() { return this->tipSlash; };
	std::string& getTipGuard() { return this->tipGuard; };
	std::string& getTipDecay() { return this->tipDecay; };
	std::string& getTipHefty() { return this->tipHefty; };
	std::string& getTipSynergy() { return this->tipSynergy; };
	std::string& getTipIronWall() { return this->tipIronWall; };

	std::string& getTipSmite() { return this->tipSmite; };
	std::string& getTipMend() { return this->tipMend; };
	std::string& getTipVengeance() { return this->tipVengeance; };
	std::string& getTipBlaze() { return this->tipBlaze; };
	std::string& getTipHeal() { return this->tipHeal; };
	std::string& getTipFlames() { return this->tipFlames; };

	std::string& getTipBarrier() { return this->tipBarrier; };
	std::string& getTipEnrage() { return this->tipEnrage; };

	//String Setters
	void setPlayerName() { this->playerName; };
};

#endif

