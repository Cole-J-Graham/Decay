#include "CombatState.h"
//Constructors and Destructors
CombatState::CombatState(sf::RenderWindow* window, std::stack<State*>* states)
    : State(window, states)
{
    //Initialization
    this->initRects();
}

CombatState::~CombatState()
{
    //Delete Rectangles
    auto ir = this->rectangles.begin();
    for (ir = this->rectangles.begin(); ir != this->rectangles.end(); ++ir) {
        delete ir->second;
    }
}

//Core Functions
void CombatState::combatLoop(const sf::Vector2f mousePos)
{
    switch (this->combatFrame) {
    case 0:
        //Players Turn
        this->characters["PLAYER"]->characterTurn(this->combatFrame, mousePos);
        break;
    case 1:
        //Zin's Turn
        this->characters["ZIN"]->characterTurn(this->combatFrame, mousePos);
        break;
    case 2:
        //Thom's turn
        this->characters["THOM"]->characterTurn(this->combatFrame, mousePos);
        break;
    case 3:
        //Hostiles Turn
        break;
    }
    std::cout << this->combatFrame << "\n";
}

//State Functions
void CombatState::updateKeybinds()
{

}

void CombatState::update()
{
    this->updateMousePositions();
    this->updateCombat(this->getMousePosView());
    this->combatLoop(this->getMousePosView());
}

void CombatState::render(sf::RenderTarget* target)
{
    this->renderRects(target);
    this->renderText(target);
    this->renderCombat(target);
}

//Rectangle Functions
void CombatState::initRects()
{
    this->rectangles["PLAYERBORDER"] = new Rectangle(25, 150, 200, 200, sf::Color::Transparent,
        sf::Color::White, 1.f, false);
    this->rectangles["ZINBORDER"] = new Rectangle(25, 420, 200, 200, sf::Color::Transparent,
        sf::Color::White, 1.f, false);
    this->rectangles["THOMBORDER"] = new Rectangle(25, 690, 200, 200, sf::Color::Transparent,
        sf::Color::White, 1.f, false);
    this->rectangles["HOSTILEBORDER"] = new Rectangle(1695, 420, 200, 200, sf::Color::Transparent,
        sf::Color::White, 1.f, false);
    this->rectangles["COMBATCONSOLE"] = new Rectangle(350, 830, 1250, 175, sf::Color::Transparent,
        sf::Color::White, 1.f, false);
}

void CombatState::renderRects(sf::RenderTarget* target)
{
    for (auto& it : this->rectangles) {
        it.second->render(target);
    }
}