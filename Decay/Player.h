#pragma once
#include"Button.h"
class Player
{
public:
	//Constructors and Deconstructors
	Player();
	~Player();

	//Core Functions
	void update(const sf::Vector2f mousePos);
	void render(sf::RenderTarget* target);

	//Combat Functions
	void playerTurn();
	void strike(int* hostileHp = nullptr);
	void cloak();
	void guard();

	//Button Functions
	void updateButtons(const sf::Vector2f mousePos);
	void initButtons();
	void renderButtons(sf::RenderTarget* target);

private:
	//Player Variables
	int hp;
	int hpMax;
	int damage;
	int defense;

	int playerFrame;

	//Player Assets
	std::map<std::string, Button*> combatButtons;
	sf::Sprite player;
	std::string combatMessage;
	sf::Font font;
};