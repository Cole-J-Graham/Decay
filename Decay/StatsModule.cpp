#include "StatsModule.h"

// Constructors and Destructors
StatsModule::StatsModule(const std::string& id, const std::string& tipText)
    : id(id), tipText(tipText) {
    // Variables
    this->level = 0;
    this->exp = 0;
    this->expNext = 100;
    this->sp = 5;
    this->buttonId = id;

    this->currentInstance = false;
    this->lastClicked = false;

    // Initialization
    this->initRects();
    this->initText();
    this->initButtons();
}

StatsModule::~StatsModule()
{
    //Delete Buttons
    for (auto& pair : this->buttons) {
        delete pair.second;
    }
}

// Core Functions
void StatsModule::update(const sf::Vector2f mousePos) {
    this->updateStats(mousePos);
    this->updateButtons(mousePos);
    this->updateText();
}

void StatsModule::render(sf::RenderTarget* target) {
    if (this->currentInstance) {
        this->renderRects(target);
        this->renderStats(target);
        this->renderButtons(target);
        this->renderText(target);
    }
    else if (this->buttons.count(this->buttonId)) { // Ensure button exists
        this->buttons[this->buttonId]->render(target);
    }
}

// Stat Functions
void StatsModule::updateStats(const sf::Vector2f mousePos) {
    for (auto& it : this->stats) {
        if (it.second) { // Check if pointer is valid
            it.second->update(mousePos);
            it.second->statUp(this->sp);
        }
    }
}

void StatsModule::createStat(const std::string& key, const std::string& statName,
    const std::string& modifiedStatName, float& stat, float statModifier) {
    if (this->stats.find(key) == this->stats.end()) {
        this->stats[key] = std::make_shared<Stat>(statName, modifiedStatName, stat, statModifier);
    }
}

void StatsModule::renderStats(sf::RenderTarget* target) {
    // Panel geometry
    const float panelX = 1410.f;
    const float rightColX = 1560.f;  // x of derived-value column
    const float rowHeight = 28.f;
    float y = 138.f;                 // first stat row (below header bar)

    // Column header background stripe
    sf::RectangleShape colHeaderBg(sf::Vector2f(260.f, 18.f));
    colHeaderBg.setPosition(panelX, y - 20.f);
    colHeaderBg.setFillColor(sf::Color(255, 255, 255, 18));
    target->draw(colHeaderBg);

    // Small column label text (stack-allocated each frame, cheap for UI)
    Text leftHeader(panelX + 28.f, y - 18.f, 11, "STAT  PTS", sf::Color(180, 180, 180, 200), false);
    Text rightHeader(rightColX, y - 18.f, 11, "CURRENT VAL", sf::Color(160, 220, 255, 200), false);
    leftHeader.render(target);
    rightHeader.render(target);

    for (auto& it : this->stats) {
        it.second->setPosition(panelX, y, rightColX);
        it.second->render(target);
        y += rowHeight;
    }

    // Separator below all stat rows
    sf::RectangleShape sep(sf::Vector2f(260.f, 2.f));
    sep.setPosition(panelX, y + 4.f);
    sep.setFillColor(sf::Color(255, 255, 255, 40));
    target->draw(sep);
}

// Stat Modifiers
void StatsModule::increaseLevel() {
    if (this->buttons.count("LEVELUP") && this->buttons["LEVELUP"]->isPressed()) {
        if (this->exp >= this->expNext) {
            this->exp -= this->expNext;
            this->level++;
            this->sp++;
        }
        else {
            std::cout << "Not enough exp for level up..." << "\n";
        }
    }
}

void StatsModule::addExp(float amount)
{
    if (amount <= 0.f) {
        return;
    }

    this->exp += amount;
    this->updateText();
}

// Rectangle Functions
void StatsModule::initRects() {
    // Main panel border (x=1400, y=50, w=270, h=620)
    this->rectangles["STATSMENU"] = std::make_unique<Rectangle>(1400, 50, 270, 620, sf::Color::Transparent,
        sf::Color::White, 1.f, false);

    // Thin divider below the header bar
    this->rectangles["HEADERDIV"] = std::make_unique<Rectangle>(1400, 82, 270, 1,
        sf::Color(255, 255, 255, 60), sf::Color::Transparent, 0.f, false);
}

void StatsModule::renderRects(sf::RenderTarget* target) {
    for (auto& it : this->rectangles) {
        it.second->render(target);
    }
}

// Button Functions
void StatsModule::updateButtons(const sf::Vector2f mousePos) {
    for (auto& it : this->buttons) {
        if (it.second) { // Ensure button is valid
            it.second->update(mousePos);
        }
    }

    if (this->currentInstance) {
        this->increaseLevel();
    }
}

void StatsModule::initButtons() {
    if (this->buttonId.empty()) {
        this->buttonId = this->id;
    }

    // The character buttons that appear when clicking — "stats"
    this->buttons[this->buttonId] = new Button(1620, 53, 100, 22, 0.5f, this->id,
        sf::Color(60, 90, 60, 160), sf::Color(100, 180, 100, 255), sf::Color(20, 20, 20, 70), false);

    // LEVEL++ button — right-aligned in the header bar, left of the toggle
    this->buttons["LEVELUP"] = new Button(1560, 53, 55, 22, 0.5f, "LVL++",
        sf::Color(60, 100, 60, 160), sf::Color(100, 180, 100, 255), sf::Color(30, 60, 30, 180), false);
}

void StatsModule::renderButtons(sf::RenderTarget* target) {
    for (auto& it : this->buttons) {
        it.second->render(target);
    }
}

// Text Functions
void StatsModule::initText() {
    // Title label
    this->text["TITLE"] = std::make_unique<Text>(1410, 55, 13,
        "CHARACTER STATS",
        sf::Color(200, 200, 200, 220), false);

    // EXP / Level line
    this->text["EXPTEXT"] = std::make_unique<Text>(1410, 84, 12,
        buildExpString(),
        sf::Color(255, 210, 100, 255), false);

    // SP line (slightly below, different colour)
    this->text["SPTEXT"] = std::make_unique<Text>(1560, 84, 12,
        buildSpString(),
        sf::Color(130, 220, 130, 255), false);

    this->text["TIPTEXT"] = std::make_unique<Text>(1410, 100, 11,
        this->tipText,
        sf::Color(255, 200, 80, 200), false); // warm gold, distinct from SP green
}

void StatsModule::renderText(sf::RenderTarget* target) {
    for (auto& it : this->text) {
        it.second->render(target);
    }
}

void StatsModule::updateText() {
    this->text["EXPTEXT"]->setString(buildExpString());
    this->text["SPTEXT"]->setString(buildSpString());
}

std::string StatsModule::toStringWithPrecision(double value, int precision) const {
    std::ostringstream out;
    out << std::fixed << std::setprecision(precision) << value;
    return out.str();
}

std::string StatsModule::buildExpString() const {
    return "EXP " + toStringWithPrecision(this->exp, 0)
        + "/" + toStringWithPrecision(this->expNext, 0)
        + "  LVL " + std::to_string(this->level);
}

std::string StatsModule::buildSpString() const {
    return "SP  " + std::to_string(this->sp);
}