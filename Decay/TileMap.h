#pragma once
#include"Sprites.h"
#include"Animation.h"
#include<SFML/Graphics/Transformable.hpp>

class TileMap : public Sprites, public Animation
{
public:
	//Constructors and Destructors
	TileMap();
	~TileMap();

	//Core Functions
	void loadMap(sf::RenderWindow& window);

	//Core Variables
	const int mapSize = 10;
	
	int fromX;
	int fromY;

	int toX;
	int toY;

	float gridSizeF = 82.f;

	int x;
	int y;

private:
};

