#include "UserInputComponent.h"
//Constructors and Deconstructors
UserInputComponent::UserInputComponent()
{
    font.loadFromFile("Assets/Fonts/tickerbit font/Tickerbit-regular.otf");

    //Initialization
    this->initButtons();
    this->initRects();
}

UserInputComponent::~UserInputComponent()
{
    //Deconstruct Buttons
    auto it = this->buttons.begin();
    for (it = this->buttons.begin(); it != this->buttons.end(); ++it) {
        delete it->second;
    }

    //Deconstruct Rectangles
    auto ir = this->rectangles.begin();
    for (ir = this->rectangles.begin(); ir != this->rectangles.end(); ++ir) {
        delete ir->second;
    }
}

//Core Functions
void UserInputComponent::update(sf::Vector2f mousePos)
{
    this->updateButtons(mousePos);
}

void UserInputComponent::render(sf::RenderTarget* target)
{
    this->renderButtons(target);
    this->renderRects(target);
}

//Button Functions
void UserInputComponent::initButtons()
{
    this->buttons["RETURN_BONFIRE"] = new Button(415, 10, 135, 25, 0.5f, this->font, "Return->Bonfire",
        sf::Color(70, 70, 70, 70), sf::Color(150, 150, 150, 255), sf::Color(20, 20, 20, 70), false);
    this->buttons["BUTTON_RIGHT"] = new Button(1335, 780, 20, 20, 0.5f, this->font, "->",
        sf::Color(70, 70, 70, 70), sf::Color(150, 150, 150, 255), sf::Color(20, 20, 20, 70), false);
    this->buttons["BUTTON_LEFT"] = new Button(565, 780, 20, 20, 0.5f, this->font, "<-",
        sf::Color(70, 70, 70, 70), sf::Color(150, 150, 150, 255), sf::Color(20, 20, 20, 70), false);

    this->buttons["DIALOGUEBOXTOP"] = new Button(0, 806, 1920, 140, 0.5f, this->font, "...",
        sf::Color(70, 70, 70, 70), sf::Color(150, 150, 150, 255), sf::Color(20, 20, 20, 70), true);
    this->buttons["DIALOGUEBOXBOTTOM"] = new Button(0, 947, 1920, 140, 0.5f, this->font, "...",
        sf::Color(70, 70, 70, 70), sf::Color(150, 150, 150, 255), sf::Color(20, 20, 20, 70), true);
}

void UserInputComponent::updateButtons(sf::Vector2f mousePos)
{
    /*Updates all buttons in the State and handles their functionality*/
    for (auto& it : this->buttons) {
        it.second->update(mousePos);
    }

    //Travel Right
    if (this->buttons["BUTTON_RIGHT"]->isPressed()) { this->right_active = true; }
    else {this->right_active = false;}
    //Travel Left
    if (this->buttons["BUTTON_LEFT"]->isPressed()) { this->left_active = true; }
    else { this->left_active = false; }
    
    //Return to bonfire
    if (this->buttons["RETURN_BONFIRE"]->isPressed()) { this->quit_active = true; }
    else { this->quit_active = false; }
    //Dialogue Options
    if (this->buttons["DIALOGUEBOXTOP"]->isPressed()) { this->top_dialogue_active = true; }
    else { this->top_dialogue_active = false; }
    if (this->buttons["DIALOGUEBOXBOTTOM"]->isPressed()) { this->bottom_dialogue_active = true; }
    else { this->bottom_dialogue_active = false; }
}

void UserInputComponent::renderButtons(sf::RenderTarget* target)
{
    for (auto& it : this->buttons) {
        it.second->render(target);
    }
}

//Rectangle Functions
void UserInputComponent::initRects()
{
    this->rectangles["BORDER"] = new Rectangle(560, 5, 800, 800, sf::Color::Transparent,
        sf::Color::White, 1.f);
    this->rectangles["LEFTBOX"] = new Rectangle(0, 5, 555, 800, sf::Color::Transparent,
        sf::Color::White, 1.f);
    this->rectangles["RIGHTBOX"] = new Rectangle(1365, 5, 555, 800, sf::Color::Transparent,
        sf::Color::White, 1.f);
}

void UserInputComponent::renderRects(sf::RenderTarget* target)
{
    for (auto& it : this->rectangles) {
        it.second->render(target);
    }
}

//Modifier Functions
void UserInputComponent::showDialogueOptions()
{
    this->buttons["DIALOGUEBOXTOP"]->show();
    this->buttons["DIALOGUEBOXBOTTOM"]->show();
}

void UserInputComponent::hideDialogueOptions()
{
    this->buttons["DIALOGUEBOXTOP"]->hide();
    this->buttons["DIALOGUEBOXBOTTOM"]->hide();
}

void UserInputComponent::showMoveArrows()
{
    this->buttons["BUTTON_RIGHT"]->show();
    this->buttons["BUTTON_LEFT"]->show();
    
}

void UserInputComponent::hideMoveArrows()
{
    this->buttons["BUTTON_RIGHT"]->hide();
    this->buttons["BUTTON_LEFT"]->hide();
}