#ifndef GAMESTATE_H
#define GAMESTATE_H
#include"State.h"
#include"ForestState.h"
#include"CombatState.h"

#include"Button.h"
#include"Rectangle.h"
class GameState : public State
{
public:
	//Constructors and Destructors
	GameState(sf::RenderWindow* window, std::stack<State*>* states);
	virtual ~GameState();

	//Functions
	void endState();

	//State Functions
	void updateKeybinds();
	void update();
	void render(sf::RenderTarget* target = nullptr);

	//Asset Functions
	void initButtons();
	void updateButtons();
	void renderButtons(sf::RenderTarget* target = nullptr);

	void initRects();
	void renderRectangles(sf::RenderTarget* target = nullptr);

private:

	//Button Assets
	sf::Font font;
	std::map<std::string, Button*> buttons;
	std::map<std::string, Rectangle*> rectangles;

	//Bonfire Assets
	sf::RectangleShape border;
	sf::Texture bonfire_texture;
	sf::Sprite bonfire;

};

#endif