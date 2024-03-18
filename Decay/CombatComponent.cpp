#include "CombatComponent.h"
//Constructors and Destructors
CombatComponent::CombatComponent()
{
    //Initialization
    this->initText();
}

CombatComponent::~CombatComponent()
{
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
}

void CombatComponent::renderCombat(sf::RenderTarget* target)
{
    this->renderPlayer(target);
    this->renderText(target);
}

void CombatComponent::updateMoveSelect()
{
    this->playerMoveSelect();
}

//Player Functions
void CombatComponent::playerMoveSelect()
{
    if (this->playerCombatButtons()["STRIKE"]->isPressed()) {
        this->strike();
    }
    if (this->playerCombatButtons()["CLOAK"]->isPressed()) {
        this->cloak();
    }
    if (this->playerCombatButtons()["GUARD"]->isPressed()) {
        this->guard();
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