#include "CombatComponent.h"
//Constructors and Destructors
CombatComponent::CombatComponent()
{
    //Initialization
    font.loadFromFile("Assets/Fonts/tickerbit font/Tickerbit-regular.otf");
    this->initCharacters();
    this->initText();
    this->initMoves();
}

CombatComponent::~CombatComponent()
{
    //Delete Characters
    auto ic = this->characters.begin();
    for (ic = this->characters.begin(); ic != this->characters.end(); ++ic) {
        delete ic->second;
    }
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
    this->renderText(target);
    this->renderCharacters(target);
}

void CombatComponent::updateMoveSelect()
{
    this->playerMoveSelect();
    this->zinMoveSelect();
}

void CombatComponent::initMoves()
{
    this->characters["PLAYER"]->createMove("Slash", "Players basic attack", 100, 25, 0.1, font, "Slash",
        sf::Color(70, 70, 70, 70), sf::Color(150, 150, 150, 255), sf::Color(20, 20, 20, 70), false);
    this->characters["PLAYER"]->createMove("Cloak", "Players basic cloak", 100, 25, 0.1, font, "Cloak",
        sf::Color(70, 70, 70, 70), sf::Color(150, 150, 150, 255), sf::Color(20, 20, 20, 70), false);

    this->characters["ZIN"]->createMove("Protection", "Zin's basic barrier", 100, 25, 0.1, font, "Protection",
        sf::Color(70, 70, 70, 70), sf::Color(150, 150, 150, 255), sf::Color(20, 20, 20, 70), false);
    this->characters["ZIN"]->createMove("Healing", "Zin's basic healing", 100, 25, 0.1, font, "Healing",
        sf::Color(70, 70, 70, 70), sf::Color(150, 150, 150, 255), sf::Color(20, 20, 20, 70), false);

    this->characters["THOM"]->createMove("Harden", "Thom's defense boost", 100, 25, 0.1, font, "Harden",
        sf::Color(70, 70, 70, 70), sf::Color(150, 150, 150, 255), sf::Color(20, 20, 20, 70), false);
    this->characters["THOM"]->createMove("Spiked", "Thom's thorn passive ability", 100, 25, 0.1, font, "Spiked",
        sf::Color(70, 70, 70, 70), sf::Color(150, 150, 150, 255), sf::Color(20, 20, 20, 70), false);
}

//Character Functions
void CombatComponent::initCharacters()
{
    this->characters["PLAYER"] = new Character("Player", 100, 100, 10, 10, 25.f, 150.f, 0.319f, "Assets/Sprites/Player.png", true);
    this->characters["ZIN"] = new Character("Zin", 100, 100, 10, 10, 25.f, 420.f, 0.066f, "Assets/Sprites/zinSprite.png", false);
    this->characters["THOM"] = new Character("Thom", 100, 100, 10, 10, 25.f, 690.f, 0.625f, "Assets/Sprites/thomNormal.png", false);
}

void CombatComponent::updateCharacters(const sf::Vector2f mousePos)
{
    for (auto& it : this->characters) {
        it.second->update(mousePos);
    }
}

void CombatComponent::renderCharacters(sf::RenderTarget* target)
{
    for (auto& it : this->characters) {
        it.second->render(target);
    }
}

//Player Functions
void CombatComponent::playerMoveSelect()
{
    if (this->characters["PLAYER"]->getMoves()["Slash"]->isPressed()) {
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
    if (this->characters["ZIN"]->getMoves()["Protection"]->isPressed()) {
        this->protection();
    }
    if (this->characters["ZIN"]->getMoves()["Healing"]->isPressed()) {
        this->healing();
    }
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

//Text Functions
void CombatComponent::initText()
{
    this->text["COMBATTEXT"] = new Text(355, 835, 16, this->combatMessage,
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