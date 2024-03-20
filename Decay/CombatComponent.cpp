#include "CombatComponent.h"
//Constructors and Destructors
CombatComponent::CombatComponent()
{
    //Initialization
    font.loadFromFile("Assets/Fonts/tickerbit font/Tickerbit-regular.otf");
    this->player = new Character(100, 100, 10, 10, 25.f, 150.f, 0.2f, playerTexture, true);
    this->initText();
    this->initMoves();
    this->playerTexture = "Assets/Sprites/Player.png";
}

CombatComponent::~CombatComponent()
{
    delete this->player;
    //Delete Text
    auto it = this->text.begin();
    for (it = this->text.begin(); it != this->text.end(); ++it) {
        delete it->second;
    }
}

//Core Functions
void CombatComponent::updateCombat(const sf::Vector2f mousePos)
{
    this->updateMoveSelect();
    this->player->update(mousePos);
}

void CombatComponent::renderCombat(sf::RenderTarget* target)
{
    this->renderText(target);
    this->player->render(target);
}

void CombatComponent::updateMoveSelect()
{
    this->playerMoveSelect();
    this->zinMoveSelect();
}

void CombatComponent::initMoves()
{
    this->player->createMove("Slash", 450, 700, 100, 25, 0.1, font, "Slash",
        sf::Color(70, 70, 70, 70), sf::Color(150, 150, 150, 255), sf::Color(20, 20, 20, 70), false);
}

//Player Functions
void CombatComponent::playerMoveSelect()
{
    if (this->player->getMoves()["Slash"]->isPressed()) {
        this->strike();
    }
}

void CombatComponent::strike()
{
    //hostileHp -= playerDamage() * 2;
    this->updateText("The player slashes at the opponent with all his might!");
}

void CombatComponent::cloak()
{
    this->updateText("The player cloaks himself!");
}

void CombatComponent::guard()
{
    this->updateText("The player prepares to protect Zin...");
}

//Zin Functions
void CombatComponent::zinMoveSelect()
{
    /*if (this->zinCombatButtons()["PROTECTION"]->isPressed()) {
        this->protection();
    }*/
}

void CombatComponent::protection()
{
    //hostileHp -= playerDamage() * 2;
    this->updateText("Zin casts a barrier around you!");
}

void CombatComponent::healing()
{
    this->updateText("Zin casts healing on you!");
}

void CombatComponent::flame()
{
    this->updateText("Zin casts flame!");
}

//Text Functions
void CombatComponent::initText()
{
    this->text["COMBATTEXT"] = new Text(500, 900, 16, this->combatMessage,
        sf::Color::White, false);
}

void CombatComponent::renderText(sf::RenderTarget* target)
{
    for (auto& it : this->text) {
        it.second->render(target);
    }
}

void CombatComponent::updateText(std::string text)
{
    this->text["COMBATTEXT"]->setString(text);
}