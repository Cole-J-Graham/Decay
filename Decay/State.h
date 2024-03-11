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
	State(sf::RenderWindow* window, std::stack<State*>* states);
	~State();

	//Core State Functionality
	virtual void updateKeybinds() = 0;
	virtual void render(sf::RenderTarget* target = nullptr) = 0;
	virtual void update() = 0;
	virtual void updateMousePositions();

	const bool& getQuit() const;
	void checkForQuit();
	virtual void endState();

	std::stack<State*>* states;
	sf::RenderWindow* window;

	//Getters
	sf::Vector2f getMousePosView() { return this->mousePosView; };

	bool quit;

private:

	//Mouse Position
	sf::Vector2i mousePosScreen;
	sf::Vector2i mousePosWindow;
	sf::Vector2f mousePosView;
};

