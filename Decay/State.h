#pragma once
#include<iostream>
#include<vector>
#include<stack>
#include<SFML/Window.hpp>
#include<SFML/Graphics.hpp>
#include<SFML/Graphics/Text.hpp>
#include<SFML/Audio.hpp>

class State
{
public:
	//Constructors and Destructors
	State();
	~State();

	//Core State Functionality
	virtual void updateKeybinds(const float& dt) = 0;
	virtual void render(sf::RenderTarget* target = nullptr) = 0;
	virtual void update(const float& dt) = 0;

	const bool& getQuit() const;
	void checkForQuit();
	void endState();


private:
	bool quit;
};

