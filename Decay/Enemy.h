#pragma once

#include <iomanip>
#include <sstream>
#include <map>
#include <memory>
#include <random>
#include <string>

#include "Text.h"
#include "Button.h"
#include "ViewerModule.h"
#include "EntityMove.h"

class Enemy
{
public:
    // Constructors and Deconstructors
    Enemy() {};
    Enemy(std::string enemyName, float hp, float hpMax, float damage, float defense,
        float scale, std::string enemyTexture, std::string enemyView,
        float reward, bool turnActive);
    ~Enemy();

    // Core Functions
    void update(const sf::Vector2f mousePos);
    void render(sf::RenderTarget* target);

    // Combat Functions
    void enemyTurn(int& combatFrame, const sf::Vector2f mousePos);
    void resetTurn();

    // Old button-flow function. Kept for compatibility, but CombatState should not use this anymore.
    void endTurn(int& combatFrame);

    // Combat Console Flow
    bool isWaitingForContinue() const { return this->enemyFrame == 1; }
    void continueTurn(int& combatFrame);

    // Button Functions
    void updateButtons(const sf::Vector2f mousePos);
    void initButtons();
    void renderButtons(sf::RenderTarget* target);

    // Move Functions
    void createMove(int key, const std::string& moveMessage, EntityMove::Operation op,
        std::string sfxId = "")
    {
        this->moves[key] = std::make_unique<EntityMove>(moveMessage, op, sfxId);
        this->enemyMoveRangeMax = static_cast<int>(this->moves.size()) - 1;
        std::cout << "ENEMY MOVE RANGE MAX:" << this->enemyMoveRangeMax << "\n";
    }

    void detectMove()
    {
        if (this->moves.empty()) {
            this->enemyFrame = 1;
            return;
        }

        std::random_device dev;
        std::mt19937 rng(dev());
        std::uniform_int_distribution<int> enemyMoveRange(this->enemyMoveRangeMin, this->enemyMoveRangeMax);

        int selectedMoveIndex = enemyMoveRange(rng);

        auto it = this->moves.find(selectedMoveIndex);

        std::cout << "ENEMY MOVE RANGE:" << selectedMoveIndex << "\n";

        if (it != this->moves.end() && it->second) {
            it->second->useMove();
        }

        this->enemyFrame = 1;
    }

    // Text Functions
    void initText();
    void renderText(sf::RenderTarget* target = nullptr);
    void updateText();
    std::string toStringWithPrecision(double value, int precision = 2);

    // Getters
    bool& isTurnActive() { return this->turnActive; }
    int& getEnemyFrame() { return this->enemyFrame; }
    float& getDamage() { return this->damage; }
    float& getHp() { return this->hp; }
    float getReward() const { return this->reward; }

private:
    // Enemy Variables
    float hp;
    float hpMax;
    float damage;
    float defense;
    float reward;

    // Asset Variables
    int enemyMoveRangeMin;
    int enemyMoveRangeMax;
    int enemyFrame;
    float x;
    float y;
    bool turnActive;

    sf::Texture enemyTexture;
    sf::Sprite enemy;
    std::string enemyName;

    ViewerModule* closeViewer;

    std::map<int, std::unique_ptr<EntityMove>> moves;
    std::map<std::string, Button*> buttons;
    std::map<std::string, Text*> text;
};