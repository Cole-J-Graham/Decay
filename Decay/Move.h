#include "Button.h"
#include "Rectangle.h"
#include "Text.h"
#include <functional>
#include <map>
#include <memory>
#include <string>

class Move {
public:
    using Operation = std::function<void(float&, float&, int&)>;

    Move(std::string key, std::string moveMessage, std::string tipMessage, 
        std::string text, Operation op, float& a, float& b, int& coolDown);
    ~Move();

    //Core Functions
    void render(sf::RenderTarget* target);
    void update(const sf::Vector2f mousePos);
    void useMove();

    //Rectangle Functions
    void initRects();
    void renderRects(sf::RenderTarget* target);

    //Modifiers
    void setPosition(float x, float y) { this->button->setPosition(x, y); }
    const bool isPressed() { return this->button->isPressed(); }
    void show() { this->hidden = false; }
    void hide() { this->hidden = true; }
    void showAttackMessage() { this->message->setShown(); }
    void hideAttackMessage() { this->message->setHidden(); }
    const bool& isHidden() { return this->hidden; }

    //Getters
    std::string& getMoveMessage() { return this->moveMessage; }

    struct Adder {
        void operator()(float& a, float& b, int&) const {
            a += b;
        }
    };

    struct Subtractor {
        void operator()(float& a, float& b, int&) const {
            a -= b;
        }
    };

    struct Subcooldown {
        void operator()(float& a, float& b, int& c) const {
            a -= b;
            c++;
        }
    };

private:

    Operation operation;

    float& a;
    float& b;
    int& coolDown;

    bool active;
    bool hidden;

    std::map<std::string, std::unique_ptr<Rectangle>> rectangles;
    std::unique_ptr<Button> button;

    Text* message;

    std::string moveMessage;
    std::string tipMessage;
};
