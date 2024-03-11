#pragma once
//States
#include"State.h"
//Assets
#include"Rectangle.h"
#include"Button.h"
//Entities
#include"Player.h"
class CombatState : public State
{
public:
	//Constructors and Destructors
	CombatState(sf::RenderWindow* window, std::stack<State*>* states);
	~CombatState();

	//Core Functions
	void combatLoop();

	//State Functions
	void updateKeybinds();
	void update();
	void render(sf::RenderTarget* target = nullptr);

	//Rectangle Functions
	void initRects();
	void renderRects(sf::RenderTarget* target = nullptr);

private:
	int combatFrame;
	Player* player;
	std::map<std::string, Rectangle*> rectangles;
};