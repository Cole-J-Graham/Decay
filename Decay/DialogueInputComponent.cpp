#include "DialogueInputComponent.h"
#include "Text.h"
#include "SfxManager.h"
#include <cctype>
#include <cstdlib>

DialogueInputComponent::DialogueInputComponent()
{
    this->initButtons();

    // Small "continue" indicator shown once the current line has fully
    // typed out. Sits in the bottom-right corner of the main dialogue box.
    this->continueIndicator = std::make_unique<Text>(
        1880.f, 1060.f,
        16,
        "v",
        sf::Color(220, 220, 220, 200),
        false
    );
}

void DialogueInputComponent::initButtons()
{
    const sf::Color idle(70, 70, 70, 70);
    const sf::Color hover(150, 150, 150, 255);
    const sf::Color active(20, 20, 20, 70);

    // DIALOGUEBOXTOP shares the same top edge as DIALOGUEBOXCENTER (810)
    // so NPC lines and the first player choice line up exactly when the
    // UI transitions between SHOWING_NPC and SHOWING_CHOICES — otherwise
    // the 4px gap reads as a small vertical jump between the two states.
    this->buttons["DIALOGUEBOXTOP"] = std::make_unique<Button>(0, 810, 1920, 140, 0.5f, "...", idle, hover, active, true);
    this->buttons["DIALOGUEBOXBOTTOM"] = std::make_unique<Button>(0, 951, 1920, 140, 0.5f, "...", idle, hover, active, true);
    this->buttons["DIALOGUEBOXCENTER"] = std::make_unique<Button>(1, 810, 1918, 275, 0.5f, "...", idle, hover, active, true);

    this->buttons["DIALOGUEBOXTOP"]->setTextPosition(10.f, 820.f);
    this->buttons["DIALOGUEBOXBOTTOM"]->setTextPosition(10.f, 961.f);
    this->buttons["DIALOGUEBOXCENTER"]->setTextPosition(10.f, 820.f);
}

void DialogueInputComponent::update(sf::Vector2f mousePos)
{
    for (auto& pair : this->buttons) {
        pair.second->update(mousePos);
    }

    this->updateTypewriter();

    this->topDialogueActive = this->buttons["DIALOGUEBOXTOP"]->isPressed();
    this->bottomDialogueActive = this->buttons["DIALOGUEBOXBOTTOM"]->isPressed();
}

void DialogueInputComponent::updateTypewriter()
{
    const bool fullyRevealed = this->revealedChars >= this->fullMainDialogueText.size();
    const bool clicked = this->buttons["DIALOGUEBOXCENTER"]->isPressed();

    if (!fullyRevealed)
    {
        const float elapsed = this->typewriterClock.restart().asSeconds();

        if (clicked)
        {
            // Click while typing skips straight to the full line instead
            // of advancing the sequence. No blips here — a burst of them
            // all at once on skip would just sound like noise.
            this->revealedChars = this->fullMainDialogueText.size();
        }
        else
        {
            this->revealTimer += elapsed;

            while (this->revealTimer >= secondsPerChar
                && this->revealedChars < this->fullMainDialogueText.size())
            {
                const char revealedChar = this->fullMainDialogueText[this->revealedChars];
                this->revealedChars++;
                this->revealTimer -= secondsPerChar;

                // Skip whitespace (spaces/newlines from wrapping), and only
                // blip every other character — one blip per char at full
                // speed reads as a buzz rather than discrete typing sounds.
                // Retune via blipEveryNChars / secondsPerChar.
                if (!std::isspace(static_cast<unsigned char>(revealedChar))
                    && (this->revealedChars % blipEveryNChars) == 0)
                {
                    const float pitch = 0.95f + (static_cast<float>(rand() % 11) * 0.01f); // 0.95-1.05
                    SfxManager::getInstance().play("dialogue_blip", 50.f, pitch);
                }
            }
        }

        std::string revealedText = this->fullMainDialogueText.substr(0, this->revealedChars);
        this->buttons["DIALOGUEBOXCENTER"]->setText(revealedText);

        this->mainDialogueActive = false;
    }
    else
    {
        this->typewriterClock.restart();
        this->revealTimer = 0.f;
        this->mainDialogueActive = clicked;
    }

    // Blink the continue indicator only once the line is fully shown
    if (fullyRevealed && this->mainDialogueVisible)
    {
        if (this->indicatorBlinkClock.getElapsedTime().asSeconds() >= indicatorBlinkInterval)
        {
            this->indicatorBlinkVisible = !this->indicatorBlinkVisible;
            this->indicatorBlinkClock.restart();
        }
    }
    else
    {
        this->indicatorBlinkVisible = false;
        this->indicatorBlinkClock.restart();
    }
}

void DialogueInputComponent::render(sf::RenderTarget* target)
{
    if (target == nullptr) {
        return;
    }

    for (auto& pair : this->buttons) {
        pair.second->render(target);
    }

    if (this->mainDialogueVisible
        && this->revealedChars >= this->fullMainDialogueText.size()
        && this->indicatorBlinkVisible)
    {
        this->continueIndicator->render(target);
    }
}

void DialogueInputComponent::setMainDialogueText(std::string& text)
{
    std::string wrapped = Text::wrapText(text, 1800.f);

    this->fullMainDialogueText = wrapped;
    this->revealedChars = 0;
    this->revealTimer = 0.f;
    this->typewriterClock.restart();

    std::string empty = "";
    this->buttons["DIALOGUEBOXCENTER"]->setText(empty);
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
    this->mainDialogueVisible = true;
}

void DialogueInputComponent::hideMainDialogue()
{
    this->buttons["DIALOGUEBOXCENTER"]->hide();
    this->mainDialogueVisible = false;
}