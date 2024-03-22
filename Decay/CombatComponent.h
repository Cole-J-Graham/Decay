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

	//Character Functions
	void initCharacters();
	void updateCharacters(const sf::Vector2f mousePos);
	void renderCharacters(sf::RenderTarget* target);

	//Player Functions
	void playerMoveSelect();
	void strike();
	void cloak();
	void guard();

	//Zin Functions
	void zinMoveSelect();
	void protection();
	void healing();

	//Text Functions
	void initText();
	void renderText(sf::RenderTarget* target = nullptr);
	void updateText(std::string text);

	std::map<std::string, Character*> characters;

private:

	sf::Font font;
	std::string combatMessage;
	std::map<std::string, Text*> text;
};