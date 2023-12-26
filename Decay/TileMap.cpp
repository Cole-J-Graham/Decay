#include "TileMap.h"

//Constructors and Destructors
TileMap::TileMap()
{
	//Core Variables
	this->gridSizeF = 64.f;
	this->col = 13;
	this->row = 13;

	//map.loadFromFile("Assets/Wallpapers/map.png");
	this->forestTile1.loadFromFile("Assets/SpriteSheets/Sprite-0001.png");
	this->forestTile2.loadFromFile("Assets/SpriteSheets/Sprite-0002.png");
	this->forestTile3.loadFromFile("Assets/SpriteSheets/Sprite-0003.png");
	this->forestTile4.loadFromFile("Assets/SpriteSheets/Sprite-0004.png");
}

TileMap::~TileMap()
{

}

void TileMap::loadingOnTile(std::vector<std::vector<sf::Sprite>>& inSprite, std::vector<std::vector<int>> tiles, sf::Texture& tex1, sf::Texture& tex2, sf::Texture& tex3, sf::Texture& tex4)
{
	//Draw a specific set texture tile based on which input is recieved from a tilemap vector
	for (int x = 0; x < col; x++) {
		for (int y = 0; y < row; y++) {
			if (tiles[x][y] == 0) {
				inSprite[x][y].setTexture(tex1);
			}
			else if (tiles[x][y] == 1){
				inSprite[x][y].setTexture(tex2);
			}
			else if (tiles[x][y] == 2) {
				inSprite[x][y].setTexture(tex3);
			}
			else if (tiles[x][y] == 3) {
				inSprite[x][y].setTexture(tex4);
			}
		}
	}
}

//TileMaps
void TileMap::loadMap(sf::RenderWindow& window)
{
	//Create Level
	std::vector<std::vector<int>> level{
		{1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{1, 1, 1, 1, 0, 0, 0, 0, 2, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},	
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	};

	//Instantiate a 2d vector
	std::vector<std::vector<sf::Sprite>> tileMap;
	//Resize the 2d vector to rows and columns of a specific size
	tileMap.resize(row, std::vector<sf::Sprite>(col));
	//Set attributes for the 2d vector
	for (int x = 0; x < col; x++) {
		for (int y = 0; y < row; y++) {
			tileMap[x][y].setScale(sf::Vector2f(0.4, 0.4));
			tileMap[x][y].setPosition(x * gridSizeF + 440, y * gridSizeF);
			loadingOnTile(tileMap, level, forestTile1, forestTile2, forestTile3, forestTile4);
		}
	}
	//Draw the 2d vector aka tilemap
	for (int x = 0; x < col; x++) {
		for (int y = 0; y < row; y++) {
			window.draw(tileMap[x][y]);
			//Basic player collision detection
			playerDetection.setSize(sf::Vector2f(60.f, 60.f));
			playerDetection.setFillColor(sf::Color::Transparent);
			playerDetection.setPosition(getXPos(), getYPos());
			if (playerDetection.getGlobalBounds().intersects(tileMap[x][y].getGlobalBounds())) {
				std::cout << "Zin colliding..." << "\n";
			}
		}
	}
}