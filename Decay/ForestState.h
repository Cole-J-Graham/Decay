#pragma once
//States
#include"State.h"
//Componenets
#include"MapComponent.h"
#include"CharacterManager.h"
class ForestState : public State
{
public:
	//Constructors and Destructors
	ForestState(sf::RenderWindow* window, std::stack<State*>* states);
	~ForestState();

	//State Functions
	void updateKeybinds();
	void update();
	void render(sf::RenderTarget* target = nullptr);
	void loadMapData(std::string input);

private:
	
	std::vector<sf::Texture> mapData;

	MapComponent* map;
	
};