#pragma once
#include<vector>
#include"Rectangle.h"
#include"Button.h"
#include"Text.h"
class StatsModule
{
public:
	//Constructors and Deconstructors
	StatsModule();
	~StatsModule();

	//Core Functions
	void update(const sf::Vector2f mousePos);
	void render(sf::RenderTarget* target);

	//Stat Functions
	void updateStats(const sf::Vector2f mousePos);
	void createStat(std::string key, std::string stat);
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
	std::map<std::string, Button*>& getButtons() { return this->buttons; };

private:
	class Stat
	{
	public:
		//Constructors and Deconstructors
		Stat(std::string stat_name)
		{
			//Variables
			this->statCount = 0;
			this->statName = stat_name;

			//Initialization
			font.loadFromFile("Assets/Fonts/tickerbit font/Tickerbit-regular.otf");
			this->button = new Button(1402, 110, 25, 25, 0.5, this->font, "  +",
				sf::Color(70, 70, 70, 70), sf::Color(150, 150, 150, 255), sf::Color(20, 20, 20, 70), false);
			this->text = new Text(1428, 110, 16, stat_name + " " + std::to_string(this->statCount),
				sf::Color::White, false);
		}
		~Stat()
		{
			delete this->button;
			delete this->text;
		}

		//Core Functions
		void update(const sf::Vector2f mousePos)
		{
			this->button->update(mousePos);
		}
		void render(sf::RenderTarget* target)
		{
			this->button->render(target);
			this->text->render(target);
		}
		void statUp(int& sp)
		{
			if (this->button->isPressed()) {
				if (sp > 0) {
					this->statCount++;
					this->text->setString(this->statName + " " + std::to_string(this->statCount));
					sp--;
				}
			}
		}

		//Modifiers
		void setPosition(float x, float y)
		{
			this->button->setPosition(x, y);
			this->text->setPosition(x + 26, y);
		}

	private:
		//Variables
		int statCount;

		//Assets
		Button* button;
		Text* text;
		sf::Font font;
		std::string statName;

	};

	int level;
	int exp;
	int expNext;
	int sp;
	bool currentInstance;

	sf::Font font;
	std::map<std::string, Stat*> stats;
	std::map<std::string, Rectangle*> rectangles;
	std::map<std::string, Text*> text;
	std::map<std::string, Button*> buttons;

};

