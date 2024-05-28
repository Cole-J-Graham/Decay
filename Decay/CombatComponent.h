#pragma once
#include<random>
//Entities
#include"CharacterManager.h"
#include"Enemy.h"
class CombatComponent
{
public:
	//Constructors and Destructors
	CombatComponent();
	~CombatComponent();

	//Core Functions
	void updateCombat(const sf::Vector2f mousePos);
	void renderCombat(sf::RenderTarget* target);
	void updateMoveSelect();
	void initMoves();

	//Character Functions
	void renderCharacters(sf::RenderTarget* target);

	//Player Functions
	void playerMoveSelect();
	void strike();
	void cloak();
	void guard();

	//Zin Functions
	void zinMoveSelect();
	void protection();
	void healing();

	//Enemy Functions
	void initEnemies();
	void renderEnemies(sf::RenderTarget* target);
	void enemyPool();

	//Text Functions
	void initText();
	void renderText(sf::RenderTarget* target = nullptr);
	void updateText(std::string text);
	void setEnemyId(std::string text);

	//Getters
	const std::string& getEnemyId() { return this->enemyId; };

	std::map<std::string, Enemy*> enemies;

private:

	sf::Font font;
	std::string combatMessage;
	std::map<std::string, Text*> text;
	std::string enemyId;

	int enemyRangeMin;
	int enemyRangeMax;
};