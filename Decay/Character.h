#pragma once
#include"Move.h"
#include"StatsManager.h"
#include"InteractionManager.h"
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
	void createMove(std::string key, std::string tipMessage, float width, float height,
		float clicktime, std::string text, sf::Color idleColor, sf::Color hoverColor,
		sf::Color activeColor, bool hidden);
	void renderMoveButtons(sf::RenderTarget* target);

	//Text Functions
	void initText();
	void renderText(sf::RenderTarget* target = nullptr);
	void updateText();

	std::map<std::string, Move*> getMoves()& { return this->moveButtons; }

private:

	//Player Variables
	int hp;
	int hpMax;
	int damage;
	int defense;

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

