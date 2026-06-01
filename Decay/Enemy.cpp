#include "Enemy.h"

// Constructors and Deconstructors
Enemy::Enemy(std::string enemyName, float hp, float hpMax, float damage, float defense,
    float scale, std::string enemyTexture, std::string enemyView,
    const RewardBundle& rewards, bool turnActive)
    : enemyName(enemyName),
    hp(hp),
    hpMax(hpMax),
    damage(damage),
    defense(defense),
    rewards(rewards),
    turnActive(turnActive)
{
    this->hp = hp;
    this->hpMax = hpMax;
    this->damage = damage;
    this->defense = defense;
    this->enemyName = enemyName;
    this->rewards = rewards;

    this->enemyMoveRangeMin = 0;
    this->enemyMoveRangeMax = -1;
    this->enemyFrame = 0;
    this->x = 1695;
    this->y = 420;

    this->enemyTexture.loadFromFile(enemyTexture);
    this->enemy.setTexture(this->enemyTexture);
    this->enemy.setPosition(this->x, this->y);
    this->enemy.setScale(scale, scale);

    this->turnActive = turnActive;

    this->initText();
    this->initButtons();
    this->closeViewer = new ViewerModule(enemyView, scale);
}

Enemy::~Enemy()
{
    delete this->closeViewer;
    this->closeViewer = nullptr;

    for (auto& pair : this->buttons) {
        delete pair.second;
        pair.second = nullptr;
    }

    this->buttons.clear();

    for (auto& pair : this->text) {
        delete pair.second;
        pair.second = nullptr;
    }

    this->text.clear();
}

// Core Functions
void Enemy::update(const sf::Vector2f mousePos)
{
    this->updateText();
    this->updateButtons(mousePos);

    if (this->closeViewer != nullptr) {
        this->closeViewer->update(mousePos);
    }
}

void Enemy::render(sf::RenderTarget* target)
{
    if (this->closeViewer != nullptr) {
        this->closeViewer->render(target);
    }

    target->draw(this->enemy);
    this->renderText(target);

    if (this->turnActive) {
        for (auto& it : this->moves) {
            it.second->renderMoveMessage(target);
        }
    }
}

// Combat Functions
void Enemy::enemyTurn(int& combatFrame, const sf::Vector2f mousePos)
{
    this->update(mousePos);

    switch (this->enemyFrame) {
    case 0:
        this->turnActive = true;
        this->detectMove();
        break;

    case 1:
        // Do not call endTurn() here.
        // CombatState owns the click-to-continue behavior now.
        break;

    default:
        this->enemyFrame = 0;
        break;
    }
}

void Enemy::resetTurn()
{
    this->turnActive = false;
    this->enemyFrame = 0;

    if (this->buttons.count("CONTINUE") > 0) {
        this->buttons["CONTINUE"]->hide();
        this->buttons["CONTINUE"]->setIdle();
    }

    for (auto& it : this->moves) {
        if (it.second) {
            it.second->hide();
        }
    }
}

void Enemy::endTurn(int& combatFrame)
{
    // Legacy behavior kept for compatibility.
    // New combat flow should use continueTurn() from CombatState.
    if (this->buttons.count("CONTINUE") <= 0) {
        return;
    }

    this->buttons["CONTINUE"]->show();

    if (this->buttons["CONTINUE"]->isPressed()) {
        this->continueTurn(combatFrame);
    }
}

void Enemy::continueTurn(int& combatFrame)
{
    this->resetTurn();
    combatFrame++;
}

// Button Functions
void Enemy::updateButtons(const sf::Vector2f mousePos)
{
    for (auto& it : this->buttons) {
        it.second->update(mousePos);
    }
}

void Enemy::initButtons()
{
    // Kept for compatibility, but hidden and no longer part of the main combat flow.
    this->buttons["CONTINUE"] = new Button(
        600,
        800,
        150,
        25,
        0.5f,
        "Continue",
        sf::Color(70, 70, 70, 70),
        sf::Color(150, 150, 150, 255),
        sf::Color(20, 20, 20, 70),
        true
    );
}

void Enemy::renderButtons(sf::RenderTarget* target)
{
    for (auto& it : this->buttons) {
        it.second->render(target);
    }
}

// Text Functions
void Enemy::initText()
{
    this->text["HP"] = new Text(
        this->x,
        this->y + 200,
        16,
        "HP: " + std::to_string(this->hp) + "/" + std::to_string(this->hpMax),
        sf::Color::White,
        false
    );
}

void Enemy::renderText(sf::RenderTarget* target)
{
    for (auto& it : this->text) {
        it.second->render(target);
    }
}

void Enemy::updateText()
{
    if (this->hp <= 0.f) {
        this->text["HP"]->setString("DEFEATED");
        return;
    }

    this->text["HP"]->setString(
        "HP: " + toStringWithPrecision(this->hp) + "/" + toStringWithPrecision(this->hpMax)
    );
}

std::string Enemy::toStringWithPrecision(double value, int precision)
{
    std::ostringstream out;
    out << std::fixed << std::setprecision(precision) << value;
    return out.str();
}
