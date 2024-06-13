#pragma once
#include"MapViewer.h"
class MapComponent
{
public:
	//Constructors and Destructors
	MapComponent();
	~MapComponent();

	//Core Functions
	void update(sf::Vector2f mousePos);
	void render(sf::RenderTarget* target);

	//Button Functions
	void initButtons();
	void updateButtons(const sf::Vector2f mousePos);
	void renderButtons(sf::RenderTarget* target);

	//Map Functions
	void initMapCores();

private:
	MapViewer* mapView;
	sf::Font font;
	std::ifstream ifs;
	std::string line;

	std::map<std::string, Button*> buttons;
};

