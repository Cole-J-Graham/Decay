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
	sf::Sprite buttonCastleEntrance;
	sf::Sprite buttonCastleDepths;

	//Rectangles
	sf::RectangleShape rect;
	sf::RectangleShape rectMap;
	sf::RectangleShape rectStats;
	sf::RectangleShape rectStatsBox;
	sf::RectangleShape rectSpriteBox;

	//Text
	sf::Font font;
	sf::Text text;
	sf::Text playerText;
	sf::Text combatText;
	sf::Text locationText;
	sf::Text menuText;
	sf::Text rectStatsText;
	sf::Text spriteText;

	//Button Text
	sf::Text castleEntranceText;
	sf::Text castleDepthsText;

	//Buttons
	sf::RectangleShape buttonMap;

	//Sounds
	sf::Sound sound;
	sf::Sound blipsound;
	sf::Sound blipmenu;
	sf::Sound soundCom;
	sf::Sound soundWalk;
	sf::Sound soundAngry;

	sf::SoundBuffer buffer;
	sf::SoundBuffer blipbuffer;
	sf::SoundBuffer blipmenubuffer;
	sf::SoundBuffer bufferCom;
	sf::SoundBuffer bufferWalk;
	sf::SoundBuffer bufferAngry;

	sf::Music music;

	//Sprite Bool
	bool spriteZinNormal;
	bool spriteZinSmug;
	bool buttonClicked;
	bool initMapTexture;
	bool initMap;
	bool initStats;
	bool zinInit;
	bool zinInitAngry;
	bool spriteInit;
	int zinTest;

	int testMap;

	bool movable;
	bool movableStatsBox;
	float rectMapX;
	float rectMapY;
	float rectStatsBoxX;
	float rectStatsBoxY;

	//Constructors & Destructors
	Assets();
	~Assets();

	//Drawing Objects
	void drawObjects();
	void drawMainWindow();
	void drawMap();
	void drawStats();
	void drawText();
	void drawSpriteBox();
	void zinSprite();

	//Sound Functions
	void loadSFX();

	//Getters and Setters

};

#endif

