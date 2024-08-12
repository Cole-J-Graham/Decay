#pragma once
#include <functional>
#include <random>
#include "Text.h"

class EntityMove
{
public:
	using Operation = std::function<void(float&, float&, int&)>;

	//Constructors and Destructors
	EntityMove(const std::string& moveMessage, Operation op,
		float& a, float& b, int coolDown);
	~EntityMove();

	//Core Functions
	void render(sf::RenderTarget* target);
	void renderMoveMessage(sf::RenderTarget* target) { this->message->render(target); }
	void update(const sf::Vector2f mousePos);
	void useMove();

	//Setters
	void show() { this->hidden = false; };
	void hide() { this->hidden = true; };

	struct Adder {
		void operator()(float& a, float& b, int&) const {
			a += b;
		}
	};

	struct Subtractor {
		void operator()(float& a, float& b, int&) const {
			a -= b;
		}
	};

private:

	Operation operation;

	float& a;
	float& b;
	int coolDown;
	bool hidden;

	std::string id;
	std::string moveMessage;
	std::unique_ptr<Text> message;
};

