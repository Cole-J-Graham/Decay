#include "Assets.h"

//Constructors & Destructors
Assets::Assets()
{
    //Sprite Bool
    this->initMapTexture = false;
    this->initMap = false;
    this->initStats = false;

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
    this->combatCounter = -1;

    //Movable
    this->movable = false;
    this->movableStatsBox = false;

    //Rect Coordinates
    this->rectMapX = 25;
    this->rectMapY = 50;
    this->rectStatsBoxX = 1490;
    this->rectStatsBoxY = 50;

    //Initialize Combat Assets
    this->combatAssets = false;
    this->playerTurnAssets = false;
    //Combat Control Flow
    this->attackCounter = -1;

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
        buttonMap.setPosition(1.0f, 795.0f);
        buttonMap.setSize(sf::Vector2f(100.0f, 25.0f));
        buttonMap.setOutlineColor(sf::Color::White);
        buttonMap.setOutlineThickness(1.0f);
        //Draw Stats Button
        rectStats.setPosition(105.0f, 795.0f);
        rectStats.setSize(sf::Vector2f(100.0f, 25.0f));
        rectStats.setOutlineColor(sf::Color::White);
        rectStats.setOutlineThickness(1.0f);
        //Draw Button
        button.setTexture(buttonTexture);
        button.setPosition(1400.0f, 765.0f);
        //Draw Back Button
        buttonBackTexture.loadFromFile("C:/Users/Cole/source/repos/SFML Console Chat/SFML Console Chat/Assets/Sprites/buttonsolidfix.png");
        buttonBack.setTexture(buttonBackTexture);
        buttonBack.setPosition(445.0f, 765.0f);
    }
    else if (combatAssets == true) {
        buttonMap.setPosition(1.0f, 10000.0f);
        rectStats.setPosition(105.0f, 10000.0f);
        button.setPosition(1400.0f, 10000.0f);
        buttonBack.setPosition(445.0f, 10000.0f);
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

            buttonCastleEntrance.setTexture(buttonTexture);
            buttonCastleEntrance.setPosition(rectMapX +34, rectMapY +20);
            buttonCastleEntrance.setScale(0.5f, 0.5f);

            buttonCastleDepths.setTexture(buttonTexture);
            buttonCastleDepths.setPosition(rectMapX + 75, rectMapY + 240);
            buttonCastleDepths.setScale(0.5f, 0.5f);

            castleEntranceText.setString("Castle Entrance");
            castleDepthsText.setString("Castle Depths");
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
    //Hp text
    statsText.setFont(font);
    statsText.setCharacterSize(16);
    statsText.setFillColor(sf::Color(sf::Color::White));
    statsText.setPosition(rectStatsBoxX, rectStatsBoxY);
    //Level up plus Box
    rectStatsPointsBox.setPosition(rectStatsBoxX, rectStatsBoxY + 580);
    rectStatsPointsBox.setSize(sf::Vector2f(20.0f, 20.0f));
    rectStatsPointsBox.setOutlineColor(sf::Color::White);
    rectStatsPointsBox.setOutlineThickness(1.0f);
    //Strength plus box
    rectStrengthPointsBox.setPosition(rectStatsBoxX, rectStatsBoxY + 560);
    rectStrengthPointsBox.setSize(sf::Vector2f(20.0f, 20.0f));
    rectStrengthPointsBox.setOutlineColor(sf::Color::White);
    rectStrengthPointsBox.setOutlineThickness(1.0f);
    //Plus sign text for level up
    statsPointsText.setFont(font);
    statsPointsText.setCharacterSize(24);
    statsPointsText.setPosition(rectStatsBoxX + 3, rectStatsBoxY + 574);
    statsPointsText.setString("+");
    //plus sign text for strength
    statsStrengthText.setFont(font);
    statsStrengthText.setCharacterSize(24);
    statsStrengthText.setPosition(rectStatsBoxX + 3, rectStatsBoxY + 552);
    statsStrengthText.setString("+");
    //Title next to level box
    statsPointsTextTitle.setFont(font);
    statsPointsTextTitle.setCharacterSize(14);
    statsPointsTextTitle.setPosition(rectStatsBoxX + 25, rectStatsBoxY + 580);
    //Title next to strength box
    statsStrengthTextTitle.setFont(font);
    statsStrengthTextTitle.setCharacterSize(14);
    statsStrengthTextTitle.setPosition(rectStatsBoxX + 25, rectStatsBoxY + 560);
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
    menuText.setFont(font);
    menuText.setCharacterSize(18);
    menuText.setPosition(1.0f, 797.0f);
    menuText.setString("Map");
    rectStatsText.setFont(font);
    rectStatsText.setCharacterSize(18);
    rectStatsText.setPosition(105.0f, 797.0f);
    rectStatsText.setString("Stats");
    //Castle Entrance Text
    castleEntranceText.setFont(font);
    castleEntranceText.setCharacterSize(12);
    castleEntranceText.setPosition(this->rectMapX, this->rectMapY + 5);
    castleEntranceText.setFillColor(sf::Color::White);
    //Castle Depths Text
    castleDepthsText.setFont(font);
    castleDepthsText.setCharacterSize(12);
    castleDepthsText.setPosition(this->rectMapX + 40, this->rectMapY + 220);
    castleDepthsText.setFillColor(sf::Color::White);
}

//Sprite Functions
void Assets::drawSpriteBox()
{
    if (this->spriteInit == true) {
        //Draw Sprite Box
        rectSpriteBox.setFillColor(sf::Color::Black);
        rectSpriteBox.setPosition(50.0f, 560.0f);
        rectSpriteBox.setSize(sf::Vector2f(153.0f, 153.0f));
        rectSpriteBox.setOutlineColor(sf::Color::White);
        rectSpriteBox.setOutlineThickness(2.0f);
        //Sprite Name Text
        spriteText.setFont(font);
        spriteText.setCharacterSize(18);
        spriteText.setPosition(50.0f, 715.0f);
        spriteText.setFillColor(sf::Color::White);
    }
    else if (this->spriteInit == false) {
        rectSpriteBox.setPosition(10000.0f, 560.0f);
        spriteText.setPosition(10000.0f, 715.0f);
    }
}

void Assets::spadeSprite()
{
    //Initialize Spade Sprite
    if (this->spadeLoadOnce == true) {
        texture.loadFromFile("C:/Users/Cole/source/repos/SFML Console Chat/SFML Console Chat/Assets/Sprites/spadePixel.png");
        sprite.setPosition(sf::Vector2f(10000.0f, 560.0f)); // absolute position
        this->spadeLoadOnce = false;
    }
    //Pick Spade Sprite Emotion
    switch (this->spadeCounter) {
    case -1:
        sprite.setPosition(sf::Vector2f(10000.0f, 560.0f)); // absolute position
        break;
    case 0:
        if (this->spadeInit == false) {
            texture.loadFromFile("C:/Users/Cole/source/repos/SFML Console Chat/SFML Console Chat/Assets/Sprites/spadePixel.png");
            sprite.setPosition(sf::Vector2f(50.0f, 560.0f)); // absolute position
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
    sprite.setTexture(texture);
    sprite.setScale(0.050f, 0.050f);
}

void Assets::zinSprite()
{
    //Initialize Spade Sprite
    if (this->zinLoadOnce == true) {
        zinTexture.loadFromFile("C:/Users/Cole/source/repos/SFML Console Chat/SFML Console Chat/Assets/Sprites/zinsprite.png");
        zin.setPosition(sf::Vector2f(10000.0f, 560.0f)); // absolute position
        this->zinLoadOnce = false;
    }
    //Pick Spade Sprite Emotion
    switch (this->zinCounter) {
    case -1:
        zin.setPosition(sf::Vector2f(10000.0f, 560.0f)); // absolute position
        break;
    case 0:
        if (this->zinInit == false) {
            zinTexture.loadFromFile("C:/Users/Cole/source/repos/SFML Console Chat/SFML Console Chat/Assets/Sprites/zinsprite.png");
            zin.setPosition(sf::Vector2f(50.0f, 345.0f)); // absolute position
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
    zin.setTexture(zinTexture);
    zin.setScale(1.70f, 1.70f);
}

//Combat Asset Functions
void Assets::initCombatAssets()
{
    if (combatAssets == true) {
        //Draw Player Sprite Box
        playerSpriteBorder.setFillColor(sf::Color::Black);
        playerSpriteBorder.setPosition(50.0f, 145.0f);
        playerSpriteBorder.setSize(sf::Vector2f(153.0f, 153.0f));
        playerSpriteBorder.setOutlineColor(sf::Color::White);
        playerSpriteBorder.setOutlineThickness(2.0f);
        //Sprite Player Name Text
        playerNameText.setFont(font);
        playerNameText.setCharacterSize(18);
        playerNameText.setPosition(50.0f, 300.0f);
        playerNameText.setFillColor(sf::Color::White);
        //Draw Zin Sprite Box
        zinSpriteBorder.setFillColor(sf::Color::Black);
        zinSpriteBorder.setPosition(50.0f, 345.0f);
        zinSpriteBorder.setSize(sf::Vector2f(153.0f, 153.0f));
        zinSpriteBorder.setOutlineColor(sf::Color::White);
        zinSpriteBorder.setOutlineThickness(2.0f);
        //Sprite Zin Name Text
        zinText.setFont(font);
        zinText.setCharacterSize(18);
        zinText.setPosition(50.0f, 500.0f);
        zinText.setFillColor(sf::Color::White);
        //Draw Hostile Sprite Box
        hostileSpriteBorder.setFillColor(sf::Color::Black);
        hostileSpriteBorder.setPosition(1650.0f, 300.0f);
        hostileSpriteBorder.setSize(sf::Vector2f(153.0f, 153));
        hostileSpriteBorder.setOutlineColor(sf::Color::White);
        hostileSpriteBorder.setOutlineThickness(2.0f);
        //Sprite Hostile Name Text
        hostileNameText.setFont(font);
        hostileNameText.setCharacterSize(18);
        hostileNameText.setPosition(1650.0f, 455.0f);
        hostileNameText.setFillColor(sf::Color::White);
        //Combat Bar Text
        attackText.setFont(font);
        attackText.setCharacterSize(18);
        attackText.setPosition(450.0f, 825.0f);
        attackText.setString("Attack");
        fleeText.setFont(font);
        fleeText.setCharacterSize(18);
        fleeText.setPosition(555.0f, 825.0f);
        fleeText.setString("Flee");
        //Draw Attack Button
        rectAttack.setPosition(450.0f, 825.0f);
        rectAttack.setSize(sf::Vector2f(100.0f, 25.0f));
        rectAttack.setOutlineColor(sf::Color::White);
        rectAttack.setOutlineThickness(1.0f);
        //Draw Flee Button
        rectFlee.setPosition(555.0f, 825.0f);
        rectFlee.setSize(sf::Vector2f(100.0f, 25.0f));
        rectFlee.setOutlineColor(sf::Color::White);
        rectFlee.setOutlineThickness(1.0f);
    }
    else if (combatAssets == false) {
        //Hide all combat assets
        playerSpriteBorder.setPosition(50.0f, 10000.0f);
        playerNameText.setPosition(50.0f, 10000.0f);
        zinSpriteBorder.setPosition(50.0f, 10000.0f);
        zinText.setPosition(50.0f, 10000.0f);
        attackText.setPosition(800.0f, 10000.0f);
        fleeText.setPosition(905.0f, 10000.0f);
        rectAttack.setPosition(800.0f, 10000.0f);
        rectFlee.setPosition(905.0f, 10000.0f);
        hostileSpriteBorder.setPosition(1650.0f, 10000.0f);
        hostileNameText.setPosition(1650.0f, 10000.0f);
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
