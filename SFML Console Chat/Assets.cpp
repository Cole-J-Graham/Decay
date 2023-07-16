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
    this->castleEntrance = true;
    this->castleDepths = false;
    this->init = false; //To initialize and uninitialize the textures loaded to manage performance

    this->testMap = -1;

    this->movable = false;
    this->rectMapX = 25;
    this->rectMapY = 50;

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
    //Draw Button
    button.setTexture(buttonTexture);
    button.setPosition(1400.0f, 765.0f);
    //Draw Back Button
    buttonBackTexture.loadFromFile("C:/Users/Cole/source/repos/SFML Console Chat/SFML Console Chat/Assets/Sprites/buttonsolidfix.png");
    buttonBack.setTexture(buttonBackTexture);
    buttonBack.setPosition(445.0f, 765.0f);

    if (castleEntrance == true) {
        switch (testTexture) {
        case 0:
            //Draw Map Sprite
            locationText.setString("Castle Entrance");
            if (this->init == false) {
                mapTexture.loadFromFile("C:/Users/Cole/source/repos/SFML Console Chat/SFML Console Chat/Assets/Sprites/castleentrance.jpeg");
                this->init = true;
            }
            map.setTexture(mapTexture);
            map.setPosition(440.0f, -200.0f); // absolute position
            break;
        case 1:
            locationText.setString("Castle Halls");
            if (this->init == false) {
                mapTexture.loadFromFile("C:/Users/Cole/source/repos/SFML Console Chat/SFML Console Chat/Assets/Sprites/download.jpeg");
                this->init = true;
            }
            map.setTexture(mapTexture);
            break;
        case 2:
            if (this->init == false) {
                mapTexture.loadFromFile("C:/Users/Cole/source/repos/SFML Console Chat/SFML Console Chat/Assets/Sprites/down.jpeg");
                this->init = true;
            }
            map.setTexture(mapTexture);
            break;
        }
    }
    else if (castleEntrance == false && castleDepths == true) {
        this->testTexture = 0;
        switch (testTexture) {
        case 0:
            if (this->init == false) {
                std::cout << "Ping!";
                mapTexture.loadFromFile("C:/Users/Cole/source/repos/SFML Console Chat/SFML Console Chat/Assets/Sprites/castleDepths.jpeg");
                this->init = true;
            }
            break;
        }
    }
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

            buttonMapSprite.setTexture(buttonTexture);
            buttonMapSprite.setPosition(rectMapX +20, rectMapY +20);
            buttonMapSprite.setScale(0.5f, 0.5f);
            this->initMapTexture = true;
        }
        break;
    }
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
    //Sprite Name Text
    spriteText.setFont(font);
    spriteText.setCharacterSize(18);
    spriteText.setPosition(50.0f, 715.0f);
    spriteText.setFillColor(sf::Color::White);
    spriteText.setString("Zin");
}

void Assets::zinSprite()
{
    if (spriteZinNormal == true) {
        texture.loadFromFile("C:/Users/Cole/source/repos/SFML Console Chat/SFML Console Chat/Assets/Sprites/zinsprite.png");
    }
    else if (spriteZinSmug == true) {
        texture.loadFromFile("C:/Users/Cole/source/repos/SFML Console Chat/SFML Console Chat/Assets/Sprites/zinsprite2.png");
    }
    texture.setSmooth(true);
    texture.setRepeated(false);
    sprite.setTexture(texture);
    sprite.setScale(1.5f, 1.5f);
    sprite.setPosition(sf::Vector2f(50.0f, 575.0f)); // absolute position
    
}
