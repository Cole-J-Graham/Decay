#ifndef GAME_H
#define GAME_H
#include"MainMenuState.h"
#include"AssetDatabase.h"

#include <memory>

class MusicPlayer;   // forward declaration — full type only needed in .cpp

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
	void initMusic();

	// Single persistent MusicPlayer for the whole application lifetime.
	// Wired into MusicManager once at boot via MusicManager_setPlayer().
	std::unique_ptr<MusicPlayer> musicPlayer;

};

#endif