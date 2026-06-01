#pragma once

#include "Move.h"
#include "StatsModule.h"

#include <map>
#include <memory>
#include <stack>
#include <string>

class Character
{
public:
    // Constructors and Deconstructors
    Character(const std::string id, std::string characterName, float hp, float hpMax, float damage, float defense,
        float healing, float x, float y, float scale, std::string characterTexture, bool turnActive);
    ~Character();

    // Core Functions
    void update(const sf::Vector2f mousePos);
    void render(sf::RenderTarget* target);
    void characterTurn(int& combatFrame, const sf::Vector2f mousePos);
    void resetTurn();

    // Old button-flow function. Kept for compatibility, but CombatState should not use this anymore.
    void endTurn(int& combatFrame);

    // Combat Console Flow
    bool isWaitingForContinue() const { return this->characterFrame == 1; }
    void continueTurn(int& combatFrame);

    // Button Functions
    void updateButtons(const sf::Vector2f mousePos);
    void updateMoveButtons(const sf::Vector2f mousePos);
    void initButtons();
    void renderIdButton(sf::RenderTarget* target) { this->buttons[this->id]->render(target); }

    // Move Functions
    void createMove(std::string key, std::string moveMessage,
        std::string tipMessage, std::string text, Move::Operation op, float& a, float& b,
        float& c, int coolDown, std::string sfxId, std::function<void()> animationCallback = nullptr);
    void renderMoveButtons(sf::RenderTarget* target);

    void clearMoves()
    {
        for (auto& pair : moveButtons) {
            delete pair.second;
            pair.second = nullptr;
        }

        moveButtons.clear();
    }

    // Text Functions
    void initText();
    void renderText(sf::RenderTarget* target = nullptr);
    void updateText();
    std::string toStringWithPrecision(double value, int precision = 2);

    // Setters
    float& setHp(float& hp) { this->hp = hp; return this->hp; }
    void resetCharacterFrame() { this->characterFrame = 0; }
    void setIdButtonPosition(int& x, int& y) { this->buttons[this->id]->setPosition(x, y); }
    void setSpritePosition(const float& x, const float& y) { this->character.setPosition(x, y); }
    void addExp(float amount)
    {
        if (this->stats) {
            this->stats->addExp(amount);
        }
    }

    //Helpers
    void renderPreview(sf::RenderTarget* target, float x, float y);
    bool idButtonIsClicked() const;
    void updateIdButton(const sf::Vector2f mousePos);
    bool idButtonLeftClicked() const;
    void takeDamage(float amount);
    void heal(float amount);

    void stun(int turns = 1);
    bool isStunned() const;
    void consumeStunTurn();
    int getStunTurns() const;

    // Getters
    float& getDamage() { return this->damage; }
    float& getHp() { return this->hp; }
    float& getHpMax() { return this->hpMax; }
    float& getDefense() { return this->defense; }
    float& getHealing() { return this->healing; }
    int& getCoolDown() { return this->coolDown; }
    int& getCharacterFrame() { return this->characterFrame; }
    bool& isTurnActive() { return this->turnActive; }

    // Resting / Recovery
    void rest();
    bool isAlive() const { return this->hp > 0.f; }

    sf::Vector2f getHitEffectPosition() const
    {
        return sf::Vector2f(
            this->x + (BORDER_WIDTH / 2.f) - 96.f,
            this->y + (BORDER_HEIGHT / 2.f) - 96.f
        );
    }

    const std::string& getId() { return this->id; }
    std::map<std::string, Move*> getMoves()& { return this->moveButtons; }
    std::unique_ptr<StatsModule>& getStats() { return this->stats; }
    std::map<std::string, std::unique_ptr<Button>>& getButtons() { return this->buttons; }

private:
    // Consts
    const std::string id;
    const int BORDER_WIDTH = 200;
    const int BORDER_HEIGHT = 200;
    const int BUTTON_X_OFFSET = 350;
    const int BUTTON_Y_OFFSET = 25;

    // Player Variables
    float hp;
    float hpMax;
    float damage;
    float defense;
    float healing;
    int coolDown;
    int stunTurns = 0;

    // Asset Variables
    int characterFrame;
    float x;
    float y;
    bool turnActive;

    sf::Texture characterTexture;
    sf::Sprite character;
    std::string characterName;
    std::unique_ptr<Rectangle> border;

    std::unique_ptr<StatsModule> stats;
    std::map<std::string, std::unique_ptr<Button>> buttons;
    std::map<std::string, std::unique_ptr<Text>> text;
    std::map<std::string, Move*> moveButtons;
};