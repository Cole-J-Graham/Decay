#include "Character.h"
//Constructors and Deconstructors
Character::Character(int hp, int hpMax, int damage, int defense, float x, float y, float scale, 
	std::string& characterTexture, bool turnActive)
{
	//Player Variables
	this->hp = hp;
	this->hpMax = hpMax;
	this->damage = damage;
	this->defense = defense;
	this->characterFrame = 0;

	//Asset Variables
	this->characterTexture.loadFromFile(characterTexture);
	this->character.setTexture(this->characterTexture);
	this->character.setPosition(x, y);
	this->character.setScale(scale, scale);

	this->turnActive = turnActive;

	//Initialization
	font.loadFromFile("Assets/Fonts/tickerbit font/Tickerbit-regular.otf");
	this->initText();
}

Character::~Character()
{
	//Delete Combat Buttons
	auto ic = this->moveButtons.begin();
	for (ic = this->moveButtons.begin(); ic != this->moveButtons.end(); ++ic) {
		delete ic->second;
	}
}

//Core Functions
void Character::update(const sf::Vector2f mousePos)
{
	this->updateText();
	this->updateButtons(mousePos);
}

void Character::render(sf::RenderTarget* target)
{
	target->draw(this->character);
	this->renderText(target);

	//Render all turn combat assets
	if (this->turnActive) { 
		this->renderMoveButtons(target); 
	}
}

void Character::playerTurn(int& combatFrame)
{
	switch (this->characterFrame) {
	case 0:
		for (auto& it : this->moveButtons) { it.second->show(); }
		break;
	case 1:
		for (auto& it : this->moveButtons) { it.second->hide(); }
		this->resetTurn();
		combatFrame++;
		break;
	}
}

void Character::resetTurn()
{
	this->characterFrame = 0;
}

//Combat Functions
void Character::updateButtons(const sf::Vector2f mousePos)
{
	for (auto& it : this->moveButtons) { it.second->update(mousePos); }

	for (auto& it : this->moveButtons) {
		if (it.second->isPressed()) {
			this->characterFrame++;
		}
	}
}

void Character::createMove(std::string key, float x, float y, float width, float height, 
	float clicktime, sf::Font font, std::string text, sf::Color idleColor, sf::Color hoverColor, 
	sf::Color activeColor, bool hidden)
{
	this->moveButtons[key] = new Button(x, y, width, height, clicktime, font, text, idleColor, 
		hoverColor, activeColor, hidden);
}

void Character::renderMoveButtons(sf::RenderTarget* target)
{
	for (auto& it : this->moveButtons) {
		it.second->render(target);
	}
}

//Text Functions
void Character::initText()
{
	this->text["HP"] = new Text(this->x, this->y + 201, 16, "HP: " + std::to_string(this->hp) + "/" + std::to_string(this->hpMax),
		sf::Color::White, false);
}

void Character::renderText(sf::RenderTarget* target)
{
	for (auto& it : this->text) {
		it.second->render(target);
	}
}

void Character::updateText()
{
	this->text["HP"]->setString("HP: " + std::to_string(this->hp) + "/" + std::to_string(this->hpMax));
}