#include "TileMap.h"

//Constructors and Destructors
TileMap::TileMap()
{
	//Core Variables
	this->fromX = 0;
	this->fromY = 0;
	this->toX = 0;
	this->toY = 0;
	//map.loadFromFile("Assets/Wallpapers/map.png");
}

TileMap::~TileMap()
{

}

//TileMaps
void TileMap::loadMap(sf::RenderWindow& window)
{

	const int mapSize = 10;
	sf::RectangleShape tileMap[mapSize][mapSize];

	for (int x = 0; x < mapSize; x++) {
		for (int y = 0; y < mapSize; y++) {
			tileMap[x][y].setSize(sf::Vector2f(gridSizeF, gridSizeF));
			tileMap[x][y].setFillColor(sf::Color::White);
			tileMap[x][y].setOutlineThickness(1.f);
			tileMap[x][y].setOutlineColor(sf::Color::Black);
			//tileMap[x][y].setScale(sf::Vector2f(gridSizeF, gridSizeF));
			tileMap[x][y].setPosition(x * gridSizeF + 540.f, y * gridSizeF);
		}
	}
	
	for (int x = 0; x < mapSize; x++) {
		for (int y = 0; y < mapSize; y++) {
			window.draw(tileMap[x][y]);
		}
	}
}