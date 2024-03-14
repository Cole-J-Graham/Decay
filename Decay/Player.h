#pragma once
#include"Button.h"
#include"StatsModule.h"
class Player
{
public:
	//Constructors and Deconstructors
	Player();
	~Player();

	//Core Functions
	void updatePlayer(const sf::Vector2f mousePos);
	void renderPlayer(sf::RenderTarget* target);

	//Combat Functions
	void playerTurn();

	//Stat Functions
	void initStats();

	//Button Functions
	void updateButtons(const sf::Vector2f mousePos);
	void initButtons();
	void renderButtons(sf::RenderTarget* target);

	//Getters
	int& playerHp() { return this->hp; };
	int& playerHpMax() { return this->hpMax; };
	int& playerDamage() { return this->damage; };
	int& playerDefense() { return this->defense; };

	int& playerFrame() { return this->player_frame; };

	std::map<std::string, Button*>& playerCombatButtons() { return this->combatButtons; };

private:
	//Player Variables
	int hp;
	int hpMax;
	int damage;
	int defense;

	int player_frame;

	//Player Assets
	StatsModule* statsMod;
	std::map<std::string, Button*> combatButtons;
	sf::Sprite player;
	sf::Font font;
};