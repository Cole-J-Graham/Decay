#pragma once
#include"Rectangle.h"
class ViewerModule
{
public:
	//Constructors and Desctructors
	ViewerModule() {};
	ViewerModule(std::string imageAssetId, float scale);
	~ViewerModule();

	//Core Functions
	void update(const sf::Vector2f mousePos);
	void render(sf::RenderTarget* target);

	//Modifier Functions
	void setView(std::string imageAssetId);

	//Rectangle Functions
	void initRects();
	void updateRects(const sf::Vector2f mousePos);
	void renderRects(sf::RenderTarget* target);


private:

	//Variables
	float x;
	float y;
	float scale;

	//Viewer — texture owned by AssetDatabase's cache, not here
	sf::Sprite image;

	std::map<std::string, Rectangle*> rectangles;
};