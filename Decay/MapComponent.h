#pragma once
#include"MapViewer.h"
class MapComponent
{
public:
	//Constructors and Destructors
	MapComponent(std::string file_input);
	~MapComponent();

	//Core Functions
	void update(sf::Vector2f mousePos);
	void render(sf::RenderTarget* target);

	//Map Functions
	void initMapCores();

	//Asset Functions
	void renderText(sf::RenderTarget* target);
	void initText();

private:
	MapViewer* mapView;
	std::string file_input;
	std::ifstream ifs;
	std::string line;

	std::map<std::string, Text*> text;
};

