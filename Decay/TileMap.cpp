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
		}
	}
}

void TileMap::loadCollisionMap(sf::RenderWindow& window)
{
	//Create Collisions
	std::vector<std::vector<int>> collisionData{
		{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
		{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
		{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
		{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
		{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
		{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
		{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
		{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
		{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
		{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
		{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
		{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
		{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
	};

	//Resize the 2d vector to rows and columns of a specific size
	collisionMap.resize(row, std::vector<sf::RectangleShape>(col));
	//Set attributes for the 2d vector
	for (int x = 0; x < col; x++) {
		for (int y = 0; y < row; y++) {
			collisionMap[x][y].setScale(sf::Vector2f(0.4, 0.4));
			collisionMap[x][y].setPosition(x * gridSizeF + 440, y * gridSizeF);
			//loadingOnTile(tileMap, level, forestTile1, forestTile2, forestTile3, forestTile4);
		}
	}
	for (int x = 0; x < col; x++) {
		for (int y = 0; y < row; y++) {
			collisionMap[x][y].setSize(sf::Vector2f(155.f, 155.f));
			if (collisionData[x][y] == 0) {
				collisionMap[x][y].setFillColor(sf::Color::Transparent);
			}
			else if (collisionData[x][y] == 1) {
				collisionMap[x][y].setFillColor(sf::Color::Blue);
			}
		}
	}
	for (int x = 0; x < collisionMap.size(); x++) {
		for (int y = 0; y < collisionMap.size(); y++) {
			if (zinPixelSprite.getGlobalBounds().intersects(collisionMap[x][y].getGlobalBounds())) {
				if (collisionData[x][y] == 1) {
					sf::FloatRect playerBounds = zinPixelSprite.getGlobalBounds();
					sf::FloatRect wallBounds = collisionMap[x][y].getGlobalBounds();
					if (playerBounds.left < wallBounds.left
						&& playerBounds.left + playerBounds.width < wallBounds.left + wallBounds.width 
						&& playerBounds.top < wallBounds.top + wallBounds.height 
						&& playerBounds.top + playerBounds.height > wallBounds.top) 
					{
						//Right Collision
						std::cout << "Right" << "\n";
						velocity.x = 0.f;
						zinPixelSprite.setPosition(wallBounds.left - playerBounds.width, playerBounds.top);
					}
					else if (playerBounds.top > wallBounds.top
						&& playerBounds.top + playerBounds.height > wallBounds.top + wallBounds.height
						&& playerBounds.left < wallBounds.left + wallBounds.width
						&& playerBounds.left + playerBounds.width > wallBounds.left)
					{
						//Top Collision
						std::cout << "Top" << "\n";
						velocity.y = 0.f;
						zinPixelSprite.setPosition(playerBounds.left, wallBounds.top + wallBounds.height);
					}
					else if (playerBounds.top < wallBounds.top 
						&& playerBounds.top + playerBounds.height < wallBounds.top + wallBounds.height
						&& playerBounds.left < wallBounds.left + wallBounds.width 
						&& playerBounds.left + playerBounds.width > wallBounds.left) 
					{
						//Bottom Collision
						std::cout << "Bottom" << "\n";
						velocity.y = 0.f;
						zinPixelSprite.setPosition(playerBounds.left, wallBounds.top - playerBounds.height);
					}
					else if (playerBounds.left > wallBounds.left
						&& playerBounds.left + playerBounds.width > wallBounds.left + wallBounds.width
						&& playerBounds.top < wallBounds.top + wallBounds.height
						&& playerBounds.top + playerBounds.height > wallBounds.top)
					{
						//Left Collision
						std::cout << "Left" << "\n";
						velocity.x = 0.f;
						zinPixelSprite.setPosition(wallBounds.left + wallBounds.width, playerBounds.top);
					}
					
				}
			}
		}
	}
	//Draw the 2d vector aka tilemap
	for (int x = 0; x < col; x++) {
		for (int y = 0; y < row; y++) {
			window.draw(collisionMap[x][y]);
		}
	}
}