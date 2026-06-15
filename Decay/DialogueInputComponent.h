#pragma once

#include "Button.h"
#include "Rectangle.h"
#include "Text.h"

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
    void updateTypewriter();

private:
    std::map<std::string, std::unique_ptr<Button>> buttons;
    std::map<std::string, std::unique_ptr<Rectangle>> rectangles;

    bool topDialogueActive = false;
    bool bottomDialogueActive = false;
    bool mainDialogueActive = false;

    // Typewriter reveal for the main dialogue line. fullMainDialogueText is
    // the wrapped target string; revealedChars grows over time until it
    // matches the full length. A click while revealing jumps straight to
    // the end instead of advancing the sequence.
    std::string fullMainDialogueText;
    size_t revealedChars = 0;
    float revealTimer = 0.f;
    sf::Clock typewriterClock;
    static constexpr float secondsPerChar = 0.02f; // ~50 chars/sec
    static constexpr int blipEveryNChars = 2;       // typing-sound throttle

    bool mainDialogueVisible = false;

    // "Click to continue" indicator — shown once the line is fully revealed
    std::unique_ptr<Text> continueIndicator;
    sf::Clock indicatorBlinkClock;
    bool indicatorBlinkVisible = true;
    static constexpr float indicatorBlinkInterval = 0.5f;
};