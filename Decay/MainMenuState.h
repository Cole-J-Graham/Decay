#pragma once
#include"GameState.h"
#include"Button.h"
class MainMenuState: public State
{
public:
	//Constructors and Destructors
	MainMenuState(sf::RenderWindow * window, std::stack<State*>* states);
	~MainMenuState();

	//State Functions
	void endState();
	void updateKeybinds(const float& dt);
	void update(const float& dt);
	void render(sf::RenderTarget* target = nullptr);

	//Asset Functions
	void initButtons();
	void updateButtons();
	void renderButtons(sf::RenderTarget* target = nullptr);
	void setAssets();
		

private:

	//Button Assets
	sf::Font font;
	
	std::map<std::string, Button*> buttons;
};

