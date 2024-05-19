#include"Button.h"
#include"Rectangle.h"
class Move {
public:
	Move(std::string key, std::string tipMessage, float width, float height, 
		float clicktime, sf::Font font, std::string text, sf::Color idleColor, 
		sf::Color hoverColor, sf::Color activeColor, bool hidden);
	~Move();

	//Core Functions
	void render(sf::RenderTarget* target);
	void update(const sf::Vector2f mousePos);

	//Rectangle Functions
	void initRects();
	void renderRects(sf::RenderTarget* target);

	//Modifiers
	void setPosition(float x, float y) { this->button->setPosition(x, y); }
	const bool isPressed();
	void show() { this->hidden = false; }
	void hide() { this->hidden = true; }
	const bool& isHidden() { return this->hidden; }

private:
	std::map<std::string, Rectangle*> rectangles;
	Button* button;
	std::string tipMessage;
	bool hidden;
};