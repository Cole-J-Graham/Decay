#pragma once
#include"Sprites.h"
#include"Animation.h"
#include<SFML/Graphics/Transformable.hpp>

class TileMap : virtual public Sprites, public Animation
{
public:
	//Constructors and Destructors
	TileMap();
	~TileMap();

	//Core Functions
	void loadingOnTile(std::vector<std::vector<sf::Sprite>>& inSprite, std::vector<std::vector<int>> tiles, sf::Texture& tex1, sf::Texture& tex2, sf::Texture& tex3, sf::Texture& tex4);
	void loadMap(sf::RenderWindow& window);
	void loadCollisionMap(sf::RenderWindow& window);

	std::vector<std::vector<sf::Sprite>> tileMap;
	std::vector<std::vector<sf::RectangleShape>> collisionMap;

	sf::Texture forestTile1;
	sf::Texture forestTile2;
	sf::Texture forestTile3;
	sf::Texture forestTile4;
	sf::RectangleShape playerDetection;

	//Core Variables	
	float gridSizeF;
	int col;
	int row;

private:
};

