#pragma once
#include<vector>
#include<iomanip>
#include<sstream>
#include<functional>
#include"Rectangle.h"
#include"Button.h"
#include"Text.h"

class StatsModule
{
public:
	//Constructors and Deconstructors
	StatsModule(const std::string& id, const std::string& tipText = "");
	~StatsModule();

	//Core Functions
	void update(const sf::Vector2f mousePos);
	void render(sf::RenderTarget* target);

	//Stat Functions
	void updateStats(const sf::Vector2f mousePos);

	// onStatUp: optional callback fired when a point is invested.
	// Receives the stat modifier amount so Character can sync hp, etc.
	// e.g. for VIT: character->getHp() += modifier
	void createStat(const std::string& key,
		const std::string& statName,
		const std::string& modifiedStatName,
		float& stat,
		float statModifier,
		std::function<void(float)> onStatUp = nullptr);

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
	int getLevel() const { return this->level; }

	//Setters
	void setButtonId(std::string& id) { this->buttonId = id; }

	// Live current/max HP display — called every frame from Character::updateText()
	void setHp(float hp, float hpMax);

	// Character blurb — set once during InitializeCharacters::initLore()
	void setTipText(const std::string& tip);

	// ------------------------------------------------------------------
	// Save/Load support
	// ------------------------------------------------------------------
	float getExp() const { return this->exp; }
	int getSp() const { return this->sp; }

	void setLevel(int level)
	{
		this->level = level;
		this->expNext = 100 + (level * level * 15);
		this->updateText();
	}
	void setExp(float exp) { this->exp = exp; this->updateText(); }
	void setSp(int sp) { this->sp = sp; this->updateText(); }
	float getExpNext() const { return this->expNext; }

	std::vector<std::string> getStatKeys() const;
	int  getStatCount(const std::string& key) const;

	// Restores invested point count AND re-applies the stat modifier
	// (count * modifier) to the underlying float so loaded saves reflect
	// the correct stat values. Does NOT fire the onStatUp callback since
	// Character stat floats are restored separately by SaveManager.
	void setStatCount(const std::string& key, int count);

private:
	class Stat
	{
	public:
		Stat(const std::string& statName,
			const std::string& modifiedStatName,
			float& stat,
			float statModifier,
			std::function<void(float)> onStatUp)
			: statName(statName)
			, stat(stat)
			, modifiedStatName(modifiedStatName)
			, statModifier(statModifier)
			, statCount(0)
			, onStatUp(std::move(onStatUp))
			, buttonWasPressed(false)
		{
			button = std::make_unique<Button>(0, 0, 22, 22, 0.5f, "+",
				sf::Color(80, 120, 80, 180), sf::Color(120, 200, 120, 255),
				sf::Color(40, 80, 40, 200), false);

			text = std::make_unique<Text>(0.f, 0.f, 14, buildStatLabel(),
				sf::Color(220, 220, 220, 255), false);

			statText = std::make_unique<Text>(0.f, 0.f, 13, buildDerivedLabel(),
				sf::Color(160, 220, 255, 255), false);
		}

		~Stat() = default;

		void update(const sf::Vector2f mousePos)
		{
			button->update(mousePos);
		}

		void render(sf::RenderTarget* target)
		{
			sf::RectangleShape divider(sf::Vector2f(260.f, 1.f));
			divider.setPosition(rowX, rowY - 3.f);
			divider.setFillColor(sf::Color(255, 255, 255, 25));
			target->draw(divider);

			button->render(target);
			text->render(target);
			statText->render(target);
		}

		// Edge-detected: fires at most once per press, not every frame held.
		void statUp(int& sp)
		{
			const bool pressed = button->isPressed();

			if (pressed && !buttonWasPressed)
			{
				if (sp > 0)
				{
					statCount++;
					this->stat += this->statModifier;
					text->setString(buildStatLabel());
					statText->setString(buildDerivedLabel());
					sp--;

					// Notify owner (e.g. Character) so it can sync hp, etc.
					if (this->onStatUp)
						this->onStatUp(this->statModifier);
				}
			}

			buttonWasPressed = pressed;
		}

		void setPosition(float xLeft, float y, float xRight)
		{
			rowX = xLeft;
			rowY = y;
			button->setPosition(xLeft, y);
			text->setPosition(xLeft + 28.f, y + 3.f);
			statText->setPosition(xRight, y + 3.f);
		}

		std::string buildDerivedLabel() const
		{
			std::ostringstream oss;
			oss << std::fixed << std::setprecision(1) << stat;
			return modifiedStatName + "  " + oss.str();
		}

		int getStatCount() const { return this->statCount; }

		// Restore count and re-apply modifier to underlying float.
		// Called by StatsModule::setStatCount during save load.
		void setStatCount(int count)
		{
			// Re-apply the difference so the underlying float ends up correct.
			// (SaveManager restores the float directly, so this is a no-op in
			// terms of the actual value — but it keeps statCount in sync.)
			this->statCount = count;
			text->setString(buildStatLabel());
			statText->setString(buildDerivedLabel());
		}

		float getStatModifier() const { return this->statModifier; }

	private:
		std::string buildStatLabel() const
		{
			return statName + "  " + std::to_string(statCount);
		}

		float rowX = 0.f, rowY = 0.f;

		int   statCount;
		float& stat;
		float statModifier;
		std::string statName;
		std::string modifiedStatName;
		std::string tipText;

		std::function<void(float)> onStatUp;  // notifies Character on point invest
		bool buttonWasPressed;                 // edge-detect: one fire per press

		std::unique_ptr<Button> button;
		std::unique_ptr<Text>   text;
		std::unique_ptr<Text>   statText;
	};

	int   level;
	int   sp;
	float exp;
	float expNext;

	bool currentInstance;
	bool lastClicked;

	std::string id;
	std::string buttonId;
	std::string tipText;

	std::map<std::string, Button*>              buttons;
	std::map<std::string, std::shared_ptr<Stat>> stats;
	std::map<std::string, std::unique_ptr<Rectangle>> rectangles;
	std::map<std::string, std::unique_ptr<Text>> text;
};