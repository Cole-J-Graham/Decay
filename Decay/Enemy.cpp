#include "Enemy.h"
//Constructors and Deconstructors
Enemy::Enemy(std::string enemyName, int hp, int hpMax, int damage, int defense, 
	float scale, std::string enemyTexture, std::string enemyView, bool turnActive)
{
	//Player Variables
	this->hp = hp;
	this->hpMax = hpMax;
	this->damage = damage;
	this->defense = defense;
	this->enemyName = enemyName;
	this->enemyFrame = 0;
	this->x = 1695;
	this->y = 420;
	
	//Asset Variables
	this->enemyTexture.loadFromFile(enemyTexture);
	this->enemy.setTexture(this->enemyTexture);
	this->enemy.setPosition(this->x, this->y);
	this->enemy.setScale(scale, scale);

	this->turnActive = turnActive;

	//Initialization
	font.loadFromFile("Assets/Fonts/tickerbit font/Tickerbit-regular.otf");
	this->initText();
	this->initButtons();
	this->closeViewer = new ViewerModule(enemyView, scale);
}

Enemy::~Enemy()
{
	//Delete ViewerModule
	delete this->closeViewer;
	//Delete Buttons
	auto ib = this->buttons.begin();
	for (ib = this->buttons.begin(); ib != this->buttons.end(); ++ib) {
		delete ib->second;
	}
}

//Core Functions
void Enemy::update(const sf::Vector2f mousePos)
{
	this->updateText();
	this->updateButtons(mousePos);
	this->closeViewer->update(mousePos);
}

void Enemy::render(sf::RenderTarget* target)
{
	this->closeViewer->render(target);
	target->draw(this->enemy);
	this->renderButtons(target);
	this->renderText(target);
}

void Enemy::enemyTurn(int& combatFrame, const sf::Vector2f mousePos)
{
	this->update(mousePos);
	switch (this->enemyFrame) {
	case 0:
		this->buttons["CONTINUE"]->show();
		this->turnActive = true;
		this->endTurn(combatFrame);
		break;
	}
}

void Enemy::resetTurn()
{
	this->enemyFrame = 0;
}

void Enemy::endTurn(int& combatFrame)
{
	if (this->buttons["CONTINUE"]->isPressed()) {
		this->resetTurn();
		combatFrame++;
		this->buttons["CONTINUE"]->hide();
	}
}

//Button Functions
void Enemy::updateButtons(const sf::Vector2f mousePos)
{
	for (auto& it : this->buttons) { it.second->update(mousePos); }
}

void Enemy::initButtons()
{
	this->buttons["CONTINUE"] = new Button(600, 800, 150, 25, 0.5f, this->font, "Continue",
		sf::Color(70, 70, 70, 70), sf::Color(150, 150, 150, 255), sf::Color(20, 20, 20, 70), true);
}

void Enemy::renderButtons(sf::RenderTarget* target)
{
	for (auto& it : this->buttons) {
		it.second->render(target);
	}
}

//Text Functions
void Enemy::initText()
{
	this->text["HP"] = new Text(this->x, this->y + 200, 16, "HP: " + std::to_string(this->hp) + "/" + std::to_string(this->hpMax),
		sf::Color::White, false);
}

void Enemy::renderText(sf::RenderTarget* target)
{
	for (auto& it : this->text) {
		it.second->render(target);
	}
}

void Enemy::updateText()
{
	this->text["HP"]->setString("HP: " + std::to_string(this->hp) + "/" + std::to_string(this->hpMax));
}