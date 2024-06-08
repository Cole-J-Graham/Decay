#include "StatsModule.h"
//Constructors and Deconstructors
StatsModule::StatsModule()
{
    //Variables
    this->level = 0;
    this->exp = 0;
    this->expNext = 100;
    this->sp = 5;
    
    this->currentInstance = false;
    this->lastClicked = false;

    //Initialization
    font.loadFromFile("Assets/Fonts/tickerbit font/Tickerbit-regular.otf");
    this->initRects();
    this->initText();
    this->initButtons();
}

StatsModule::~StatsModule()
{
    //Delete Stats
    auto is = this->stats.begin();
    for (is = this->stats.begin(); is != this->stats.end(); ++is) {
        delete is->second;
    }
    //Delete Rectangles
    auto ir = this->rectangles.begin();
    for (ir = this->rectangles.begin(); ir != this->rectangles.end(); ++ir) {
        delete ir->second;
    }
    //Delete Buttons
    auto ib = this->buttons.begin();
    for (ib = this->buttons.begin(); ib != this->buttons.end(); ++ib) {
        delete ib->second;
    }
}

//Core Functions
void StatsModule::update(const sf::Vector2f mousePos)
{
    this->updateStats(mousePos);
    this->updateButtons(mousePos);
    this->updateText();
}

void StatsModule::render(sf::RenderTarget* target)
{
    if (this->currentInstance) {
        this->renderRects(target);
        this->renderStats(target);
        this->renderButtons(target);
        this->renderText(target);
    }
    else {
        this->buttons[this->buttonId]->render(target);
    }
}

//Stat Functions
void StatsModule::updateStats(const sf::Vector2f mousePos)
{
    for (auto& it : this->stats) {
        it.second->update(mousePos);
        it.second->statUp(this->sp);
        this->buttonId = this->id;
    }
}

void StatsModule::createStat(std::string key, std::string stat_name)
{
	this->stats[key] = new Stat(stat_name);
}

void StatsModule::renderStats(sf::RenderTarget* target)
{
    int y = 110;
    for (auto& it : this->stats) {
        it.second->setPosition(1402, y += 25);
        it.second->render(target);
    }
}

//Stat Modifiers
void StatsModule::increaseLevel()
{
    if (this->buttons["LEVELUP"]->isPressed()) {
        if (this->exp >= this->expNext) {
            this->exp - this->expNext;
            this->level++;
            this->sp++;
        }
        else {
            std::cout << "Not enough exp for level up..." << "\n";
        }
    }
}

//Rectangle Functions
void StatsModule::initRects()
{
    this->rectangles["STATSMENU"] = new Rectangle(1400, 50, 300, 600, sf::Color::Transparent,
        sf::Color::White, 1.f, false);
}

void StatsModule::renderRects(sf::RenderTarget* target)
{
    for (auto& it : this->rectangles) {
        it.second->render(target);
    }
}

//Button Functions
void StatsModule::updateButtons(const sf::Vector2f mousePos)
{
    for (auto& it : this->buttons) {
        it.second->update(mousePos);
        it.second->setText(this->id);
    }

    if (this->buttons[this->buttonId]->isPressed() && this->currentInstance) {
        this->currentInstance = false;
        this->lastClicked = false;
    }
    else if (this->buttons[this->buttonId]->isPressed() && !this->currentInstance) {
        this->currentInstance = true;
        this->lastClicked = true;
    }

    this->increaseLevel();
}

void StatsModule::initButtons()
{
    this->buttons[this->buttonId] = new Button(1505, 50, 100, 25, 0.5f, this->font, this->id,
        sf::Color(70, 70, 70, 70), sf::Color(150, 150, 150, 255), sf::Color(20, 20, 20, 70), false);
    this->buttons["LEVELUP"] = new Button(1402, 53, 100, 25, 0.5f, this->font, "LEVEL++",
        sf::Color(70, 70, 70, 70), sf::Color(150, 150, 150, 255), sf::Color(20, 20, 20, 70), false);
}

void StatsModule::renderButtons(sf::RenderTarget* target)
{
    for (auto& it : this->buttons) {
        it.second->render(target);
    }
}

//Text Functions
void StatsModule::initText()
{
    this->text["LEVELTEXT"] = new Text(1504, 53, 16, std::to_string(this->exp) + "/" + std::to_string(this->expNext) + "              LVL: " + std::to_string(this->level) + "\n                         SP: " + std::to_string(this->sp),
        sf::Color::White, false);
}

void StatsModule::renderText(sf::RenderTarget* target)
{
    for (auto& it : this->text) {
        it.second->render(target);
    }
}

void StatsModule::updateText()
{
    this->text["LEVELTEXT"]->setString(std::to_string(this->exp) + "/" + std::to_string(this->expNext) + "              LVL: " + std::to_string(this->level) + "\n                         SP: " + std::to_string(this->sp));

}