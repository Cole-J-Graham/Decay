#ifndef TRAEVLSTATE_H
#define TRAVELSTATE_H
#include"State.h"

#include"Button.h"
#include"Rectangle.h"
class TravelState : public State
{
public:
	//Constructors and Destructors
	TravelState(sf::RenderWindow* window, std::stack<State*>* states);
	~TravelState();

	//State Functions
	void updateKeybinds(const float& dt);
	void update(const float& dt);
	void render(sf::RenderTarget* target = nullptr);

	//Asset Functions
	void initButtons();
	void renderButtons(sf::RenderTarget* target);
	void initRects();
	void renderRects(sf::RenderTarget* target);

private:

	//Assets
	std::map<std::string, Rectangle*> buttons;
	std::map<std::string, Rectangle*> rectangles;

};

#endif

