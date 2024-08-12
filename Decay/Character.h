#pragma once
#include"Move.h"
#include"StatsManager.h"
#include<stack>
class Character
{
public:
	//Constructors and Deconstructors
	Character(std::string characterName, float hp, float hpMax, float damage, float defense,
		float healing, float x, float y, float scale, std::string characterTexture, bool turnActive);
	~Character();

	//Core Functions
	void update(const sf::Vector2f mousePos);
	void render(sf::RenderTarget* target);
	void characterTurn(int& combatFrame, const sf::Vector2f mousePos);
	void resetTurn();
	void endTurn(int& combatFrame);

	//Button Functions
	void updateButtons(const sf::Vector2f mousePos);
	void updateMoveButtons(const sf::Vector2f mousePos);
	void initButtons();
	void renderButtons(sf::RenderTarget* target);

	//Move Functions
	void createMove(std::string key, std::string moveMessage, 
		std::string tipMessage, std::string text, Move::Operation op, float& a, float& b, int coolDown);
	void renderMoveButtons(sf::RenderTarget* target);

	//Text Functions
	void initText();
	void renderText(sf::RenderTarget* target = nullptr);
	void updateText();

	//Setters
	float& setHp(float& hp) { this->hp = hp; };
	void resetCharacterFrame() { this->characterFrame = 0; };
	
	//Getters
	float& getDamage() { return this->damage; };
	float& getHp() { return this->hp; };
	float& getDefense() { return this->defense; };
	float& getHealing() { return this->healing; };
	int& getCoolDown() { return this->coolDown; };
	int& getCharacterFrame() { return this->characterFrame; };
	bool& isTurnActive() { return this->turnActive; };

	std::map<std::string, Move*> getMoves()& { return this->moveButtons; };

private:

	//Consts
	const int BORDER_WIDTH = 200;
	const int BORDER_HEIGHT = 200;
	const int BUTTON_X_OFFSET = 350;
	const int BUTTON_Y_OFFSET = 25;

	//Player Variables
	float hp;
	float hpMax;
	float damage;
	float defense;
	float healing;
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

