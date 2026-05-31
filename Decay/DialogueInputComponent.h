#pragma once

#include "Button.h"
#include "Rectangle.h"

#include <map>
#include <memory>
#include <string>

class DialogueInputComponent
{
public:
    DialogueInputComponent();

    void update(sf::Vector2f mousePos);
    void render(sf::RenderTarget* target);

    bool topDialogueClicked() const { return this->topDialogueActive; }
    bool bottomDialogueClicked() const { return this->bottomDialogueActive; }
    bool mainDialogueClicked() const { return this->mainDialogueActive; }

    void setMainDialogueText(std::string& text);
    void setDialogueOptions(std::string& top, std::string& bottom);

    void showDialogueOptions();
    void hideDialogueOptions();

    void showMainDialogue();
    void hideMainDialogue();

private:
    void initButtons();
    void initRects();

private:
    std::map<std::string, std::unique_ptr<Button>> buttons;
    std::map<std::string, std::unique_ptr<Rectangle>> rectangles;

    bool topDialogueActive = false;
    bool bottomDialogueActive = false;
    bool mainDialogueActive = false;
};