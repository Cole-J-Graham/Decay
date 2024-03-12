#pragma once
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
	void createStat(std::string key, int posX, int posY, std::string stat);

private:
	class Stat
	{
	public:
		//Constructors and Deconstructors
		Stat(int posX, int posY, std::string stat)
		{
			//Variables
			this->statCount = 0;
			this->posX = posX;
			this->posY = posY;

			//Initialization
			font.loadFromFile("Assets/Fonts/tickerbit font/Tickerbit-regular.otf");
			this->button = new Button(posX, posY, 25, 25, this->font, "+",
				sf::Color(70, 70, 70, 70), sf::Color(150, 150, 150, 255), sf::Color(20, 20, 20, 70), false);
			this->text = new Text(posX + 26, posY, 16, stat,
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

	private:
		//Variables
		int statCount;

		int posX;
		int posY;

		//Assets
		Button* button;
		Text* text;
		sf::Font font;
	};

	int level;
	int sp;
	std::map<std::string, Stat*> stats;

};

