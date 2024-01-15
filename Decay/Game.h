#ifndef GAME_H
#define GAME_H
#include"GameState.h"
#include"MainMenuState.h"

class Game
{
public:
	//Constructors and Destructors
	Game();
	virtual ~Game();
	void endApplication();

	//Update
	void update();
	void updateDt();
	void updateSFMLEvents();

	//Render
	void render();

	//Core
	void run();

	std::stack<State*> states;

private:
	//Variables
	sf::RenderWindow* window;
	sf::Event sfEvent;

	sf::Clock dtClock;
	float dt;

	//Initialization
	void initWindow();
	void initStates();

};

#endif