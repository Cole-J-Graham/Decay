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
	/*Copy code below to ensure its safety as you continue your work. Attempt to make this similar to the
		code in the SFML tilesheets example utilizing an array to push in specific tiles from a tilesheet.
		Once loading from a specific tilesheet, the tilemaps process will be complete.
		Also attempt to make these functions more reusable and functional for future use as this code is
		extremely reusable.
	*/
	int col = 10;
	int row = 10;

	//Instantiate a 2d vector
	std::vector<std::vector<sf::Sprite>> tileMap;
	//Resize the 2d vector to rows and columns of a specific size
	tileMap.resize(row, std::vector<sf::Sprite>(col));
	//Set attributes for the 2d vector
	for (int x = 0; x < row; x++) {
		for (int y = 0; y < col; y++) {
			tileMap[x][y].setScale(sf::Vector2f(0.05, 0.05));
			tileMap[x][y].setTexture(zinTexture);
			tileMap[x][y].setPosition(x * gridSizeF, y * gridSizeF);
		}
	}
	//Draw the 2d vector aka tilemap
	for (int x = 0; x < row; x++) {
		for (int y = 0; y < col; y++) {
			window.draw(tileMap[x][y]);
		}
	}
}