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
	void resetTurn();

	//Stat Functions
	void initStats();

	//Button Functions
	void updateButtons(const sf::Vector2f mousePos);
	void initButtons();
	void renderButtons(sf::RenderTarget* target);

	//Text Functions
	void initText();
	void renderText(sf::RenderTarget* target = nullptr);
	void updateText();

	//Sprite Functions
	void initSprite();
	void renderSprite(sf::RenderTarget* target = nullptr);

	//Getters
	int& playerHp() { return this->hp; };
	int& playerHpMax() { return this->hpMax; };
	int& playerDamage() { return this->damage; };
	int& playerDefense() { return this->defense; };

	int& getPlayerFrame() { return this->playerFrame; };

	std::map<std::string, Button*>& playerCombatButtons() { return this->combatButtons; };

private:
	//Player Variables
	int hp;
	int hpMax;
	int damage;
	int defense;

	int playerFrame;

	//Player Assets
	StatsModule* statsMod;
	sf::Texture playerTexture;
	sf::Sprite player;
	std::map<std::string, Button*> combatButtons;
	std::map<std::string, Text*> text;
	sf::Font font;
};