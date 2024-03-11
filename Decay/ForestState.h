#pragma once
//States
#include"State.h"
//Componenets
#include"MapComponent.h"
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

private:
	
	MapComponent* map;
	
};