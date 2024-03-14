#pragma once
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

	//Rectangle Functions
	void initRects();
	void renderRects(sf::RenderTarget* target = nullptr);

	//Modifiers
	bool hidden;
	void setHidden() { this->hidden = true; };
	void setShown() { this->hidden = false; };

private:
	class Stat
	{
	public:
		//Constructors and Deconstructors
		Stat(std::string stat_name)
		{
			//Variables
			this->statCount = 0;

			//Initialization
			font.loadFromFile("Assets/Fonts/tickerbit font/Tickerbit-regular.otf");
			this->button = new Button(1402, 103, 25, 25, this->font, "+",
				sf::Color(70, 70, 70, 70), sf::Color(150, 150, 150, 255), sf::Color(20, 20, 20, 70), false);
			this->text = new Text(1428, 103, 16, stat_name,
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
		void statUp()
		{
			if (this->button->isPressed()) {
				this->statCount++;
			}
		}

		//Modifiers
		void setPosition(int x, int y)
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
	};

	int level;
	int sp;
	std::map<std::string, Stat*> stats;
	std::map<std::string, Rectangle*> rectangles;

};

