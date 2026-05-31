#pragma once
#include"MapViewer.h"
class MapComponent
{
public:
	//Constructors and Destructors
	MapComponent();
	~MapComponent();

	//Core Functions
	void update(sf::Vector2f mousePos, bool moveRight, bool moveLeft);
	void render(sf::RenderTarget* target);
	bool mapIsOpen() const;
	bool mapIsSelected() const;

	//Button Functions
	void initButtons();
	void updateButtons(const sf::Vector2f mousePos);
	void renderButtons(sf::RenderTarget* target);

	//Map Functions
	void initMapCores();
	void showMapButton() { this->mapView->showOpenMapButton(); };
	void hideMapButton() { this->mapView->hideOpenMapButton(); };

	//Getters
	std::string getCurrentAreaId() const;
	bool rollEvent() { return this->mapView->rollEventForCurrentMap(); };
	bool eventIsActive() const { return this->mapView->currentEventIsActive(); };

private:
	MapViewer* mapView;
	std::ifstream ifs;
	std::string line;

	std::map<std::string, Button*> buttons;
};

