#pragma once
#include"State.h"
class MainMenuState : State
{
public:
	MainMenuState();
	~MainMenuState();

	//State Functions
	void updateKeybinds(const float& dt);
	void update(const float& dt);
	void render(sf::RenderTarget* target = nullptr);

private:

};

