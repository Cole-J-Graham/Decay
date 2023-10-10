#include "Assets.h"

//Constructors & Destructors
Assets::Assets()
{
    //Sprite Bool
    this->initialDrawIn = false;
    this->initMapTexture = false;
    this->initForestMapTexture = false;
    this->initDecayMapTexture = false;
    this->initMap = false;
    this->initStats = false;
    this->initInventory = false;
    this->plusboxes = false;

    //Menu Control Flow
    this->playerStatsInit = false;
    this->zinStatsInit = false;
    this->bootClicked = false;
    this->introFinished = false;
    this->settingsShown = false;

    //Map Button Control Flow
    this->areaUnlocked = 2;
    this->forestAreaUnlocked = 4;
    this->castleAreaUnlocked = 4;
    this->decayAreaUnlocked = 4;

    //Sprite Control Flow
    this->siwardLoadOnce = true;
    this->playerLoadOnce = true;
    this->zinLoadOnce = true;
    this->spadeLoadOnce = true;
    this->hostileLoadOnce = true;
    this->startFrame = true;
    this->endFrame = false;

    this->zinInit = false;
    this->spadeInit = false;
    this->hostileInit = false;

    //Sprite Border Control Flow
    this->spriteInit = false;
    this->playerInit = false;

    //Sprite Integer Selection
    this->siwardCounter = -1;
    this->playerCounter = -1;
    this->zinCounter = -1;
    this->spadeCounter = -1;
    this->hostileCounter = -1;
    this->mapCounter = -1;
    this->dialogueCounter = 0;
    this->combatCounter = 0;
    this->showAnsBoxesCounter = -1;
    this->choiceCounter = -1;
    this->tipBoxCounter = -1;
    this->spriteViewerCounter = -1;
    this->entityViewerCounter = -1;

    //Movable
    this->movable = false;
    this->movableStatsBox = false;

    //Rect Coordinates
    this->rectMapX = 25;
    this->rectMapY = 50;
    this->rectStatsBoxX = 1470;
    this->rectStatsBoxY = 10;
    this->rectInventoryBoxX = 1700;
    this->rectInventoryBoxY = 10;

    //Initialize Combat Assets
    this->combatAssets = false;
    this->eventAssets = false;
    this->bonfireAssets = false;
    this->playerTurnAssets = false;
    this->zinTurnAssets = false;

    //Combat Move Unlocks
    this->combatPlayerMoves = 2;
    this->combatZinMoves = 2;

    //Strings
    this->playerName = "player";

    buttonTexture.loadFromFile("C:/Users/Cole/source/repos/SFML Console Chat/SFML Console Chat/Assets/Sprites/buttonsolidfix.png");
    arrowTextureRight.loadFromFile("C:/Users/Cole/source/repos/SFML Console Chat/SFML Console Chat/Assets/Sprites/arrowright.png");
    arrowTextureLeft.loadFromFile("C:/Users/Cole/source/repos/SFML Console Chat/SFML Console Chat/Assets/Sprites/arrowleft.png");

    //Zin Sprites
    zinTexture.loadFromFile("C:/Users/Cole/source/repos/SFML Console Chat/SFML Console Chat/Assets/Sprites/zinsprite.png");
    zinTextureHappy.loadFromFile("C:/Users/Cole/source/repos/SFML Console Chat/SFML Console Chat/Assets/Sprites/zinHappySprite.png");
    zinTextureConcerned.loadFromFile("C:/Users/Cole/source/repos/SFML Console Chat/SFML Console Chat/Assets/Sprites/zinConcerned.png");
    zinTextureAnnoyed.loadFromFile("C:/Users/Cole/source/repos/SFML Console Chat/SFML Console Chat/Assets/Sprites/zinspriteannoyed.png");

    //Load Entity Viewer Files Main
    blankEntity.loadFromFile("C:/Users/Cole/source/repos/SFML Console Chat/SFML Console Chat/Assets/Sprites/entityBlank.png");
    siwardEntityTexture.loadFromFile("C:/Users/Cole/source/repos/SFML Console Chat/SFML Console Chat/Assets/Sprites/siwardEntity.jpeg");
    spadeEntityForest.loadFromFile("C:/Users/Cole/source/repos/SFML Console Chat/SFML Console Chat/Assets/Sprites/spadeEntityForest.png");
    spadeEntityCastle.loadFromFile("C:/Users/Cole/source/repos/SFML Console Chat/SFML Console Chat/Assets/Sprites/spadeEntityCastle.jpg");
    //Load Entity Viewer Files Random Events
    treeEntity.loadFromFile("C:/Users/Cole/source/repos/SFML Console Chat/SFML Console Chat/Assets/Sprites/entityTree.jpeg");
    obeliskEntity.loadFromFile("C:/Users/Cole/source/repos/SFML Console Chat/SFML Console Chat/Assets/Sprites/obeliskEntity.jpeg");
    //Load Entity Viewer Files Hostile Entities
    decayEntity.loadFromFile("C:/Users/Cole/source/repos/SFML Console Chat/SFML Console Chat/Assets/Sprites/decayEntity.jpeg");
    hostileTreeEntity.loadFromFile("C:/Users/Cole/source/repos/SFML Console Chat/SFML Console Chat/Assets/Sprites/hostileTreeSpriteEntity.jpeg");
    lostNunEntity.loadFromFile("C:/Users/Cole/source/repos/SFML Console Chat/SFML Console Chat/Assets/Sprites/lostNunEntity.jpeg");

    /*bufferClick.loadFromFile("C:/Users/Cole/source/repos/SFML Console Chat/SFML Console Chat/Assets/Sounds/click.wav");
    bufferCampfire.loadFromFile("C:/Users/Cole/source/repos/SFML Console Chat/SFML Console Chat/Assets/Sounds/campfire.wav");
    bufferDecay.loadFromFile("C:/Users/Cole/source/repos/SFML Console Chat/SFML Console Chat/Assets/Sounds/decayblade.wav");
    bufferVengeance.loadFromFile("C:/Users/Cole/source/repos/SFML Console Chat/SFML Console Chat/Assets/Sounds/vengeance.wav");
    bufferSlash.loadFromFile("C:/Users/Cole/source/repos/SFML Console Chat/SFML Console Chat/Assets/Sounds/slash.wav");
    bufferSmite.loadFromFile("C:/Users/Cole/source/repos/SFML Console Chat/SFML Console Chat/Assets/Sounds/smite.wav");
    bufferMend.loadFromFile("C:/Users/Cole/source/repos/SFML Console Chat/SFML Console Chat/Assets/Sounds/mend.wav");
    bufferGuarded.loadFromFile("C:/Users/Cole/source/repos/SFML Console Chat/SFML Console Chat/Assets/Sounds/guarded.wav");
    bufferGuard.loadFromFile("C:/Users/Cole/source/repos/SFML Console Chat/SFML Console Chat/Assets/Sounds/guard.wav");
    bufferSoundHover.loadFromFile("C:/Users/Cole/source/repos/SFML Console Chat/SFML Console Chat/Assets/Sounds/hoversound.wav");
    bufferWalk.loadFromFile("C:/Users/Cole/source/repos/SFML Console Chat/SFML Console Chat/Assets/Sounds/moveRoom.wav");
    bufferCom.loadFromFile("C:/Users/Cole/source/repos/SFML Console Chat/SFML Console Chat/Assets/Sounds/Boss hit 1.wav");
    buffer.loadFromFile("C:/Users/Cole/source/repos/SFML Console Chat/SFML Console Chat/Assets/Sounds/Text 1.wav");
    blipbuffer.loadFromFile("C:/Users/Cole/source/repos/SFML Console Chat/SFML Console Chat/Assets/Sounds/blipSelect.wav");
    blipmenubuffer.loadFromFile("C:/Users/Cole/source/repos/SFML Console Chat/SFML Console Chat/Assets/Sounds/menuclick.wav");
    bufferAngry.loadFromFile("C:/Users/Cole/source/repos/SFML Console Chat/SFML Console Chat/Assets/Sounds/angry.wav");
    bufferCombatStart.loadFromFile("C:/Users/Cole/source/repos/SFML Console Chat/SFML Console Chat/Assets/Sounds/combatstart.wav");*/
}

Assets::~Assets()
{

}

//Drawing Objects
void Assets::drawObjects()
{
    this->drawMainWindow();
    this->drawText();
    this->drawMap();
    this->drawStats();
    this->drawInventory();
    this->drawZinStats();
    this->drawTipBox();
    this->drawEntityViewer();
    //Sprite Assets
    this->siwardSprite();
    this->playerSprite();
    this->spadeSprite();
    this->zinSprite();
    this->hostileSprite();
    this->drawSpriteBoxes();
    //Combat Asset Functions
    this->initCombatAssets();
    //Detection
    this->bonfireHealDetection();
    this->bonfireSmithDetection();
    //User Input
    this->drawAnswerBoxes();
}

void Assets::drawMainWindow()
{
    //Draw Menu Box
    rect.setPosition(0.0f, 825.0f);
    rect.setSize(sf::Vector2f(1920.0f, 825.0f));
    rect.setOutlineColor(sf::Color::White);
    rect.setOutlineThickness(1.0f);
    if (combatAssets == false && bonfireAssets == false) {
        //Draw Rect Element Similiarities
        for (int i = 0; i < rectElements.size(); i++) {
            rectElements[i].setSize(sf::Vector2f(100.0f, 25.0f));
            rectElements[i].setOutlineColor(sf::Color::White);
            rectElements[i].setOutlineThickness(1.0f);
        }
        //Draw Map Button position
        rectElements[2].setPosition(1.0f, 795.0f);
        //Draw Stats Button position
        rectElements[0].setPosition(105.0f, 795.0f);
        //Draw Inventory Button position
        rectElements[1].setPosition(209.0f, 795.0f);
        //Draw Button
        if (this->endFrame) {
            spriteElements[0].setPosition(10000.0f, 10000.0f);
        }
        else {
            spriteElements[0].setPosition(1400.0f, 765.0f);
        }
        spriteElements[0].setTexture(arrowTextureRight);
        spriteElements[0].setScale(0.04, 0.04);
        //Draw Back Button
        if (this->startFrame == true) {
            spriteElements[1].setPosition(10000.0f, 10000.0f);
        }
        else {
            spriteElements[1].setPosition(445.0f, 765.0f);
        }
        buttonBackTexture.loadFromFile("C:/Users/Cole/source/repos/SFML Console Chat/SFML Console Chat/Assets/Sprites/buttonsolidfix.png");
        spriteElements[1].setTexture(arrowTextureLeft);
        spriteElements[1].setScale(0.04, 0.04);
        if (eventAssets == true) {
            //Make assets hidden during Events
            rectElements[2].setPosition(1.0f, 10000.0f);
            rectElements[1].setPosition(209.0f, 10000.0f);
            rectElements[0].setPosition(105.0f, 10000.0f);
            spriteElements[0].setPosition(1400.0f, 10000.0f);
            spriteElements[1].setPosition(445.0f, 10000.0f);
        }
    }
    else if (combatAssets == true) {
        //Make assets hidden during combat
        rectElements[2].setPosition(1.0f, 10000.0f);
        rectElements[1].setPosition(209.0f, 10000.0f);
        rectElements[0].setPosition(105.0f, 10000.0f);
        spriteElements[0].setPosition(1400.0f, 10000.0f);
        spriteElements[1].setPosition(445.0f, 10000.0f);
    }
    else if (bonfireAssets == true) {
        //Draw Map Button
        rectElements[2].setPosition(1.0f, 795.0f);
        rectElements[2].setSize(sf::Vector2f(100.0f, 25.0f));
        rectElements[2].setOutlineColor(sf::Color::White);
        rectElements[2].setOutlineThickness(1.0f);
        //Draw Stats Button
        rectElements[0].setPosition(105.0f, 795.0f);
        rectElements[0].setSize(sf::Vector2f(100.0f, 25.0f));
        rectElements[0].setOutlineColor(sf::Color::White);
        rectElements[0].setOutlineThickness(1.0f);
        //Draw Inventory Button
        rectElements[1].setPosition(209.0f, 795.0f);
        rectElements[1].setSize(sf::Vector2f(100.0f, 25.0f));
        rectElements[1].setOutlineColor(sf::Color::White);
        rectElements[1].setOutlineThickness(1.0f);
        //Hide Back and Forward Buttons
        spriteElements[0].setPosition(1400.0f, 10000.0f);
        spriteElements[1].setPosition(445.0f, 10000.0f);
    }
}

void Assets::drawStats()
{
    //Main Rect
    rectStatsBox.setFillColor(sf::Color::Black);
    rectStatsBox.setPosition(rectStatsBoxX, rectStatsBoxY);
    rectStatsBox.setSize(sf::Vector2f(200.0f, 600.0f));
    rectStatsBox.setOutlineColor(sf::Color::White);
    rectStatsBox.setOutlineThickness(1.0f);
    //Side Menu Player Stats Menu Rect
    playerStatElements[4].setPosition(rectStatsBoxX + 200, rectStatsBoxY);
    playerStatElements[4].setSize(sf::Vector2f(20.0f, 120.0f));
    playerStatElements[4].setOutlineColor(sf::Color::White);
    playerStatElements[4].setOutlineThickness(1.0f);
    //Side Menu Player Stats Menu Rect Text
    playerTextElements[8].setFont(font);
    playerTextElements[8].setCharacterSize(16);
    playerTextElements[8].setPosition(rectStatsBoxX + 205, rectStatsBoxY);
    playerTextElements[8].setString("P\nL\nA\nY\nE\nR");
    playerTextElements[8].setFillColor(sf::Color::White);
    //Side Menu Zin Stats Menu Rect
    playerStatElements[5].setPosition(rectStatsBoxX + 200, rectStatsBoxY + 120);
    playerStatElements[5].setSize(sf::Vector2f(20.0f, 100.0f));
    playerStatElements[5].setOutlineColor(sf::Color::White);
    playerStatElements[5].setOutlineThickness(1.0f);
    //Side Menu Zin Stats Menu Rect Text
    playerTextElements[9].setFont(font);
    playerTextElements[9].setCharacterSize(16);
    playerTextElements[9].setPosition(rectStatsBoxX + 205, rectStatsBoxY + 120);
    playerTextElements[9].setString("\nZ\nI\nN");
    playerTextElements[9].setFillColor(sf::Color::White);
    //Hp text
    playerTextElements[10].setFont(font);
    playerTextElements[10].setCharacterSize(16);
    playerTextElements[10].setFillColor(sf::Color(sf::Color::White));
    playerTextElements[10].setPosition(rectStatsBoxX, rectStatsBoxY);
    //Level up plus Box
    playerStatElements[0].setPosition(rectStatsBoxX, rectStatsBoxY + 100);
    playerStatElements[0].setSize(sf::Vector2f(20.0f, 20.0f));
    playerStatElements[0].setOutlineColor(sf::Color::White);
    playerStatElements[0].setOutlineThickness(1.0f);
    //Strength plus box
    playerStatElements[1].setPosition(rectStatsBoxX, rectStatsBoxY + 180);
    playerStatElements[1].setSize(sf::Vector2f(20.0f, 20.0f));
    playerStatElements[1].setOutlineColor(sf::Color::White);
    playerStatElements[1].setOutlineThickness(1.0f);
    //Fortitude plus box
    playerStatElements[2].setPosition(rectStatsBoxX, rectStatsBoxY + 160);
    playerStatElements[2].setSize(sf::Vector2f(20.0f, 20.0f));
    playerStatElements[2].setOutlineColor(sf::Color::White);
    playerStatElements[2].setOutlineThickness(1.0f);
    //Vitality plus box
    playerStatElements[3].setPosition(rectStatsBoxX, rectStatsBoxY + 140);
    playerStatElements[3].setSize(sf::Vector2f(20.0f, 20.0f));
    playerStatElements[3].setOutlineColor(sf::Color::White);
    playerStatElements[3].setOutlineThickness(1.0f);
    //Plus sign text for level up
    playerTextElements[0].setFont(font);
    playerTextElements[0].setCharacterSize(24);
    playerTextElements[0].setPosition(rectStatsBoxX + 3, rectStatsBoxY + 94);
    playerTextElements[0].setString("+");
    //plus sign text for strength
    playerTextElements[1].setFont(font);
    playerTextElements[1].setCharacterSize(24);
    playerTextElements[1].setPosition(rectStatsBoxX + 3, rectStatsBoxY + 174);
    playerTextElements[1].setString("+");
    //plus sign text for fortitude
    playerTextElements[2].setFont(font);
    playerTextElements[2].setCharacterSize(24);
    playerTextElements[2].setPosition(rectStatsBoxX + 3, rectStatsBoxY + 154);
    playerTextElements[2].setString("+");
    //plus sign text for vitality
    playerTextElements[3].setFont(font);
    playerTextElements[3].setCharacterSize(24);
    playerTextElements[3].setPosition(rectStatsBoxX + 3, rectStatsBoxY + 133);
    playerTextElements[3].setString("+");
    //Title next to level box
    playerTextElements[4].setFont(font);
    playerTextElements[4].setCharacterSize(14);
    playerTextElements[4].setPosition(rectStatsBoxX + 25, rectStatsBoxY + 100);
    playerTextElements[4].setFillColor(sf::Color::White);
    //Title next to strength box
    playerTextElements[5].setFont(font);
    playerTextElements[5].setCharacterSize(14);
    playerTextElements[5].setPosition(rectStatsBoxX + 25, rectStatsBoxY + 180);
    playerTextElements[5].setFillColor(sf::Color::White);
    //Title next to fortitude box
    playerTextElements[6].setFont(font);
    playerTextElements[6].setCharacterSize(14);
    playerTextElements[6].setPosition(rectStatsBoxX + 25, rectStatsBoxY + 160);
    playerTextElements[6].setFillColor(sf::Color::White);
    //Title next to vitality box
    playerTextElements[7].setFont(font);
    playerTextElements[7].setCharacterSize(14);
    playerTextElements[7].setPosition(rectStatsBoxX + 25, rectStatsBoxY + 140);
    playerTextElements[7].setFillColor(sf::Color::White);
}

void Assets::drawInventory()
{
    //Main Rect
    rectInventoryBox.setFillColor(sf::Color::Black);
    rectInventoryBox.setPosition(rectInventoryBoxX, rectInventoryBoxY);
    rectInventoryBox.setSize(sf::Vector2f(200.0f, 600.0f));
    rectInventoryBox.setOutlineColor(sf::Color::White);
    rectInventoryBox.setOutlineThickness(1.0f);
    //Inventory Text
    inventoryText.setFont(font);
    inventoryText.setCharacterSize(16);
    inventoryText.setFillColor(sf::Color(sf::Color::White));
    inventoryText.setPosition(rectInventoryBoxX, rectInventoryBoxY);
}

void Assets::drawZinStats()
{
    //Level up plus Box
    zinStatElements[0].setPosition(rectStatsBoxX, rectStatsBoxY + 100);
    zinStatElements[0].setSize(sf::Vector2f(20.0f, 20.0f));
    zinStatElements[0].setOutlineColor(sf::Color::White);
    zinStatElements[0].setOutlineThickness(1.0f);
    //Resolve plus box
    zinStatElements[1].setPosition(rectStatsBoxX, rectStatsBoxY + 180);
    zinStatElements[1].setSize(sf::Vector2f(20.0f, 20.0f));
    zinStatElements[1].setOutlineColor(sf::Color::White);
    zinStatElements[1].setOutlineThickness(1.0f);
    //Patience plus box
    zinStatElements[2].setPosition(rectStatsBoxX, rectStatsBoxY + 160);
    zinStatElements[2].setSize(sf::Vector2f(20.0f, 20.0f));
    zinStatElements[2].setOutlineColor(sf::Color::White);
    zinStatElements[2].setOutlineThickness(1.0f);
    //Resilience plus box
    zinStatElements[3].setPosition(rectStatsBoxX, rectStatsBoxY + 140);
    zinStatElements[3].setSize(sf::Vector2f(20.0f, 20.0f));
    zinStatElements[3].setOutlineColor(sf::Color::White);
    zinStatElements[3].setOutlineThickness(1.0f);
    //Plus sign text for level up
    zinTextElements[0].setFont(font);
    zinTextElements[0].setCharacterSize(24);
    zinTextElements[0].setPosition(rectStatsBoxX + 3, rectStatsBoxY + 94);
    zinTextElements[0].setString("+");
    //plus sign text for resolve
    zinTextElements[1].setFont(font);
    zinTextElements[1].setCharacterSize(24);
    zinTextElements[1].setPosition(rectStatsBoxX + 3, rectStatsBoxY + 174);
    zinTextElements[1].setString("+");
    //plus sign text for patience
    zinTextElements[2].setFont(font);
    zinTextElements[2].setCharacterSize(24);
    zinTextElements[2].setPosition(rectStatsBoxX + 3, rectStatsBoxY + 154);
    zinTextElements[2].setString("+");
    //plus sign text for resilience
    zinTextElements[3].setFont(font);
    zinTextElements[3].setCharacterSize(24);
    zinTextElements[3].setPosition(rectStatsBoxX + 3, rectStatsBoxY + 133);
    zinTextElements[3].setString("+");
    //Title next to level box
    zinTextElements[4].setFont(font);
    zinTextElements[4].setCharacterSize(14);
    zinTextElements[4].setPosition(rectStatsBoxX + 25, rectStatsBoxY + 100);
    zinTextElements[4].setFillColor(sf::Color::White);
    //Title next to resolve box
    zinTextElements[5].setFont(font);
    zinTextElements[5].setCharacterSize(14);
    zinTextElements[5].setPosition(rectStatsBoxX + 25, rectStatsBoxY + 180);
    zinTextElements[5].setFillColor(sf::Color::White);
    //Title next to patience box
    zinTextElements[6].setFont(font);
    zinTextElements[6].setCharacterSize(14);
    zinTextElements[6].setPosition(rectStatsBoxX + 25, rectStatsBoxY + 160);
    zinTextElements[6].setFillColor(sf::Color::White);
    //Title next to resilience box
    zinTextElements[7].setFont(font);
    zinTextElements[7].setCharacterSize(14);
    zinTextElements[7].setPosition(rectStatsBoxX + 25, rectStatsBoxY + 140);
    zinTextElements[7].setFillColor(sf::Color::White);
    //Side Menu Player Stats Menu Rect Text
    zinTextElements[8].setFont(font);
    zinTextElements[8].setCharacterSize(16);
    zinTextElements[8].setPosition(rectStatsBoxX + 205, rectStatsBoxY);
    zinTextElements[8].setString("P\nL\nA\nY\nE\nR");
    zinTextElements[8].setFillColor(sf::Color::White);
    //Side Menu Zin Stats Menu Rect Text
    zinTextElements[9].setFont(font);
    zinTextElements[9].setCharacterSize(16);
    zinTextElements[9].setPosition(rectStatsBoxX + 205, rectStatsBoxY + 120);
    zinTextElements[9].setString("\nZ\nI\nN");
    zinTextElements[9].setFillColor(sf::Color::White);
    //Hp text
    zinTextElements[10].setFont(font);
    zinTextElements[10].setCharacterSize(16);
    zinTextElements[10].setFillColor(sf::Color(sf::Color::White));
    zinTextElements[10].setPosition(rectStatsBoxX, rectStatsBoxY);
}

void Assets::drawText()
{
    //Draw Font
    font.loadFromFile("C:/Users/Cole/source/repos/SFML Console Chat/SFML Console Chat/Assets/Fonts/tickerbit font/Tickerbit-regular.otf");
    //Draw Font and Output Text
    text.setFont(font);
    text.setCharacterSize(16);
    text.setFillColor(sf::Color(sf::Color::White));
    text.setPosition(0.0f, 825.0f);
    //Draw Input Text
    playerText.setFont(font);
    playerText.setFillColor(sf::Color(sf::Color::White));
    playerText.setPosition(0.0f, 970.0f);
    //Draw Location Text
    locationText.setFont(font);
    locationText.setCharacterSize(18);
    locationText.setFillColor(sf::Color(sf::Color::White));
    locationText.setPosition(275.0f, 10.0f);
    //Menu Bar Text
    textElements[2].setFont(font);
    textElements[2].setCharacterSize(16);
    textElements[2].setPosition(1.0f, 797.0f);
    textElements[2].setString("Map");
    textElements[0].setFont(font);
    textElements[0].setCharacterSize(16);
    textElements[0].setPosition(105.0f, 797.0f);
    textElements[0].setString("Stats");
    textElements[1].setFont(font);
    textElements[1].setCharacterSize(16);
    textElements[1].setPosition(210.0f, 797.0f);
    textElements[1].setString("Inventory");
}

void Assets::drawMainMenu()
{
    //Set all screen elements attributes
    for (int i = 0; i < menuScreenElements.size(); i++) {
        menuScreenElementsText[i].setFont(font);
        menuScreenElementsText[i].setCharacterSize(18);
        menuScreenElements[i].setSize(sf::Vector2f(150.0f, 25.0f));
        menuScreenElements[i].setOutlineColor(sf::Color::White);
        menuScreenElements[i].setOutlineThickness(1.0f);
    }

    //Set Text Elements Names
    menuScreenElementsText[0].setString("Boot");
    menuScreenElementsText[1].setString("Load");
    menuScreenElementsText[2].setString("Quit");
    menuScreenElementsText[3].setString("Play Intro");
    menuScreenElementsText[4].setString("Skip Intro");

    menuScreenElementsText[5].setString("Save Game");

    if (!this->introFinished) {
        font.loadFromFile("C:/Users/Cole/source/repos/SFML Console Chat/SFML Console Chat/Assets/Fonts/tickerbit font/Tickerbit-regular.otf");
        //Draw Main Menu
        menuScreen.setSize(sf::Vector2f(1920.0f, 1080.0f));
        menuScreen.setFillColor(sf::Color::Black);

        //Choose which elements are currently visible on the screen for choosing whether to skip intro or not
        if (this->bootClicked == false) {
            menuScreenElements[3].setPosition(10000.0f, 10000.0f);
            menuScreenElements[4].setPosition(10000.0f, 10000.0f);
            menuScreenElements[5].setPosition(10000.0f, 10000.0f);
            menuScreenElementsText[3].setPosition(10000.0f, 10000.0f);
            menuScreenElementsText[4].setPosition(10000.0f, 10000.0f);
            menuScreenElementsText[5].setPosition(10000.0f, 10000.0f);

            menuScreenElements[0].setPosition(10.0f, 100.0f);
            menuScreenElements[1].setPosition(10.0f, 125.0f);
            menuScreenElements[2].setPosition(10.0f, 150.0f);
            menuScreenElementsText[0].setPosition(10.0f, 100.0f);
            menuScreenElementsText[1].setPosition(10.0f, 125.0f);
            menuScreenElementsText[2].setPosition(10.0f, 150.0f);
        }
        else if (this->bootClicked == true) {
            //Hide menu buttons
            menuScreenElements[0].setPosition(10.0f, 10000.0f);
            menuScreenElements[1].setPosition(10.0f, 10000.0f);
            menuScreenElements[2].setPosition(10.0f, 10000.0f);
            menuScreenElementsText[0].setPosition(10.0f, 10000.0f);
            menuScreenElementsText[1].setPosition(10.0f, 10000.0f);
            menuScreenElementsText[2].setPosition(10.0f, 10000.0f);
            //Show skip or no skip intro
            menuScreenElements[3].setPosition(10.0f, 100.0f);
            menuScreenElements[4].setPosition(10.0f, 125.0f);
            menuScreenElementsText[3].setPosition(10.0f, 100.0f);
            menuScreenElementsText[4].setPosition(10.0f, 125.0f);
        }
    }
    else if (this->introFinished) {
        if (this->settingsShown) {
            //Hide intro options
            menuScreenElements[3].setPosition(10000.0f, 10000.0f);
            menuScreenElements[4].setPosition(10000.0f, 10000.0f);
            menuScreenElementsText[3].setPosition(10000.0f, 10000.0f);
            menuScreenElementsText[4].setPosition(10000.0f, 10000.0f);
            //Show setting options
            menuScreenElements[1].setPosition(10.0f, 125.0f);
            menuScreenElements[2].setPosition(10.0f, 150.0f);
            menuScreenElements[5].setPosition(10.0f, 175.0f);
            menuScreenElementsText[1].setPosition(10.0f, 125.0f);
            menuScreenElementsText[2].setPosition(10.0f, 150.0f);
            menuScreenElementsText[5].setPosition(10.0f, 175.0f);
        }
        else if (!this->settingsShown) {
            //Hide all elements
            menuScreenElements[1].setPosition(10000.0f, 10000.0f);
            menuScreenElements[2].setPosition(10000.0f, 10000.0f);
            menuScreenElements[5].setPosition(10000.0f, 10000.0f);
            menuScreenElementsText[1].setPosition(10000.0f, 10000.0f);
            menuScreenElementsText[2].setPosition(10000.0f, 10000.0f);
            menuScreenElementsText[5].setPosition(10000.0f, 10000.0f);
        }
    }
}

void Assets::drawDeathAssets()
{
    font.loadFromFile("C:/Users/Cole/source/repos/SFML Console Chat/SFML Console Chat/Assets/Fonts/tickerbit font/Tickerbit-regular.otf");

    //Draw Load and Quit Buttons
    menuScreenElements[1].setPosition(10.0f, 125.0f);
    menuScreenElements[2].setPosition(10.0f, 150.0f);

    menuScreenElements[1].setSize(sf::Vector2f(100.0f, 25.0f));
    menuScreenElements[1].setOutlineColor(sf::Color::White);
    menuScreenElements[1].setOutlineThickness(1.0f);
    menuScreenElements[2].setSize(sf::Vector2f(100.0f, 25.0f));
    menuScreenElements[2].setOutlineColor(sf::Color::White);
    menuScreenElements[2].setOutlineThickness(1.0f);
    //Draw Load and Quit Text
    deathText.setFont(font);
    deathText.setCharacterSize(48);
    deathText.setString("Perished...");
    deathText.setPosition(25.0f, 25.0f);

    menuScreenElementsText[1].setFont(font);
    menuScreenElementsText[1].setCharacterSize(18);
    menuScreenElementsText[1].setString("Load");
    menuScreenElementsText[2].setFont(font);
    menuScreenElementsText[2].setCharacterSize(18);
    menuScreenElementsText[2].setString("Quit");
    menuScreenElementsText[1].setPosition(10.0f, 125.0f);
    menuScreenElementsText[2].setPosition(10.0f, 150.0f);
}

void Assets::drawAnswerBoxes()
{
    switch (this->showAnsBoxesCounter) {
    case -1:
        for (int i = 0; i < answerBox.size(); i++) {
            answerBox[i].setPosition(10000, 10000);
            answerBoxText[i].setPosition(10000, 10000);
        }
        break;
    case 0:
        for (int i = 0; i < answerBox.size(); i++) {
            answerBox[i].setSize(sf::Vector2f(1920.0f,127.5f));
            answerBox[i].setOutlineColor(sf::Color::White);
            answerBox[i].setOutlineThickness(1.0f);
            answerBoxText[i].setFont(font);
            answerBoxText[i].setCharacterSize(16);
        }
        answerBox[0].setPosition(0.0f, 825.0f);
        answerBox[1].setPosition(0.0f, 952.5f);

        answerBoxText[0].setPosition(0.0f, 825.0f);
        answerBoxText[1].setPosition(0.0f, 952.0f);
        break;
    }
}

void Assets::drawTipBox()
{
    tipBox.setFillColor(sf::Color::Black);
    tipBox.setSize(sf::Vector2f(380.0f, 150.0f));
    tipBox.setOutlineColor(sf::Color::White);
    tipBox.setOutlineThickness(1.0f);

    tipBoxText.setFont(font);
    tipBoxText.setCharacterSize(14);

    switch (this->tipBoxCounter) {
    case -1:
        tipBox.setPosition(10000, 10000);
        tipBoxText.setPosition(10000, 10000);
        break;
    case 0:
        tipBox.setPosition(1500, 650);
        tipBoxText.setPosition(1500, 650);
        break;
    }
}

void Assets::drawEntityViewer()
{
    entityBoxText.setFont(font);
    entityBoxText.setCharacterSize(14);
    entityBoxText.setString("Close Vision Viewer");
    entityBoxText.setPosition(1500, 75);

    entityBoxHeader.setFillColor(sf::Color::Black);
    entityBoxHeader.setSize(sf::Vector2f(250.0f, 25.0f));
    entityBoxHeader.setOutlineColor(sf::Color::White);
    entityBoxHeader.setOutlineThickness(1.0f);
    entityBoxHeader.setPosition(1500, 75);

    entityBox.setFillColor(sf::Color::Black);
    entityBox.setSize(sf::Vector2f(250.0f, 250.0f));
    entityBox.setOutlineColor(sf::Color::White);
    entityBox.setOutlineThickness(1.0f);
    //Select which sprite to use in the entity viewer
    switch (this->entityViewerCounter) {
    case -1:
        entitySprite.setTexture(blankEntity);
        break;
    case 0:
        entitySprite.setTexture(siwardEntityTexture);
        break;
    case 1:
        entitySprite.setTexture(decayEntity);
        break;
    case 2:
        entitySprite.setTexture(treeEntity);
        break;
    case 3:
        entitySprite.setTexture(spadeEntityForest);
        break;
    case 4:
        entitySprite.setTexture(spadeEntityCastle);
        break;
    case 5:
        entitySprite.setTexture(hostileTreeEntity);
        break;
    case 6:
        entitySprite.setTexture(obeliskEntity);
        break;
    case 7:
        entitySprite.setTexture(lostNunEntity);
        break;
    }
    //Select whether or not the sprite is visible
    switch (this->spriteViewerCounter) {
    case -1:
        entityBox.setPosition(10000, 10000);
        entitySprite.setPosition(10000, 10000);
        entityBoxText.setPosition(10000, 10000);
        entityBoxHeader.setPosition(10000, 10000);
        break;
    case 0:
        entityBox.setPosition(1500, 100);
        entitySprite.setPosition(1500, 100);
        entityBoxText.setPosition(1500, 75);
        entityBoxHeader.setPosition(1500, 75);
        break;
    }

    entitySprite.setScale(0.244, 0.244f);
}

//Drawing Map Segments
void Assets::drawMap()
{
    rectMap.setFillColor(sf::Color::Black);
    rectMap.setPosition(rectMapX, rectMapY);
    rectMap.setSize(sf::Vector2f(400.0f, 400.0f));
    rectMap.setOutlineColor(sf::Color::White);
    rectMap.setOutlineThickness(1.0f);

    //Switch map areas via map selectors
    switch (this->areaUnlocked) {
    case 0:
        //Load no buttons
        break;
    case 1:
        for (int i = 0; i < buttonViewMap.size(); i++) {
            buttonViewMap[i].setSize(sf::Vector2f(200.0f, 25.0f));
            buttonViewMap[i].setOutlineColor(sf::Color::White);
            buttonViewMap[i].setOutlineThickness(1.0f);
        }
        //Set button map selector positions
        buttonViewMap[0].setPosition(rectMapX, rectMapY - 25);
        buttonViewMap[1].setPosition(rectMapX + 200, rectMapY - 25);
        buttonViewMap[2].setPosition(rectMapX + 20000, rectMapY - 25);
        for (int i = 0; i < buttonViewMapText.size(); i++) {
            buttonViewMapText[i].setFont(font);
            buttonViewMapText[i].setCharacterSize(12);
        }
        //Castle Map Button Selector Text
        buttonViewMapText[0].setPosition(rectMapX, rectMapY - 25);
        buttonViewMapText[0].setString("Forest Plane");

        buttonViewMapText[1].setPosition(rectMapX + 200, rectMapY - 25);
        buttonViewMapText[1].setString("Castle Plane");
        break;
    case 2:
        for (int i = 0; i < buttonViewMap.size(); i++) {
            buttonViewMap[i].setSize(sf::Vector2f(133.3f, 25.0f));
            buttonViewMap[i].setOutlineColor(sf::Color::White);
            buttonViewMap[i].setOutlineThickness(1.0f);
        }
        //Set button map selector positions
        buttonViewMap[0].setPosition(rectMapX, rectMapY - 25);
        buttonViewMap[1].setPosition(rectMapX + 133.0, rectMapY - 25);
        buttonViewMap[2].setPosition(rectMapX + 266.0, rectMapY - 25);
        for (int i = 0; i < buttonViewMapText.size(); i++) {
            buttonViewMapText[i].setFont(font);
            buttonViewMapText[i].setCharacterSize(14);
        }
        //Castle Map Button Selector Text
        buttonViewMapText[0].setPosition(rectMapX, rectMapY - 25);
        buttonViewMapText[0].setString("Forest Plane");

        buttonViewMapText[1].setPosition(rectMapX + 133.0, rectMapY - 25);
        buttonViewMapText[1].setString("Castle Plane");

        buttonViewMapText[2].setPosition(rectMapX + 266.0, rectMapY - 25);
        buttonViewMapText[2].setString("Decay Plane");
        break;
    }

    multiArrow.setPosition(rectMapX + 340, rectMapY + 10);
    multiArrow.setScale(0.06, 0.06);
    switch (mapCounter) {
    case 0:
        this->drawForestMapButtons();
        break;
    case 1:
        this->drawCastleMapButtons();
        break;
    case 2:
        this->drawDecayMapButtons();
        break;
    }
}

void Assets::drawForestMapButtons()
{
    if (this->initForestMapTexture == false) {
        //Hide Castle Textures
        spriteMapView.setPosition(10000, 10000);
        for (int i = 0; i < mapCastleElements.size(); i++) {
            mapCastleElements[i].setPosition(10000, 10000);
            mapCastleElementsText[i].setPosition(10000, 10000);
        }
        //Hide Decay Textures
        decayMapView.setPosition(10000, 10000);
        for (int i = 0; i < mapDecayElements.size(); i++) {
            mapDecayElements[i].setPosition(10000, 10000);
            mapDecayElementsText[i].setPosition(10000, 10000);
        }

        //Load Movable Arrow
        multiArrowTexture.loadFromFile("C:/Users/Cole/source/repos/SFML Console Chat/SFML Console Chat/Assets/Sprites/multiarrow.png");
        multiArrow.setTexture(multiArrowTexture);

        //Load Map View
        forestMapTexture.loadFromFile("C:/Users/Cole/source/repos/SFML Console Chat/SFML Console Chat/Assets/Sprites/forest/forestmap.jpeg");
        forestMapView.setTexture(forestMapTexture);
        forestMapView.setPosition(rectMapX, rectMapY);
        forestMapView.setScale(0.39f, 0.39f);

        //Load Buttons
        for (int i = 0; i < mapForestElements.size(); i++) {
            mapForestElements[i].setTexture(buttonTexture);
            mapForestElements[i].setScale(0.5f, 0.5f);
            mapForestElementsText[i].setFont(font);
            mapForestElementsText[i].setFillColor(sf::Color::White);
            mapForestElementsText[i].setCharacterSize(12);
        }

        //Forest areas unlocked
        switch (this->forestAreaUnlocked) {
        case 0:
            mapForestElements[0].setPosition(rectMapX + 145, rectMapY + 25);
            mapForestElementsText[0].setPosition(rectMapX + 145, rectMapY + 10);
            mapForestElementsText[0].setString("Bonfire");
            //Hidden
            mapForestElements[1].setPosition(rectMapX + 10000, rectMapY + 10000);
            mapForestElements[2].setPosition(rectMapX + 10000, rectMapY + 10000);
            mapForestElements[3].setPosition(rectMapX + 10000, rectMapY + 10000);
            mapForestElements[4].setPosition(rectMapX + 10000, rectMapY + 10000);
            break;
        case 1:
            mapForestElements[0].setPosition(rectMapX + 145, rectMapY + 25);
            mapForestElementsText[0].setPosition(rectMapX + 145, rectMapY + 10);
            mapForestElementsText[0].setString("Bonfire");
            mapForestElements[1].setPosition(rectMapX + 34, rectMapY + 20);
            mapForestElementsText[1].setPosition(rectMapX + 34, rectMapY + 5);
            mapForestElementsText[1].setString("Forest Entrance");
            //Hidden
            mapForestElements[2].setPosition(rectMapX + 10000, rectMapY + 10000);
            mapForestElements[3].setPosition(rectMapX + 10000, rectMapY + 10000);
            mapForestElements[4].setPosition(rectMapX + 10000, rectMapY + 10000);
            break;
        case 2:
            mapForestElements[0].setPosition(rectMapX + 145, rectMapY + 25);
            mapForestElementsText[0].setPosition(rectMapX + 145, rectMapY + 10);
            mapForestElementsText[0].setString("Bonfire");
            mapForestElements[1].setPosition(rectMapX + 34, rectMapY + 20);
            mapForestElementsText[1].setPosition(rectMapX + 34, rectMapY + 5);
            mapForestElementsText[1].setString("Forest Entrance");
            mapForestElements[2].setPosition(rectMapX + 75, rectMapY + 240);
            mapForestElementsText[2].setPosition(rectMapX + 75, rectMapY + 225);
            mapForestElementsText[2].setString("Forest Depths");
            //Hidden
            mapForestElements[3].setPosition(rectMapX + 10000, rectMapY + 10000);
            mapForestElements[4].setPosition(rectMapX + 10000, rectMapY + 10000);
            break;
        case 3:
            mapForestElements[0].setPosition(rectMapX + 145, rectMapY + 25);
            mapForestElementsText[0].setPosition(rectMapX + 145, rectMapY + 10);
            mapForestElementsText[0].setString("Bonfire");
            mapForestElements[1].setPosition(rectMapX + 34, rectMapY + 20);
            mapForestElementsText[1].setPosition(rectMapX + 34, rectMapY + 5);
            mapForestElementsText[1].setString("Forest Entrance");
            mapForestElements[2].setPosition(rectMapX + 75, rectMapY + 240);
            mapForestElementsText[2].setPosition(rectMapX + 75, rectMapY + 225);
            mapForestElementsText[2].setString("Forest Depths");
            mapForestElements[3].setPosition(rectMapX + 175, rectMapY + 200);
            mapForestElementsText[3].setPosition(rectMapX + 175, rectMapY + 185);
            mapForestElementsText[3].setString("Abyssal Forest");
            //Hidden
            mapForestElements[4].setPosition(rectMapX + 10000, rectMapY + 10000);
            break;
        case 4:
            mapForestElements[0].setPosition(rectMapX + 145, rectMapY + 25);
            mapForestElementsText[0].setPosition(rectMapX + 145, rectMapY + 10);
            mapForestElementsText[0].setString("Bonfire");
            mapForestElements[1].setPosition(rectMapX + 34, rectMapY + 20);
            mapForestElementsText[1].setPosition(rectMapX + 34, rectMapY + 5);
            mapForestElementsText[1].setString("Forest Entrance");
            mapForestElements[2].setPosition(rectMapX + 75, rectMapY + 240);
            mapForestElementsText[2].setPosition(rectMapX + 75, rectMapY + 225);
            mapForestElementsText[2].setString("Forest Depths");
            mapForestElements[3].setPosition(rectMapX + 175, rectMapY + 200);
            mapForestElementsText[3].setPosition(rectMapX + 175, rectMapY + 185);
            mapForestElementsText[3].setString("Abyssal Forest");
            mapForestElements[4].setPosition(rectMapX + 240, rectMapY + 320);
            mapForestElementsText[4].setPosition(rectMapX + 240, rectMapY + 305);
            mapForestElementsText[4].setString("Abyssal Depths");
            break;
        }
        this->initForestMapTexture = true;
    }
}

void Assets::drawCastleMapButtons()
{
    if (this->initMapTexture == false) {
        //Load Movable Arrow
        multiArrowTexture.loadFromFile("C:/Users/Cole/source/repos/SFML Console Chat/SFML Console Chat/Assets/Sprites/multiarrow.png");
        multiArrow.setTexture(multiArrowTexture);

        //Hide Forest Textures
        forestMapView.setPosition(10000, 10000);
        for (int i = 0; i < mapForestElements.size(); i++) {
            mapForestElements[i].setPosition(10000, 10000);
            mapForestElementsText[i].setPosition(10000, 10000);
        }
        //Hide Decay Textures
        decayMapView.setPosition(10000, 10000);
        for (int i = 0; i < mapDecayElements.size(); i++) {
            mapDecayElements[i].setPosition(10000, 10000);
            mapDecayElementsText[i].setPosition(10000, 10000);
        }

        //Load Map View
        textureMapView.loadFromFile("C:/Users/Cole/source/repos/SFML Console Chat/SFML Console Chat/Assets/Sprites/mapTexture.jpeg");
        spriteMapView.setTexture(textureMapView);
        spriteMapView.setPosition(rectMapX, rectMapY);
        spriteMapView.setScale(0.38f, 0.38f);

        //Load Castle Buttons
        for (int i = 0; i < mapCastleElements.size(); i++) {
            mapCastleElements[i].setTexture(buttonTexture);
            mapCastleElements[i].setScale(0.5f, 0.5f);
            mapCastleElementsText[i].setFont(font);
            mapCastleElementsText[i].setCharacterSize(12);
            mapCastleElementsText[i].setFillColor(sf::Color::White);
        }

        switch (this->castleAreaUnlocked) {
        case 0:
            mapCastleElements[0].setPosition(rectMapX + 27, rectMapY + 322);
            mapCastleElementsText[0].setPosition(rectMapX + 27, rectMapY + 307);
            mapCastleElementsText[0].setString("Bonfire");
            break;
        case 1:
            mapCastleElements[0].setPosition(rectMapX + 27, rectMapY + 322);
            mapCastleElementsText[0].setPosition(rectMapX + 27, rectMapY + 307);
            mapCastleElementsText[0].setString("Bonfire");
            mapCastleElements[1].setPosition(rectMapX + 75, rectMapY + 240);
            mapCastleElementsText[1].setPosition(rectMapX + 75, rectMapY + 225);
            mapCastleElementsText[1].setString("Halls");
            break;
        case 2:
            mapCastleElements[0].setPosition(rectMapX + 27, rectMapY + 322);
            mapCastleElementsText[0].setPosition(rectMapX + 27, rectMapY + 307);
            mapCastleElementsText[0].setString("Bonfire");
            mapCastleElements[1].setPosition(rectMapX + 75, rectMapY + 240);
            mapCastleElementsText[1].setPosition(rectMapX + 75, rectMapY + 225);
            mapCastleElementsText[1].setString("Halls");
            mapCastleElements[2].setPosition(rectMapX + 34, rectMapY + 20);
            mapCastleElementsText[2].setPosition(rectMapX + 34, rectMapY + 5);
            mapCastleElementsText[2].setString("Depths");
            break;
        case 3:
            mapCastleElements[0].setPosition(rectMapX + 27, rectMapY + 322);
            mapCastleElementsText[0].setPosition(rectMapX + 27, rectMapY + 307);
            mapCastleElementsText[0].setString("Bonfire");
            mapCastleElements[1].setPosition(rectMapX + 75, rectMapY + 240);
            mapCastleElementsText[1].setPosition(rectMapX + 75, rectMapY + 225);
            mapCastleElementsText[1].setString("Halls");
            mapCastleElements[2].setPosition(rectMapX + 34, rectMapY + 20);
            mapCastleElementsText[2].setPosition(rectMapX + 34, rectMapY + 5);
            mapCastleElementsText[2].setString("Depths");
            mapCastleElements[3].setPosition(rectMapX + 200, rectMapY + 20);
            mapCastleElementsText[3].setPosition(rectMapX + 200, rectMapY + 5);
            mapCastleElementsText[3].setString("Chambers");
            break;
        case 4:
            mapCastleElements[0].setPosition(rectMapX + 27, rectMapY + 322);
            mapCastleElementsText[0].setPosition(rectMapX + 27, rectMapY + 307);
            mapCastleElementsText[0].setString("Bonfire");
            mapCastleElements[1].setPosition(rectMapX + 75, rectMapY + 240);
            mapCastleElementsText[1].setPosition(rectMapX + 75, rectMapY + 225);
            mapCastleElementsText[1].setString("Halls");
            mapCastleElements[2].setPosition(rectMapX + 34, rectMapY + 20);
            mapCastleElementsText[2].setPosition(rectMapX + 34, rectMapY + 5);
            mapCastleElementsText[2].setString("Depths");
            mapCastleElements[3].setPosition(rectMapX + 200, rectMapY + 20);
            mapCastleElementsText[3].setPosition(rectMapX + 200, rectMapY + 5);
            mapCastleElementsText[3].setString("Chambers");
            mapCastleElements[4].setPosition(rectMapX + 305, rectMapY + 210);
            mapCastleElementsText[4].setPosition(rectMapX + 305, rectMapY + 195);
            mapCastleElementsText[4].setString("Labyrinth");
            break;
        }
        this->initMapTexture = true;
    }
}

void Assets::drawDecayMapButtons()
{
    if (this->initDecayMapTexture == false) {
        //Load Movable Arrow
        multiArrowTexture.loadFromFile("C:/Users/Cole/source/repos/SFML Console Chat/SFML Console Chat/Assets/Sprites/multiarrow.png");
        multiArrow.setTexture(multiArrowTexture);

        //Hide Forest Textures
        forestMapView.setPosition(10000, 10000);
        for (int i = 0; i < mapForestElements.size(); i++) {
            mapForestElements[i].setPosition(10000, 10000);
            mapForestElementsText[i].setPosition(10000, 10000);
        }
        //Hide Castle Textures
        spriteMapView.setPosition(10000, 10000);
        for (int i = 0; i < mapCastleElements.size(); i++) {
            mapCastleElements[i].setPosition(10000, 10000);
            mapCastleElementsText[i].setPosition(10000, 10000);
        }

        //Load Map View
        decayTexture.loadFromFile("C:/Users/Cole/source/repos/SFML Console Chat/SFML Console Chat/Assets/Sprites/Decay/decayMap.jpeg");
        decayMapView.setTexture(decayTexture);
        decayMapView.setPosition(rectMapX, rectMapY);
        decayMapView.setScale(0.39f, 0.39f);

        //Load Decay buttons
        for (int i = 0; i < mapDecayElements.size(); i++) {
            mapDecayElements[i].setTexture(buttonTexture);
            mapDecayElements[i].setScale(0.5f, 0.5f);
            mapDecayElementsText[i].setFont(font);
            mapDecayElementsText[i].setCharacterSize(12);
            mapDecayElementsText[i].setFillColor(sf::Color::White);
        }

        switch (this->decayAreaUnlocked) {
        case 0:
            mapDecayElements[0].setPosition(rectMapX + 220, rectMapY + 215);
            mapDecayElementsText[0].setPosition(rectMapX + 220, rectMapY + 200);
            mapDecayElementsText[0].setString("Bonfire");
            break;
        case 1:
            mapDecayElements[0].setPosition(rectMapX + 220, rectMapY + 215);
            mapDecayElementsText[0].setPosition(rectMapX + 220, rectMapY + 200);
            mapDecayElementsText[0].setString("Bonfire");
            mapDecayElements[1].setPosition(rectMapX + 245, rectMapY + 110);
            mapDecayElementsText[1].setPosition(rectMapX + 245, rectMapY + 95);
            mapDecayElementsText[1].setString("Crimson Chasms");
            break;
        case 2:
            mapDecayElements[0].setPosition(rectMapX + 220, rectMapY + 215);
            mapDecayElementsText[0].setPosition(rectMapX + 220, rectMapY + 200);
            mapDecayElementsText[0].setString("Bonfire");
            mapDecayElements[1].setPosition(rectMapX + 245, rectMapY + 110);
            mapDecayElementsText[1].setPosition(rectMapX + 245, rectMapY + 95);
            mapDecayElementsText[1].setString("Crimson Chasms");
            mapDecayElements[2].setPosition(rectMapX + 200, rectMapY + 60);
            mapDecayElementsText[2].setPosition(rectMapX + 200, rectMapY + 45);
            mapDecayElementsText[2].setString("Decay Ocean");
            break;
        case 3:
            mapDecayElements[0].setPosition(rectMapX + 220, rectMapY + 215);
            mapDecayElementsText[0].setPosition(rectMapX + 220, rectMapY + 200);
            mapDecayElementsText[0].setString("Bonfire");
            mapDecayElements[1].setPosition(rectMapX + 245, rectMapY + 110);
            mapDecayElementsText[1].setPosition(rectMapX + 245, rectMapY + 95);
            mapDecayElementsText[1].setString("Crimson Chasms");
            mapDecayElements[2].setPosition(rectMapX + 200, rectMapY + 60);
            mapDecayElementsText[2].setPosition(rectMapX + 200, rectMapY + 45);
            mapDecayElementsText[2].setString("Decay Ocean");
            mapDecayElements[3].setPosition(rectMapX + 150, rectMapY + 40);
            mapDecayElementsText[3].setPosition(rectMapX + 150, rectMapY + 25);
            mapDecayElementsText[3].setString("Decay Forest");
            break;
        case 4:
            mapDecayElements[0].setPosition(rectMapX + 220, rectMapY + 215);
            mapDecayElementsText[0].setPosition(rectMapX + 220, rectMapY + 200);
            mapDecayElementsText[0].setString("Bonfire");
            mapDecayElements[1].setPosition(rectMapX + 245, rectMapY + 110);
            mapDecayElementsText[1].setPosition(rectMapX + 245, rectMapY + 95);
            mapDecayElementsText[1].setString("Crimson Chasms");
            mapDecayElements[2].setPosition(rectMapX + 200, rectMapY + 60);
            mapDecayElementsText[2].setPosition(rectMapX + 200, rectMapY + 45);
            mapDecayElementsText[2].setString("Decay Ocean");
            mapDecayElements[3].setPosition(rectMapX + 150, rectMapY + 40);
            mapDecayElementsText[3].setPosition(rectMapX + 150, rectMapY + 25);
            mapDecayElementsText[3].setString("Decay Forest");
            mapDecayElements[4].setPosition(rectMapX + 25, rectMapY + 50);
            mapDecayElementsText[4].setPosition(rectMapX + 25, rectMapY + 35);
            mapDecayElementsText[4].setString("Giants Plateau");
            break;
        } 
        this->initDecayMapTexture = true;
    }
}

//Detection Functions
void Assets::bonfireHealDetection()
{
    switch (this->mapCounter) {
    case 0:
        //Forest Bonfire Heal Detection
        bonfireHealDetectionRect.setFillColor(sf::Color::Transparent);
        bonfireHealDetectionRect.setSize(sf::Vector2f(300, 250));
        bonfireHealDetectionRect.setPosition(650, 450);

        bonfireHealDetectionText.setFont(font);
        bonfireHealDetectionText.setCharacterSize(18);
        bonfireHealDetectionText.setFillColor(sf::Color::White);
        break;
    case 1:
        //Castle Bonfire Heal Detection
        bonfireHealDetectionRect.setFillColor(sf::Color::Transparent);
        bonfireHealDetectionRect.setSize(sf::Vector2f(250, 250));
        bonfireHealDetectionRect.setPosition(650, 500);

        bonfireHealDetectionText.setFont(font);
        bonfireHealDetectionText.setCharacterSize(18);
        bonfireHealDetectionText.setFillColor(sf::Color::White);
        break;
    case 2:
        //Decay Bonfire Heal Detection
        bonfireHealDetectionRect.setFillColor(sf::Color::Transparent);
        bonfireHealDetectionRect.setSize(sf::Vector2f(200, 200));
        bonfireHealDetectionRect.setPosition(700, 250);

        bonfireHealDetectionText.setFont(font);
        bonfireHealDetectionText.setCharacterSize(18);
        bonfireHealDetectionText.setFillColor(sf::Color::White);
        break;
    }
}

void Assets::bonfireSmithDetection()
{
    switch (this->mapCounter) {
    case 0:
        //Forest Bonfire Smith Detection
        bonfireSmithDetectionRect.setFillColor(sf::Color::Transparent);
        bonfireSmithDetectionRect.setSize(sf::Vector2f(150, 150));
        bonfireSmithDetectionRect.setPosition(975, 450);

        bonfireSmithDetectionText.setFont(font);
        bonfireSmithDetectionText.setCharacterSize(18);
        bonfireSmithDetectionText.setFillColor(sf::Color::White);
        break;
    case 1:
        //Castle Bonfire Smith Detection
        bonfireSmithDetectionRect.setFillColor(sf::Color::Transparent);
        bonfireSmithDetectionRect.setSize(sf::Vector2f(600, 60));
        bonfireSmithDetectionRect.setPosition(450, 755);

        bonfireSmithDetectionText.setFont(font);
        bonfireSmithDetectionText.setCharacterSize(18);
        bonfireSmithDetectionText.setFillColor(sf::Color::White);
        break;
    case 2:
        //Decay Bonfire Smith Detection
        bonfireSmithDetectionRect.setFillColor(sf::Color::Transparent);
        bonfireSmithDetectionRect.setSize(sf::Vector2f(100, 100));
        bonfireSmithDetectionRect.setPosition(1350, 200);

        bonfireSmithDetectionText.setFont(font);
        bonfireSmithDetectionText.setCharacterSize(18);
        bonfireSmithDetectionText.setFillColor(sf::Color::White);
        break;
    }
}

//Draw Sprite Boxes
void Assets::drawSpriteBoxes()
{
    for (int i = 0; i < spriteRect.size(); i++) {
        spriteRect[i].setFillColor(sf::Color::Black);
        spriteRect[i].setSize(sf::Vector2f(153.0f, 153.0f));
        spriteRect[i].setOutlineColor(sf::Color::White);
        spriteRect[i].setOutlineThickness(2.0f);
        spriteText[i].setFont(font);
        spriteText[i].setCharacterSize(18);
        spriteText[i].setFillColor(sf::Color::White);
    }

    //Set Text Rect Names
    textPlayer.setString(playerName);
    textZin.setString("Zin");
    textSpade.setString("Spade");
    textSiward.setString("Siward");
}

//Sprite Functions
void Assets::playerSprite()
{
    //Initialize Player Sprite
    if (this->playerLoadOnce == true) {
        playerTexture.loadFromFile("C:/Users/Cole/source/repos/SFML Console Chat/SFML Console Chat/Assets/Sprites/player.png");
        spriteElements[4].setPosition(sf::Vector2f(10000.0f, 10000.0f));
        this->playerLoadOnce = false;
    }
    //Pick Player Sprite Emotion
    switch (this->playerCounter) {
    case -1:
        spriteElements[4].setPosition(sf::Vector2f(10000.0f, 10000.0f));
        spriteRect[0].setPosition(10000.0f, 10000.0f);
        spriteText[0].setPosition(10000.0f, 10000.0f);
        break;
    case 0:
        if (this->playerInit == false) {
            playerTexture.loadFromFile("C:/Users/Cole/source/repos/SFML Console Chat/SFML Console Chat/Assets/Sprites/player.png");
            spriteElements[4].setPosition(sf::Vector2f(50.0f, 100.0f));
            spriteRect[0].setPosition(50.0f, 100.0f);
            spriteText[0].setPosition(50.0f, 253.0f);
            this->playerInit = true;
        }
        break;
    }

    //Sprite Options, ect
    playerTexture.setSmooth(true);
    playerTexture.setRepeated(false);
    spriteElements[4].setTexture(playerTexture);
    spriteElements[4].setScale(0.244f, 0.244f);
}

void Assets::spadeSprite()
{
    //Initialize Spade Sprite
    if (this->spadeLoadOnce == true) {
        spadeTexture.loadFromFile("C:/Users/Cole/source/repos/SFML Console Chat/SFML Console Chat/Assets/Sprites/spadePixel.png");
        spriteElements[2].setPosition(sf::Vector2f(10000.0f, 10000.0f));
        this->spadeLoadOnce = false;
    }
    //Pick Spade Sprite Emotion
    switch (this->spadeCounter) {
    case -1:
        spriteElements[2].setPosition(sf::Vector2f(10000.0f, 10000.0f));
        spriteRect[3].setPosition(sf::Vector2f(10000.0f, 10000.0f));
        break;
    case 0:
        if (this->spadeInit == false) {
            spadeTexture.loadFromFile("C:/Users/Cole/source/repos/SFML Console Chat/SFML Console Chat/Assets/Sprites/spadePixel.png");
            spriteElements[2].setPosition(sf::Vector2f(1650.0f, 300.0f));
            spriteRect[3].setPosition(sf::Vector2f(1650.0f, 300.0f));
            this->spadeInit = true;
        }
        break;
    case 1:
        if (this->spadeInit == false) {
            spadeTexture.loadFromFile("C:/Users/Cole/source/repos/SFML Console Chat/SFML Console Chat/Assets/Sprites/spadePixelAngry.png");
            this->spadeInit = true;
        }
        break;
    }
   
    //Sprite Options, ect
    spadeTexture.setSmooth(true);
    spadeTexture.setRepeated(false);
    spriteElements[2].setTexture(spadeTexture);
    spriteElements[2].setScale(0.050f, 0.050f);
}

void Assets::zinSprite()
{
    //Pick Zin Sprite Emotion
    switch (this->zinCounter) {
    case -1:
        spriteElements[3].setPosition(sf::Vector2f(10000.0f, 10000.0f));
        spriteRect[1].setPosition(sf::Vector2f(10000.0f, 10000.0f));
        spriteText[1].setPosition(sf::Vector2f(10000.0f, 10000.0f));
        break;
    case 0:
        spriteElements[3].setTexture(zinTexture);
        spriteElements[3].setPosition(sf::Vector2f(50.0f, 300.0f));
        spriteRect[1].setPosition(sf::Vector2f(50.0f, 300.0f));
        spriteText[1].setPosition(sf::Vector2f(50.0f, 453.0f));
        break;
    case 1:
        spriteElements[3].setTexture(zinTextureHappy);
        spriteElements[3].setPosition(sf::Vector2f(50.0f, 300.0f));
        spriteRect[1].setPosition(sf::Vector2f(50.0f, 300.0f));
        spriteText[1].setPosition(sf::Vector2f(50.0f, 453.0f));
        break;
    case 2:
        spriteElements[3].setTexture(zinTextureConcerned);
        spriteElements[3].setPosition(sf::Vector2f(50.0f, 300.0f));
        spriteRect[1].setPosition(sf::Vector2f(50.0f, 300.0f));
        spriteText[1].setPosition(sf::Vector2f(50.0f, 453.0f));
        break;
    case 3:
        spriteElements[3].setTexture(zinTextureAnnoyed);
        spriteElements[3].setPosition(sf::Vector2f(50.0f, 300.0f));
        spriteRect[1].setPosition(sf::Vector2f(50.0f, 300.0f));
        spriteText[1].setPosition(sf::Vector2f(50.0f, 453.0f));
        break;
    }

    //Sprite Options, ect
    zinTexture.setRepeated(false);
    spriteElements[3].setScale(0.0504f, 0.0504f);
}

void Assets::hostileSprite()
{
    //Initialize Hostile Sprite
    if (this->hostileLoadOnce == true) {
        hostileTextureWalker.loadFromFile("C:/Users/Cole/source/repos/SFML Console Chat/SFML Console Chat/Assets/Sprites/decaywalkersprite.jpeg");
        hostileTextureWolf.loadFromFile("C:/Users/Cole/source/repos/SFML Console Chat/SFML Console Chat/Assets/Sprites/wolfsprite.png");
        hostileTextureKnight.loadFromFile("C:/Users/Cole/source/repos/SFML Console Chat/SFML Console Chat/Assets/Sprites/decayknight.png");
        hostileTextureTree.loadFromFile("C:/Users/Cole/source/repos/SFML Console Chat/SFML Console Chat/Assets/Sprites/hostileTreeSprite.jpeg");
        hostileTextureNun.loadFromFile("C:/Users/Cole/source/repos/SFML Console Chat/SFML Console Chat/Assets/Sprites/lostNunSprite.jpeg");
        spriteElements[5].setPosition(sf::Vector2f(10000.0f, 10000.0f));
        spriteRect[2].setPosition(sf::Vector2f(10000.0f, 10000.0f));
        spriteText[2].setPosition(sf::Vector2f(10000.0f, 10000.0f));
        this->hostileLoadOnce = false;
    }
    //Pick Hostile Sprite
    switch (this->hostileCounter) {
    case -1:
        spriteElements[5].setPosition(sf::Vector2f(10000.0f, 10000.0f));
        break;
    case 0:
        if (this->hostileInit == false) {
            spriteElements[5].setPosition(sf::Vector2f(1650.0f, 300.0f));
            this->hostileInit = true;
        }
        break;
    case 1:
        //Wolf Sprite
        if (this->hostileInit == false) {
            hostileTextureWolf.setRepeated(false);
            spriteElements[5].setTexture(hostileTextureWolf);
            spriteElements[5].setPosition(sf::Vector2f(1650.0f, 300.0f));
            spriteRect[2].setPosition(sf::Vector2f(1650.0f, 300.0f));
            spriteText[2].setPosition(sf::Vector2f(1650.0f, 453.0f));
            spriteElements[5].setScale(0.15f, 0.15f);
            this->hostileInit = true;
        }
        break;
    case 2:
        //Decay Walker Sprite
        if (this->hostileInit == false) {
            hostileTextureWalker.setRepeated(false);
            spriteElements[5].setTexture(hostileTextureWalker);
            spriteElements[5].setPosition(sf::Vector2f(1650.0f, 300.0f));
            spriteRect[2].setPosition(sf::Vector2f(1650.0f, 300.0f));
            spriteText[2].setPosition(sf::Vector2f(1650.0f, 453.0f));
            spriteElements[5].setScale(0.235f, 0.235f);
            this->hostileInit = true;
        }
        break;
    case 3:
        //Decay knight Sprite
        if (this->hostileInit == false) {
            hostileTextureKnight.setRepeated(false);
            spriteElements[5].setTexture(hostileTextureKnight);
            spriteElements[5].setPosition(sf::Vector2f(1650.0f, 300.0f));
            spriteRect[2].setPosition(sf::Vector2f(1650.0f, 300.0f));
            spriteText[2].setPosition(sf::Vector2f(1650.0f, 453.0f));
            spriteElements[5].setScale(0.235f, 0.235f);
            this->hostileInit = true;
        }
        break;
    case 4:
        //Hostile Tree Mimic
        if (this->hostileInit == false) {
            hostileTextureTree.setRepeated(false);
            spriteElements[5].setTexture(hostileTextureTree);
            spriteElements[5].setPosition(sf::Vector2f(1650.0f, 300.0f));
            spriteRect[2].setPosition(sf::Vector2f(1650.0f, 300.0f));
            spriteText[2].setPosition(sf::Vector2f(1650.0f, 453.0f));
            spriteElements[5].setScale(0.318f, 0.318f);
            this->hostileInit = true;
        }
        break;
    case 5:
        //Hostile Nun
        if (this->hostileInit == false) {
            hostileTextureTree.setRepeated(false);
            spriteElements[5].setTexture(hostileTextureNun);
            spriteElements[5].setPosition(sf::Vector2f(1650.0f, 300.0f));
            spriteRect[2].setPosition(sf::Vector2f(1650.0f, 300.0f));
            spriteText[2].setPosition(sf::Vector2f(1650.0f, 453.0f));
            spriteElements[5].setScale(0.15f, 0.15f);
            this->hostileInit = true;
        }
        break;
    }
}

void Assets::siwardSprite()
{
    //Initialize Siward Sprite
    if (this->siwardLoadOnce == true) {
        siwardTexture.loadFromFile("C:/Users/Cole/source/repos/SFML Console Chat/SFML Console Chat/Assets/Sprites/siward.png");
        spriteElements[6].setPosition(sf::Vector2f(10000.0f, 10000.0f));
        this->siwardLoadOnce = false;
    }
    //Pick Siward Sprite Emotion
    switch (this->siwardCounter) {
    case -1:
        spriteElements[6].setPosition(sf::Vector2f(10000.0f, 10000.0f));
        spriteRect[4].setPosition(sf::Vector2f(10000.0f, 10000.0f));
        break;
    case 0:
        if (this->siwardLoadOnce == false) {
            spriteElements[6].setPosition(sf::Vector2f(1650.0f, 300.0f));
            spriteRect[4].setPosition(sf::Vector2f(1650.0f, 300.0f));
            this->siwardLoadOnce = true;
        }
        break;
    }

    //Sprite Options, ect
    siwardTexture.setRepeated(false);
    spriteElements[6].setTexture(siwardTexture);
    spriteElements[6].setScale(0.24f, 0.24f);
}

//Combat Asset Functions
void Assets::initCombatAssets()
{
    if (combatAssets == true) {
        //Set All Objects
        for (int i = 0; i < combatRect.size(); i++) {
            combatRect[i].setSize(sf::Vector2f(100.0f, 25.0f));
            combatRect[i].setOutlineColor(sf::Color::White);
            combatRect[i].setOutlineThickness(1.0f);
            combatRect[i].setPosition(10000, 10000);
            combatText[i].setFont(font);
            combatText[i].setCharacterSize(18);
            combatText[i].setPosition(10000, 10000);
        }
        this->playerCombatAssets();
        this->zinCombatAssets();
    }
    else if (combatAssets == false && bonfireAssets == false && eventAssets == false) {
        //Hide all combat assets
        for (int i = 0; i < spriteRect.size(); i++) {
            spriteRect[i].setPosition(10000, 10000);
            spriteText[i].setPosition(10000, 10000);
            combatRect[i].setPosition(10000, 10000);
            combatText[i].setPosition(10000, 10000);
        }
        playerCounter = -1;
        zinCounter = -1;
        hostileCounter = -1;
    }
}

void Assets::playerCombatAssets()
{
    if (this->playerTurnAssets) {
        switch (this->combatPlayerMoves) {
        case 0:
            //Draw Player Slash Button
            combatRect[0].setPosition(335.0f, 795.0f);
            //Draw Player Slash Text
            combatText[0].setPosition(335.0f, 795.0f);
            combatText[0].setString("Slash");
            break;
        case 1:
            //Draw Player Slash Button
            combatRect[0].setPosition(335.0f, 795.0f);
            //Draw Player Slash Text
            combatText[0].setPosition(335.0f, 795.0f);
            combatText[0].setString("Slash");
            //Draw Player Guard Button
            combatRect[1].setPosition(335.0f, 765.0f);
            //Draw Player Guard Text
            combatText[1].setPosition(335.0f, 765.0f);
            combatText[1].setString("Guard");
            break;
        case 2:
            //Draw Player Slash Button
            combatRect[0].setPosition(335.0f, 795.0f);
            //Draw Player Slash Text
            combatText[0].setPosition(335.0f, 795.0f);
            combatText[0].setString("Slash");
            //Draw Player Guard Button
            combatRect[1].setPosition(335.0f, 765.0f);
            //Draw Player Guard Text
            combatText[1].setPosition(335.0f, 765.0f);
            combatText[1].setString("Guard");
            //Draw Player Decay Button
            combatRect[2].setPosition(335.0f, 735.0f);
            //Draw Player Decay Text
            combatText[2].setPosition(335.0f, 735.0f);
            combatText[2].setString("Decay");
            break;
        }
    }
    else if (!this->playerTurnAssets) {
        combatRect[0].setPosition(10000.0f, 10000.0f);
        combatRect[1].setPosition(10000.0f, 10000.0f);
        combatRect[2].setPosition(10000.0f, 10000.0f);
    }
}

void Assets::zinCombatAssets()
{
    if (this->zinTurnAssets) {
        switch (this->combatZinMoves) {
        case 0:
            //Draw Player Slash Button
            combatRect[3].setPosition(335.0f, 795.0f);
            //Draw Player Slash Text
            combatText[3].setPosition(335.0f, 795.0f);
            combatText[3].setString("Smite");
            break;
        case 1:
            //Draw Player Slash Button
            combatRect[3].setPosition(335.0f, 795.0f);
            //Draw Player Slash Text
            combatText[3].setPosition(335.0f, 795.0f);
            combatText[3].setString("Smite");
            //Draw Player Guard Button
            combatRect[4].setPosition(335.0f, 765.0f);
            //Draw Player Guard Text
            combatText[4].setPosition(335.0f, 765.0f);
            combatText[4].setString("Mend");
            break;
        case 2:
            //Draw Player Slash Button
            combatRect[3].setPosition(335.0f, 795.0f);
            //Draw Player Slash Text
            combatText[3].setPosition(335.0f, 795.0f);
            combatText[3].setString("Smite");
            //Draw Player Guard Button
            combatRect[4].setPosition(335.0f, 765.0f);
            //Draw Player Guard Text
            combatText[4].setPosition(335.0f, 765.0f);
            combatText[4].setString("Mend");
            //Draw Player Decay Button
            combatRect[5].setPosition(335.0f, 735.0f);
            //Draw Player Decay Text
            combatText[5].setPosition(335.0f, 735.0f);
            combatText[5].setString("Vengeance");
            break;
        }
    }
    else if (!this->playerTurnAssets) {
        combatRect[3].setPosition(10000.0f, 10000.0f);
        combatRect[4].setPosition(10000.0f, 10000.0f);
        combatRect[5].setPosition(10000.0f, 10000.0f);
    }
}

//Sound Functions
void Assets::loadSFX()
{
    //Set Volume Levels
    blipmenu.setVolume(60);

   //Click Sound
    soundClick.setBuffer(bufferClick);
    //Load Campfire Sound
    soundCampfire.setBuffer(bufferCampfire);
    //Load Decay Blade Sound
    soundDecay.setBuffer(bufferDecay);
    //Load Vengeance Sound
    soundVengeance.setBuffer(bufferVengeance);
    //Load Smite Sound
    soundSlash.setBuffer(bufferSlash);
    //Load Smite Sound
    soundSmite.setBuffer(bufferSmite);
    //Load Mend Sound
    soundMend.setBuffer(bufferMend);
    //Load Guarded Sound
    soundGuarded.setBuffer(bufferGuarded);
    //Load Guard Sound
    soundGuard.setBuffer(bufferGuard);
    //Load Hover Sound
    soundHover.setBuffer(bufferSoundHover);
    //Load Walk Sound
    soundWalk.setBuffer(bufferWalk);
    //Load Combat Sound Effects
    soundCom.setBuffer(bufferCom);
    //Load Text Sfx
    sound.setBuffer(buffer);
    //Load Button Sfx
    blipsound.setBuffer(blipbuffer);
    blipmenu.setBuffer(blipmenubuffer);
    blipmenu.setVolume(60);
    //Load Anger Sfx
    soundAngry.setBuffer(bufferAngry);
    //Load Combat Start Sfx
    soundCombatStart.setBuffer(bufferCombatStart);
}
