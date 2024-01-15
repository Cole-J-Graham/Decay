#ifndef GAMESTATE_H
#define GAMESTATE_H

#include"State.h"
class GameState : public State
{
public:
	//Constructors and Destructors
	GameState();
	virtual ~GameState();

	//Functions
	void endState();

	//State Functions
	void updateKeybinds(const float& dt);
	void update(const float& dt);
	void render(sf::RenderTarget* target = nullptr);

private:


};

#endif