#pragma once
//States
#include"State.h"
//Modules
#include"CombatComponent.h"
class CombatState : public State, public CombatComponent
{
public:
	//Constructors and Destructors
	CombatState(sf::RenderWindow* window, std::stack<State*>* states);
	~CombatState();

	//Core Functions
	void combatLoop(const sf::Vector2f mousePos);

	//State Functions
	void updateKeybinds();
	void update();
	void render(sf::RenderTarget* target = nullptr);

	//Rectangle Functions
	void initRects();
	void renderRects(sf::RenderTarget* target = nullptr);

private:
	int combatFrame;
	std::map<std::string, Rectangle*> rectangles;
};