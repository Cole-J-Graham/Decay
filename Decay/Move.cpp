#include "Move.h"

Move::Move(std::string moveMessage, std::string tipMessage,
    std::string text, Operation op, float& a, float& b, float& c,
    int coolDown, std::string sfxId, std::function<void()> animationCallback)
    : operation(op), a(a), b(b), c(c), coolDown(coolDown), sfxId(sfxId), animationCallback(animationCallback)
{
    const sf::Color idle(70, 70, 70, 70);
    const sf::Color hover(150, 150, 150, 255);
    const sf::Color active(20, 20, 20, 70);

    this->button = std::make_unique<Button>(350, 800, 100, 25, 0.1f, text, idle, hover, active, false);
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
    this->operation(this->a, this->b, this->c, this->coolDown);

    if (!this->sfxId.empty()) {
        SfxManager::getInstance().play(this->sfxId);
    }

    if (this->animationCallback) {
        this->animationCallback();
    }

    this->message->setShown();

    std::cout << "Operation applied: a = " << a << ", b = " << b << std::endl;
}

// Rectangle Functions
void Move::initRects()
{
    this->rectangles["TIPBOX"] = std::make_unique<Rectangle>(
        this->tipMessage,
        sf::Color::White,
        16,
        1700,
        100,
        200,
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