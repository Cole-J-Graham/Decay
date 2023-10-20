#include "Assets.h"

//Constructors & Destructors
Assets::Assets()
{
    this->thomUnlocked = false;
    this->dialogueCounter = 0;
    this->combatCounter = 0;
    this->playerCounter = -1;
    this->zinCounter = -1;
    this->thomCounter = -1;
    this->hostileCounter = -1;
    this->mapCounter = -1;
    this->tipBoxCounter = -1;
    this->showAnsBoxesCounter = -1;

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

    this->startFrame = true;
    this->endFrame = false;

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
    this->thomTurnAssets = false;

    //Combat Move Unlocks
    this->combatPlayerMoves = 2;
    this->combatZinMoves = 2;
    this->combatThomMoves = 1;

    //Strings
    this->playerName = "player";

    //Load game assets
    this->loadSprites();
    this->loadSounds();
}

Assets::~Assets()
{

}

//Load Functions
void Assets::loadSprites()
{
    //Game Resource Textures
    windowIcon.loadFromFile("Assets/Game_Resources/shieldicon.jpeg");
    buttonTexture.loadFromFile("Assets/Game_Resources/buttonsolid.png");
    arrowTextureRight.loadFromFile("Assets/Game_Resources/arrowright.png");
    arrowTextureLeft.loadFromFile("Assets/Game_Resources/arrowleft.png");
}

void Assets::loadSounds()
{
    bufferClick.loadFromFile("Assets/Sounds/click.wav");
    //bufferCampfire.loadFromFile("Assets/Sounds/campfire.wav");
    bufferDecay.loadFromFile("Assets/Sounds/decayblade.wav");
    bufferVengeance.loadFromFile("Assets/Sounds/vengeance.wav");
    bufferSlash.loadFromFile("Assets/Sounds/slash.wav");
    bufferSmite.loadFromFile("Assets/Sounds/smite.wav");
    bufferMend.loadFromFile("Assets/Sounds/mend.wav");
    bufferGuarded.loadFromFile("Assets/Sounds/guarded.wav");
    bufferGuard.loadFromFile("Assets/Sounds/guard.wav");
    bufferSoundHover.loadFromFile("Assets/Sounds/hoversound.wav");
    bufferWalk.loadFromFile("Assets/Sounds/moveRoom.wav");
    bufferCom.loadFromFile("Assets/Sounds/Boss hit 1.wav");
    buffer.loadFromFile("Assets/Sounds/Text 1.wav");
    blipbuffer.loadFromFile("Assets/Sounds/blipSelect.wav");
    blipmenubuffer.loadFromFile("Assets/Sounds/menuclick.wav");
    bufferAngry.loadFromFile("Assets/Sounds/angry.wav");
    bufferCombatStart.loadFromFile("Assets/Sounds/combatstart.wav");
    bufferPlayerGuarded.loadFromFile("Assets/Sounds/playerguarded.wav");
    bufferThomGuard.loadFromFile("Assets/Sounds/thomatkguard.wav");
    bufferEnraged.loadFromFile("Assets/Sounds/enraged.wav");
}

//Draw Fuctions
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
        spriteElements[0].setScale(0.04f, 0.04f);
        //Draw Back Button
        if (this->startFrame == true) {
            spriteElements[1].setPosition(10000.0f, 10000.0f);
        }
        else {
            spriteElements[1].setPosition(445.0f, 765.0f);
        }
        buttonBackTexture.loadFromFile("Assets/Game_Resources/buttonsolid.png");
        spriteElements[1].setTexture(arrowTextureLeft);
        spriteElements[1].setScale(0.04f, 0.04f);
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

void Assets::drawText()
{
    //Draw Font
    font.loadFromFile("Assets/Fonts/tickerbit font/Tickerbit-regular.otf");
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
        font.loadFromFile("Assets/Fonts/tickerbit font/Tickerbit-regular.otf");
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
    font.loadFromFile("Assets/Fonts/tickerbit font/Tickerbit-regular.otf");

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

//Stat && Inventory Functions
void Assets::drawStats()
{
    //Main Rect
    rectStatsBox.setFillColor(sf::Color::Black);
    rectStatsBox.setPosition(rectStatsBoxX, rectStatsBoxY);
    rectStatsBox.setSize(sf::Vector2f(200.0f, 600.0f));
    rectStatsBox.setOutlineColor(sf::Color::White);
    rectStatsBox.setOutlineThickness(1.0f);

    //Player Stat Elements Loop
    for (int i = 0; i < playerStatElements.size(); i++) {
        playerStatElements[i].setOutlineColor(sf::Color::White);
        playerStatElements[i].setOutlineThickness(1.0f);
    }
    //Level up plus Box
    playerStatElements[0].setPosition(rectStatsBoxX, rectStatsBoxY + 100);
    playerStatElements[0].setSize(sf::Vector2f(20.0f, 20.0f));
    //Strength plus box
    playerStatElements[1].setPosition(rectStatsBoxX, rectStatsBoxY + 180);
    playerStatElements[1].setSize(sf::Vector2f(20.0f, 20.0f));
    //Fortitude plus box
    playerStatElements[2].setPosition(rectStatsBoxX, rectStatsBoxY + 160);
    playerStatElements[2].setSize(sf::Vector2f(20.0f, 20.0f));
    //Vitality plus box
    playerStatElements[3].setPosition(rectStatsBoxX, rectStatsBoxY + 140);
    playerStatElements[3].setSize(sf::Vector2f(20.0f, 20.0f));
    //Side Menu Player Stats Menu Rect
    playerStatElements[4].setPosition(rectStatsBoxX + 200, rectStatsBoxY);
    playerStatElements[4].setSize(sf::Vector2f(20.0f, 120.0f));
    //Side Menu Zin Stats Menu Rect
    playerStatElements[5].setPosition(rectStatsBoxX + 200, rectStatsBoxY + 120);
    playerStatElements[5].setSize(sf::Vector2f(20.0f, 100.0f));

    //Plus sign text for level up
    for (int i = 0; i < playerTextPlus.size(); i++) {
        playerTextPlus[i].setFont(font);
    }
    playerTextPlus[0].setPosition(rectStatsBoxX + 3, rectStatsBoxY + 94);
    playerTextPlus[0].setString("+");
    playerTextPlus[0].setCharacterSize(24);
    //plus sign text for strength
    playerTextPlus[1].setPosition(rectStatsBoxX + 3, rectStatsBoxY + 174);
    playerTextPlus[1].setString("+");
    playerTextPlus[1].setCharacterSize(24);
    //plus sign text for fortitude
    playerTextPlus[2].setPosition(rectStatsBoxX + 3, rectStatsBoxY + 154);
    playerTextPlus[2].setString("+");
    playerTextPlus[2].setCharacterSize(24);
    //plus sign text for vitality
    playerTextPlus[3].setPosition(rectStatsBoxX + 3, rectStatsBoxY + 133);
    playerTextPlus[3].setString("+");
    playerTextPlus[3].setCharacterSize(24);
    //Side Menu Player Stats Menu Rect Text
    playerTextPlus[4].setCharacterSize(16);
    playerTextPlus[4].setPosition(rectStatsBoxX + 205, rectStatsBoxY);
    playerTextPlus[4].setString("P\nL\nA\nY\nE\nR");
    //Side Menu Zin Stats Menu Rect Text
    playerTextPlus[5].setCharacterSize(16);
    playerTextPlus[5].setPosition(rectStatsBoxX + 205, rectStatsBoxY + 120);
    playerTextPlus[5].setString("\nZ\nI\nN");

    //Player Text Elements Loop
    for (int i = 0; i < playerTextElements.size(); i++) {
        playerTextElements[i].setFont(font);
        playerTextElements[i].setFillColor(sf::Color::White);
    }
    //Title next to level box
    playerTextElements[0].setCharacterSize(14);
    playerTextElements[0].setPosition(rectStatsBoxX + 25, rectStatsBoxY + 100);
    //Title next to strength box
    playerTextElements[1].setFont(font);
    playerTextElements[1].setCharacterSize(14);
    playerTextElements[1].setPosition(rectStatsBoxX + 25, rectStatsBoxY + 180);
    //Title next to fortitude box
    playerTextElements[2].setFont(font);
    playerTextElements[2].setCharacterSize(14);
    playerTextElements[2].setPosition(rectStatsBoxX + 25, rectStatsBoxY + 160);
    //Title next to vitality box
    playerTextElements[3].setFont(font);
    playerTextElements[3].setCharacterSize(14);
    playerTextElements[3].setPosition(rectStatsBoxX + 25, rectStatsBoxY + 140);
    //Hp text
    playerTextElements[4].setCharacterSize(16);
    playerTextElements[4].setPosition(rectStatsBoxX, rectStatsBoxY);
}

void Assets::drawZinStats()
{
    //Zin Stat Elements Loop
    for (int i = 0; i < zinStatElements.size(); i++) {
        zinStatElements[i].setOutlineColor(sf::Color::White);
        zinStatElements[i].setOutlineThickness(1.0f);
    }
    //Level up plus Box
    zinStatElements[0].setPosition(rectStatsBoxX, rectStatsBoxY + 100);
    zinStatElements[0].setSize(sf::Vector2f(20.0f, 20.0f));
    //Strength plus box
    zinStatElements[1].setPosition(rectStatsBoxX, rectStatsBoxY + 180);
    zinStatElements[1].setSize(sf::Vector2f(20.0f, 20.0f));
    //Fortitude plus box
    zinStatElements[2].setPosition(rectStatsBoxX, rectStatsBoxY + 160);
    zinStatElements[2].setSize(sf::Vector2f(20.0f, 20.0f));
    //Vitality plus box
    zinStatElements[3].setPosition(rectStatsBoxX, rectStatsBoxY + 140);
    zinStatElements[3].setSize(sf::Vector2f(20.0f, 20.0f));
    //Side Menu Zin Stats Menu Rect
    zinStatElements[4].setPosition(rectStatsBoxX + 200, rectStatsBoxY);
    zinStatElements[4].setSize(sf::Vector2f(20.0f, 120.0f));
    //Side Menu Zin Stats Menu Rect
    zinStatElements[5].setPosition(rectStatsBoxX + 200, rectStatsBoxY + 120);
    zinStatElements[5].setSize(sf::Vector2f(20.0f, 100.0f));

    //Plus sign text for level up
    for (int i = 0; i < zinTextPlus.size(); i++) {
        zinTextPlus[i].setFont(font);
    }
    zinTextPlus[0].setPosition(rectStatsBoxX + 3, rectStatsBoxY + 94);
    zinTextPlus[0].setString("+");
    zinTextPlus[0].setCharacterSize(24);
    //plus sign text for resolve
    zinTextPlus[1].setPosition(rectStatsBoxX + 3, rectStatsBoxY + 174);
    zinTextPlus[1].setString("+");
    zinTextPlus[1].setCharacterSize(24);
    //plus sign text for patience
    zinTextPlus[2].setPosition(rectStatsBoxX + 3, rectStatsBoxY + 154);
    zinTextPlus[2].setString("+");
    zinTextPlus[2].setCharacterSize(24);
    //plus sign text for resilience
    zinTextPlus[3].setPosition(rectStatsBoxX + 3, rectStatsBoxY + 133);
    zinTextPlus[3].setString("+");
    zinTextPlus[3].setCharacterSize(24);
    //Side Menu Zin Stats Menu Rect Text
    zinTextPlus[4].setCharacterSize(16);
    zinTextPlus[4].setPosition(rectStatsBoxX + 205, rectStatsBoxY);
    zinTextPlus[4].setString("P\nL\nA\nY\nE\nR");
    //Side Menu Zin Stats Menu Rect Text
    zinTextPlus[5].setCharacterSize(16);
    zinTextPlus[5].setPosition(rectStatsBoxX + 205, rectStatsBoxY + 120);
    zinTextPlus[5].setString("\nZ\nI\nN");

    //Zin Text Elements Loop
    for (int i = 0; i < zinTextElements.size(); i++) {
        zinTextElements[i].setFont(font);
        zinTextElements[i].setFillColor(sf::Color::White);
    }
    //Title next to level box
    zinTextElements[0].setCharacterSize(14);
    zinTextElements[0].setPosition(rectStatsBoxX + 25, rectStatsBoxY + 100);
    //Title next to resolve box
    zinTextElements[1].setFont(font);
    zinTextElements[1].setCharacterSize(14);
    zinTextElements[1].setPosition(rectStatsBoxX + 25, rectStatsBoxY + 180);
    //Title next to patience box
    zinTextElements[2].setFont(font);
    zinTextElements[2].setCharacterSize(14);
    zinTextElements[2].setPosition(rectStatsBoxX + 25, rectStatsBoxY + 160);
    //Title next to resilience box
    zinTextElements[3].setFont(font);
    zinTextElements[3].setCharacterSize(14);
    zinTextElements[3].setPosition(rectStatsBoxX + 25, rectStatsBoxY + 140);
    //Hp text
    zinTextElements[4].setCharacterSize(16);
    zinTextElements[4].setPosition(rectStatsBoxX, rectStatsBoxY);
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
        buttonViewMap[1].setPosition(rectMapX + 133.0f, rectMapY - 25.0f);
        buttonViewMap[2].setPosition(rectMapX + 266.0f, rectMapY - 25.0f);
        for (int i = 0; i < buttonViewMapText.size(); i++) {
            buttonViewMapText[i].setFont(font);
            buttonViewMapText[i].setCharacterSize(14);
        }
        //Castle Map Button Selector Text
        buttonViewMapText[0].setPosition(rectMapX, rectMapY - 25);
        buttonViewMapText[0].setString("Forest Plane");

        buttonViewMapText[1].setPosition(rectMapX + 133.0f, rectMapY - 25.0f);
        buttonViewMapText[1].setString("Castle Plane");

        buttonViewMapText[2].setPosition(rectMapX + 266.0f, rectMapY - 25.0f);
        buttonViewMapText[2].setString("Decay Plane");
        break;
    }

    multiArrow.setPosition(rectMapX + 340, rectMapY + 10);
    multiArrow.setScale(0.06f, 0.06f);
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
        multiArrowTexture.loadFromFile("Assets/Game_Resources/multiarrow.png");
        multiArrow.setTexture(multiArrowTexture);

        //Load Map View
        forestMapTexture.loadFromFile("Assets/Wallpapers/Forest/forestmap.jpeg");
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
        multiArrowTexture.loadFromFile("Assets/Game_Resources/multiarrow.png");
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
        textureMapView.loadFromFile("Assets/Wallpapers/Castle/castleMap.jpeg");
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
        multiArrowTexture.loadFromFile("Assets/Game_Resources/multiarrow.png");
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
        decayTexture.loadFromFile("Assets/Wallpapers/Decay/decayMap.jpeg");
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
    textThom.setString("Thom");
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
        this->thomCombatAssets();
    }
    else if (!combatAssets && !bonfireAssets && !eventAssets) {
        //Hide all combat assets
        for (int i = 0; i < spriteRect.size(); i++) {
            spriteRect[i].setPosition(10000, 10000);
            spriteText[i].setPosition(10000, 10000);
        }
        for (int i = 0; i < combatRect.size(); i++) {
            combatRect[i].setPosition(10000, 10000);
            combatText[i].setPosition(10000, 10000);
        }
        playerCounter = -1;
        zinCounter = -1;
        hostileCounter = -1;
        thomCounter = -1;
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
        combatText[3].setPosition(10000.0f, 10000.0f);
        combatText[4].setPosition(10000.0f, 10000.0f);
        combatText[5].setPosition(10000.0f, 10000.0f);
    }
}

void Assets::thomCombatAssets()
{
    if (this->thomTurnAssets) {
        switch (this->combatThomMoves) {
        case 0:
            //Draw Thom Barrier Button
            combatRect[6].setPosition(335.0f, 795.0f);
            //Draw Player Slash Text
            combatText[6].setPosition(335.0f, 795.0f);
            combatText[6].setString("Barrier");
            break;
        case 1:
            //Draw Thom Barrier Button
            combatRect[6].setPosition(335.0f, 795.0f);
            //Draw Player Slash Text
            combatText[6].setPosition(335.0f, 795.0f);
            combatText[6].setString("Barrier");
            //Draw Thom Barrier Button
            combatRect[7].setPosition(335.0f, 765.0f);
            //Draw Player Slash Text
            combatText[7].setPosition(335.0f, 765.0f);
            combatText[7].setString("Enrage");
            break;
        }
    }
    else if (!this->thomTurnAssets) {
        combatRect[6].setPosition(10000.0f, 10000.0f);
        combatText[6].setPosition(10000.0f, 10000.0f);
        combatRect[7].setPosition(10000.0f, 10000.0f);
        combatText[7].setPosition(10000.0f, 10000.0f);
    }
}

//Sound Functions
void Assets::loadSFX()
{
    //Click Sound
    soundClick.setBuffer(bufferClick);
    //Load Campfire Sound
    soundCampfire.setBuffer(bufferCampfire);

    //Load Hover Sound
    soundHover.setBuffer(bufferSoundHover);
    //Load Walk Sound
    soundWalk.setBuffer(bufferWalk);
    //Load Text Sfx
    sound.setBuffer(buffer);
    //Load Button Sfx
    blipsound.setBuffer(blipbuffer);
    blipmenu.setBuffer(blipmenubuffer);

    //Load Combat Sound Effects
    soundCom.setBuffer(bufferCom);
    //Load Decay Blade Sound
    soundDecay.setBuffer(bufferDecay);
    //Load Vengeance Sound
    soundVengeance.setBuffer(bufferVengeance);
    //Load Slash Sound
    soundSlash.setBuffer(bufferSlash);
    //Load Smite Sound
    soundSmite.setBuffer(bufferSmite);
    //Load Mend Sound
    soundMend.setBuffer(bufferMend);
    //Load Guarded Sound
    soundGuarded.setBuffer(bufferGuarded);
    //Load Guard Sound
    soundGuard.setBuffer(bufferGuard);
    //Load Anger Sfx
    soundAngry.setBuffer(bufferAngry);
    //Load Combat Start Sfx
    soundCombatStart.setBuffer(bufferCombatStart);
    //Load Thom Guarding Player Sfx
    soundPlayerGuarded.setBuffer(bufferPlayerGuarded);
    //Load Thom's Barrier Shattering Sfx
    soundThomGuard.setBuffer(bufferThomGuard);
    //Load Enraged Sfx
    soundEnraged.setBuffer(bufferEnraged);
   
    //Set Volume Levels
    blipmenu.setVolume(60);
}
