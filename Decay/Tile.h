#pragma once
#include<SFML/Graphics.hpp>

class Tile
{
public:
	//Constructors and Destructors
	Tile(sf::Texture* texture_sheet, sf::IntRect texture_rect, bool damaging = false);

	const sf::FloatRect getGlobalBounds() const;

	void update();
	void render(sf::RenderTarget& target);

private:
	sf::Sprite sprite;
	const bool damaging;



};

