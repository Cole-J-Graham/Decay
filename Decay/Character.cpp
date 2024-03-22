#include "Character.h"
//Constructors and Deconstructors
Character::Character(std::string characterName, int hp, int hpMax, int damage, int defense, 
	float x, float y, float scale, std::string characterTexture, bool turnActive)
{
	//Player Variables
	this->hp = hp;
	this->hpMax = hpMax;
	this->damage = damage;
	this->defense = defense;
	this->characterFrame = 0;
	this->x = x;
	this->y = y;

	//Asset Variables
	this->characterTexture.loadFromFile(characterTexture);
	this->character.setTexture(this->characterTexture);
	this->character.setPosition(x, y);
	this->character.setScale(scale, scale);
	this->characterName = characterName;
	this->xMove = 350;
	this->yMove = 800;
	this->endActive = false;

	this->turnActive = turnActive;

	//Initialization
	font.loadFromFile("Assets/Fonts/tickerbit font/Tickerbit-regular.otf");
	this->initText();
	this->initButtons();
}

Character::~Character()
{
	//Delete Buttons
	auto ib = this->buttons.begin();
	for (ib = this->buttons.begin(); ib != this->buttons.end(); ++ib) {
		delete ib->second;
	}
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
	this->renderButtons(target);
	this->renderText(target);

	//Render all turn combat assets
	if (this->turnActive) { 
		this->renderMoveButtons(target); 
	}
}

void Character::characterTurn(int& combatFrame, const sf::Vector2f mousePos)
{
	this->update(mousePos);
	switch (this->characterFrame) {
	case 0:
		this->turnActive = true;
		for (auto& it : this->moveButtons) { it.second->show(); }
		break;
	case 1:
		for (auto& it : this->moveButtons) { it.second->hide(); }
		this->endTurn(combatFrame);
		break;
	}
}

void Character::resetTurn()
{
	this->characterFrame = 0;
}

void Character::endTurn(int& combatFrame)
{
	this->buttons["ENDTURN"]->show();
	if (this->buttons["ENDTURN"]->isPressed()) {
		this->resetTurn();
		combatFrame++;
		this->buttons["ENDTURN"]->hide();
		this->endActive = true;
	}
	else {
		this->endActive = false;
	}
}

//Button Functions
void Character::updateButtons(const sf::Vector2f mousePos)
{
	for (auto& it : this->moveButtons) { it.second->update(mousePos); }
	for (auto& it : this->buttons) { it.second->update(mousePos); }

	for (auto& it : this->moveButtons) {
		if (it.second->isPressed()) {
			this->characterFrame++;
		}
	}
}

void Character::initButtons()
{
	this->buttons["ENDTURN"] = new Button(1450, 800, 150, 25, 0.5f, this->font, "End " + this->characterName + "'s Turn",
		sf::Color(70, 70, 70, 70), sf::Color(150, 150, 150, 255), sf::Color(20, 20, 20, 70), true);
}

void Character::renderButtons(sf::RenderTarget* target)
{
	for (auto& it : this->buttons) {
		it.second->render(target);
	}
}

//Move Functions
void Character::createMove(std::string key, float width, float height, 
	float clicktime, sf::Font font, std::string text, sf::Color idleColor, sf::Color hoverColor, 
	sf::Color activeColor, bool hidden)
{
	this->moveButtons[key] = new Button(this->xMove, this->yMove, width, height, clicktime, font, text, idleColor, 
		hoverColor, activeColor, hidden);
}

void Character::renderMoveButtons(sf::RenderTarget* target)
{
	int y = this->yMove;
	for (auto& it : this->moveButtons) {
		it.second->render(target);
		it.second->setPosition(this->xMove, y -= 25);
	}
}

//Text Functions
void Character::initText()
{
	this->text["HP"] = new Text(this->x, this->y + 200, 16, "HP: " + std::to_string(this->hp) + "/" + std::to_string(this->hpMax),
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