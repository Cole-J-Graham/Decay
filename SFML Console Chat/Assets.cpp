#include "Assets.h"

//Constructors & Destructors
Assets::Assets()
{
    //Sprite Bool
    this->spriteZinNormal = false;
    this->spriteZinSmug = false;
    this->spriteMainWindow = true;
    this->buttonClicked = false;

    this->castleRoom1 = false;
    this->castleRoom2 = false;
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
}

void Assets::drawMainWindow()
{
    //Draw Menu Box
    rect.setFillColor(sf::Color::Black);
    rect.setPosition(0.0f, 825.0f);
    rect.setSize(sf::Vector2f(1920.0f, 825.0f));
    rect.setOutlineColor(sf::Color::White);
    rect.setOutlineThickness(1.0f);
    //Draw Button
    buttonTexture.loadFromFile("C:/Users/Cole/source/repos/SFML Console Chat/SFML Console Chat/Assets/Sprites/buttonsolidfix.png");
    button.setTexture(buttonTexture);
    button.setPosition(1400.0f, 765.0f);
    //Draw Back Button
    buttonBackTexture.loadFromFile("C:/Users/Cole/source/repos/SFML Console Chat/SFML Console Chat/Assets/Sprites/buttonsolidfix.png");
    buttonBack.setTexture(buttonBackTexture);
    buttonBack.setPosition(445.0f, 765.0f);
    switch (testTexture) {
    case 0:
        locationText.setString("Castle Entrance");
        //Draw Map Sprite
        mapTexture.loadFromFile("C:/Users/Cole/source/repos/SFML Console Chat/SFML Console Chat/Assets/Sprites/castleentrance.jpeg");
        map.setTexture(mapTexture);
        map.setPosition(440.0f, -200.0f); // absolute position
        break;
    case 1:
        locationText.setString("Castle Halls");
        mapTexture.loadFromFile("C:/Users/Cole/source/repos/SFML Console Chat/SFML Console Chat/Assets/Sprites/download.jpeg");
        map.setTexture(mapTexture);
        break;
    case 2:
        mapTexture.loadFromFile("C:/Users/Cole/source/repos/SFML Console Chat/SFML Console Chat/Assets/Sprites/down.jpeg");
        map.setTexture(mapTexture);
        break;
    }
   /*if (spriteMainWindow == true && castleRoom1 == false) {
       locationText.setString("Castle Entrance");
        //Draw Map Sprite
        mapTexture.loadFromFile("C:/Users/Cole/source/repos/SFML Console Chat/SFML Console Chat/Assets/Sprites/castleentrance.jpeg");
        map.setTexture(mapTexture);
        map.setPosition(440.0f, -200.0f); // absolute position
        //Draw Menu Box
        rect.setFillColor(sf::Color::Black);
        rect.setPosition(0.0f, 825.0f);
        rect.setSize(sf::Vector2f(1920.0f, 825.0f));
        rect.setOutlineColor(sf::Color::White);
        rect.setOutlineThickness(1.0f);
        //Draw Button
        buttonTexture.loadFromFile("C:/Users/Cole/source/repos/SFML Console Chat/SFML Console Chat/Assets/Sprites/buttonsolidfix.png");
        button.setTexture(buttonTexture);
        button.setPosition(1400.0f, 765.0f);
        //Draw Back Button
        buttonBackTexture.loadFromFile("C:/Users/Cole/source/repos/SFML Console Chat/SFML Console Chat/Assets/Sprites/buttonsolidfix.png");
        buttonBack.setTexture(buttonBackTexture);
        buttonBack.setPosition(445.0f, 765.0f);
   }
   else if (spriteMainWindow == false && castleRoom1 == true) {
        locationText.setString("Castle Halls");
        mapTexture.loadFromFile("C:/Users/Cole/source/repos/SFML Console Chat/SFML Console Chat/Assets/Sprites/download.jpeg");
        map.setTexture(mapTexture);
   }
   else if (castleRoom1 == false && castleRoom2 == true) {
       mapTexture.loadFromFile("C:/Users/Cole/source/repos/SFML Console Chat/SFML Console Chat/Assets/Sprites/down.jpeg");
       map.setTexture(mapTexture);
   }*/
}

void Assets::drawCastle()
{
    locationText.setString("Castle Halls");
    mapTexture.loadFromFile("C:/Users/Cole/source/repos/SFML Console Chat/SFML Console Chat/Assets/Sprites/download.jpeg");
    map.setTexture(mapTexture);
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
    sprite.setPosition(sf::Vector2f(50.0f, 650.0f)); // absolute position
    
}
