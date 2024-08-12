#include "EntityMove.h"
//Constructors and Destructors
EntityMove::EntityMove(const std::string& moveMessage, Operation op,
	float& a, float& b, int coolDown) : operation(op), a(a), b(b), coolDown(coolDown)
{
	this->hidden = true;
	this->moveMessage = moveMessage;
	this->message = std::make_unique<Text>(355, 835, 16, moveMessage, sf::Color::White, true);

	srand(time(NULL));
}

EntityMove::~EntityMove()
{

}

//Core Functions
void EntityMove::render(sf::RenderTarget* target)
{
	if (!this->hidden) {
		this->message->render(target);
	}
}

void EntityMove::update(const sf::Vector2f mousePos)
{

}

void EntityMove::useMove()
{
	this->operation(a, b, this->coolDown);
	this->message->setShown();
	std::cout << "Entity Operation applied: a = " << a << ", b = " << b << std::endl;
}