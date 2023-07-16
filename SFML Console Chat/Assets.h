#ifndef ASSETS_H
#define ASSETS_H

#include<iostream>
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
	sf::Texture buttonBackTexture;
	sf::Texture textureTravel;

	//Map Textures
	sf::Texture textureMapView;

	//Sprites
	sf::Sprite sprite;
	sf::Sprite box;
	sf::Sprite map;
	sf::Sprite button;
	sf::Sprite buttonBack;
	sf::Sprite spriteTravel;

	//Map Sprites
	sf::Sprite spriteMapView;
	sf::Sprite buttonMapSprite;

	int testTexture;
	int testMap;

	bool castleEntrance;
	bool castleDepths;
	bool movable;
	float rectMapX;
	float rectMapY;

	//Rectangles
	sf::RectangleShape rect;
	sf::RectangleShape buttonMap;
	sf::RectangleShape rectMap;

	//Text
	sf::Font font;
	sf::Text text;
	sf::Text playerText;
	sf::Text combatText;
	sf::Text locationText;
	sf::Text menuText;
	sf::Text spriteText;

	//Sprite Bool
	bool spriteZinNormal;
	bool spriteZinSmug;
	bool buttonClicked;
	bool init;
	bool initMapTexture;
	bool initMap;

	//Constructors & Destructors
	Assets();
	~Assets();

	//Drawing Objects
	void drawObjects();
	void drawMainWindow();
	void drawMap();
	void drawText();
	void zinSprite();

	//Getters and Setters

};

#endif

