#pragma once
#include<stack>
#include<fstream>
#include<map>
#include"Button.h"
#include"Rectangle.h"
#include"EventModule.h"
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
	void updateMaps(const sf::Vector2f mousePos);
	void renderMaps(sf::RenderTarget* target);
	void createMapCore(int mapId, float scale, std::string mapInput,
		sf::Vector2f pos1, std::string in1, std::string str1, sf::Vector2f pos2, std::string in2,
		std::string str2, sf::Vector2f pos3, std::string in3, std::string str3, sf::Vector2f pos4,
		std::string in4, std::string str4, sf::Vector2f pos5, std::string in5, std::string str5);
	void detectNewArea(std::string in1, std::string in2,
		std::string in3, std::string in4, std::string in5);
	void move();


	//Rectangle Functions
	void initRects();
	void renderRects(sf::RenderTarget* target);

	//Button Functions
	void initButtons();
	void updateButtons(const sf::Vector2f mousePos);
	void renderButtons(sf::RenderTarget* target);

	//Asset Functions
	void loadMap(std::string file_input);

	//Getters
	int& getMapMaxSize() { return this->mapMaxSize; };
	bool& getHidden() { return this->hidden; };
	int& getCurrentMapId() { return this->currentMapId; };

	class MapCore {
	public:
		//Constructors and Deconstructors
		MapCore(float scale, std::string mapInput, 
			sf::Vector2f pos1, std::string in1, std::string str1, sf::Vector2f pos2, std::string in2,
			std::string str2, sf::Vector2f pos3, std::string in3, std::string str3, sf::Vector2f pos4,
			std::string in4, std::string str4, sf::Vector2f pos5, std::string in5, std::string str5) {
			//Init Map
			font.loadFromFile("Assets/Fonts/tickerbit font/Tickerbit-regular.otf");
			this->mapInput = mapInput;
			this->mapTexture.loadFromFile(this->mapInput);
			this->map.setTexture(this->mapTexture);
			this->map.setPosition(100, 100);
			this->map.setScale(scale, scale);
			this->hidden = true;

			this->mapPositionInputs.push_back(in1);
			this->mapPositionInputs.push_back(in2);
			this->mapPositionInputs.push_back(in3);
			this->mapPositionInputs.push_back(in4);
			this->mapPositionInputs.push_back(in5);

			//Init Button Positions
			this->buttonPosFirst = pos1;
			this->buttonPosSecond = pos2;
			this->buttonPosThird = pos3;
			this->buttonPosFourth = pos4;
			this->buttonPosFifth = pos5;
			//Init Button Names
			this->buttonNameFirst = str1;
			this->buttonNameSecond = str2;
			this->buttonNameThird = str3;
			this->buttonNameFourth = str4;
			this->buttonNameFifth = str5;

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

		void loadMap(std::string& input) 
		{ 
			this->mapContainer.push_back(input);
		};

		void clearMap()
		{
			this->mapContainer.clear();
		};

		//Modifiers
		const bool& isHidden() { return this->hidden; };
		bool& setHidden() { return this->hidden = true; };
		bool& setShown() { return this->hidden = false; };
		std::vector<std::string>& getMapContainer() { return this->mapContainer; };
		std::vector<std::string>& getMapPositionsContainer() { return this->mapPositionInputs; };
		std::map<std::string, Button*>& getButtons() { return this->buttons; };


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

		std::vector<std::string> mapPositionInputs;

		sf::Texture mapTexture;
		std::string mapInput;
		sf::Font font;
		sf::Sprite map;
		std::map<std::string, Button*> buttons;
		std::vector<std::string> mapContainer;

		bool hidden;

	};

	std::map<int, MapCore*> maps;

	//Modifier Functions
	void setMapFrame(int& frame) {
		this->texture.loadFromFile(this->maps[currentMapId]->getMapContainer()[frame]);
		this->mapSprite.setTexture(this->texture);
	};

private:

	EventModule* event;

	float x;
	float y;
	bool hidden;
	int map;
	int mapFrame;
	int currentMapId;

	sf::Clock clock;
	sf::Time time;
	float move_time;
	int mapMaxSize;

	sf::Sprite mapSprite;
	sf::Texture texture;
	std::ifstream ifs;
	std::string line;

	sf::Font font;
	std::map<std::string, Button*> buttons;
	std::map<std::string, Rectangle*> rectangles;

};

