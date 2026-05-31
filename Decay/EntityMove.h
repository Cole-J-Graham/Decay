#pragma once

#include <functional>
#include <memory>
#include <string>

#include "Text.h"
#include "SfxManager.h"

class EntityMove
{
public:
    using Operation = std::function<void()>;

    // Constructors and Destructors
    EntityMove(const std::string& moveMessage, Operation op,
        std::string sfxId = "");
    ~EntityMove() = default;

    // Core Functions
    void render(sf::RenderTarget* target);
    void renderMoveMessage(sf::RenderTarget* target);
    void update(const sf::Vector2f mousePos);
    void useMove();

    // Setters
    void show();
    void hide();

private:
    Operation operation;

    bool hidden;

    std::string id;
    std::string moveMessage;
    std::string sfxId;

    std::unique_ptr<Text> message;
};