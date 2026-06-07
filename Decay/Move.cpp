#include "Move.h"

#include <iostream>

Move::Move(
    std::string moveMessage,
    std::string tipMessage,
    std::string text,
    Operation operation,
    std::string sfxId
)
    : operation(operation), sfxId(sfxId), text(text)
{
    const sf::Color idle(15, 15, 30, 200);        // dark navy, matches console bg
    const sf::Color hover(255, 200, 80, 40);       // gold tint on hover, matches accent bar
    const sf::Color active(255, 200, 80, 80);      // brighter gold on press

    this->button = std::make_unique<Button>(350, 800, 0.f, 25, 0.1f, text, idle, hover, active, false);
    this->button->setClickSfxEnabled(false);
    this->message = std::make_unique<Text>(355, 835, 16, moveMessage, sf::Color::White, true);

    this->moveMessage = moveMessage;
    this->tipMessage = tipMessage;
    this->hidden = true;

    this->initRects();
}

// Core Functions
void Move::render(sf::RenderTarget* target)
{
    if (target == nullptr) {
        return;
    }

    if (!this->hidden) {
        this->button->render(target);
        this->renderRects(target);
    }

    this->renderMoveMessage(target);
}

void Move::renderMoveMessage(sf::RenderTarget* target)
{
    if (target == nullptr) {
        return;
    }

    this->message->render(target);
}

void Move::update(const sf::Vector2f mousePos)
{
    if (this->hidden) {
        return;
    }

    if (!this->canUse()) {
        this->button->disable();
    }
    else {
        this->button->enable();
    }

    this->button->update(mousePos);

    if (this->button->isHovered()) {
        this->rectangles["TIPBOX"]->show();
    }
    else {
        this->rectangles["TIPBOX"]->hide();
    }

    if (this->button->isPressed()) {
        this->useMove();
    }
}

void Move::useMove()
{
    if (!this->canUse()) {
        return;
    }

    if (this->operation) {
        this->operation();
    }

    if (!this->sfxId.empty()) {
        SfxManager::getInstance().play(this->sfxId);
    }

    this->message->setShown();

    std::cout << "Move used: " << this->moveMessage << "\n";
}

// MP Functions
void Move::initMp(int maxUses, int currentUses)
{
    this->mpMax = maxUses;
    this->mp = (maxUses == -1) ? -1 : currentUses;
    this->updateButton();
}

bool Move::canUse() const
{
    return this->mpMax == -1 || this->mp > 0;
}

void Move::consumeMp()
{
    if (this->mpMax != -1 && this->mp > 0) {
        this->mp--;
        this->updateButton();
    }
}

void Move::restoreMp()
{
    if (this->mpMax != -1) {
        this->mp = this->mpMax;
        this->updateButton();
    }
}

std::string Move::getMpString() const
{
    if (this->mpMax == -1) return "";
    return " [" + std::to_string(this->mp) + "/" + std::to_string(this->mpMax) + "]";
}

// Rectangle Functions
static std::string wrapText(const std::string& text, const sf::Font& font, unsigned int charSize, float maxWidth)
{
    std::string result;
    std::string line;
    std::istringstream stream(text);
    std::string word;

    while (stream >> word) {
        std::string testLine = line.empty() ? word : line + " " + word;

        sf::Text temp;
        temp.setFont(font);
        temp.setCharacterSize(charSize);
        temp.setString(testLine);

        if (!line.empty() && temp.getLocalBounds().width > maxWidth) {
            result += line + "\n";
            line = word;
        }
        else {
            line = testLine;
        }
    }

    if (!line.empty()) {
        result += line;
    }

    return result;
}

void Move::initRects()
{
    const float boxWidth = 200.f;
    const float padding = 8.f;
    const unsigned int tipFontSize = 16;

    const sf::Font& font = AssetDatabase::getInstance().getFont("ticker_font");
    std::string wrappedTip = wrapText(this->tipMessage, font, tipFontSize, boxWidth - padding * 2);

    this->rectangles["TIPBOX"] = std::make_unique<Rectangle>(
        wrappedTip,           // <-- wrapped string instead of raw tipMessage
        sf::Color::White,
        tipFontSize,
        1700,
        100,
        boxWidth,
        200,
        sf::Color::Transparent,
        sf::Color::White,
        1.f,
        true
    );
}

void Move::renderRects(sf::RenderTarget* target)
{
    if (target == nullptr) {
        return;
    }

    for (auto& it : this->rectangles) {
        it.second->render(target);
    }
}

void Move::updateButton()
{
    std::string label = this->text;
    if (this->mpMax != -1) {
        label += " [" + std::to_string(this->mp) + "/" + std::to_string(this->mpMax) + "]";
    }
    this->button->setTextConst(label);

    // Resize to fit new label
    sf::Text temp;
    temp.setFont(AssetDatabase::getInstance().getFont("ticker_font"));
    temp.setString(label);
    temp.setCharacterSize(16);
    this->button->setSize(temp.getLocalBounds().width + 10.f, 25.f);
}