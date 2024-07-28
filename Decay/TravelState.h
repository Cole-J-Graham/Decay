#pragma once

//States
#include"State.h"
//Componenets
#include"MapComponent.h"
//Managers
#include"CharacterManager.h"
//States
#include"CombatState.h"
class TravelState : public State
{
public:
	//Constructors and Destructors
	TravelState(sf::RenderWindow* window, std::stack<State*>* states);
	~TravelState();

	//Core Functions
	void update();
	void render(sf::RenderTarget* target = nullptr);

	//Rectangle Functions
	void initRects();
	void renderRects(sf::RenderTarget* target);

private:
	
	std::vector<sf::Texture> mapData;
	std::map<std::string, Rectangle*> rectangles;

	MapComponent* map;
	
};