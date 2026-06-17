#include "Character.h"
#include "AssetDatabase.h"

// Constructors and Deconstructors
Character::Character(const std::string id, std::string characterName, float hp, float hpMax, float damage, float defense,
    float healing, float x, float y, float scale, std::string characterTexture, bool turnActive)
    : id(id), hp(hp), hpMax(hpMax), damage(damage), defense(defense), healing(healing),
    x(x), y(y), turnActive(turnActive), characterName(characterName),
    characterFrame(0), coolDown(0)
{
    this->pose.loadIdleTexture(characterTexture, this->character);
    this->character.setPosition(x, y);
    this->character.setScale(scale, scale);

    this->border = std::make_unique<Rectangle>(
        this->x,
        this->y,
        BORDER_WIDTH,
        BORDER_HEIGHT,
        sf::Color::Transparent,
        sf::Color::White,
        1.f,
        false
    );

    this->stats = std::make_unique<StatsModule>(id);

    this->initText();
    this->initButtons();
    this->updateText(); // initialises HP display immediately
}

Character::~Character()
{
    for (auto& pair : this->moveButtons) {
        delete pair.second;
        pair.second = nullptr;
    }

    this->moveButtons.clear();
}

// Core Functions
void Character::update(const sf::Vector2f mousePos)
{
    this->updateText();
    this->updateButtons(mousePos);
}

void Character::render(sf::RenderTarget* target)
{
    target->draw(this->character);
    this->border->render(target);
    this->renderText(target);

    if (this->turnActive) {
        this->renderMoveButtons(target);

        for (auto& it : this->moveButtons) {
            it.second->renderMoveMessage(target);
        }
    }
}

void Character::characterTurn(int& combatFrame, const sf::Vector2f mousePos)
{
    switch (this->characterFrame) {
    case 0:
        this->turnActive = true;

        for (auto& it : this->moveButtons) {
            it.second->show();
        }

        if (!this->waitingForMouseRelease && !this->justContinued) {
            this->updateMoveButtons(mousePos);
        }
        this->justContinued = false;
        break;

    case 1:
        for (auto& it : this->moveButtons) {
            it.second->hide();
        }
        break;

    default:
        this->characterFrame = 0;
        break;
    }
}

void Character::resetTurn()
{
    this->justContinued = false;
    this->turnActive = false;
    this->characterFrame = 0;

    if (this->buttons.count("ENDTURN") > 0) {
        this->buttons["ENDTURN"]->setIdle();
        this->buttons["ENDTURN"]->hide();
    }

    for (auto& it : this->moveButtons) {
        it.second->hide();
        it.second->hideAttackMessage();
    }
}

void Character::endTurn(int& combatFrame)
{
    // Legacy behavior kept for compatibility.
    // New combat flow should use continueTurn() from CombatState.
    if (this->buttons.count("ENDTURN") <= 0) {
        return;
    }

    this->buttons["ENDTURN"]->show();

    if (this->buttons["ENDTURN"]->isPressed()) {
        this->continueTurn(combatFrame);
    }
}

void Character::continueTurn(int& combatFrame)
{
    this->turnActive = false;
    this->characterFrame = 0;

    if (this->buttons.count("ENDTURN") > 0) {
        this->buttons["ENDTURN"]->hide();
        this->buttons["ENDTURN"]->setIdle();
    }

    this->coolDown--;

    for (auto& it : this->moveButtons) {
        it.second->hide();
        it.second->hideAttackMessage();
    }

    this->tickTemporaryEffects();
    this->consumePoseTurn();

    combatFrame++;
}

void Character::rest()
{
    this->waitingForMouseRelease = true;
    this->justContinued = true;
    this->hp = this->hpMax;
    this->block = 0.f;
    this->coolDown = 0;
    this->moveMp.clear();
    this->resetTurn();
    this->updateText();
}

// Button Functions
void Character::updateButtons(const sf::Vector2f mousePos)
{
    for (auto& it : this->buttons) {
        it.second->update(mousePos);
    }
}

void Character::updateMoveButtons(const sf::Vector2f mousePos)
{
    for (auto& it : this->moveButtons) {
        it.second->update(mousePos);
    }

    for (auto& it : this->moveButtons) {
        if (it.second->isPressed()) {
            std::cout << "MOVE PRESSED: " << it.first << " by " << this->id << "\n";
            this->characterFrame = 1;
            for (auto& other : this->moveButtons) {
                other.second->hide();
            }
            return;
        }
    }
}

void Character::initButtons()
{
    this->buttons[this->id] = std::make_unique<Button>(
        1402,
        50,
        120,
        22,
        0.5f,
        this->characterName,
        sf::Color(70, 70, 70, 70),
        sf::Color(100, 130, 100, 200),
        sf::Color(20, 20, 20, 70),
        false
    );

    this->buttons["ENDTURN"] = std::make_unique<Button>(
        450, 800, 150, 25, 0.5f,
        "End " + this->characterName + "'s Turn",
        sf::Color(70, 70, 70, 70),
        sf::Color(150, 150, 150, 255),
        sf::Color(20, 20, 20, 70),
        true
    );
}

// Move Functions
void Character::createMove(
    const std::string& key,
    const std::string& moveMessage,
    const std::string& tipMessage,
    const std::string& text,
    Move::Operation operation,
    const std::string& sfxId
)
{
    this->moveButtons[key] = new Move(
        moveMessage,
        tipMessage,
        text,
        operation,
        sfxId
    );
}

void Character::renderMoveButtons(sf::RenderTarget* target)
{
    int tempButtonY = 795;

    for (auto& it : this->moveButtons) {
        if (!it.second->isHidden()) {
            it.second->setPosition(BUTTON_X_OFFSET, tempButtonY -= BUTTON_Y_OFFSET);
            it.second->render(target);
        }
    }
}

// Text Functions
void Character::initText()
{
    this->text["NAME"] = std::make_unique<Text>(
        this->x,
        this->y - 20.f,
        16,
        this->characterName,
        sf::Color::White,
        false
    );

    this->text["HP"] = std::make_unique<Text>(
        this->x,
        this->y + 200,
        16,
        "HP: " + toStringWithPrecision(this->hp) + "/" + toStringWithPrecision(this->hpMax) +
        " BLK: " + toStringWithPrecision(this->block),
        sf::Color::White,
        false
    );
}

void Character::renderText(sf::RenderTarget* target)
{
    for (auto& it : this->text) {
        it.second->render(target);
    }
}

void Character::updateText()
{
    this->text["HP"]->setString(
        "HP: " + toStringWithPrecision(this->hp) + "/" + toStringWithPrecision(this->hpMax) +
        " BLK: " + toStringWithPrecision(this->block)
    );

    if (this->stats) {
        this->stats->setHp(this->hp, this->hpMax);
    }
}

std::string Character::toStringWithPrecision(double value, int precision)
{
    std::ostringstream out;
    out << std::fixed << std::setprecision(precision) << value;
    return out.str();
}

// Helpers
void Character::renderPreview(sf::RenderTarget* target, float x, float y)
{
    if (target == nullptr) {
        return;
    }

    const sf::Vector2f oldPosition = this->character.getPosition();

    this->character.setPosition(x, y);
    target->draw(this->character);

    this->character.setPosition(oldPosition);
}

bool Character::idButtonIsClicked() const
{
    auto it = this->buttons.find(this->id);

    if (it == this->buttons.end() || it->second == nullptr) {
        return false;
    }

    return it->second->isPressedRight();
}

void Character::updateIdButton(const sf::Vector2f mousePos)
{
    auto it = this->buttons.find(this->id);

    if (it != this->buttons.end() && it->second != nullptr) {
        it->second->update(mousePos);
    }
}

bool Character::idButtonLeftClicked() const
{
    auto it = this->buttons.find(this->id);

    if (it == this->buttons.end() || it->second == nullptr) {
        return false;
    }

    return it->second->isPressed();
}

void Character::takeDamage(float amount)
{
    if (this->block > 0.f)
    {
        const float absorbed = std::min(this->block, amount);

        this->block -= absorbed;
        amount -= absorbed;
    }

    if (amount > 0.f)
    {
        this->hp -= amount;
        std::cout << this->id << " HP after damage: " << this->hp << "\n";
        if (this->hp < 0.f)
        {
            this->hp = 0.f;
        }
    }

    this->updateText();
}

void Character::heal(float amount)
{
    if (amount <= 0.f) {
        return;
    }

    this->hp += amount;

    if (this->hp > this->hpMax) {
        this->hp = this->hpMax;
    }

    this->updateText();
}

// Status / Effects — all delegated to CharacterStatus
void Character::addTemporaryStatMultiplier(
    const std::string& id,
    const std::string& stat,
    float multiplier,
    int durationTurns
)
{
    this->status.addTemporaryStatMultiplier(id, stat, multiplier, durationTurns);
}

void Character::tickTemporaryEffects()
{
    this->status.tickTemporaryEffects();
}

float Character::getEffectiveDamage() const
{
    return this->status.getEffectiveDamage(this->damage);
}

float Character::getEffectiveDefense() const
{
    return this->status.getEffectiveDefense(this->defense);
}

// Emotion Functions
void Character::addEmotion(const std::string& emotion, const std::string& assetId)
{
    this->emotionAssets[emotion] = assetId;
}

void Character::setEmotion(const std::string& emotion)
{
    if (emotion.empty() || emotion == this->currentEmotion) return;

    this->currentEmotion = emotion;

    auto it = this->emotionAssets.find(emotion);
    if (it != this->emotionAssets.end() && AssetDatabase::getInstance().has(it->second))
    {
        this->character.setTexture(AssetDatabase::getInstance().getTexture(it->second));
    }
    // No fallback needed — if emotion not found, portrait stays as-is
}
