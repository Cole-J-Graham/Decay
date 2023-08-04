#include "Assets.h"

//Constructors & Destructors
Assets::Assets()
{
    //Sprite Bool
    this->initialDrawIn = false;
    this->initMapTexture = false;
    this->initMap = false;
    this->initStats = false;
    this->initInventory = false;
    this->plusboxes = false;

    //Menu Control Flow
    this->playerStatsInit = true;
    this->zinStatsInit = false;

    //Sprite Control Flow
    this->spadeInit = false;
    this->spadeLoadOnce = true;

    this->zinInit = false;
    this->zinLoadOnce = true;

    //Sprite Border Control Flow
    this->spriteInit = true;

    //Sprite Integer Selection
    this->spadeCounter = -1;
    this->zinCounter = -1;
    this->mapCounter = -1;
    this->dialogueCounter = 0;
    this->combatCounter = 0;

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
    this->playerTurnAssets = false;
    this->zinTurnAssets = false;

    //Strings
    this->playerName = "player";

    buttonTexture.loadFromFile("C:/Users/Cole/source/repos/SFML Console Chat/SFML Console Chat/Assets/Sprites/buttonsolidfix.png");
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
    //Sprite Assets
    this->spadeSprite();
    this->zinSprite();
    this->drawSpriteBox();
    //Combat Asset Functions
    this->initCombatAssets();
}

void Assets::drawMainWindow()
{
    //Draw Menu Box
    rect.setPosition(0.0f, 825.0f);
    rect.setSize(sf::Vector2f(1920.0f, 825.0f));
    rect.setOutlineColor(sf::Color::White);
    rect.setOutlineThickness(1.0f);
    if (combatAssets == false) {
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
        //Draw Button
        spriteElements[0].setTexture(buttonTexture);
        spriteElements[0].setPosition(1400.0f, 765.0f);
        //Draw Back Button
        buttonBackTexture.loadFromFile("C:/Users/Cole/source/repos/SFML Console Chat/SFML Console Chat/Assets/Sprites/buttonsolidfix.png");
        spriteElements[1].setTexture(buttonBackTexture);
        spriteElements[1].setPosition(445.0f, 765.0f);
    }
    else if (combatAssets == true) {
        //Make assets hidden during combat
        rectElements[2].setPosition(1.0f, 10000.0f);
        rectElements[1].setPosition(209.0f, 10000.0f);
        rectElements[0].setPosition(105.0f, 10000.0f);
        spriteElements[0].setPosition(1400.0f, 10000.0f);
        spriteElements[0].setPosition(445.0f, 10000.0f);
    }
}

void Assets::drawMap()
{
    rectMap.setFillColor(sf::Color::Black);
    rectMap.setPosition(rectMapX, rectMapY);
    rectMap.setSize(sf::Vector2f(400.0f, 400.0f));
    rectMap.setOutlineColor(sf::Color::White);
    rectMap.setOutlineThickness(1.0f);
    switch (mapCounter) {
    case 0:
        if (this->initMapTexture == false) {
            //Load Map View
            textureMapView.loadFromFile("C:/Users/Cole/source/repos/SFML Console Chat/SFML Console Chat/Assets/Sprites/mapTexture.jpeg");
            spriteMapView.setTexture(textureMapView);
            spriteMapView.setPosition(rectMapX, rectMapY);
            spriteMapView.setScale(0.38f, 0.38f);

            mapCastleElements[0].setTexture(buttonTexture);
            mapCastleElements[0].setPosition(rectMapX +34, rectMapY +20);
            mapCastleElements[0].setScale(0.5f, 0.5f);

            mapCastleElements[1].setTexture(buttonTexture);
            mapCastleElements[1].setPosition(rectMapX + 75, rectMapY + 240);
            mapCastleElements[1].setScale(0.5f, 0.5f);

            mapCastleElementsText[0].setString("Castle Entrance");
            mapCastleElementsText[1].setString("Castle Depths");
            this->initMapTexture = true;
        }
        break;
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
    playerTextElements[8].setFillColor(sf::Color::Red);
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
    playerTextElements[9].setFillColor(sf::Color::Blue);
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
    zinTextElements[8].setFillColor(sf::Color::Blue);
    //Side Menu Zin Stats Menu Rect Text
    zinTextElements[9].setFont(font);
    zinTextElements[9].setCharacterSize(16);
    zinTextElements[9].setPosition(rectStatsBoxX + 205, rectStatsBoxY + 120);
    zinTextElements[9].setString("\nZ\nI\nN");
    zinTextElements[9].setFillColor(sf::Color::Red);
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
    text.setCharacterSize(18);
    text.setFillColor(sf::Color(sf::Color::White));
    text.setPosition(0.0f, 835.0f);
    //Draw Input Text
    playerText.setFont(font);
    playerText.setFillColor(sf::Color(sf::Color::White));
    playerText.setPosition(0.0f, 970.0f);
    //Draw Right Hand Side Text
    combatText.setFont(font);
    combatText.setCharacterSize(18);
    combatText.setFillColor(sf::Color(sf::Color::White));
    combatText.setPosition(500.0f, 835.0f);
    //Draw Location Text
    locationText.setFont(font);
    locationText.setCharacterSize(18);
    locationText.setFillColor(sf::Color(sf::Color::White));
    locationText.setPosition(275.0f, 10.0f);
    //Menu Bar Text
    textElements[2].setFont(font);
    textElements[2].setCharacterSize(18);
    textElements[2].setPosition(1.0f, 797.0f);
    textElements[2].setString("Map");
    textElements[0].setFont(font);
    textElements[0].setCharacterSize(18);
    textElements[0].setPosition(105.0f, 797.0f);
    textElements[0].setString("Stats");
    textElements[1].setFont(font);
    textElements[1].setCharacterSize(18);
    textElements[1].setPosition(210.0f, 797.0f);
    textElements[1].setString("Inventory");
    //Castle Entrance Text
    mapCastleElementsText[0].setFont(font);
    mapCastleElementsText[0].setCharacterSize(12);
    mapCastleElementsText[0].setPosition(this->rectMapX, this->rectMapY + 5);
    mapCastleElementsText[0].setFillColor(sf::Color::White);
    //Castle Depths Text
    mapCastleElementsText[1].setFont(font);
    mapCastleElementsText[1].setCharacterSize(12);
    mapCastleElementsText[1].setPosition(this->rectMapX + 40, this->rectMapY + 220);
    mapCastleElementsText[1].setFillColor(sf::Color::White);
}

//Sprite Functions
void Assets::drawSpriteBox()
{
    if (this->spriteInit == true) {
        //Draw Sprite Box
        rectElements[5].setFillColor(sf::Color::Black);
        rectElements[5].setPosition(50.0f, 560.0f);
        rectElements[5].setSize(sf::Vector2f(153.0f, 153.0f));
        rectElements[5].setOutlineColor(sf::Color::White);
        rectElements[5].setOutlineThickness(2.0f);
        //Sprite Name Text
        textElements[5].setFont(font);
        textElements[5].setCharacterSize(18);
        textElements[5].setPosition(50.0f, 715.0f);
        textElements[5].setFillColor(sf::Color::White);
    }
    else if (this->spriteInit == false) {
        rectElements[5].setPosition(10000.0f, 560.0f);
        textElements[5].setPosition(10000.0f, 715.0f);
    }
}

void Assets::spadeSprite()
{
    //Initialize Spade Sprite
    if (this->spadeLoadOnce == true) {
        texture.loadFromFile("C:/Users/Cole/source/repos/SFML Console Chat/SFML Console Chat/Assets/Sprites/spadePixel.png");
        spriteElements[2].setPosition(sf::Vector2f(10000.0f, 560.0f)); // absolute position
        this->spadeLoadOnce = false;
    }
    //Pick Spade Sprite Emotion
    switch (this->spadeCounter) {
    case -1:
        spriteElements[2].setPosition(sf::Vector2f(10000.0f, 560.0f)); // absolute position
        break;
    case 0:
        if (this->spadeInit == false) {
            texture.loadFromFile("C:/Users/Cole/source/repos/SFML Console Chat/SFML Console Chat/Assets/Sprites/spadePixel.png");
            spriteElements[2].setPosition(sf::Vector2f(50.0f, 560.0f)); // absolute position
            spriteText.setString("Spade");
            this->spadeInit = true;
        }
        break;
    case 1:
        if (this->spadeInit == false) {
            spriteText.setString("Spade");
            texture.loadFromFile("C:/Users/Cole/source/repos/SFML Console Chat/SFML Console Chat/Assets/Sprites/spadePixelAngry.png");
            this->spadeInit = true;
        }
        break;
    }
   

    //Sprite Options, ect
    texture.setSmooth(true);
    texture.setRepeated(false);
    spriteElements[2].setTexture(texture);
    spriteElements[2].setScale(0.050f, 0.050f);
}

void Assets::zinSprite()
{
    //Initialize Spade Sprite
    if (this->zinLoadOnce == true) {
        zinTexture.loadFromFile("C:/Users/Cole/source/repos/SFML Console Chat/SFML Console Chat/Assets/Sprites/zinsprite.png");
        spriteElements[3].setPosition(sf::Vector2f(10000.0f, 560.0f)); // absolute position
        this->zinLoadOnce = false;
    }
    //Pick Spade Sprite Emotion
    switch (this->zinCounter) {
    case -1:
        spriteElements[3].setPosition(sf::Vector2f(10000.0f, 560.0f)); // absolute position
        break;
    case 0:
        if (this->zinInit == false) {
            zinTexture.loadFromFile("C:/Users/Cole/source/repos/SFML Console Chat/SFML Console Chat/Assets/Sprites/zinsprite.png");
            spriteElements[3].setPosition(sf::Vector2f(50.0f, 345.0f)); // absolute position
            this->zinInit = true;
        }
        break;
    case 1:
        if (this->zinInit == false) {
            zinTexture.loadFromFile("C:/Users/Cole/source/repos/SFML Console Chat/SFML Console Chat/Assets/Sprites/zinsprite.png");
            this->zinInit = true;
        }
        break;
    }


    //Sprite Options, ect
    //zinTexture.setSmooth(true);
    zinTexture.setRepeated(false);
    spriteElements[3].setTexture(zinTexture);
    spriteElements[3].setScale(1.70f, 1.70f);
}

//Combat Asset Functions
void Assets::initCombatAssets()
{
    if (combatAssets == true) {
        //Draw Player Sprite Box
        rectElements[6].setFillColor(sf::Color::Black);
        rectElements[6].setPosition(50.0f, 145.0f);
        rectElements[6].setSize(sf::Vector2f(153.0f, 153.0f));
        rectElements[6].setOutlineColor(sf::Color::White);
        rectElements[6].setOutlineThickness(2.0f);
        //Sprite Player Name Text
        textElements[6].setFont(font);
        textElements[6].setCharacterSize(18);
        textElements[6].setPosition(50.0f, 300.0f);
        textElements[6].setFillColor(sf::Color::White);
        //Draw Zin Sprite Box
        rectElements[7].setFillColor(sf::Color::Black);
        rectElements[7].setPosition(50.0f, 345.0f);
        rectElements[7].setSize(sf::Vector2f(153.0f, 153.0f));
        rectElements[7].setOutlineColor(sf::Color::White);
        rectElements[7].setOutlineThickness(2.0f);
        //Sprite Zin Name Text
        textElements[7].setFont(font);
        textElements[7].setCharacterSize(18);
        textElements[7].setPosition(50.0f, 500.0f);
        textElements[7].setFillColor(sf::Color::White);
        //Draw Hostile Sprite Box
        rectElements[8].setFillColor(sf::Color::Black);
        rectElements[8].setPosition(1650.0f, 300.0f);
        rectElements[8].setSize(sf::Vector2f(153.0f, 153));
        rectElements[8].setOutlineColor(sf::Color::White);
        rectElements[8].setOutlineThickness(2.0f);
        //Sprite Hostile Name Text
        textElements[8].setFont(font);
        textElements[8].setCharacterSize(18);
        textElements[8].setPosition(1650.0f, 455.0f);
        textElements[8].setFillColor(sf::Color::White);
        if (this->playerTurnAssets == true) {
            //Draw Player Slash Text
            textElements[3].setFont(font);
            textElements[3].setCharacterSize(18);
            textElements[3].setPosition(335.0f, 795.0f);
            textElements[3].setString("Slash");
            //Draw Player Slash Button
            rectElements[3].setPosition(335.0f, 795.0f);
            rectElements[3].setSize(sf::Vector2f(100.0f, 25.0f));
            rectElements[3].setOutlineColor(sf::Color::White);
            rectElements[3].setOutlineThickness(1.0f);
        }
        else if (this->playerTurnAssets == false) {
            textElements[3].setPosition(335.0f, 10000.0f);
            rectElements[3].setPosition(335.0f, 10000.0f);
        }
        if (this->zinTurnAssets == true) {
            //Draw Zin Smite Text
            textElements[4].setFont(font);
            textElements[4].setCharacterSize(18);
            textElements[4].setPosition(335.0f, 795.0f);
            textElements[4].setString("Smite");
            //Draw Zin Smite Button
            rectElements[4].setPosition(335.0f, 795.0f);
            rectElements[4].setSize(sf::Vector2f(100.0f, 25.0f));
            rectElements[4].setOutlineColor(sf::Color::White);
            rectElements[4].setOutlineThickness(1.0f);
        }
        else if (this->zinTurnAssets == false) {
            textElements[4].setPosition(335.0f, 10000.0f);
            rectElements[4].setPosition(335.0f, 10000.0f);
        }
    }
    else if (combatAssets == false) {
        //Hide all combat assets
        playerSpriteBorder.setPosition(50.0f, 10000.0f);
        textElements[3].setPosition(335.0f, 10000.0f);
        rectElements[3].setPosition(335.0f, 10000.0f);
        textElements[4].setPosition(335.0f, 10000.0f);
        rectElements[4].setPosition(335.0f, 10000.0f);
        rectElements[6].setPosition(50.0f, 10000.0f);
        textElements[6].setPosition(50.0f, 10000.0f);
        rectElements[7].setPosition(50.0f, 10000.0f);
        textElements[7].setPosition(50.0f, 10000.0f);
        textElements[8].setPosition(1650.0f, 10000.0f);
        rectElements[8].setPosition(1650.0f, 10000.0f);
        zinCounter = -1;
    }
}

//Sound Functions
void Assets::loadSFX()
{
    bufferWalk.loadFromFile("C:/Users/Cole/source/repos/SFML Console Chat/SFML Console Chat/Assets/Sounds/moveRoom.wav");
    soundWalk.setBuffer(bufferWalk);
    //Load Combat Sound Effects
    bufferCom.loadFromFile("C:/Users/Cole/source/repos/SFML Console Chat/SFML Console Chat/Assets/Sounds/Boss hit 1.wav");
    soundCom.setBuffer(bufferCom);
    //Load Text Sfx
    buffer.loadFromFile("C:/Users/Cole/source/repos/SFML Console Chat/SFML Console Chat/Assets/Sounds/Text 1.wav");
    sound.setBuffer(buffer);
    //Load Button Sfx
    blipbuffer.loadFromFile("C:/Users/Cole/source/repos/SFML Console Chat/SFML Console Chat/Assets/Sounds/blipSelect.wav");
    blipsound.setBuffer(blipbuffer);
    blipmenubuffer.loadFromFile("C:/Users/Cole/source/repos/SFML Console Chat/SFML Console Chat/Assets/Sounds/menuclick.wav");
    blipmenu.setBuffer(blipmenubuffer);
    //Load Anger Sfx
    bufferAngry.loadFromFile("C:/Users/Cole/source/repos/SFML Console Chat/SFML Console Chat/Assets/Sounds/angry.wav");
    soundAngry.setBuffer(bufferAngry);
    //Load Combat Start Sfx
    bufferCombatStart.loadFromFile("C:/Users/Cole/source/repos/SFML Console Chat/SFML Console Chat/Assets/Sounds/combatstart.wav");
    soundCombatStart.setBuffer(bufferCombatStart);
    //Load and stream music
    music.openFromFile("C:/Users/Cole/source/repos/SFML Console Chat/SFML Console Chat/Assets/Music/track1.wav");
    //music.play();
}
