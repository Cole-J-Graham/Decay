#pragma once
#include"State.h"
class MainMenuState: public State
{
public:
	MainMenuState(sf::RenderWindow * window);
	~MainMenuState();

	//State Functions
	void updateKeybinds(const float& dt);
	void update(const float& dt);
	void render(sf::RenderTarget* target = nullptr);

	//Asset Functions
	void setAssets();
	void setAssetsPos();
		

private:

	//Button Assets
	sf::Font font;
	sf::RectangleShape start_button;
	sf::RectangleShape load_button;
	sf::RectangleShape quit_button;
	sf::Text start_text;
	sf::Text load_text;
	sf::Text quit_text;

	//Vectors
	std::vector<sf::RectangleShape> buttons{start_button, load_button, quit_button};
	std::vector<sf::Text> buttonsText{ start_text, load_text, quit_text };
};

