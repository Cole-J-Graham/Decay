#pragma once
#include<iomanip>
#include<sstream>
#include"Text.h"
#include"Button.h"
#include"ViewerModule.h"
#include"EntityMove.h"

class Enemy
{
public:
	//Constructors and Deconstructors
	Enemy() {};
	Enemy(std::string enemyName, float hp, float hpMax, float damage, float defense,
		float scale, std::string enemyTexture, std::string enemyView, bool turnActive);
	~Enemy();

	//Core Functions
	void update(const sf::Vector2f mousePos);
	void render(sf::RenderTarget* target);

	//Combat Functions
	void enemyTurn(int& combatFrame, const sf::Vector2f mousePos);
	void resetTurn();
	void endTurn(int& combatFrame);
	
	//Button Functions
	void updateButtons(const sf::Vector2f mousePos);
	void initButtons();
	void renderButtons(sf::RenderTarget* target);

	//Move Functions
	void createMove(int key, const std::string& moveMessage, EntityMove::Operation op,
		float& a, float& b, int coolDown) {
		this->moves[key] = std::make_unique<EntityMove>(moveMessage, op, a, b, coolDown);
		//Subtract one to ensure that enemyMoveRangeMax matches the size of the moves container
		this->enemyMoveRangeMax = this->moves.size() - 1;
		std::cout << "ENEMY MOVE RANGE MAX:" << this->enemyMoveRangeMax << "\n";
	}

	void detectMove() {
		std::random_device dev;
		std::mt19937 rng(dev());
		std::uniform_int_distribution<std::mt19937::result_type> enemyMoveRange(this->enemyMoveRangeMin, this->enemyMoveRangeMax);
		
		int selectedMoveIndex = enemyMoveRange(rng);

		auto it = this->moves.find(selectedMoveIndex);
		std::cout << "ENEMY MOVE RANGE:" << enemyMoveRange(rng) << "\n";
		if (it != this->moves.end() && it->second) {
			it->second->useMove();  // Example usage
		}
		this->enemyFrame = 1;
	}

	//Text Functions
	void initText();
	void renderText(sf::RenderTarget* target = nullptr);
	void updateText();
	std::string toStringWithPrecision(double value, int precision = 2);

	//Getters
	bool& isTurnActive() { return this->turnActive; };
	int& getEnemyFrame() { return this->enemyFrame; };
	float& getDamage() { return this->damage; };
	float& getHp() { return this->hp; }

private:

	//Enemy Variables
	float hp;
	float hpMax;
	float damage;
	float defense;
	float rewardModifier;

	//Asset Variables
	int enemyMoveRangeMin;
	int enemyMoveRangeMax;
	int enemyFrame;
	float x;
	float y;
	bool turnActive;

	sf::Texture enemyTexture;
	sf::Sprite enemy;
	std::string enemyName;

	ViewerModule* closeViewer;

	std::map<int, std::unique_ptr<EntityMove>> moves;
	std::map<std::string, Button*> buttons;
	std::map<std::string, Text*> text;
};