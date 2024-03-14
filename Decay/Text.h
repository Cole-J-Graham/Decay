#pragma once
#include"Asset.h"
class Text
{
public:
	//Constructors and Destructors
	Text(float x, float y, int text_size, std::string text, sf::Color text_color, 
		bool hidden);
	~Text();

	//Text Functions
	void render(sf::RenderTarget* target);
	void setString(std::string text);

	//Modifiers
	void setPosition(int x, int y) { this->text.setPosition(x, y); };

	//Getters
	bool& getHidden() { return this->hidden; };

	//Setters
	bool& setHidden() { return this->hidden = true; };
	bool& setShown() { return this->hidden = false; };

private:
	//Text Variables
	sf::Text text;
	sf::Font font;
	sf::Color text_color;

	float x;
	float y;

	int text_size;
	bool hidden;

};

