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
	bool detectEnemyDeath();
	void resetCombat();

	//State Functions
	void updateKeybinds();
	void update();
	void render(sf::RenderTarget* target = nullptr);

	//Character Functions
	void resetAllCharacterTurns();

	//Rectangle Functions
	void initRects();
	void updateRects(const sf::Vector2f mousePos);
	void renderRects(sf::RenderTarget* target = nullptr);

private:

	bool stateEnd;
	int combatFrame;
	std::map<std::string, Rectangle*> rectangles;
};