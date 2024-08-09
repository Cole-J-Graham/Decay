#pragma once
#include<vector>
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
	void createStat(const std::string& key, const std::string& stat_name,
		float& stat, float statModifier);
	void renderStats(sf::RenderTarget* target);

	//Stat Modifiers
	void increaseLevel();

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
		Stat(const std::string& stat_name, float& stat, float statModifier)
			: statName(stat_name), stat(stat), statModifier(statModifier), statCount(0)
		{
			//Initialization
			button = std::make_unique<Button>(1402, 110, 25, 25, 0.5f, "++",
				sf::Color(70, 70, 70, 70), sf::Color(150, 150, 150, 255), sf::Color(20, 20, 20, 70), false);
			text = std::make_unique<Text>(1428, 110, 16, stat_name + " " + std::to_string(statCount),
				sf::Color::White, false);
		}

		~Stat() = default;

		// Core Functions
		void update(const sf::Vector2f mousePos)
		{
			button->update(mousePos);
		}

		void render(sf::RenderTarget* target)
		{
			button->render(target);
			text->render(target);
		}

		void statUp(int& sp)
		{
			if (button->isPressed()) {
				if (sp > 0) {
					statCount++;
					this->stat += this->statModifier;
					text->setString(statName + " " + std::to_string(statCount));
					sp--;
				}
			}
		}

		// Modifiers
		void setPosition(float x, float y)
		{
			button->setPosition(x, y);
			text->setPosition(x + 26, y);
		}

	private:

		int statCount;
		float& stat;
		float statModifier;
		std::string statName;
		std::unique_ptr<Button> button;
		std::unique_ptr<Text> text;
	};

	int level;
	float exp;
	float expNext;
	int sp;
	bool currentInstance;
	bool lastClicked;

	const std::string& id;
	std::string buttonId;

	std::map<std::string, Button*> buttons;
	std::map<std::string, std::shared_ptr<Stat>> stats;
	std::map<std::string, std::unique_ptr<Rectangle>> rectangles;
	std::map<std::string, std::unique_ptr<Text>> text;

};

