#pragma once
#include"State.h"
#include"Button.h"
class MainMenuState: public State
{
public:
	//Constructors and Destructors
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
	
	Button* gamestate_btn;
};

