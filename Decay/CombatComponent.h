#pragma once
#include<memory>
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
	void initMoves();

	//Character Functions
	void renderCharacters(sf::RenderTarget* target);

	//Enemy Functions
	void renderEnemies(sf::RenderTarget* target);
	void enemyPool();

	//Text Functions
	void setEnemyId(std::string text);

	//Getters
	const std::string& getEnemyId() { return this->enemyId; };

	std::map<std::string, Enemy*> enemies;

private:

	std::string enemyId;

	int enemyRangeMin;
	int enemyRangeMax;

	bool movesInitialized;
};