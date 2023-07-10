#ifndef ASSETS_H
#define ASSETS_H

#include <iostream>
#include<vector>
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

	//Rectangles
	sf::RectangleShape rect;

	//Text
	sf::Font font;
	sf::Text text;
	sf::Text playerText;
	sf::Text combatText;

	//Sprite Bool
	bool spriteZinNormal;
	bool spriteZinSmug;
	bool buttonClicked;
	bool spriteMainWindow;
	bool arrows;

	//Dungeon Frames
	bool castleRoom1;
	bool castleRoom2;

	//Constructors & Destructors
	Assets();
	~Assets();

	//Drawing Objects
	void drawObjects();
	void drawMainWindow();
	void drawText();
	void zinSprite();

	//Getters and Setters

};

#endif

