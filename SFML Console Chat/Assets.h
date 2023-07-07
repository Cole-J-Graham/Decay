#ifndef ASSETS_H
#define ASSETS_H

#include<SFML/Graphics.hpp>
#include<SFML/Graphics/Text.hpp>
#include<SFML/Audio.hpp>

class Assets
{
private:

public:
	//Textures
	sf::Texture texture;
	sf::Texture combatTexture;
	sf::Texture boxTexture;
	sf::Texture mapTexture;
	sf::Texture buttonTexture;
	sf::Texture textureTravel;

	//Sprites
	sf::Sprite sprite;
	sf::Sprite box;
	sf::Sprite map;
	sf::Sprite button;
	sf::Sprite spriteTravel;

	//Text
	sf::Font font;
	sf::Text text;
	sf::Text playerText;
	sf::Text combatText;

	//Sprite Bool
	bool sprite1;
	bool sprite2;
	bool buttonClicked;
	bool travelsprite;

	//Constructors & Destructors
	Assets();
	~Assets();

	//Drawing Objects
	void drawObjects();
	void drawOutputBox();
	void drawCombatText();
	void drawMap();
	void zinSprite();
	void travelSprite();

	//Getters and Setters

};

#endif

