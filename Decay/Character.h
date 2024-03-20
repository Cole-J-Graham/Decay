#pragma once
#include"Button.h"
#include"StatsModule.h"
class Character
{
public:
	//Constructors and Deconstructors
	Character(int hp, int hpMax, int damage, int defense, float x, float y, 
		float scale, std::string& characterTexture, bool turnActive);
	~Character();

	//Core Functions
	void update(const sf::Vector2f mousePos);
	void render(sf::RenderTarget* target);

	//Combat Functions
	void updateButtons(const sf::Vector2f mousePos);
	void createMove(std::string key, float x, float y, float width, float height,
		float clicktime, sf::Font font, std::string text, sf::Color idleColor, sf::Color hoverColor,
		sf::Color activeColor, bool hidden);
	void renderMoveButtons(sf::RenderTarget* target);
	void playerTurn(int& combatFrame);
	void resetTurn();

	//Text Functions
	void initText();
	void renderText(sf::RenderTarget* target = nullptr);
	void updateText();

	std::map<std::string, Button*> getMoves() { return this->moveButtons; };

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
	bool turnActive;
	sf::Texture characterTexture;
	sf::Sprite character;
	std::map<std::string, Button*> moveButtons;
	std::map<std::string, Text*> text;
	sf::Font font;
};

