#include "Assets.h"

//Constructors & Destructors
Assets::Assets()
{
    //Sprite Bool
    this->sprite1 = false;
    this->sprite2 = false;
    this->travelsprite = false;
    this->buttonClicked = false;
}

Assets::~Assets()
{

}

//Drawing Objects
void Assets::drawObjects()
{
    this->zinSprite();
    this->drawMap();
    this->drawOutputBox();
    this->drawCombatText();
    this->travelSprite();
}

void Assets::drawOutputBox()
{
    font.loadFromFile("C:/Users/Cole/source/repos/SFML Console Chat/SFML Console Chat/Assets/Fonts/tickerbit font/Tickerbit-regular.otf");
    text.setFont(font);
    text.setCharacterSize(18);
    text.setFillColor(sf::Color(sf::Color::White));
    text.setPosition(0.0f, 835.0f);

    boxTexture.loadFromFile("C:/Users/Cole/source/repos/SFML Console Chat/SFML Console Chat/Assets/Sprites/menu.png");
    box.setTexture(boxTexture);
    box.setPosition(0.0f, 825.0f);
}

void Assets::drawCombatText()
{
    font.loadFromFile("C:/Users/Cole/source/repos/SFML Console Chat/SFML Console Chat/Assets/Fonts/tickerbit font/Tickerbit-regular.otf");
    combatText.setFont(font);
    combatText.setCharacterSize(18);
    combatText.setFillColor(sf::Color(sf::Color::White));
    combatText.setPosition(500.0f, 835.0f);
}

void Assets::drawMap()
{
    mapTexture.loadFromFile("C:/Users/Cole/source/repos/SFML Console Chat/SFML Console Chat/Assets/Sprites/map2.jpeg");
    map.setTexture(mapTexture);
    map.setPosition(0.0f, 0.0f);

    buttonTexture.loadFromFile("C:/Users/Cole/source/repos/SFML Console Chat/SFML Console Chat/Assets/Sprites/buttonsolidfix.png");
    button.setTexture(buttonTexture);
    button.setPosition(40.0f, 100.0f);
    if (buttonClicked == true) {
        buttonTexture.loadFromFile("C:/Users/Cole/source/repos/SFML Console Chat/SFML Console Chat/Assets/Sprites/buttonhoverfix.png");
        button.setTexture(buttonTexture);
        button.setPosition(40.0f, 100.0f);
    }
}

void Assets::zinSprite()
{
    if (sprite1 == true) {
        texture.loadFromFile("C:/Users/Cole/source/repos/SFML Console Chat/SFML Console Chat/Assets/Sprites/zinsprite.png");
    }
    else if (sprite2 == true) {
        texture.loadFromFile("C:/Users/Cole/source/repos/SFML Console Chat/SFML Console Chat/Assets/Sprites/zinsprite2.png");
    }
    //texture.update(window);
    texture.setSmooth(true);
    texture.setRepeated(false);
    sprite.setTexture(texture);
    sprite.setScale(1.5f, 1.5f);
    sprite.setPosition(sf::Vector2f(50.0f, 650.0f)); // absolute position
}

void Assets::travelSprite()
{
    if (travelsprite == true) {
        textureTravel.loadFromFile("C:/Users/Cole/source/repos/SFML Console Chat/SFML Console Chat/Assets/Sprites/castleentrance.jpeg");
        //textureTravel.update(window);
        textureTravel.setSmooth(true);
        textureTravel.setRepeated(false);
        spriteTravel.setTexture(textureTravel);
        spriteTravel.setScale(1.0f, 1.0f);
        spriteTravel.setPosition(sf::Vector2f(440.0f, -191.0f)); // absolute position
    }
}
