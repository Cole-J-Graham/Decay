#pragma once
#include"Text.h"
#include"Button.h"
class Enemy
{
public:
	//Constructors and Deconstructors
	Enemy() {};
	Enemy(std::string enemyName, int hp, int hpMax, int damage, 
		int defense, float scale, std::string enemyTexture, bool turnActive);
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

	int& getEnemyFrame() { return this->enemyFrame; };

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

	std::map<std::string, Button*> buttons;
	std::map<std::string, Text*> text;

	sf::Font font;
};