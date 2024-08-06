#pragma once
#include"Move.h"
#include"StatsManager.h"
#include<stack>
class Character
{
public:
	//Constructors and Deconstructors
	Character(std::string characterName, int hp, int hpMax, int damage, int defense, 
		float x, float y, float scale, std::string characterTexture, bool turnActive);
	~Character();

	//Core Functions
	void update(const sf::Vector2f mousePos);
	void render(sf::RenderTarget* target);
	void characterTurn(int& combatFrame, const sf::Vector2f mousePos);
	void resetTurn();
	void endTurn(int& combatFrame);

	//Button Functions
	void updateButtons(const sf::Vector2f mousePos);
	void initButtons();
	void renderButtons(sf::RenderTarget* target);

	//Move Functions
	void createMove(std::string key, std::string moveMessage, 
		std::string tipMessage, std::string text, Move::Operation op, int& a, int& b);
	void renderMoveButtons(sf::RenderTarget* target);

	//Text Functions
	void initText();
	void renderText(sf::RenderTarget* target = nullptr);
	void updateText();

	//Setters
	int& setHp(int& hp) { this->hp = hp; };

	//Getters
	int& getDamage() { return this->damage; };
	int& getHp() { return this->hp; };
	int& getCoolDown() { return this->coolDown; };

	std::map<std::string, Move*> getMoves()& { return this->moveButtons; };

private:

	//Player Variables
	int hp;
	int hpMax;
	int damage;
	int defense;
	int coolDown;

	//Asset Variables
	int characterFrame;
	float x;
	float y;
	bool turnActive;

	sf::Texture characterTexture;
	sf::Sprite character;
	std::string characterName;
	std::unique_ptr<Rectangle> border;

	std::map<std::string, std::unique_ptr<Button>> buttons;
	std::map<std::string, std::unique_ptr<Text>> text;
	std::map<std::string, Move*> moveButtons;
};

