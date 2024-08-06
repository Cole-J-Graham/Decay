#pragma once
#include"Text.h"
#include"Button.h"
#include"ViewerModule.h"
class Enemy
{
public:
	//Constructors and Deconstructors
	Enemy() {};
	Enemy(std::string enemyName, int hp, int hpMax, int damage, int defense, 
		float scale, std::string enemyTexture, std::string enemyView, bool turnActive);
	~Enemy();

	//Core Functions
	void update(const sf::Vector2f mousePos);
	void render(sf::RenderTarget* target);
	void enemyTurn(int& combatFrame, const sf::Vector2f mousePos);
	void resetTurn();
	void endTurn(int& combatFrame);

	//Button Functions
	void updateButtons(const sf::Vector2f mousePos);
	void initButtons();
	void renderButtons(sf::RenderTarget* target);

	//Text Functions
	void initText();
	void renderText(sf::RenderTarget* target = nullptr);
	void updateText();

	//Getters
	int& getEnemyFrame() { return this->enemyFrame; };
	int& getDamage() { return this->damage; };
	int& getHp() { return this->hp; }

private:

	//Player Variables
	int hp;
	int hpMax;
	int damage;
	int defense;

	//Asset Variables
	int enemyFrame;
	float x;
	float y;
	bool turnActive;

	sf::Texture enemyTexture;
	sf::Sprite enemy;
	std::string enemyName;

	ViewerModule* closeViewer;
	std::map<std::string, Button*> buttons;
	std::map<std::string, Text*> text;
};