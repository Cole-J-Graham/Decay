#include "DialogueInputComponent.h"
#include "Text.h"

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

    this->buttons["DIALOGUEBOXTOP"]->setTextPosition(10.f, 816.f);
    this->buttons["DIALOGUEBOXBOTTOM"]->setTextPosition(10.f, 957.f);
    this->buttons["DIALOGUEBOXCENTER"]->setTextPosition(10.f, 820.f);
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
    std::string wrapped = Text::wrapText(text, 1800.f);
    this->buttons["DIALOGUEBOXCENTER"]->setText(wrapped);
}

void DialogueInputComponent::setDialogueOptions(std::string& top, std::string& bottom)
{
    std::string wrappedTop = Text::wrapText(top, 1800.f);
    std::string wrappedBottom = Text::wrapText(bottom, 1800.f);
    this->buttons["DIALOGUEBOXTOP"]->setText(wrappedTop);
    this->buttons["DIALOGUEBOXBOTTOM"]->setText(wrappedBottom);
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