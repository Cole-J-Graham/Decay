#pragma once
//Entities
#include"Player.h"
//Assets
#include"text.h"
class CombatComponent : public Player
{
public:
	//Constructors and Destructors
	CombatComponent();
	~CombatComponent();

	//Core Functions
	void updateCombat(const sf::Vector2f mousePos);
	void renderCombat(sf::RenderTarget* target);
	void updateMoveSelect();

	//Player Functions
	void playerMoveSelect();
	void strike();
	void cloak();
	void guard();

	//Text Functions
	void initText();
	void renderText(sf::RenderTarget* target = nullptr);
	void updateText(std::string text);


private:

	std::string combatMessage;
	std::map<std::string, Text*> text;
};