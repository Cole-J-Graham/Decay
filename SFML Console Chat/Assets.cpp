#include "Assets.h"

//Constructors & Destructors
Assets::Assets()
{
    //Sprite Bool
    this->spriteZinNormal = false; //Control flow
    this->spriteZinSmug = false; //Control flow
    this->buttonClicked = false; //Control flow
    this->initMapTexture = false;
    this->initMap = false;
    this->initStats = false;

    //Sprite Control Flow Bool
    this->zinInit = true;
    this->zinInitAngry = false;
    this->spriteInit = true;

    this->zinTest = -1;
    this->testMap = -1;

    this->movable = false;
    this->movableStatsBox = false;
    this->rectMapX = 25;
    this->rectMapY = 50;
    this->rectStatsBoxX = 1490;
    this->rectStatsBoxY = 50;

    buttonTexture.loadFromFile("C:/Users/Cole/source/repos/SFML Console Chat/SFML Console Chat/Assets/Sprites/buttonsolidfix.png");
}

Assets::~Assets()
{

}

//Drawing Objects
void Assets::drawObjects()
{
    this->drawMainWindow();
    this->zinSprite();
    this->drawText();
    this->drawMap();
    this->drawStats();
    this->drawSpriteBox();
}

void Assets::drawMainWindow()
{
    //Draw Menu Box
    rect.setFillColor(sf::Color::Black);
    rect.setPosition(0.0f, 825.0f);
    rect.setSize(sf::Vector2f(1920.0f, 825.0f));
    rect.setOutlineColor(sf::Color::White);
    rect.setOutlineThickness(1.0f);
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

void Assets::drawMap()
{
    rectMap.setFillColor(sf::Color::Black);
    rectMap.setPosition(rectMapX, rectMapY);
    rectMap.setSize(sf::Vector2f(400.0f, 400.0f));
    rectMap.setOutlineColor(sf::Color::White);
    rectMap.setOutlineThickness(1.0f);
    switch (testMap) {
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
    rectStatsBox.setFillColor(sf::Color::Black);
    rectStatsBox.setPosition(rectStatsBoxX, rectStatsBoxY);
    rectStatsBox.setSize(sf::Vector2f(200.0f, 600.0f));
    rectStatsBox.setOutlineColor(sf::Color::White);
    rectStatsBox.setOutlineThickness(1.0f);
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
}

void Assets::zinSprite()
{
    if (this->zinInit == true) {
        spriteText.setString("Spade");
        texture.loadFromFile("C:/Users/Cole/source/repos/SFML Console Chat/SFML Console Chat/Assets/Sprites/spadePixel.png");
        this->zinInit = false;
    }
    
    if (this->zinInitAngry == true) {
        spriteText.setString("Spade");
        texture.loadFromFile("C:/Users/Cole/source/repos/SFML Console Chat/SFML Console Chat/Assets/Sprites/spadePixelAngry.png");
        this->zinInitAngry = false;
    }
   

    //Sprite Location, ect
    texture.setSmooth(true);
    texture.setRepeated(false);
    sprite.setTexture(texture);
    sprite.setScale(0.050f, 0.050f);
    sprite.setPosition(sf::Vector2f(50.0f, 560.0f)); // absolute position
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
    //Load and stream music
    music.openFromFile("C:/Users/Cole/source/repos/SFML Console Chat/SFML Console Chat/Assets/Music/track1.wav");
    //music.play();
}
