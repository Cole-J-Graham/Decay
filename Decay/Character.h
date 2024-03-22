#pragma once
#include"Button.h"
#include"StatsModule.h"
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
	void createMove(std::string key, float width, float height,
		float clicktime, sf::Font font, std::string text, sf::Color idleColor, sf::Color hoverColor,
		sf::Color activeColor, bool hidden);
	void renderMoveButtons(sf::RenderTarget* target);

	//Text Functions
	void initText();
	void renderText(sf::RenderTarget* target = nullptr);
	void updateText();

	std::map<std::string, Button*> getMoves() { return this->moveButtons; };
	bool& isEndClicked() { return this->endActive; };

private:
	class Move {
	public:


	private:

	};

	//Player Variables
	int hp;
	int hpMax;
	int damage;
	int defense;

	//Asset Variables
	int characterFrame;
	float x;
	float y;
	float xMove;
	float yMove;
	bool turnActive;
	bool endActive;
	sf::Texture characterTexture;
	sf::Sprite character;
	std::string characterName;
	std::map<std::string, Button*> buttons;
	std::map<std::string, Button*> moveButtons;
	std::map<std::string, Text*> text;
	sf::Font font;
};

