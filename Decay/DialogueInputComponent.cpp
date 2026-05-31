#include "DialogueInputComponent.h"

DialogueInputComponent::DialogueInputComponent()
{
    this->initButtons();
    this->initRects();
}

void DialogueInputComponent::initButtons()
{
    const sf::Color idle(70, 70, 70, 70);
    const sf::Color hover(150, 150, 150, 255);
    const sf::Color active(20, 20, 20, 70);

    this->buttons["DIALOGUEBOXTOP"] = std::make_unique<Button>(0, 806, 1920, 140, 0.5f, "...", idle, hover, active, true);
    this->buttons["DIALOGUEBOXBOTTOM"] = std::make_unique<Button>(0, 947, 1920, 140, 0.5f, "...", idle, hover, active, true);
    this->buttons["DIALOGUEBOXCENTER"] = std::make_unique<Button>(1, 810, 1918, 275, 0.5f, "...", idle, hover, active, true);
}

void DialogueInputComponent::initRects()
{
    this->rectangles["DIALOGUE_BOX"] = std::make_unique<Rectangle>("", sf::Color::White, 16, 1, 810, 1918, 275, sf::Color::Transparent, sf::Color::White, 1.f, false);
}

void DialogueInputComponent::update(sf::Vector2f mousePos)
{
    for (auto& pair : this->buttons) {
        pair.second->update(mousePos);
    }

    for (auto& pair : this->rectangles) {
        pair.second->update(mousePos);
    }

    this->topDialogueActive = this->buttons["DIALOGUEBOXTOP"]->isPressed();
    this->bottomDialogueActive = this->buttons["DIALOGUEBOXBOTTOM"]->isPressed();
    this->mainDialogueActive = this->buttons["DIALOGUEBOXCENTER"]->isPressed();
}

void DialogueInputComponent::render(sf::RenderTarget* target)
{
    if (target == nullptr) {
        return;
    }

    for (auto& pair : this->buttons) {
        pair.second->render(target);
    }

    for (auto& pair : this->rectangles) {
        pair.second->render(target);
    }
}

void DialogueInputComponent::setMainDialogueText(std::string& text)
{
    this->buttons["DIALOGUEBOXCENTER"]->setText(text);
}

void DialogueInputComponent::setDialogueOptions(std::string& top, std::string& bottom)
{
    this->buttons["DIALOGUEBOXTOP"]->setText(top);
    this->buttons["DIALOGUEBOXBOTTOM"]->setText(bottom);
}

void DialogueInputComponent::showDialogueOptions()
{
    this->buttons["DIALOGUEBOXTOP"]->show();
    this->buttons["DIALOGUEBOXBOTTOM"]->show();
}

void DialogueInputComponent::hideDialogueOptions()
{
    this->buttons["DIALOGUEBOXTOP"]->hide();
    this->buttons["DIALOGUEBOXBOTTOM"]->hide();
}

void DialogueInputComponent::showMainDialogue()
{
    this->buttons["DIALOGUEBOXCENTER"]->show();
}

void DialogueInputComponent::hideMainDialogue()
{
    this->buttons["DIALOGUEBOXCENTER"]->hide();
}