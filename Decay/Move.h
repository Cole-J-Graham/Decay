#pragma once

#include "Button.h"
#include "Rectangle.h"
#include "Text.h"
#include "SfxManager.h"

#include <functional>
#include <map>
#include <memory>
#include <string>

class Move {
public:
    using Operation = std::function<void(float&, float&, float&, int&)>;

    Move(std::string moveMessage, std::string tipMessage,
        std::string text, Operation op, float& a, float& b, float& c,
        int coolDown, std::string sfxId = "", std::function<void()> animationCallback = nullptr);

    ~Move() = default;

    // Core Functions
    void render(sf::RenderTarget* target);
    void renderMoveMessage(sf::RenderTarget* target);
    void update(const sf::Vector2f mousePos);
    void useMove();

    // Rectangle Functions
    void initRects();
    void renderRects(sf::RenderTarget* target);

    // Modifiers
    void setPosition(float x, float y) { this->button->setPosition(x, y); }
    bool isPressed() const { return this->button->isPressed(); }

    void show() { this->hidden = false; }
    void hide() { this->hidden = true; }

    void showAttackMessage() { this->message->setShown(); }
    void hideAttackMessage() { this->message->setHidden(); }

    const bool& isHidden() { return this->hidden; }

    // Getters
    std::string& getMoveMessage() { return this->moveMessage; }
    std::unique_ptr<Button>& getButton() { return this->button; }

    struct Adder {
        void operator()(float& a, float& b, float&, int&) const {
            a += b;
        }
    };

    struct Subtractor {
        void operator()(float& a, float& b, float&, int&) const {
            a -= b;
        }
    };

    struct Subcooldown {
        void operator()(float& a, float& b, float& c, int&) const {
            a -= b;
            c++;
        }
    };

    struct Healer {
        void operator()(float& a, float& b, float& c, int&) const {
            if (c >= a) {
                std::cout << "Skipped healing. Hp is full..." << "\n";
            }
            else {
                a += b;
            }
        }
    };

private:
    Operation operation;

    float& a;
    float& b;
    float& c;
    int coolDown;

    bool hidden;

    std::function<void()> animationCallback;
    std::map<std::string, std::unique_ptr<Rectangle>> rectangles;
    std::unique_ptr<Button> button;
    std::unique_ptr<Text> message;

    std::string moveMessage;
    std::string tipMessage;
    std::string sfxId;
};