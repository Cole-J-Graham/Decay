#ifndef MAINMENU_STATE_H
#define MAINMENU_STATE_H
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
	void updateKeybinds();
	void update();
	void render(sf::RenderTarget* target = nullptr);

	//Asset Functions
	void initButtons();
	void updateButtons();
	void renderButtons(sf::RenderTarget* target = nullptr);
		

private:

	//Button Assets
	sf::Font font;
	
	std::map<std::string, Button*> buttons;
};

#endif
