#pragma once
#include<vector>
#include<iomanip>
#include<sstream>
#include"Rectangle.h"
#include"Button.h"
#include"Text.h"

class StatsModule
{
public:
	//Constructors and Deconstructors
	StatsModule(const std::string& id);
	~StatsModule();

	//Core Functions
	void update(const sf::Vector2f mousePos);
	void render(sf::RenderTarget* target);

	//Stat Functions
	void updateStats(const sf::Vector2f mousePos);
	void createStat(const std::string& key, const std::string& statName,
		const std::string& modifiedStatName, float& stat, float statModifier);
	void renderStats(sf::RenderTarget* target);

	//Stat Modifiers
	void increaseLevel();
	void addExp(float amount);

	//Rectangle Functions
	void initRects();
	void renderRects(sf::RenderTarget* target = nullptr);

	//Button Functions
	void updateButtons(const sf::Vector2f mousePos);
	void initButtons();
	void renderButtons(sf::RenderTarget* target = nullptr);

	//Text Functions
	void initText();
	void renderText(sf::RenderTarget* target = nullptr);
	void updateText();
	std::string toStringWithPrecision(double value, int precision = 2) const;
	std::string buildExpString() const;
	std::string buildSpString() const;

	//Getters
	bool& getCurrentInstance() { return this->currentInstance; }
	bool& getLastClicked() { return this->lastClicked; }
	const std::string& getId() { return this->id; }
	std::string& getButtonId() { return this->buttonId; }
	std::map<std::string, Button*>& getButtons() { return this->buttons; };

	//Setters
	void setButtonId(std::string& id) { this->buttonId = id; }

private:
	class Stat
	{
	public:
		// Constructors and Destructors
		Stat(const std::string& statName, const std::string& modifiedStatName, float& stat, float statModifier)
			: statName(statName), stat(stat), modifiedStatName(modifiedStatName), statModifier(statModifier), statCount(0)
		{
			// Left side: [++] button + "STR  3" label
			button = std::make_unique<Button>(0, 0, 22, 22, 0.5f, "+",
				sf::Color(80, 120, 80, 180), sf::Color(120, 200, 120, 255), sf::Color(40, 80, 40, 200), false);

			// Stat name + invested count  (e.g. "STR   3")
			text = std::make_unique<Text>(0.f, 0.f, 14, buildStatLabel(),
				sf::Color(220, 220, 220, 255), false);

			// Right column: derived value  (e.g. "Max HP  125")
			statText = std::make_unique<Text>(0.f, 0.f, 13, buildDerivedLabel(),
				sf::Color(160, 220, 255, 255), false);

			// Thin divider line drawn manually in render()
		}

		~Stat() = default;

		// Core Functions
		void update(const sf::Vector2f mousePos)
		{
			button->update(mousePos);
		}

		void render(sf::RenderTarget* target)
		{
			// Horizontal rule above each row (subtle)
			sf::RectangleShape divider(sf::Vector2f(260.f, 1.f));
			divider.setPosition(rowX, rowY - 3.f);
			divider.setFillColor(sf::Color(255, 255, 255, 25));
			target->draw(divider);

			button->render(target);
			text->render(target);
			statText->render(target);
		}

		void statUp(int& sp)
		{
			if (button->isPressed()) {
				if (sp > 0) {
					statCount++;
					this->stat += this->statModifier;
					text->setString(buildStatLabel());
					statText->setString(buildDerivedLabel());
					sp--;
				}
			}
		}

		// Setters / layout
		// xLeft = left edge of panel, xRight = x of right column
		void setPosition(float xLeft, float y, float xRight)
		{
			rowX = xLeft;
			rowY = y;
			button->setPosition(xLeft, y);
			text->setPosition(xLeft + 28.f, y + 3.f);
			statText->setPosition(xRight, y + 3.f);
		}

		// Expose derived label for the summary section
		std::string buildDerivedLabel() const
		{
			std::ostringstream oss;
			oss << std::fixed << std::setprecision(1) << stat;
			return modifiedStatName + "  " + oss.str();
		}

	private:
		std::string buildStatLabel() const
		{
			return statName + "  " + std::to_string(statCount);
		}

		float rowX = 0.f, rowY = 0.f;

		int statCount;
		float& stat;
		float statModifier;
		std::string statName;
		std::string modifiedStatName;
		std::unique_ptr<Button> button;
		std::unique_ptr<Text> text;
		std::unique_ptr<Text> statText;
	};

	int level;
	int sp;
	float exp;
	float expNext;

	bool currentInstance;
	bool lastClicked;

	const std::string& id;
	std::string buttonId;

	std::map<std::string, Button*> buttons;
	std::map<std::string, std::shared_ptr<Stat>> stats;
	std::map<std::string, std::unique_ptr<Rectangle>> rectangles;
	std::map<std::string, std::unique_ptr<Text>> text;

};