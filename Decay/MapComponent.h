#pragma once
#include"MapViewer.h"
#include"EventModule.h"
#include<fstream>
class MapComponent
{
public:
	//Constructors and Destructors
	MapComponent(std::string file_input);
	~MapComponent();

	//Core Functions
	void update(sf::Vector2f mousePos);
	void render(sf::RenderTarget* target);
	void move();

	//Asset Functions
	void loadMap(std::string file_input);
	void renderText(sf::RenderTarget* target);
	void initText();

	//Getters
	int& getMapMaxSize() { return this->mapMaxSize; };

	//Modifier Functions
	void setMapFrame(int& frame) { this->map.setTexture(this->mapView->maps.top()->getMapContainer()[frame]);};

private:
	EventModule* event;
	MapViewer* mapView;
	std::string file_input;
	std::ifstream ifs;
	std::string line;

	sf::Sprite map;
	sf::Texture texture;
	std::map<std::string, Text*> text;

	sf::Clock clock;
	sf::Time time;
	float move_time;

	int mapFrame;
	int mapMaxSize;
};

