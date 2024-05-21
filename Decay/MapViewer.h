#pragma once
#include"Button.h"
#include"Rectangle.h"
class MapViewer
{
public:
	//Constructor and Deconstructor
	MapViewer();
	~MapViewer();

	//Core Functions
	void update(const sf::Vector2f mousePos);
	void render(sf::RenderTarget* target);

	//Map Functions
	void initMapCore();
	void updateMaps(const sf::Vector2f mousePos);
	void renderMaps(sf::RenderTarget* target);

	//Rectangle Functions
	void initRects();
	void renderRects(sf::RenderTarget* target);

	//Button Functions
	void initButtons();
	void updateButtons(const sf::Vector2f mousePos);
	void renderButtons(sf::RenderTarget* target);

private:
	class MapCore {
	public:
		//Constructors and Deconstructors
		MapCore(float scale, std::string mapInput, sf::Vector2f posFirst, std::string strFirst, sf::Vector2f posSecond,
			std::string strSecond, sf::Vector2f posThird, std::string strThird, sf::Vector2f posFourth,
			std::string strFourth, sf::Vector2f posFifth, std::string strFifth) {
			//Init Map
			font.loadFromFile("Assets/Fonts/tickerbit font/Tickerbit-regular.otf");
			this->mapInput = mapInput;
			this->mapTexture.loadFromFile(this->mapInput);
			this->map.setTexture(this->mapTexture);
			this->map.setPosition(100, 100);
			this->map.setScale(scale, scale);
			this->hidden = true;

			//Init Button Positions
			this->buttonPosFirst = posFirst;
			this->buttonPosSecond = posSecond;
			this->buttonPosThird = posThird;
			this->buttonPosFourth = posFourth;
			this->buttonPosFifth = posFifth;
			//Init Button Names
			this->buttonNameFirst = strFirst;
			this->buttonNameSecond = strSecond;
			this->buttonNameThird = strThird;
			this->buttonNameFourth = strFourth;
			this->buttonNameFifth = strFifth;

			//Init Functions
			this->initButtons();
		}

		~MapCore() {

		}

		//Core Functions
		void update(const sf::Vector2f mousePos) {
			if (!this->hidden) {
				this->updateButtons(mousePos);
			}
		}

		void render(sf::RenderTarget* target) {
			if (!this->hidden) {
				target->draw(this->map);
				this->renderButtons(target);
			}
		}

		//Button Functions
		void initButtons()
		{
			this->buttons["POS1"] = new Button(this->buttonPosFirst, 100, 25, 0.5f, this->font, this->buttonNameFirst,
				sf::Color(70, 70, 70, 70), sf::Color(150, 150, 150, 255), sf::Color(20, 20, 20, 70), false);
			this->buttons["POS2"] = new Button(this->buttonPosSecond, 100, 25, 0.5f, this->font, this->buttonNameSecond,
				sf::Color(70, 70, 70, 70), sf::Color(150, 150, 150, 255), sf::Color(20, 20, 20, 70), false);
			this->buttons["POS3"] = new Button(this->buttonPosThird, 100, 25, 0.5f, this->font, this->buttonNameThird,
				sf::Color(70, 70, 70, 70), sf::Color(150, 150, 150, 255), sf::Color(20, 20, 20, 70), false);
			this->buttons["POS4"] = new Button(this->buttonPosFourth, 100, 25, 0.5f, this->font, this->buttonNameFourth,
				sf::Color(70, 70, 70, 70), sf::Color(150, 150, 150, 255), sf::Color(20, 20, 20, 70), false);
			this->buttons["POS5"] = new Button(this->buttonPosFifth, 100, 25, 0.5f, this->font, this->buttonNameFifth,
				sf::Color(70, 70, 70, 70), sf::Color(150, 150, 150, 255), sf::Color(20, 20, 20, 70), false);
		}

		void updateButtons(const sf::Vector2f mousePos)
		{
			for (auto& it : this->buttons) {
				it.second->update(mousePos);
			}
		}

		void renderButtons(sf::RenderTarget* target)
		{
			for (auto& it : this->buttons) {
				it.second->render(target);
			}
		}

		//Modifiers
		const bool& isHidden() { return this->hidden; };
		bool& setHidden() { return this->hidden = true; }
		bool& setShown() { return this->hidden = false; }

	private:
		sf::Vector2f buttonPosFirst;
		sf::Vector2f buttonPosSecond;
		sf::Vector2f buttonPosThird;
		sf::Vector2f buttonPosFourth;
		sf::Vector2f buttonPosFifth;

		std::string buttonNameFirst;
		std::string buttonNameSecond;
		std::string buttonNameThird;
		std::string buttonNameFourth;
		std::string buttonNameFifth;

		sf::Texture mapTexture;
		std::string mapInput;
		sf::Font font;
		sf::Sprite map;
		std::map<std::string, Button*> buttons;

		bool hidden;

	};

	float x;
	float y;
	bool hidden;
	int map;

	sf::Font font;
	std::map<std::string, MapCore*> maps;
	std::map<std::string, Button*> buttons;
	std::map<std::string, Rectangle*> rectangles;
};

