#pragma once
//Entities
#include"Character.h"
class CombatComponent
{
public:
	//Constructors and Destructors
	CombatComponent();
	~CombatComponent();

	//Core Functions
	void updateCombat(const sf::Vector2f mousePos);
	void renderCombat(sf::RenderTarget* target);
	void updateMoveSelect();
	void initMoves();

	//Player Functions
	void playerMoveSelect();
	void strike();
	void cloak();
	void guard();

	//Zin Functions
	void zinMoveSelect();
	void protection();
	void healing();
	void flame();

	//Text Functions
	void initText();
	void renderText(sf::RenderTarget* target = nullptr);
	void updateText(std::string text);


private:
	Character* player;
	Character* zin;
	sf::Font font;
	std::string playerTexture;
	std::string combatMessage;
	std::map<std::string, Text*> text;
};