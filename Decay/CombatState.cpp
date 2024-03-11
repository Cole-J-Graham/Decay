#include "CombatState.h"
//Constructors and Destructors
CombatState::CombatState(sf::RenderWindow* window, std::stack<State*>* states)
    : State(window, states)
{
    //Initialization
    this->initRects();
    this->player = new Player();
}

CombatState::~CombatState()
{
    //Delete Entities
    delete this->player;
    //Delete Rectangles
    auto ir = this->rectangles.begin();
    for (ir = this->rectangles.begin(); ir != this->rectangles.end(); ++ir) {
        delete ir->second;
    }
}

//Core Functions
void CombatState::combatLoop()
{
    switch (this->combatFrame) {
    case 0:
        //Players Turn
        break;
    case 1:
        //Zin's Turn
        break;
    case 2:
        //Thom's turn
        break;
    case 3:
        //Hostiles Turn
        break;
    }
}

//State Functions
void CombatState::updateKeybinds()
{

}

void CombatState::update()
{
    this->updateMousePositions();
    this->player->update(this->getMousePosView());
}

void CombatState::render(sf::RenderTarget* target)
{
    this->renderRects(target);
    this->player->render(target);
}

//Rectangle Functions
void CombatState::initRects()
{
    this->rectangles["PLAYERBORDER"] = new Rectangle(25, 150, 200, 200, sf::Color::Transparent,
        sf::Color::White, 1.f);
    this->rectangles["ZINBORDER"] = new Rectangle(25, 420, 200, 200, sf::Color::Transparent,
        sf::Color::White, 1.f);
    this->rectangles["THOMBORDER"] = new Rectangle(25, 690, 200, 200, sf::Color::Transparent,
        sf::Color::White, 1.f);
}

void CombatState::renderRects(sf::RenderTarget* target)
{
    for (auto& it : this->rectangles) {
        it.second->render(target);
    }
}