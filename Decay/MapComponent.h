#pragma once
#include"MapViewer.h"
#include"EventModule.h"
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
	void detectNewArea(std::string pos1, std::string pos2,
		std::string pos3, std::string pos4, std::string pos5);

	//Asset Functions
	void loadMap(std::string file_input);
	void renderText(sf::RenderTarget* target);
	void initText();

	//Getters
	int& getMapMaxSize() { return this->mapMaxSize; };

	//Modifier Functions
	void setMapFrame(int& frame) {
		this->texture.loadFromFile(this->mapView->maps.top()->getMapContainer()[frame]);
		this->map.setTexture(this->texture);
	};

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

